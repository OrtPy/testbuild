#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "ef2/platform.h"
#include "ef2/gles.h"

// A small set of dynsym symbols are actually used by the original callers.
// Provide real forwarding wrappers for those to keep ABI behavior close to the
// stock library while keeping the rest as stubs.
#include "ef2/curve.h"
#include "ef2/program.h"
#include "ef2/timeutil.h"
#include "ef2/event.h"
#include "ef2/renderer.h"
#include "ef2/rendererdata.h"

#if defined(__arm__) && !defined(__aarch64__)

/*
 * --- section boundary symbols (match original dynsym) ---
 *
 * The original Sony liblwplocal.so exports these absolute section boundary
 * symbols in .dynsym:
 *   __bss_start, _edata, _end
 *
 * We define their values via the linker script (src/compat/section_boundary_syms.ld).
 * The declarations below exist so our export-list checker can verify we still
 * provide the expected names (and so IDEs/compilers know these are intentional).
 */
extern char __bss_start __asm__("__bss_start");
extern char _edata     __asm__("_edata");
extern char _end       __asm__("_end");


/* Auto-generated. See tools/symbols/gen_compat_exports_c.py */

#define EF2_COMPAT_EXPORT __attribute__((visibility("default"), used))
#define EF2_COMPAT_WEAK_EXPORT __attribute__((visibility("default"), used, weak))

static inline uintptr_t ef2_compat_ret0(void) {
  return 0;
}


// ---------------------------------------------------------------------------
// buffer ABI (IDA decomp, 32-bit): sizeof(buffer)==0x20
//   target : *(u32*)(this + 0x18)
//   id     : *(u32*)(this + 0x1C) (initialized to -1 then glGenBuffers fills)

typedef struct ef2_buffer_abi {
  uint8_t raw[0x20];
} ef2_buffer_abi;

#define EF2_BUF_TARGET_OFF 0x18
#define EF2_BUF_ID_OFF     0x1C

#define EF2_BUF_CFG_PTR_OFF 0x00
#define EF2_BUF_CFG_LEN_OFF 0x04
#define EF2_BUF_CFG_CAP_OFF 0x08

static inline void*** ef2_buf_cfg_ptr_ptr(ef2_buffer_abi* b) {
  return (void***)(void*)(b->raw + EF2_BUF_CFG_PTR_OFF);
}
static inline uint32_t* ef2_buf_cfg_len_ptr(ef2_buffer_abi* b) {
  return (uint32_t*)(void*)(b->raw + EF2_BUF_CFG_LEN_OFF);
}
static inline uint32_t* ef2_buf_cfg_cap_ptr(ef2_buffer_abi* b) {
  return (uint32_t*)(void*)(b->raw + EF2_BUF_CFG_CAP_OFF);
}

/* Minimal bufferconfig ABI used by buffer::touch / bufferconfig::set
   (derived from 95KB liblwplocal.so disasm):
     0x00: buffer*
     0x04: int
     0x08: int
     0x0C: u8 touched
*/
typedef struct ef2_bufferconfig_abi {
  void*    owner_buf;
  int32_t  a;
  int32_t  b;
  uint8_t  touched;
  uint8_t  _pad[3];
} ef2_bufferconfig_abi;

static inline __attribute__((always_inline)) void ef2_buffer_cfgvec_add(ef2_buffer_abi* b, void* cfg) {
  if (!b || !cfg) return;
  void** arr = *ef2_buf_cfg_ptr_ptr(b);
  uint32_t len = *ef2_buf_cfg_len_ptr(b);
  uint32_t cap = *ef2_buf_cfg_cap_ptr(b);

  // de-dup (linear; typical config count is small)
  {
    uint32_t i;
    for (i = 0; i < len; i++) {
      if (arr && arr[i] == cfg) return;
    }
  }

  if (len >= cap) {
    uint32_t new_cap = cap ? (cap * 2u) : 8u;
    void** new_arr = (void**)realloc(arr, (size_t)new_cap * sizeof(void*));
    if (!new_arr) {
      ef2_log_print(6 /* ERROR */, "EF2", "buffer::addconfig realloc failed (cap=%u->%u)", cap, new_cap);
      return;
    }
    arr = new_arr;
    cap = new_cap;
    *ef2_buf_cfg_ptr_ptr(b) = arr;
    *ef2_buf_cfg_cap_ptr(b) = cap;
  }

  arr[len++] = cfg;
  *ef2_buf_cfg_len_ptr(b) = len;
  // keep count in the original slot for compatibility (buffer+0x14)
  *(uint32_t*)(void*)(b->raw + 0x14) = len;
}

static inline __attribute__((always_inline)) void ef2_buffer_cfgvec_touch_cleanup(ef2_buffer_abi* b) {
  if (!b) return;
  void** arr = *ef2_buf_cfg_ptr_ptr(b);
  uint32_t len = *ef2_buf_cfg_len_ptr(b);

  uint32_t i = 0;
  while (i < len) {
    ef2_bufferconfig_abi* cfg = (ef2_bufferconfig_abi*)arr[i];
    if (!cfg || cfg->owner_buf != (void*)b) {
      // remove (swap with last)
      if (len > 1 && i != (len - 1)) arr[i] = arr[len - 1];
      len--;
      continue;
    }
    cfg->touched = 1;
    i++;
  }

  *ef2_buf_cfg_len_ptr(b) = len;
  *(uint32_t*)(void*)(b->raw + 0x14) = len;

  if (len == 0 && arr) {
    free(arr);
    *ef2_buf_cfg_ptr_ptr(b) = NULL;
    *ef2_buf_cfg_cap_ptr(b) = 0;
  }
}

static inline __attribute__((always_inline)) void ef2_varray_abi_ctor(void* self) {
  if (!self) return;
  uint8_t* p = (uint8_t*)self;
  memset(p + 8, 0, 0x10);
  *(uint32_t*)(void*)(p + 0x18) = 0;
  uint32_t base = (uint32_t)(uintptr_t)(p + 8);
  *(uint32_t*)(void*)(p + 0x10) = base;
  *(uint32_t*)(void*)(p + 0x14) = base;
}


static inline uint32_t* ef2_buf_target_ptr(ef2_buffer_abi* b) {
  return (uint32_t*)(void*)(b->raw + EF2_BUF_TARGET_OFF);
}

static inline uint32_t* ef2_buf_id_ptr(ef2_buffer_abi* b) {
  return (uint32_t*)(void*)(b->raw + EF2_BUF_ID_OFF);
}

static inline __attribute__((always_inline)) void ef2_buffer_abi_ctor(ef2_buffer_abi* self, uint32_t target, int32_t id_or_alloc) {
  if (!self) return;
  memset(self->raw, 0, sizeof(self->raw));
  *ef2_buf_target_ptr(self) = target;
  *ef2_buf_id_ptr(self) = (uint32_t)id_or_alloc;
  if ((int32_t)*ef2_buf_id_ptr(self) == -1) {
    glGenBuffers(1, (GLuint*)ef2_buf_id_ptr(self));
  }
}

static inline __attribute__((always_inline)) void ef2_buffer_abi_dtor(ef2_buffer_abi* self) {
  if (!self) return;

  // free our lightweight config vector if used
  void** arr = *ef2_buf_cfg_ptr_ptr(self);
  if (arr) {
    free(arr);
    *ef2_buf_cfg_ptr_ptr(self) = NULL;
    *ef2_buf_cfg_len_ptr(self) = 0;
    *ef2_buf_cfg_cap_ptr(self) = 0;
    *(uint32_t*)(void*)(self->raw + 0x14) = 0;
  }

  uint32_t id = *ef2_buf_id_ptr(self);
  if (id != 0 && (int32_t)id != -1) {
    GLuint gid = (GLuint)id;
    glDeleteBuffers(1, &gid);
  }
}

static inline __attribute__((always_inline)) void ef2_buffer_abi_set(ef2_buffer_abi* self, uint32_t size, const void* data, uint32_t usage) {
  if (!self) return;
  glBindBuffer((GLenum)*ef2_buf_target_ptr(self), (GLuint)*ef2_buf_id_ptr(self));
  glBufferData((GLenum)*ef2_buf_target_ptr(self), (ptrdiff_t)size, data, (GLenum)usage);
  // 95KB ref: buffer::set calls buffer::touch afterwards.
  ef2_buffer_cfgvec_touch_cleanup(self);
}

static inline __attribute__((always_inline)) void ef2_buffer_abi_subset(ef2_buffer_abi* self, uint32_t offset, uint32_t size, const void* data) {
  if (!self) return;
  glBindBuffer((GLenum)*ef2_buf_target_ptr(self), (GLuint)*ef2_buf_id_ptr(self));
  glBufferSubData((GLenum)*ef2_buf_target_ptr(self), (ptrdiff_t)offset, (ptrdiff_t)size, data);
  // 95KB ref: buffer::subset calls buffer::touch afterwards.
  ef2_buffer_cfgvec_touch_cleanup(self);
}

/* ---- OBJECT symbols ---- */
EF2_COMPAT_EXPORT uintptr_t ef2_compat_obj_0001 __asm__("_ZN11framebuffer7fbstackE");
EF2_COMPAT_EXPORT uintptr_t ef2_compat_obj_0002 __asm__("_ZN7program11attribindexE");
EF2_COMPAT_EXPORT uintptr_t ef2_compat_obj_0003 __asm__("_ZN7program5boundE");
EF2_COMPAT_EXPORT uintptr_t ef2_compat_obj_0004 __asm__("_ZN7program7attribsE");
EF2_COMPAT_EXPORT uintptr_t ef2_compat_obj_0005 __asm__("_ZN7program8uniformsE");

// NOTE:
// lodepng.cpp (20131115) defines the following OBJECT symbols with real content:
//   _ZTV12LodePNGState
//   _ZTVN7lodepng5StateE
//   lodepng_default_compress_settings
//   lodepng_default_decompress_settings
// Do NOT provide dummy definitions here (would change .rodata/.rel.* and prevent perfect match).

/* ---- FUNC symbols ---- */
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0016(void) __asm__("_Z13lodepng_crc32PKhj");
uintptr_t ef2_compat_fn_0016(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0017(void) __asm__("_Z14lodepng_decodePPhPjS1_P12LodePNGStatePKhj");
uintptr_t ef2_compat_fn_0017(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0018(void) __asm__("_Z14lodepng_encodePPhPjPKhjjP12LodePNGState");
uintptr_t ef2_compat_fn_0018(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0019(void) __asm__("_Z15lodepng_convertPhPKhP16LodePNGColorModePKS2_jjj");
uintptr_t ef2_compat_fn_0019(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0020(void) __asm__("_Z15lodepng_deflatePPhPjPKhjPK23LodePNGCompressSettings");
uintptr_t ef2_compat_fn_0020(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0021(void) __asm__("_Z15lodepng_get_bppPK16LodePNGColorMode");
uintptr_t ef2_compat_fn_0021(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0022(void) __asm__("_Z15lodepng_inflatePPhPjPKhjPK25LodePNGDecompressSettings");
uintptr_t ef2_compat_fn_0022(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0023(void) __asm__("_Z15lodepng_inspectPjS_P12LodePNGStatePKhj");
uintptr_t ef2_compat_fn_0023(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0024(void) __asm__("_Z16lodepng_add_textP11LodePNGInfoPKcS2_");
uintptr_t ef2_compat_fn_0024(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0025(void) __asm__("_Z16lodepng_decode24PPhPjS1_PKhj");
uintptr_t ef2_compat_fn_0025(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0026(void) __asm__("_Z16lodepng_decode32PPhPjS1_PKhj");
uintptr_t ef2_compat_fn_0026(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0027(void) __asm__("_Z16lodepng_encode24PPhPjPKhjj");
uintptr_t ef2_compat_fn_0027(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0028(void) __asm__("_Z16lodepng_encode32PPhPjPKhjj");
uintptr_t ef2_compat_fn_0028(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0029(void) __asm__("_Z17lodepng_add_itextP11LodePNGInfoPKcS2_S2_S2_");
uintptr_t ef2_compat_fn_0029(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0030(void) __asm__("_Z17lodepng_info_copyP11LodePNGInfoPKS_");
uintptr_t ef2_compat_fn_0030(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0031(void) __asm__("_Z17lodepng_info_initP11LodePNGInfo");
uintptr_t ef2_compat_fn_0031(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0032(void) __asm__("_Z17lodepng_info_swapP11LodePNGInfoS0_");
uintptr_t ef2_compat_fn_0032(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0033(void) __asm__("_Z17lodepng_load_filePPhPjPKc");
uintptr_t ef2_compat_fn_0033(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0034(void) __asm__("_Z17lodepng_save_filePKhjPKc");
uintptr_t ef2_compat_fn_0034(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0035(void) __asm__("_Z18lodepng_chunk_dataPh");
uintptr_t ef2_compat_fn_0035(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0036(void) __asm__("_Z18lodepng_chunk_nextPh");
uintptr_t ef2_compat_fn_0036(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0037(void) __asm__("_Z18lodepng_chunk_typePcPKh");
uintptr_t ef2_compat_fn_0037(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0038(void) __asm__("_Z18lodepng_clear_textP11LodePNGInfo");
uintptr_t ef2_compat_fn_0038(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0039(void) __asm__("_Z18lodepng_error_textj");
uintptr_t ef2_compat_fn_0039(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0040(void) __asm__("_Z18lodepng_state_copyP12LodePNGStatePKS_");
uintptr_t ef2_compat_fn_0040(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0041(void) __asm__("_Z18lodepng_state_initP12LodePNGState");
uintptr_t ef2_compat_fn_0041(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0042(void) __asm__("_Z19lodepng_clear_itextP11LodePNGInfo");
uintptr_t ef2_compat_fn_0042(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0043(void) __asm__("_Z19lodepng_decode_filePPhPjS1_PKc16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0043(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0044(void) __asm__("_Z19lodepng_encode_filePKcPKhjj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0044(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0045(void) __asm__("_Z19lodepng_palette_addP16LodePNGColorModehhhh");
uintptr_t ef2_compat_fn_0045(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0046(void) __asm__("_Z20getValueRequiredBitst");
uintptr_t ef2_compat_fn_0046(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0047(void) __asm__("_Z20lodepng_chunk_appendPPhPjPKh");
uintptr_t ef2_compat_fn_0047(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0048(void) __asm__("_Z20lodepng_chunk_createPPhPjjPKcPKh");
uintptr_t ef2_compat_fn_0048(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0049(void) __asm__("_Z20lodepng_chunk_lengthPKh");
uintptr_t ef2_compat_fn_0049(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0050(void) __asm__("_Z20lodepng_get_channelsPK16LodePNGColorMode");
uintptr_t ef2_compat_fn_0050(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0051(void) __asm__("_Z20lodepng_get_raw_sizejjPK16LodePNGColorMode");
uintptr_t ef2_compat_fn_0051(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0052(void) __asm__("_Z20lodepng_info_cleanupP11LodePNGInfo");
uintptr_t ef2_compat_fn_0052(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0053(void) __asm__("_Z20lodepng_read32bitIntPKh");
uintptr_t ef2_compat_fn_0053(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0054(void) __asm__("_Z21lodepng_chunk_privatePKh");
uintptr_t ef2_compat_fn_0054(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0055(void) __asm__("_Z21lodepng_decode24_filePPhPjS1_PKc");
uintptr_t ef2_compat_fn_0055(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0056(void) __asm__("_Z21lodepng_decode32_filePPhPjS1_PKc");
uintptr_t ef2_compat_fn_0056(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0057(void) __asm__("_Z21lodepng_decode_memoryPPhPjS1_PKhj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0057(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0058(void) __asm__("_Z21lodepng_encode24_filePKcPKhjj");
uintptr_t ef2_compat_fn_0058(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0059(void) __asm__("_Z21lodepng_encode32_filePKcPKhjj");
uintptr_t ef2_compat_fn_0059(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0060(void) __asm__("_Z21lodepng_encode_memoryPPhPjPKhjj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0060(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0061(void) __asm__("_Z21lodepng_is_alpha_typePK16LodePNGColorMode");
uintptr_t ef2_compat_fn_0061(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0062(void) __asm__("_Z21lodepng_palette_clearP16LodePNGColorMode");
uintptr_t ef2_compat_fn_0062(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0063(void) __asm__("_Z21lodepng_state_cleanupP12LodePNGState");
uintptr_t ef2_compat_fn_0063(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0064(void) __asm__("_Z21lodepng_zlib_compressPPhPjPKhjPK23LodePNGCompressSettings");
uintptr_t ef2_compat_fn_0064(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0065(void) __asm__("_Z22lodepng_can_have_alphaPK16LodePNGColorMode");
uintptr_t ef2_compat_fn_0065(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0066(void) __asm__("_Z23lodepng_chunk_ancillaryPKh");
uintptr_t ef2_compat_fn_0066(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0067(void) __asm__("_Z23lodepng_chunk_check_crcPKh");
uintptr_t ef2_compat_fn_0067(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0068(void) __asm__("_Z23lodepng_color_mode_copyP16LodePNGColorModePKS_");
uintptr_t ef2_compat_fn_0068(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0069(void) __asm__("_Z23lodepng_color_mode_initP16LodePNGColorMode");
uintptr_t ef2_compat_fn_0069(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0070(void) __asm__("_Z23lodepng_is_palette_typePK16LodePNGColorMode");
uintptr_t ef2_compat_fn_0070(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0071(void) __asm__("_Z23lodepng_zlib_decompressPPhPjPKhjPK25LodePNGDecompressSettings");
uintptr_t ef2_compat_fn_0071(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0072(void) __asm__("_Z24lodepng_chunk_data_constPKh");
uintptr_t ef2_compat_fn_0072(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0073(void) __asm__("_Z24lodepng_chunk_next_constPKh");
uintptr_t ef2_compat_fn_0073(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0074(void) __asm__("_Z24lodepng_chunk_safetocopyPKh");
uintptr_t ef2_compat_fn_0074(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0075(void) __asm__("_Z24lodepng_get_raw_size_lctjj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0075(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0076(void) __asm__("_Z25lodepng_auto_choose_colorP16LodePNGColorModePKhjjPKS_18LodePNGAutoConvert");
uintptr_t ef2_compat_fn_0076(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0077(void) __asm__("_Z25lodepng_chunk_type_equalsPKhPKc");
uintptr_t ef2_compat_fn_0077(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0078(void) __asm__("_Z25lodepng_has_palette_alphaPK16LodePNGColorMode");
uintptr_t ef2_compat_fn_0078(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0079(void) __asm__("_Z25lodepng_is_greyscale_typePK16LodePNGColorMode");
uintptr_t ef2_compat_fn_0079(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0080(void) __asm__("_Z26lodepng_chunk_generate_crcPh");
uintptr_t ef2_compat_fn_0080(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0081(void) __asm__("_Z26lodepng_color_mode_cleanupP16LodePNGColorMode");
uintptr_t ef2_compat_fn_0081(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0082(void) __asm__("_Z28lodepng_huffman_code_lengthsPjPKjjj");
uintptr_t ef2_compat_fn_0082(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0083(void) __asm__("_Z29lodepng_decoder_settings_initP22LodePNGDecoderSettings");
uintptr_t ef2_compat_fn_0083(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0084(void) __asm__("_Z29lodepng_encoder_settings_initP22LodePNGEncoderSettings");
uintptr_t ef2_compat_fn_0084(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0085(void) __asm__("_Z30lodepng_compress_settings_initP23LodePNGCompressSettings");
uintptr_t ef2_compat_fn_0085(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0086(void) __asm__("_Z32lodepng_decompress_settings_initP25LodePNGDecompressSettings");
uintptr_t ef2_compat_fn_0086(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0087(void) __asm__("_Z3mixfff");
uintptr_t ef2_compat_fn_0087(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0088(void) __asm__("_Z5themeP13AAssetManageri");
uintptr_t ef2_compat_fn_0088(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0089(void) __asm__("_Z9readThemeISt19basic_istringstreamIcSt11char_traitsIcESaIcEEESt3mapISs14themeparameterSt4lessISsESaISt4pairIKSsS6_EEERT_");
uintptr_t ef2_compat_fn_0089(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0090(void) __asm__("_Z9timesinceRK8timespec");
uintptr_t ef2_compat_fn_0090(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0091(void) __asm__("_ZN11CurveClientC1Ev");
uintptr_t ef2_compat_fn_0091(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0092(void) __asm__("_ZN11CurveClientC2Ev");
uintptr_t ef2_compat_fn_0092(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0093(void) __asm__("_ZN11framebuffer3setEjP7texture");
uintptr_t ef2_compat_fn_0093(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0094(void) __asm__("_ZN11framebuffer4exitEv");
uintptr_t ef2_compat_fn_0094(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0095(void) __asm__("_ZN11framebuffer5enterEPS_");
uintptr_t ef2_compat_fn_0095(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0096(void) __asm__("_ZN11framebufferC1Ev");
uintptr_t ef2_compat_fn_0096(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0097(void) __asm__("_ZN11framebufferC2Ev");
uintptr_t ef2_compat_fn_0097(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0098(void) __asm__("_ZN12LodePNGStateD0Ev");
uintptr_t ef2_compat_fn_0098(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0099(void) __asm__("_ZN12LodePNGStateD1Ev");
uintptr_t ef2_compat_fn_0099(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0100(void) __asm__("_ZN12LodePNGStateD2Ev");
uintptr_t ef2_compat_fn_0100(void) { return ef2_compat_ret0(); }
EF2_COMPAT_EXPORT int ef2_compat_bufferconfig_set(ef2_bufferconfig_abi* self, ef2_buffer_abi* buf, int32_t a, int32_t b)
    __asm__("_ZN12bufferconfig3setEP6bufferii");

// Forward declaration (used by bufferconfig::set shim before definition).
EF2_COMPAT_EXPORT int ef2_compat_buffer_addconfig(ef2_buffer_abi* self, void* cfg)
    __asm__("_ZN6buffer9addconfigEP12bufferconfig");

int ef2_compat_bufferconfig_set(ef2_bufferconfig_abi* self, ef2_buffer_abi* buf, int32_t a, int32_t b)
{
  // 95KB ref: bufferconfig::set returns buffer::addconfig(buf, this) result.
  if (!self || !buf) return 0;

  // original order: addconfig(buf, this) then set fields
  int add_res = ef2_compat_buffer_addconfig(buf, (void*)self);

  self->owner_buf = (void*)buf;
  self->touched = 1;
  self->a = a;
  self->b = b;

  return add_res;
}
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0102(void) __asm__("_ZN12rendererdataC1ERKS_");
uintptr_t ef2_compat_fn_0102(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0103(void) __asm__("_ZN12rendererdataC2ERKS_");
uintptr_t ef2_compat_fn_0103(void) { return ef2_compat_ret0(); }
// --- Curve ABI wrappers (originally exported C++ methods) ---

EF2_COMPAT_EXPORT void ef2_compat_Curve_deactivate(ef2_Curve* self)
    __asm__("_ZN5Curve10deactivateEv");
void ef2_compat_Curve_deactivate(ef2_Curve* self) { ef2_Curve_deactivate(self); }

EF2_COMPAT_EXPORT void ef2_compat_Curve_requestColors(ef2_Curve* self, ef2_AAssetManager* mgr, int mode)
    __asm__("_ZN5Curve13requestColorsEP13AAssetManageri");
void ef2_compat_Curve_requestColors(ef2_Curve* self, ef2_AAssetManager* mgr, int mode)
{
    ef2_Curve_requestColors(self, mgr, mode);
}

// NOTE: The original call site passes (&rendererdata, curve). Even though the
// symbol is mangled as a Curve method, the effective calling convention is:
//   rendererdata* updateRenderer(rendererdata* out, Curve* curve)
//
// The original 95KB liblwplocal.so contains a large body here (~3KB) that
// fills the rendererdata structure from Curve state and updates several Curve
// cached fields. For binary matching we keep this logic directly inside the
// exported symbol (instead of delegating to an internal helper).

static int32_t ef2_ur_read_i32(const void* base, size_t off)
{
  int32_t v = 0;
  memcpy(&v, (const uint8_t*)base + off, sizeof(v));
  return v;
}

static uint32_t ef2_ur_read_u32(const void* base, size_t off)
{
  uint32_t v = 0;
  memcpy(&v, (const uint8_t*)base + off, sizeof(v));
  return v;
}

static double ef2_ur_read_f64(const void* base, size_t off)
{
  double v = 0.0;
  memcpy(&v, (const uint8_t*)base + off, sizeof(v));
  return v;
}

static void ef2_ur_write_f64(void* base, size_t off, double v)
{
  memcpy((uint8_t*)base + off, &v, sizeof(v));
}

static void ef2_ur_write_f32(void* dst4, float v)
{
  memcpy(dst4, &v, sizeof(v));
}

static double ef2_ur_absd(double x) { return (x < 0.0) ? -x : x; }
static double ef2_ur_signd(double x) { return (x < 0.0) ? -1.0 : 1.0; }

EF2_COMPAT_EXPORT ef2_rendererdata* ef2_compat_Curve_updateRenderer(ef2_rendererdata* out, ef2_Curve* curve)
    __asm__("_ZN5Curve14updateRendererEv");
ef2_rendererdata* ef2_compat_Curve_updateRenderer(ef2_rendererdata* out, ef2_Curve* curve)
{

  if (!out || !curve) return out;

  // The original constructs rendererdata with a pointer to Curve's theme tree
  // (used later for ".transitions"). For now we clear but keep the pointer.
  ef2_rendererdata_init(out);
  *(uint32_t*)out->field_0x10 = (uint32_t)(uintptr_t)((uint8_t*)curve + 0x20);

  // ---- time ---------------------------------------------------------------
  const double out_time = timesince((const ef2_timespec32*)curve->_pad_0xB8, 0);
  memcpy(out->time_0x8, &out_time, sizeof(out_time));

  // v7 = 1 - timesince(curve->field_0xC0), clamp >= 0
  double v7 = 1.0 - timesince((const ef2_timespec32*)((uint8_t*)curve + 0xC0), 0);
  if (v7 < 0.0) v7 = 0.0;

  const int32_t c8 = ef2_ur_read_i32(curve, 0xC8);
  const int32_t cc = ef2_ur_read_i32(curve, 0xCC);

  double v6 = 1.0;
  if ((c8 & 2) != 0) {
    if ((cc & 1) == 0) v6 = 0.0;
  } else {
    v6 = 0.0;
  }

  const double v8 = (double)(c8 & 1) + v7 * v6;

  double v9 = 1.0;
  if (ef2_ur_read_u32(curve, 0xB4) == 0) v9 = 0.0;

  out->field_0x0[0] = 0;
  ef2_ur_write_f32(out->field_0x40, (float)(v8 * v9));

  // ---- screen/layout (from client blob) -----------------------------------
  uint32_t* cblob = (uint32_t*)curve->client_0x8;
  if (cblob) {
    ef2_ur_write_f32(out->field_0x28, (float)(int32_t)cblob[3]);
    ef2_ur_write_f32(out->field_0x2C, (float)(int32_t)cblob[4]);
    ef2_ur_write_f32(out->field_0x30, (float)(int32_t)cblob[1]);
    ef2_ur_write_f32(out->field_0x34, (float)(int32_t)cblob[2]);
  }
  ef2_ur_write_f32(out->field_0x38, (float)ef2_ur_read_i32(curve, 0x144));
  ef2_ur_write_f32(out->field_0x3C, (float)ef2_ur_read_i32(curve, 0x148));

  // ---- first-frame / cache init -------------------------------------------
  if (curve->client_0x8 && (*(uint8_t*)curve->client_0x8) == 0) {
    out->field_0x0[0] = 1;
    // cached values used to decide when to refresh texture-related uniforms
    ((int32_t*)curve->client_0x8)[21] = -1;
    ((int32_t*)curve->client_0x8)[22] = -1;
  }

  // Debug print (kept - matches decomp; low overhead)
  (void)ef2_log_print(3, "lwplocal", "chk:%d nfd:%p bgfd:%p tc:%d\n",
                      (int)out->field_0x0[0],
                      curve->ptr_0xB0,
                      (void*)(uintptr_t)ef2_ur_read_u32(curve, 0xB4),
                      ef2_ur_read_i32(curve, 0x140));

  // ---- texture/uniform cache refresh --------------------------------------
  out->field_0x68[0] = 0;
  out->field_0x69[0] = 0;

  const int32_t v14  = ef2_ur_read_i32(curve, 0x14C);
  const int32_t v150 = ef2_ur_read_i32(curve, 0x150);

  int need_refresh = (out->field_0x0[0] != 0);
  if (!need_refresh && curve->client_0x8) {
    int32_t* ci = (int32_t*)curve->client_0x8;
    if (ci[21] != v14 || ci[22] != v150) need_refresh = 1;
  }

  if (need_refresh) {
    *(uint32_t*)out->field_0x70 = (uint32_t)(uintptr_t)curve->ptr_0xB0;
    *(uint32_t*)out->field_0x6C = ef2_ur_read_u32(curve, 0xB4);
    *(uint32_t*)out->field_0x74 = ef2_ur_read_u32(curve, 0x164);
    *(uint32_t*)out->field_0x78 = ef2_ur_read_u32(curve, 0x168);
    *(uint32_t*)out->field_0x7C = ef2_ur_read_u32(curve, 0x16C);
    *(uint32_t*)out->field_0x80 = ef2_ur_read_u32(curve, 0x170);
    *(uint32_t*)out->field_0x84 = ef2_ur_read_u32(curve, 0x154);
    *(uint32_t*)out->field_0x88 = ef2_ur_read_u32(curve, 0x154 + 12);

    out->field_0x68[0] = 1;
    out->field_0x69[0] = 1;

    if (curve->client_0x8) {
      int32_t* ci = (int32_t*)curve->client_0x8;
      ci[21] = v14;
      ci[22] = v150;
    }
  }

  // ---- physics-ish update block -------------------------------------------
  const int32_t touch_count = ef2_ur_read_i32(curve, 0x140);

  const double v16 = ef2_ur_read_f64(curve, 0xD0); // target X
  const double v17 = ef2_ur_read_f64(curve, 0xD8); // target Y

  // keep last target X in F8
  ef2_ur_write_f64(curve, 0xF8, v16);
  if (touch_count == 0) {
    // when no touch, also snap the stored "100" to target Y
    ef2_ur_write_f64(curve, 0x100, v17);
  }

  double v19, v20, v21;
  if ((c8 & 2) != 0) {
    v19 = 1.0; v20 = 5.35; v21 = v19;
  } else if ((c8 & 1) != 0) {
    v19 = 2.0; v20 = 4.35; v21 = 4.0;
  } else {
    v19 = 1.0; v20 = 1.0; v21 = v19;
  }

  const double v22 = ef2_ur_read_f64(curve, 0xE0);
  const double v23 = ef2_ur_read_f64(curve, 0xF0);
  const double v28 = ef2_ur_read_f64(curve, 0xE8);
  const double v30 = ef2_ur_read_f64(curve, 0x130);
  const double dt  = out_time - v30;

  const double v26 = v16 - v22;                // dx (target - current)
  const double v29 = ef2_ur_read_f64(curve, 0x100) - v23;
  const double v32 = v16 - v28;
  const double v49 = ef2_ur_read_f64(curve, 0x120);
  const double v50 = ef2_ur_read_f64(curve, 0x110);
  const double v52 = v16 - v49;
  const double v54 = v17 - v50;

  // E0
  double v33 = ef2_ur_absd(v26 * 4.0) * dt;
  double cap = ef2_ur_absd(v26);
  if (cap < v33) v33 = cap;
  ef2_ur_write_f64(curve, 0xE0, v22 + v33 * ef2_ur_signd(v26));
  const double v161 = ef2_ur_read_f64(curve, 0xE0);

  // E8
  double v37 = ef2_ur_absd(v32 * 4.0) * dt;
  cap = ef2_ur_absd(v32);
  if (cap < v37) v37 = cap;
  ef2_ur_write_f64(curve, 0xE8, v28 + v37 * ef2_ur_signd(v32));

  // F0
  double v42 = ef2_ur_absd((v29 + v29)) * dt;
  cap = ef2_ur_absd(v29);
  if (cap < v42) v42 = cap;
  ef2_ur_write_f64(curve, 0xF0, v23 + v42 * ef2_ur_signd(v29));

  // 128 accumulator
  double v47 = ef2_ur_absd((v26 + v26)) * dt;
  cap = ef2_ur_absd(v26);
  if (cap < v47) v47 = cap;
  ef2_ur_write_f64(curve, 0x128, ef2_ur_read_f64(curve, 0x128) + v47 * 0.1);

  // 118
  double v55 = ef2_ur_absd(v52 * 24.0) * dt;
  cap = ef2_ur_absd(v52);
  if (cap < v55) v55 = cap;
  const double v58 = ef2_ur_read_f64(curve, 0x118) + v55 * ef2_ur_signd(v52);
  ef2_ur_write_f64(curve, 0x118, v58);

  // 108
  double v60 = ef2_ur_absd(v54 * 24.0) * dt;
  cap = ef2_ur_absd(v54);
  if (cap < v60) v60 = cap;
  const double v63 = ef2_ur_read_f64(curve, 0x108) + v60 * ef2_ur_signd(v54);
  ef2_ur_write_f64(curve, 0x108, v63);

  // 120 (first)
  double v65 = ef2_ur_absd(v58 * v21) * dt;
  cap = ef2_ur_absd(v58);
  if (cap < v65) v65 = cap;
  const double v69 = v49 + v65 * ef2_ur_signd(v58);
  ef2_ur_write_f64(curve, 0x120, v69);

  // 110 (first)
  double v71 = ef2_ur_absd(v63 * v21) * dt;
  cap = ef2_ur_absd(v63);
  if (cap < v71) v71 = cap;
  const double v76 = v50 + v71 * ef2_ur_signd(v63);
  ef2_ur_write_f64(curve, 0x110, v76);

  // 120 (second)
  double v77 = ef2_ur_absd(v52 * v20) * dt;
  cap = ef2_ur_absd(v52);
  if (cap < v77) v77 = cap;
  const double v80 = v69 + v77 * ef2_ur_signd(v52);
  ef2_ur_write_f64(curve, 0x120, v80);

  // 110 (second)
  double v82 = ef2_ur_absd(v54 * v20) * dt;
  cap = ef2_ur_absd(v54);
  if (cap < v82) v82 = cap;
  const double v85 = v76 + v82 * ef2_ur_signd(v54);
  ef2_ur_write_f64(curve, 0x110, v85);

  // E0 (second), D0, F8
  const double v86 = v54 * v19;

  double v88 = ef2_ur_absd(v86) * dt;
  cap = ef2_ur_absd(v54);
  if (cap < v88) v88 = cap;
  ef2_ur_write_f64(curve, 0xE0, v161 + v88 * ef2_ur_signd(v26));
  const double v91 = ef2_ur_read_f64(curve, 0xE0);

  double v93 = ef2_ur_absd(v86) * dt;
  cap = ef2_ur_absd(v54);
  if (cap < v93) v93 = cap;
  ef2_ur_write_f64(curve, 0xD0, v16 + v93 * ef2_ur_signd(v26));

  double v97 = ef2_ur_absd(v86) * dt;
  cap = ef2_ur_absd(v54);
  if (cap < v97) v97 = cap;
  ef2_ur_write_f64(curve, 0xF8, v16 + v97 * ef2_ur_signd(v26));

  // outputs for renderer uniforms
  ef2_ur_write_f32(out->field_0x48, (float)(v80 - v91));
  ef2_ur_write_f32(out->field_0x58, (float)(ef2_ur_read_f64(curve, 0x110) - ef2_ur_read_f64(curve, 0xF0)));

  // derive curve->field_0x138 (energy * 8)
  const double v102 = ef2_ur_read_f64(curve, 0x120) - ef2_ur_read_f64(curve, 0xE0);
  double v106 = ef2_ur_absd(v32) + ef2_ur_absd(v26) + ef2_ur_absd(v102) +
                ef2_ur_absd(v52) + ef2_ur_absd(ef2_ur_read_f64(curve, 0x118));
  const double v107 = ef2_ur_read_f64(curve, 0x110) - ef2_ur_read_f64(curve, 0xF0);
  const double v111 = ef2_ur_absd(v29) + ef2_ur_absd(v107) + ef2_ur_absd(v54) +
                      ef2_ur_absd(ef2_ur_read_f64(curve, 0x108));
  if (v106 < v111) v106 = v111;
  if (ef2_ur_absd(v32) >= v106) v106 = ef2_ur_absd(v32);
  ef2_ur_write_f64(curve, 0x138, v106 * 8.0);

  ef2_ur_write_f32(out->field_0x4C, (float)ef2_ur_read_f64(curve, 0xD0));
  ef2_ur_write_f32(out->field_0x5C, (float)ef2_ur_read_f64(curve, 0xD8));
  ef2_ur_write_f32(out->field_0x50, (float)ef2_ur_read_f64(curve, 0xE0));
  ef2_ur_write_f32(out->field_0x60, (float)ef2_ur_read_f64(curve, 0xF0));
  ef2_ur_write_f32(out->field_0x54, (float)ef2_ur_read_f64(curve, 0xE8));

  // ---- commit frame time ----------------------------------------------------
  ef2_ur_write_f64(curve, 0x130, out_time);
  if (curve->client_0x8) {
    ((uint64_t*)curve->client_0x8)[9] = *(const uint64_t*)out->time_0x8; // raw bits
    *(uint8_t*)curve->client_0x8 = 1;
  }

  return out;
}

EF2_COMPAT_EXPORT void ef2_compat_Curve_updateScreenLayout(
    ef2_Curve* self,
    int x,
    int y,
    int w,
    int h,
    int screenW,
    int screenH)
    __asm__("_ZN5Curve18updateScreenLayoutEiiiiii");
void ef2_compat_Curve_updateScreenLayout(
    ef2_Curve* self,
    int x,
    int y,
    int w,
    int h,
    int screenW,
    int screenH)
{
    ef2_Curve_updateScreenLayout(self, x, y, w, h, screenW, screenH);
}

EF2_COMPAT_EXPORT int ef2_compat_Curve_getSleepRecommendation(ef2_Curve* self)
    __asm__("_ZN5Curve22getSleepRecommendationEv");
int ef2_compat_Curve_getSleepRecommendation(ef2_Curve* self) { return ef2_Curve_getSleepRecommendation(self); }

EF2_COMPAT_EXPORT void ef2_compat_Curve_touch(Curve* self, float x, float y) __asm__("_ZN5Curve5touchEff");
void ef2_compat_Curve_touch(Curve* self, float x, float y)
{
    ef2_Curve_touch(self, x, y);
    __asm__ __volatile__("" ::: "memory");
}

EF2_COMPAT_EXPORT void ef2_compat_Curve_touchUp(Curve* self, float x, float y) __asm__("_ZN5Curve7touchUpEff");
void ef2_compat_Curve_touchUp(Curve* self, float x, float y)
{
    ef2_Curve_touchUp(self, x, y);
    __asm__ __volatile__("" ::: "memory");
}

EF2_COMPAT_EXPORT void ef2_compat_Curve_activate(ef2_Curve* self) __asm__("_ZN5Curve8activateEv");
void ef2_compat_Curve_activate(ef2_Curve* self) { ef2_Curve_activate(self); }

EF2_COMPAT_EXPORT void ef2_compat_Curve_touchDown(Curve* self, float x, float y) __asm__("_ZN5Curve9touchDownEff");
void ef2_compat_Curve_touchDown(Curve* self, float x, float y)
{
    ef2_Curve_touchDown(self, x, y);
    __asm__ __volatile__("" ::: "memory");
}

EF2_COMPAT_EXPORT void ef2_compat_Curve_ctor1(ef2_Curve* self, ef2_AAssetManager* mgr)
    __asm__("_ZN5CurveC1EP13AAssetManager");
void ef2_compat_Curve_ctor1(ef2_Curve* self, ef2_AAssetManager* mgr) { ef2_Curve_init(self, mgr); }

EF2_COMPAT_EXPORT void ef2_compat_Curve_ctor2(ef2_Curve* self, ef2_AAssetManager* mgr)
    __asm__("_ZN5CurveC2EP13AAssetManager");
void ef2_compat_Curve_ctor2(ef2_Curve* self, ef2_AAssetManager* mgr) { ef2_Curve_init(self, mgr); }
EF2_COMPAT_EXPORT void ef2_compat_buffer_set(ef2_buffer_abi* self, uint32_t size, void* data, uint32_t usage)
    __asm__("_ZN6buffer3setEjPvj");
void ef2_compat_buffer_set(ef2_buffer_abi* self, uint32_t size, void* data, uint32_t usage)
{
  ef2_buffer_abi_set(self, size, data, usage);
}

EF2_COMPAT_EXPORT void ef2_compat_buffer_touch(ef2_buffer_abi* self) __asm__("_ZN6buffer5touchEv");
void ef2_compat_buffer_touch(ef2_buffer_abi* self)
{
  // See 95KB liblwplocal.so: buffer::touch iterates its config set,
  // marks configs owned by this buffer as touched, and removes stale ones.
  ef2_buffer_cfgvec_touch_cleanup(self);
}

EF2_COMPAT_EXPORT void ef2_compat_buffer_subset(ef2_buffer_abi* self, uint32_t offset, uint32_t size, void* data)
    __asm__("_ZN6buffer6subsetEjjPv");
void ef2_compat_buffer_subset(ef2_buffer_abi* self, uint32_t offset, uint32_t size, void* data)
{
  ef2_buffer_abi_subset(self, offset, size, data);
}

EF2_COMPAT_EXPORT int ef2_compat_buffer_addconfig(ef2_buffer_abi* self, void* cfg)
    __asm__("_ZN6buffer9addconfigEP12bufferconfig");
int ef2_compat_buffer_addconfig(ef2_buffer_abi* self, void* cfg)
{
  // Original uses an rb-tree keyed by bufferconfig*.
  // In the C port, keep a small de-duped vector in the buffer object.
  if (!self || !cfg) return 0;
  ef2_buffer_cfgvec_add(self, cfg);
  // Return value in the 95KB ref is an rb-tree node pointer (truthy).
  // We don't build that structure, so return the cfg pointer as a stable
  // non-zero sentinel.
  return (int)(uintptr_t)cfg;
}

EF2_COMPAT_EXPORT void ef2_compat_buffer_ctor1(ef2_buffer_abi* self, uint32_t target, int32_t id_or_alloc)
    __asm__("_ZN6bufferC1Eji");
void ef2_compat_buffer_ctor1(ef2_buffer_abi* self, uint32_t target, int32_t id_or_alloc)
{
  ef2_buffer_abi_ctor(self, target, id_or_alloc);
}

EF2_COMPAT_EXPORT void ef2_compat_buffer_ctor2(ef2_buffer_abi* self, uint32_t target, int32_t id_or_alloc)
    __asm__("_ZN6bufferC2Eji");
void ef2_compat_buffer_ctor2(ef2_buffer_abi* self, uint32_t target, int32_t id_or_alloc)
{
  ef2_buffer_abi_ctor(self, target, id_or_alloc);
}

EF2_COMPAT_EXPORT void ef2_compat_buffer_dtor1(ef2_buffer_abi* self) __asm__("_ZN6bufferD1Ev");
void ef2_compat_buffer_dtor1(ef2_buffer_abi* self)
{
  ef2_buffer_abi_dtor(self);
}

EF2_COMPAT_EXPORT void ef2_compat_buffer_dtor2(ef2_buffer_abi* self) __asm__("_ZN6bufferD2Ev");
void ef2_compat_buffer_dtor2(ef2_buffer_abi* self)
{
  ef2_buffer_abi_dtor(self);
}
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0123(void) __asm__("_ZN6varray6updateEv");
uintptr_t ef2_compat_fn_0123(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0124(void) __asm__("_ZN6varray9getconfigESs");
uintptr_t ef2_compat_fn_0124(void) { return ef2_compat_ret0(); }
EF2_COMPAT_EXPORT void ef2_compat_varray_ctor1(void* self) __asm__("_ZN6varrayC1Ev");
void ef2_compat_varray_ctor1(void* self) { ef2_varray_abi_ctor(self); }
EF2_COMPAT_EXPORT void ef2_compat_varray_ctor2(void* self) __asm__("_ZN6varrayC2Ev");
void ef2_compat_varray_ctor2(void* self) { ef2_varray_abi_ctor(self); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0127(void) __asm__("_ZN7lodepng10decompressERSt6vectorIhSaIhEEPKhjRK25LodePNGDecompressSettings");
uintptr_t ef2_compat_fn_0127(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0128(void) __asm__("_ZN7lodepng10decompressERSt6vectorIhSaIhEERKS2_RK25LodePNGDecompressSettings");
uintptr_t ef2_compat_fn_0128(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0129(void) __asm__("_ZN7lodepng5StateC1ERKS0_");
uintptr_t ef2_compat_fn_0129(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0130(void) __asm__("_ZN7lodepng5StateC1Ev");
uintptr_t ef2_compat_fn_0130(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0131(void) __asm__("_ZN7lodepng5StateC2ERKS0_");
uintptr_t ef2_compat_fn_0131(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0132(void) __asm__("_ZN7lodepng5StateC2Ev");
uintptr_t ef2_compat_fn_0132(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0133(void) __asm__("_ZN7lodepng5StateD0Ev");
uintptr_t ef2_compat_fn_0133(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0134(void) __asm__("_ZN7lodepng5StateD1Ev");
uintptr_t ef2_compat_fn_0134(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0135(void) __asm__("_ZN7lodepng5StateD2Ev");
uintptr_t ef2_compat_fn_0135(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0136(void) __asm__("_ZN7lodepng5StateaSERKS0_");
uintptr_t ef2_compat_fn_0136(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0137(void) __asm__("_ZN7lodepng6decodeERSt6vectorIhSaIhEERjS4_PKhj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0137(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0138(void) __asm__("_ZN7lodepng6decodeERSt6vectorIhSaIhEERjS4_RKS2_16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0138(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0139(void) __asm__("_ZN7lodepng6decodeERSt6vectorIhSaIhEERjS4_RKSs16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0139(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0140(void) __asm__("_ZN7lodepng6decodeERSt6vectorIhSaIhEERjS4_RNS_5StateEPKhj");
uintptr_t ef2_compat_fn_0140(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0141(void) __asm__("_ZN7lodepng6decodeERSt6vectorIhSaIhEERjS4_RNS_5StateERKS2_");
uintptr_t ef2_compat_fn_0141(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0142(void) __asm__("_ZN7lodepng6encodeERKSsPKhjj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0142(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0143(void) __asm__("_ZN7lodepng6encodeERKSsRKSt6vectorIhSaIhEEjj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0143(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0144(void) __asm__("_ZN7lodepng6encodeERSt6vectorIhSaIhEEPKhjj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0144(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0145(void) __asm__("_ZN7lodepng6encodeERSt6vectorIhSaIhEEPKhjjRNS_5StateE");
uintptr_t ef2_compat_fn_0145(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0146(void) __asm__("_ZN7lodepng6encodeERSt6vectorIhSaIhEERKS2_jj16LodePNGColorTypej");
uintptr_t ef2_compat_fn_0146(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0147(void) __asm__("_ZN7lodepng6encodeERSt6vectorIhSaIhEERKS2_jjRNS_5StateE");
uintptr_t ef2_compat_fn_0147(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0148(void) __asm__("_ZN7lodepng8compressERSt6vectorIhSaIhEEPKhjRK23LodePNGCompressSettings");
uintptr_t ef2_compat_fn_0148(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0149(void) __asm__("_ZN7lodepng8compressERSt6vectorIhSaIhEERKS2_RK23LodePNGCompressSettings");
uintptr_t ef2_compat_fn_0149(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0150(void) __asm__("_ZN7lodepng9load_fileERSt6vectorIhSaIhEERKSs");
uintptr_t ef2_compat_fn_0150(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0151(void) __asm__("_ZN7lodepng9save_fileERKSt6vectorIhSaIhEERKSs");
uintptr_t ef2_compat_fn_0151(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0152(void) __asm__("_ZN7program10getuniformESs");
uintptr_t ef2_compat_fn_0152(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0153(void) __asm__("_ZN7program13createProgramERSt6vectorIjSaIjEE");
uintptr_t ef2_compat_fn_0153(void) { return ef2_compat_ret0(); }
EF2_COMPAT_EXPORT void ef2_compat_fn_0154(ef2_Program* p) __asm__("_ZN7program4bindEv");
EF2_COMPAT_EXPORT void ef2_compat_fn_0154(ef2_Program* p)
{
    if (!p) return;
    // Delegate to our C implementation (keeps behavior consistent across build modes).
    ef2_Program_use(p);
}
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0155(void) __asm__("_ZN7program6shaderEjSsRSt6vectorIjSaIjEE");
uintptr_t ef2_compat_fn_0155(void) { return ef2_compat_ret0(); }
EF2_COMPAT_EXPORT void ef2_compat_fn_0156(ef2_Program* p) __asm__("_ZN7program6updateEv");
EF2_COMPAT_EXPORT void ef2_compat_fn_0156(ef2_Program* p)
{
    if (!p) return;
    // In the original, program::update is effectively "push cached uniforms".
    // Our C core already implements this in a compatible way.
    ef2_Program_applyUniforms(p);
}
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0157(void) __asm__("_ZN7program9getattribESs");
uintptr_t ef2_compat_fn_0157(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0158(void) __asm__("_ZN7programC1ERj");
uintptr_t ef2_compat_fn_0158(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0159(void) __asm__("_ZN7programC2ERj");
uintptr_t ef2_compat_fn_0159(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0160(void) __asm__("_ZN7programD1Ev");
uintptr_t ef2_compat_fn_0160(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0161(void) __asm__("_ZN7programD2Ev");
uintptr_t ef2_compat_fn_0161(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0162(void) __asm__("_ZN7texture3setESs");
uintptr_t ef2_compat_fn_0162(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0163(void) __asm__("_ZN7texture3setEiiiiiPvb");
uintptr_t ef2_compat_fn_0163(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0164(void) __asm__("_ZN7texture4bindEi");
uintptr_t ef2_compat_fn_0164(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0165(void) __asm__("_ZN7texture4loadESs");
uintptr_t ef2_compat_fn_0165(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0166(void) __asm__("_ZN7textureC1Ej");
uintptr_t ef2_compat_fn_0166(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0167(void) __asm__("_ZN7textureC1Ev");
uintptr_t ef2_compat_fn_0167(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0168(void) __asm__("_ZN7textureC2Ej");
uintptr_t ef2_compat_fn_0168(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0169(void) __asm__("_ZN7textureC2Ev");
uintptr_t ef2_compat_fn_0169(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0170(void) __asm__("_ZN7uniform3setIfEEvT_");
uintptr_t ef2_compat_fn_0170(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0171(void) __asm__("_ZN7uniform3setIfEEvT_S1_");
uintptr_t ef2_compat_fn_0171(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0172(void) __asm__("_ZN7uniform3setIfEEvT_S1_S1_S1_");
uintptr_t ef2_compat_fn_0172(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0173(void) __asm__("_ZN7uniform7touchedEv");
uintptr_t ef2_compat_fn_0173(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0174(void) __asm__("_ZN8fsshader3runEv");
uintptr_t ef2_compat_fn_0174(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0175(void) __asm__("_ZN8fsshaderC1EP7program");
uintptr_t ef2_compat_fn_0175(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0176(void) __asm__("_ZN8fsshaderC2EP7program");
uintptr_t ef2_compat_fn_0176(void) { return ef2_compat_ret0(); }

EF2_COMPAT_EXPORT ef2_buffer_abi* ef2_compat_renderer_createIndices(ef2_Renderer* self, int cols, int rows)
    __asm__("_ZN8renderer13createIndicesEii");
ef2_buffer_abi* ef2_compat_renderer_createIndices(ef2_Renderer* self, int cols, int rows)
{
  (void)self;
  if (cols <= 0 || rows <= 0) return NULL;

  // indexCount = rows * 2 * (cols + 2) - 2
  const uint32_t ucols = (uint32_t)cols;
  const uint32_t urows = (uint32_t)rows;
  const uint32_t indexCount = urows * 2u * (ucols + 2u) - 2u;
  if (indexCount == 0) return NULL;

  // u16 indices
  size_t bytes = (size_t)indexCount * sizeof(uint16_t);
  uint16_t* indices = (uint16_t*)malloc(bytes);
  if (!indices) return NULL;

  const uint32_t stride = ucols + 1u;
  uint32_t out = 0;
  uint32_t base = 0;

  {
    uint32_t r;
    uint32_t c;
    for (r = 0; r < urows; ++r)
    {
    if (r > 0)
    {
      indices[out++] = (uint16_t)base;
    }

      for (c = 0; c < stride; ++c)
      {
        indices[out++] = (uint16_t)(base + c);
        indices[out++] = (uint16_t)(base + stride + c);
      }

      if (r < urows - 1u)
      {
        indices[out++] = (uint16_t)(base + 2u * stride - 1u);
      }

      base += stride;
    }
  }

  // Defensive: ensure we filled as expected.
  if (out != indexCount)
  {
    free(indices);
    return NULL;
  }

  ef2_buffer_abi* buf = (ef2_buffer_abi*)malloc(sizeof(ef2_buffer_abi));
  if (!buf)
  {
    free(indices);
    return NULL;
  }

  ef2_buffer_abi_ctor(buf, 0x8893u /* GL_ELEMENT_ARRAY_BUFFER */, -1);
  ef2_buffer_abi_set(buf, (uint32_t)bytes, indices, 0x88E4u /* GL_STATIC_DRAW */);

  free(indices);
  return buf;
}


EF2_COMPAT_EXPORT ef2_buffer_abi* ef2_compat_renderer_createVertices(ef2_Renderer* self, int cols, int rows)
    __asm__("_ZN8renderer14createVerticesEii");
ef2_buffer_abi* ef2_compat_renderer_createVertices(ef2_Renderer* self, int cols, int rows)
{
  (void)self;
  if (cols <= 0 || rows <= 0) return NULL;

  const uint32_t ucols = (uint32_t)cols;
  const uint32_t urows = (uint32_t)rows;
  const uint32_t vertCount = (ucols + 1u) * (urows + 1u);
  const uint32_t floatCount = vertCount * 2u; // (u,v)
  size_t bytes = (size_t)floatCount * sizeof(float);

  float* verts = (float*)malloc(bytes);
  if (!verts) return NULL;

  const float invCols = (ucols == 0) ? 0.0f : (1.0f / (float)ucols);
  const float invRows = (urows == 0) ? 0.0f : (1.0f / (float)urows);

  {
    uint32_t k = 0;
    uint32_t r;
    uint32_t c;
    for (r = 0; r <= urows; ++r)
    {
      for (c = 0; c <= ucols; ++c)
      {
        verts[k++] = (float)c * invCols;
        verts[k++] = (float)r * invRows;
      }
    }
  }

  ef2_buffer_abi* buf = (ef2_buffer_abi*)malloc(sizeof(ef2_buffer_abi));
  if (!buf)
  {
    free(verts);
    return NULL;
  }

  ef2_buffer_abi_ctor(buf, 0x8892u /* GL_ARRAY_BUFFER */, -1);
  ef2_buffer_abi_set(buf, (uint32_t)bytes, verts, 0x88E4u /* GL_STATIC_DRAW */);

  free(verts);
  return buf;
}

EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0179(void) __asm__("_ZN8renderer15buildShaderFileEP13AAssetManagerSsSs");
uintptr_t ef2_compat_fn_0179(void) { return ef2_compat_ret0(); }

#if 0 // provided by src/compat/cpp_shims_v7a.cpp for ABI/size matching\nEF2_COMPAT_EXPORT void ef2_compat_renderer_init(ef2_Renderer* self, ef2_AAssetManager* mgr)
    __asm__("_ZN8renderer4initEP13AAssetManager");
void ef2_compat_renderer_init(ef2_Renderer* self, ef2_AAssetManager* mgr)
{
  ef2_Renderer_init(self, mgr);
  __asm__ __volatile__("" ::: "memory");
}
#endif


#if 0 // provided by src/renderer/renderer.c for size matching

EF2_COMPAT_EXPORT void ef2_compat_renderer_render(ef2_Renderer* self, ef2_AAssetManager* mgr)
    __asm__("_ZN8renderer6renderEP13AAssetManager");
void ef2_compat_renderer_render(ef2_Renderer* self, ef2_AAssetManager* mgr)
{
  ef2_Renderer_render(self, mgr);
}
#endif

EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0182(void) __asm__("_ZN8renderer7getfileEP13AAssetManagerSs");
uintptr_t ef2_compat_fn_0182(void) { return ef2_compat_ret0(); }

EF2_COMPAT_EXPORT void ef2_compat_renderer_ctor1(ef2_Renderer* self)
    __asm__("_ZN8rendererC1Ev");
void ef2_compat_renderer_ctor1(ef2_Renderer* self)
{
  if (!self) return;
  memset(self->raw, 0, sizeof(self->raw));
}


EF2_COMPAT_EXPORT void ef2_compat_renderer_ctor2(ef2_Renderer* self)
    __asm__("_ZN8rendererC2Ev");
void ef2_compat_renderer_ctor2(ef2_Renderer* self)
{
  if (!self) return;
  memset(self->raw, 0, sizeof(self->raw));
}

EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0185(void) __asm__("_ZNKSt6vectorIhSaIhEE12_M_check_lenEjPKc");
uintptr_t ef2_compat_fn_0185(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0186(void) __asm__("_ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_");
uintptr_t ef2_compat_fn_0186(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0187(void) __asm__("_ZNSt13_Rb_tree_nodeISt4pairIKSs14themeparameterEEC1IIRKS3_EEEDpOT_");
uintptr_t ef2_compat_fn_0187(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0188(void) __asm__("_ZNSt13_Rb_tree_nodeISt4pairIKSs14themeparameterEEC1IJRKS3_EEEDpOT_");
uintptr_t ef2_compat_fn_0188(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0189(void) __asm__("_ZNSt13_Rb_tree_nodeISt4pairIKSs14themeparameterEEC2IIRKS3_EEEDpOT_");
uintptr_t ef2_compat_fn_0189(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0190(void) __asm__("_ZNSt13_Rb_tree_nodeISt4pairIKSs14themeparameterEEC2IJRKS3_EEEDpOT_");
uintptr_t ef2_compat_fn_0190(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0191(void) __asm__("_ZNSt23mersenne_twister_engineIjLj32ELj624ELj397ELj31ELj2567483615ELj11ELj4294967295ELj7ELj2636928640ELj15ELj4022730752ELj18ELj1812433253EE4seedEj");
uintptr_t ef2_compat_fn_0191(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0192(void) __asm__("_ZNSt23mersenne_twister_engineIjLj32ELj624ELj397ELj31ELj2567483615ELj11ELj4294967295ELj7ELj2636928640ELj15ELj4022730752ELj18ELj1812433253EEclEv");
uintptr_t ef2_compat_fn_0192(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0193(void) __asm__("_ZNSt3mapISs14themeparameterSt4lessISsESaISt4pairIKSsS0_EEEixEOSs");
uintptr_t ef2_compat_fn_0193(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0194(void) __asm__("_ZNSt3mapISs14themeparameterSt4lessISsESaISt4pairIKSsS0_EEEixERS4_");
uintptr_t ef2_compat_fn_0194(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0195(void) __asm__("_ZNSt3mapISsP12bufferconfigSt4lessISsESaISt4pairIKSsS1_EEEixERS5_");
uintptr_t ef2_compat_fn_0195(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0196(void) __asm__("_ZNSt3mapISsP7uniformSt4lessISsESaISt4pairIKSsS1_EEED1Ev");
uintptr_t ef2_compat_fn_0196(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0197(void) __asm__("_ZNSt3mapISsP7uniformSt4lessISsESaISt4pairIKSsS1_EEED2Ev");
uintptr_t ef2_compat_fn_0197(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0198(void) __asm__("_ZNSt3mapISsP7uniformSt4lessISsESaISt4pairIKSsS1_EEEixEOSs");
uintptr_t ef2_compat_fn_0198(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0199(void) __asm__("_ZNSt3mapISsP9attributeSt4lessISsESaISt4pairIKSsS1_EEED1Ev");
uintptr_t ef2_compat_fn_0199(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0200(void) __asm__("_ZNSt3mapISsP9attributeSt4lessISsESaISt4pairIKSsS1_EEED2Ev");
uintptr_t ef2_compat_fn_0200(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0201(void) __asm__("_ZNSt3mapISsP9attributeSt4lessISsESaISt4pairIKSsS1_EEEixEOSs");
uintptr_t ef2_compat_fn_0201(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0202(void) __asm__("_ZNSt3mapIi17RendererInterfaceSt4lessIiESaISt4pairIKiS0_EEED1Ev");
uintptr_t ef2_compat_fn_0202(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0203(void) __asm__("_ZNSt3mapIi17RendererInterfaceSt4lessIiESaISt4pairIKiS0_EEED2Ev");
uintptr_t ef2_compat_fn_0203(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0204(void) __asm__("_ZNSt3mapIi17RendererInterfaceSt4lessIiESaISt4pairIKiS0_EEEixERS4_");
uintptr_t ef2_compat_fn_0204(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0205(void) __asm__("_ZNSt6vectorIP11framebufferSaIS1_EE19_M_emplace_back_auxIIRKS1_EEEvDpOT_");
uintptr_t ef2_compat_fn_0205(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0206(void) __asm__("_ZNSt6vectorIP11framebufferSaIS1_EE19_M_emplace_back_auxIJRKS1_EEEvDpOT_");
uintptr_t ef2_compat_fn_0206(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0207(void) __asm__("_ZNSt6vectorIP11framebufferSaIS1_EED1Ev");
uintptr_t ef2_compat_fn_0207(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0208(void) __asm__("_ZNSt6vectorIP11framebufferSaIS1_EED2Ev");
uintptr_t ef2_compat_fn_0208(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0209(void) __asm__("_ZNSt6vectorIP12bufferconfigSaIS1_EE19_M_emplace_back_auxIIRKS1_EEEvDpOT_");
uintptr_t ef2_compat_fn_0209(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0210(void) __asm__("_ZNSt6vectorIP12bufferconfigSaIS1_EE19_M_emplace_back_auxIJRKS1_EEEvDpOT_");
uintptr_t ef2_compat_fn_0210(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0211(void) __asm__("_ZNSt6vectorIP13uniformconfigSaIS1_EE19_M_emplace_back_auxIIRKS1_EEEvDpOT_");
uintptr_t ef2_compat_fn_0211(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0212(void) __asm__("_ZNSt6vectorIP13uniformconfigSaIS1_EE19_M_emplace_back_auxIJRKS1_EEEvDpOT_");
uintptr_t ef2_compat_fn_0212(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0213(void) __asm__("_ZNSt6vectorIhSaIhEE15_M_range_insertIPhEEvN9__gnu_cxx17__normal_iteratorIS3_S1_EET_S7_St20forward_iterator_tag");
uintptr_t ef2_compat_fn_0213(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0214(void) __asm__("_ZNSt6vectorIjSaIjEE19_M_emplace_back_auxIIRKjEEEvDpOT_");
uintptr_t ef2_compat_fn_0214(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0215(void) __asm__("_ZNSt6vectorIjSaIjEE19_M_emplace_back_auxIJRKjEEEvDpOT_");
uintptr_t ef2_compat_fn_0215(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0216(void) __asm__("_ZNSt8_Rb_treeIP12bufferconfigS1_St9_IdentityIS1_ESt4lessIS1_ESaIS1_EE8_M_eraseEPSt13_Rb_tree_nodeIS1_E");
uintptr_t ef2_compat_fn_0216(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0217(void) __asm__("_ZNSt8_Rb_treeIP13uniformconfigS1_St9_IdentityIS1_ESt4lessIS1_ESaIS1_EE16_M_insert_uniqueIRKS1_EESt4pairISt17_Rb_tree_iteratorIS1_EbEOT_");
uintptr_t ef2_compat_fn_0217(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0218(void) __asm__("_ZNSt8_Rb_treeIP13uniformconfigS1_St9_IdentityIS1_ESt4lessIS1_ESaIS1_EE5eraseERKS1_");
uintptr_t ef2_compat_fn_0218(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0219(void) __asm__("_ZNSt8_Rb_treeIP13uniformconfigS1_St9_IdentityIS1_ESt4lessIS1_ESaIS1_EE8_M_eraseEPSt13_Rb_tree_nodeIS1_E");
uintptr_t ef2_compat_fn_0219(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0220(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE13_Rb_tree_implIS7_Lb1EEC1Ev");
uintptr_t ef2_compat_fn_0220(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0221(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE13_Rb_tree_implIS7_Lb1EEC2Ev");
uintptr_t ef2_compat_fn_0221(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0222(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E");
uintptr_t ef2_compat_fn_0222(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0223(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_");
uintptr_t ef2_compat_fn_0223(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0224(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOSsEESE_IJEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_");
uintptr_t ef2_compat_fn_0224(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0225(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE24_M_get_insert_unique_posERS1_");
uintptr_t ef2_compat_fn_0225(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0226(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS1_");
uintptr_t ef2_compat_fn_0226(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0227(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE4findERS1_");
uintptr_t ef2_compat_fn_0227(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0228(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE7_M_copyEPKSt13_Rb_tree_nodeIS3_EPSB_");
uintptr_t ef2_compat_fn_0228(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0229(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E");
uintptr_t ef2_compat_fn_0229(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0230(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP12bufferconfigESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESF_IIEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0230(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0231(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP12bufferconfigESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0231(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0232(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP12bufferconfigESt10_Select1stIS4_ESt4lessISsESaIS4_EE24_M_get_insert_unique_posERS1_");
uintptr_t ef2_compat_fn_0232(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0233(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP7uniformESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESF_IIEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0233(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0234(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP7uniformESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESF_IIEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0234(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0235(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP7uniformESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOSsEESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0235(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0236(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP7uniformESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0236(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0237(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP7uniformESt10_Select1stIS4_ESt4lessISsESaIS4_EE24_M_get_insert_unique_posERS1_");
uintptr_t ef2_compat_fn_0237(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0238(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP7uniformESt10_Select1stIS4_ESt4lessISsESaIS4_EE8_M_eraseEPSt13_Rb_tree_nodeIS4_E");
uintptr_t ef2_compat_fn_0238(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0239(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP9attributeESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESF_IIEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0239(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0240(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP9attributeESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESF_IIEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0240(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0241(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP9attributeESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOSsEESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0241(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0242(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP9attributeESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_");
uintptr_t ef2_compat_fn_0242(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0243(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP9attributeESt10_Select1stIS4_ESt4lessISsESaIS4_EE24_M_get_insert_unique_posERS1_");
uintptr_t ef2_compat_fn_0243(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0244(void) __asm__("_ZNSt8_Rb_treeISsSt4pairIKSsP9attributeESt10_Select1stIS4_ESt4lessISsESaIS4_EE8_M_eraseEPSt13_Rb_tree_nodeIS4_E");
uintptr_t ef2_compat_fn_0244(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0245(void) __asm__("_ZNSt8_Rb_treeIiSt4pairIKi17RendererInterfaceESt10_Select1stIS3_ESt4lessIiESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_");
uintptr_t ef2_compat_fn_0245(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0246(void) __asm__("_ZNSt8_Rb_treeIiSt4pairIKi17RendererInterfaceESt10_Select1stIS3_ESt4lessIiESaIS3_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESE_IJEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_");
uintptr_t ef2_compat_fn_0246(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0247(void) __asm__("_ZNSt8_Rb_treeIiSt4pairIKi17RendererInterfaceESt10_Select1stIS3_ESt4lessIiESaIS3_EE24_M_get_insert_unique_posERS1_");
uintptr_t ef2_compat_fn_0247(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0248(void) __asm__("_ZNSt8_Rb_treeIiSt4pairIKi17RendererInterfaceESt10_Select1stIS3_ESt4lessIiESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E");
uintptr_t ef2_compat_fn_0248(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0249(void) __asm__("_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_");
uintptr_t ef2_compat_fn_0249(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0250(void) __asm__("_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_");
uintptr_t ef2_compat_fn_0250(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0251(void) __asm__("_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_S7_");
uintptr_t ef2_compat_fn_0251(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0252(void) __asm__("_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_");
uintptr_t ef2_compat_fn_0252(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0258(void) __asm__("__aeabi_idiv");
uintptr_t ef2_compat_fn_0258(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0259(void) __asm__("__aeabi_idiv0");
uintptr_t ef2_compat_fn_0259(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0261(void) __asm__("__aeabi_ldiv0");
uintptr_t ef2_compat_fn_0261(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0266(void) __asm__("__aeabi_unwind_cpp_pr2");
uintptr_t ef2_compat_fn_0266(void) { return ef2_compat_ret0(); }
EF2_COMPAT_WEAK_EXPORT uintptr_t ef2_compat_fn_0267(void) __asm__("__divsi3");
uintptr_t ef2_compat_fn_0267(void) { return ef2_compat_ret0(); }
#endif