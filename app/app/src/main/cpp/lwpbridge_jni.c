#include <jni.h>
#include <dlfcn.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>

#include "elf_exports.h"

#define TAG "lwpbridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)

// Implemented in ffi_call_arm32.S
extern uint64_t ffi_call_words(void *fn, const uint32_t *args, int argc_words);

// Keep the last dlopen/dlsym error message.
// dlerror() is "consuming", so we cache it here for RPC responses.
static char g_last_dlerror[1024] = {0};
static void set_last_dlerror(const char *e) {
    if (!e) { g_last_dlerror[0] = 0; return; }
    size_t n = strlen(e);
    if (n >= sizeof(g_last_dlerror)) n = sizeof(g_last_dlerror) - 1;
    memcpy(g_last_dlerror, e, n);
    g_last_dlerror[n] = 0;
}

static jstring jstr(JNIEnv *env, const char *s) {
    if (!s) s = "";
    return (*env)->NewStringUTF(env, s);
}

JNIEXPORT jlong JNICALL
Java_com_example_lwprpcharness_NativeBridge_dlopen(JNIEnv *env, jclass clazz, jstring jpath, jint flags) {
    (void)clazz;
    const char *path = (*env)->GetStringUTFChars(env, jpath, NULL);

    int f = (int)flags;
    LOGI("dlopen req: flags=%d (0x%x) path=%s", f, (unsigned)f, path ? path : "(null)");

    dlerror();
    void *h = dlopen(path, f);
    const char *err = dlerror();

    // Workaround #1:
    // Some clients historically used "RTLD_GLOBAL=100" (0x64) by mistake,
    // producing flags like 0x64 or 0x66, which bionic rejects as "invalid flags".
    // If we detect this, normalize 0x64 -> 0x100 and retry once.
    if (!h && err && strstr(err, "invalid flags") != NULL) {
        if ((f & 0x64) != 0 && (f & 0x100) == 0) {
            int f2 = (f & ~0x64) | 0x100;
            LOGW("dlopen retry: normalize legacy flags %d (0x%x) -> %d (0x%x)", f, (unsigned)f, f2, (unsigned)f2);
            dlerror();
            h = dlopen(path, f2);
            err = dlerror();
            // Keep f in sync for later fallback logic
            f = f2;
        }
    }

    // Workaround #2:
    // Some Android builds (or namespaces) reject certain flag combinations.
    // If the first attempt still fails with "invalid flags", retry with a conservative
    // subset (drop RTLD_GLOBAL and any unknown bits), finally falling back to RTLD_NOW.
    if (!h && err && strstr(err, "invalid flags") != NULL) {
        int f3 = f;
        // Drop common problematic bits first.
        f3 &= ~(0x100 | 0x64); // RTLD_GLOBAL (0x100) and legacy wrong-global (0x64)
        // Keep only known-safe bits.
        f3 &= (RTLD_LAZY | RTLD_NOW | RTLD_NOLOAD | RTLD_NODELETE | RTLD_LOCAL);
        // Ensure we have a binding mode.
        if ((f3 & (RTLD_LAZY | RTLD_NOW)) == 0) f3 |= RTLD_NOW;
        if (f3 != f) {
            LOGW("dlopen retry: conservative flags %d (0x%x) -> %d (0x%x)", f, (unsigned)f, f3, (unsigned)f3);
            dlerror();
            h = dlopen(path, f3);
            err = dlerror();
        }
        if (!h && err && strstr(err, "invalid flags") != NULL && f3 != RTLD_NOW) {
            LOGW("dlopen retry: last resort RTLD_NOW (%d)", RTLD_NOW);
            dlerror();
            h = dlopen(path, RTLD_NOW);
            err = dlerror();
        }
    }

    set_last_dlerror(err);
    if (!h) {
        LOGW("dlopen failed: %s (%s)", path, err ? err : "");
    } else {
        LOGI("dlopen ok: %s -> %p", path, h);
    }
    (*env)->ReleaseStringUTFChars(env, jpath, path);
    return (jlong)(uintptr_t)h;
}

JNIEXPORT void JNICALL
Java_com_example_lwprpcharness_NativeBridge_dlclose(JNIEnv *env, jclass clazz, jlong handle) {
    (void)env; (void)clazz;
    void *h = (void *)(uintptr_t)handle;
    if (h) {
        dlclose(h);
        LOGI("dlclose %p", h);
    }
}

JNIEXPORT jlong JNICALL
Java_com_example_lwprpcharness_NativeBridge_dlsym(JNIEnv *env, jclass clazz, jlong handle, jstring jname) {
    (void)clazz;
    void *h = (void *)(uintptr_t)handle;
    const char *name = (*env)->GetStringUTFChars(env, jname, NULL);
    dlerror();
    void *p = dlsym(h, name);
    const char *err = dlerror();
    set_last_dlerror(err);
    if (!p) {
        LOGW("dlsym failed: %s (%s)", name, err ? err : "");
    }
    (*env)->ReleaseStringUTFChars(env, jname, name);
    return (jlong)(uintptr_t)p;
}

JNIEXPORT jstring JNICALL
Java_com_example_lwprpcharness_NativeBridge_dlerrorString(JNIEnv *env, jclass clazz) {
    (void)clazz;
    return jstr(env, g_last_dlerror);
}


JNIEXPORT jobjectArray JNICALL
Java_com_example_lwprpcharness_NativeBridge_dladdr(JNIEnv *env, jclass clazz, jlong addr) {
    (void)clazz;
    jclass stringClass = (*env)->FindClass(env, "java/lang/String");
    if (!addr) {
        return (*env)->NewObjectArray(env, 0, stringClass, NULL);
    }
    Dl_info info;
    memset(&info, 0, sizeof(info));
    int ok = dladdr((void *)(uintptr_t)addr, &info);
    if (!ok) {
        return (*env)->NewObjectArray(env, 0, stringClass, NULL);
    }
    jobjectArray arr = (*env)->NewObjectArray(env, 4, stringClass, NULL);

    char fbase_hex[32];
    char saddr_hex[32];
    snprintf(fbase_hex, sizeof(fbase_hex), "0x%lx", (unsigned long)(uintptr_t)info.dli_fbase);
    snprintf(saddr_hex, sizeof(saddr_hex), "0x%lx", (unsigned long)(uintptr_t)info.dli_saddr);

    (*env)->SetObjectArrayElement(env, arr, 0, jstr(env, info.dli_fname ? info.dli_fname : ""));
    (*env)->SetObjectArrayElement(env, arr, 1, jstr(env, info.dli_sname ? info.dli_sname : ""));
    (*env)->SetObjectArrayElement(env, arr, 2, jstr(env, fbase_hex));
    (*env)->SetObjectArrayElement(env, arr, 3, jstr(env, saddr_hex));
    return arr;
}

JNIEXPORT jobjectArray JNICALL
Java_com_example_lwprpcharness_NativeBridge_listExports(JNIEnv *env, jclass clazz, jstring jpath, jstring jfilter) {
    (void)clazz;
    const char *path = (*env)->GetStringUTFChars(env, jpath, NULL);
    const char *filter = NULL;
    if (jfilter != NULL) {
        filter = (*env)->GetStringUTFChars(env, jfilter, NULL);
        if (filter && filter[0] == 0) filter = NULL;
    }

    char **names = NULL;
    int count = 0;
    int ok = list_exported_function_names(path, filter, &names, &count);

    jclass stringClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray arr = (*env)->NewObjectArray(env, ok ? count : 0, stringClass, NULL);

    for (int i = 0; i < count; i++) {
        (*env)->SetObjectArrayElement(env, arr, i, jstr(env, names[i]));
    }

    free_string_list(names, count);

    if (jfilter != NULL) {
        (*env)->ReleaseStringUTFChars(env, jfilter, filter ? filter : "");
    }
    (*env)->ReleaseStringUTFChars(env, jpath, path);
    return arr;
}

JNIEXPORT jlongArray JNICALL
Java_com_example_lwprpcharness_NativeBridge_callWords(JNIEnv *env, jclass clazz, jlong fnPtr, jintArray jargs) {
    (void)clazz;
    void *fn = (void *)(uintptr_t)fnPtr;
    jsize n = jargs ? (*env)->GetArrayLength(env, jargs) : 0;

    uint32_t *buf = NULL;
    if (n > 0) {
        buf = (uint32_t *)calloc((size_t)n, sizeof(uint32_t));
        jint *tmp = (*env)->GetIntArrayElements(env, jargs, NULL);
        for (int i = 0; i < n; i++) buf[i] = (uint32_t)tmp[i];
        (*env)->ReleaseIntArrayElements(env, jargs, tmp, JNI_ABORT);
    }

    uint64_t ret = ffi_call_words(fn, buf, (int)n);
    free(buf);

    jlongArray out = (*env)->NewLongArray(env, 2);
    jlong vals[2];
    vals[0] = (jlong)(uint32_t)(ret & 0xFFFFFFFFu);
    vals[1] = (jlong)(uint32_t)((ret >> 32) & 0xFFFFFFFFu);
    (*env)->SetLongArrayRegion(env, out, 0, 2, vals);
    return out;
}

JNIEXPORT jlong JNICALL
Java_com_example_lwprpcharness_NativeBridge_malloc(JNIEnv *env, jclass clazz, jint size) {
    (void)env; (void)clazz;
    void *p = malloc((size_t)size);
    return (jlong)(uintptr_t)p;
}

JNIEXPORT void JNICALL
Java_com_example_lwprpcharness_NativeBridge_free(JNIEnv *env, jclass clazz, jlong ptr) {
    (void)env; (void)clazz;
    void *p = (void *)(uintptr_t)ptr;
    free(p);
}

JNIEXPORT jboolean JNICALL
Java_com_example_lwprpcharness_NativeBridge_writeMem(JNIEnv *env, jclass clazz, jlong ptr, jbyteArray jdata) {
    (void)clazz;
    if (!ptr || !jdata) return JNI_FALSE;
    void *p = (void *)(uintptr_t)ptr;
    jsize n = (*env)->GetArrayLength(env, jdata);
    jbyte *b = (*env)->GetByteArrayElements(env, jdata, NULL);
    memcpy(p, b, (size_t)n);
    (*env)->ReleaseByteArrayElements(env, jdata, b, JNI_ABORT);
    return JNI_TRUE;
}

JNIEXPORT jbyteArray JNICALL
Java_com_example_lwprpcharness_NativeBridge_readMem(JNIEnv *env, jclass clazz, jlong ptr, jint size) {
    (void)clazz;
    if (!ptr || size <= 0) {
        return (*env)->NewByteArray(env, 0);
    }
    void *p = (void *)(uintptr_t)ptr;
    jbyteArray out = (*env)->NewByteArray(env, size);
    (*env)->SetByteArrayRegion(env, out, 0, size, (const jbyte *)p);
    return out;
}
