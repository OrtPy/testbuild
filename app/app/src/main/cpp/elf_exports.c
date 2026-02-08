#include "elf_exports.h"

#include <elf.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static int read_all(const char *path, uint8_t **out_buf, size_t *out_size) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return 0;
    struct stat st;
    if (fstat(fd, &st) != 0) { close(fd); return 0; }
    size_t size = (size_t)st.st_size;
    uint8_t *buf = (uint8_t *)malloc(size);
    if (!buf) { close(fd); return 0; }
    size_t off = 0;
    while (off < size) {
        ssize_t r = read(fd, buf + off, size - off);
        if (r <= 0) { free(buf); close(fd); return 0; }
        off += (size_t)r;
    }
    close(fd);
    *out_buf = buf;
    *out_size = size;
    return 1;
}

static int vaddr_to_offset(Elf32_Addr vaddr, const Elf32_Phdr *phdrs, int phnum, Elf32_Off *out_off) {
    for (int i = 0; i < phnum; i++) {
        const Elf32_Phdr *p = &phdrs[i];
        if (p->p_type != PT_LOAD) continue;
        Elf32_Addr start = p->p_vaddr;
        Elf32_Addr end = p->p_vaddr + p->p_memsz;
        if (vaddr >= start && vaddr < end) {
            *out_off = p->p_offset + (vaddr - start);
            return 1;
        }
    }
    return 0;
}

void free_string_list(char **names, int count) {
    if (!names) return;
    for (int i = 0; i < count; i++) {
        free(names[i]);
    }
    free(names);
}

int list_exported_function_names(const char *path, const char *filter, char ***out_names, int *out_count) {
    *out_names = NULL;
    *out_count = 0;

    uint8_t *buf = NULL;
    size_t size = 0;
    if (!read_all(path, &buf, &size)) return 0;

    if (size < sizeof(Elf32_Ehdr)) { free(buf); return 0; }
    const Elf32_Ehdr *eh = (const Elf32_Ehdr *)buf;
    if (!(eh->e_ident[EI_MAG0] == ELFMAG0 && eh->e_ident[EI_MAG1] == ELFMAG1 && eh->e_ident[EI_MAG2] == ELFMAG2 && eh->e_ident[EI_MAG3] == ELFMAG3)) {
        free(buf); return 0;
    }
    if (eh->e_ident[EI_CLASS] != ELFCLASS32) { free(buf); return 0; }
    if (eh->e_phoff == 0 || eh->e_phnum == 0) { free(buf); return 0; }
    if ((size_t)eh->e_phoff + (size_t)eh->e_phnum * sizeof(Elf32_Phdr) > size) { free(buf); return 0; }

    const Elf32_Phdr *phdrs = (const Elf32_Phdr *)(buf + eh->e_phoff);

    // Find PT_DYNAMIC
    const Elf32_Phdr *dynph = NULL;
    for (int i = 0; i < eh->e_phnum; i++) {
        if (phdrs[i].p_type == PT_DYNAMIC) { dynph = &phdrs[i]; break; }
    }
    if (!dynph) { free(buf); return 0; }

    // Read dynamic entries
    Elf32_Off dyn_off = dynph->p_offset;
    if ((size_t)dyn_off + dynph->p_filesz > size) { free(buf); return 0; }

    const Elf32_Dyn *dyn = (const Elf32_Dyn *)(buf + dyn_off);
    size_t dyn_count = dynph->p_filesz / sizeof(Elf32_Dyn);

    Elf32_Addr symtab_va = 0;
    Elf32_Addr strtab_va = 0;
    Elf32_Addr hash_va = 0;

    for (size_t i = 0; i < dyn_count; i++) {
        if (dyn[i].d_tag == DT_NULL) break;
        if (dyn[i].d_tag == DT_SYMTAB) symtab_va = (Elf32_Addr)dyn[i].d_un.d_ptr;
        else if (dyn[i].d_tag == DT_STRTAB) strtab_va = (Elf32_Addr)dyn[i].d_un.d_ptr;
        else if (dyn[i].d_tag == DT_HASH) hash_va = (Elf32_Addr)dyn[i].d_un.d_ptr;
    }

    if (!symtab_va || !strtab_va || !hash_va) { free(buf); return 0; }

    Elf32_Off symtab_off = 0, strtab_off = 0, hash_off = 0;
    if (!vaddr_to_offset(symtab_va, phdrs, eh->e_phnum, &symtab_off)) { free(buf); return 0; }
    if (!vaddr_to_offset(strtab_va, phdrs, eh->e_phnum, &strtab_off)) { free(buf); return 0; }
    if (!vaddr_to_offset(hash_va, phdrs, eh->e_phnum, &hash_off)) { free(buf); return 0; }

    if ((size_t)hash_off + 8 > size) { free(buf); return 0; }
    const uint32_t *hashtab = (const uint32_t *)(buf + hash_off);
    uint32_t nbucket = hashtab[0];
    uint32_t nchain = hashtab[1];
    (void)nbucket;

    size_t symtab_bytes = (size_t)nchain * sizeof(Elf32_Sym);
    if ((size_t)symtab_off + symtab_bytes > size) { free(buf); return 0; }

    const Elf32_Sym *syms = (const Elf32_Sym *)(buf + symtab_off);
    const char *strs = (const char *)(buf + strtab_off);
    // strtab length is not explicitly known here; we assume names are NUL terminated within file bounds.

    // Collect names
    int cap = 256;
    int count = 0;
    char **names = (char **)calloc((size_t)cap, sizeof(char *));
    if (!names) { free(buf); return 0; }

    for (uint32_t i = 0; i < nchain; i++) {
        const Elf32_Sym *s = &syms[i];
        if (s->st_name == 0) continue;
        if (s->st_shndx == SHN_UNDEF) continue;

        unsigned type = ELF32_ST_TYPE(s->st_info);
        unsigned bind = ELF32_ST_BIND(s->st_info);
        if (type != STT_FUNC) continue;
        if (!(bind == STB_GLOBAL || bind == STB_WEAK)) continue;

        const char *name = strs + s->st_name;
        // basic bounds: ensure within file
        uintptr_t name_off = (uintptr_t)((const uint8_t *)name - buf);
        if (name_off >= size) continue;
        // ensure NUL termination within file
        size_t maxlen = size - name_off;
        size_t len = strnlen(name, maxlen);
        if (len == 0 || len == maxlen) continue;

        if (filter && !strstr(name, filter)) continue;

        if (count >= cap) {
            cap *= 2;
            char **tmp = (char **)realloc(names, (size_t)cap * sizeof(char *));
            if (!tmp) { free_string_list(names, count); free(buf); return 0; }
            names = tmp;
        }
        names[count] = (char *)malloc(len + 1);
        if (!names[count]) { free_string_list(names, count); free(buf); return 0; }
        memcpy(names[count], name, len + 1);
        count++;
    }

    free(buf);
    *out_names = names;
    *out_count = count;
    return 1;
}
