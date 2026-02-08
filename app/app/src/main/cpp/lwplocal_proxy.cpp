#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#include <string>

#define TAG "lwplocal_proxy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

// ---
// Proxy strategy
//  - This library (built as liblwplocal_proxy.so) provides the same JNI entrypoints.
//  - It forwards to the original Sony library packaged as liblwplocal.so.
//  - The original is located in the same directory as this .so, so we derive the path via dladdr().
//  - We log every call (args + basic result) and never crash on missing symbols.
// ---

namespace {

struct Api {
    void* h = nullptr;

    using FnInit = jint (*)(JNIEnv*, jobject, jobject);
    using FnActivate = void (*)(JNIEnv*, jobject, jint);
    using FnDeactivate = void (*)(JNIEnv*, jobject, jint);
    using FnRequestColors = void (*)(JNIEnv*, jobject, jint, jobject, jint);
    using FnUpdateScreenLayout = void (*)(JNIEnv*, jobject, jint, jint, jint, jint, jint, jint, jint);
    using FnRender = void (*)(JNIEnv*, jobject, jint, jobject);
    using FnTouch = void (*)(JNIEnv*, jobject, jint, jfloat, jfloat);
    using FnGetSleep = jint (*)(JNIEnv*, jobject, jint);

    FnInit init = nullptr;
    FnActivate activate = nullptr;
    FnDeactivate deactivate = nullptr;
    FnRequestColors requestColors = nullptr;
    FnUpdateScreenLayout updateScreenLayout = nullptr;
    FnRender render = nullptr;
    FnTouch touchDown = nullptr;
    FnTouch touch = nullptr;
    FnTouch touchUp = nullptr;
    FnGetSleep getSleepRecommendation = nullptr;

    const char* last_error = nullptr;
};

static Api g_api;
static pthread_mutex_t g_mu = PTHREAD_MUTEX_INITIALIZER;

static std::string dirname_of(const char* path) {
    if (!path) return std::string();
    std::string s(path);
    auto pos = s.find_last_of('/');
    if (pos == std::string::npos) return std::string();
    return s.substr(0, pos);
}

static std::string self_path() {
    Dl_info info{};
    if (dladdr((void*)&self_path, &info) && info.dli_fname) {
        return std::string(info.dli_fname);
    }
    return std::string();
}


static std::string read_file_trim(const char* path) {
    int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) return std::string();
    char buf[4096];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (n <= 0) return std::string();
    buf[n] = 0;
    std::string s(buf);
    // trim whitespace/newlines
    while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == ' ' || s.back() == '\t')) s.pop_back();
    size_t i = 0;
    while (i < s.size() && (s[i] == '\n' || s[i] == '\r' || s[i] == ' ' || s[i] == '\t')) i++;
    if (i > 0) s = s.substr(i);
    return s;
}

static std::string self_pkgname() {
    // Read /proc/self/cmdline => first NUL-terminated string is the process name.
    int fd = open("/proc/self/cmdline", O_RDONLY | O_CLOEXEC);
    if (fd < 0) return std::string();
    char buf[512];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (n <= 0) return std::string();
    buf[n] = 0;
    // cmdline is NUL-separated; take first segment.
    std::string s(buf);
    // Strip process suffix like "com.example.app:worker"
    size_t pos = s.find(':');
    if (pos != std::string::npos) s = s.substr(0, pos);
    return s;
}

static std::string real_path_file() {
    const std::string pkg = self_pkgname();
    if (pkg.empty()) return std::string();
    // App private filesDir path is predictable on most Android builds.
    // (We are running in the app process, so this should be readable.)
    return std::string("/data/data/") + pkg + "/files/lwplocal_real_path.txt";
}

static std::string orig_path() {
    // 1) If a real-path override file exists, prefer it.
    const std::string f = real_path_file();
    if (!f.empty()) {
        const std::string p = read_file_trim(f.c_str());
        if (!p.empty()) {
            struct stat st{};
            if (stat(p.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
                LOGI("orig_path override: %s -> %s", f.c_str(), p.c_str());
                return p;
            } else {
                LOGW("orig_path override invalid: %s -> %s (errno=%d)", f.c_str(), p.c_str(), errno);
            }
        }
    }

    // 2) Default: sibling liblwplocal.so next to this proxy.
    const std::string self = self_path();
    const std::string dir = dirname_of(self.c_str());
    if (!dir.empty()) {
        const std::string p = dir + "/liblwplocal.so";
        LOGI("orig_path default: %s", p.c_str());
        return p;
    }

    // 3) Last resort: rely on loader search path.
    LOGW("orig_path fallback by name");
    return std::string("liblwplocal.so");
}

static void set_last_error(Api& api, const char* e) {
    api.last_error = e;
}

static void* sym(Api& api, const char* name) {
    dlerror();
    void* p = dlsym(api.h, name);
    const char* e = dlerror();
    set_last_error(api, e);
    if (!p) {
        LOGW("dlsym failed: %s (%s)", name, e ? e : "");
    }
    return p;
}

static bool ensure_loaded_locked(Api& api) {
    if (api.h) return true;

    // Preload legacy STL if present (some Sony builds depend on it).
    {
        const std::string self = self_path();
        const std::string dir = dirname_of(self.c_str());
        if (!dir.empty()) {
            const std::string gn = dir + "/libgnustl_shared.so";
            dlerror();
            void* hg = dlopen(gn.c_str(), RTLD_NOW | RTLD_GLOBAL);
            const char* eg = dlerror();
            if (hg) {
                LOGI("preload ok: %s -> %p", gn.c_str(), hg);
            } else {
                LOGW("preload skipped: %s (%s)", gn.c_str(), eg ? eg : "");
            }
        }
    }

    const std::string path = orig_path();
    dlerror();
    api.h = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
    const char* e = dlerror();
    set_last_error(api, e);

    if (!api.h) {
        LOGE("dlopen orig failed: %s (%s)", path.c_str(), e ? e : "");
        return false;
    }

    LOGI("dlopen orig ok: %s -> %p", path.c_str(), api.h);

    api.init = (Api::FnInit)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_init");
    api.activate = (Api::FnActivate)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_activate");
    api.deactivate = (Api::FnDeactivate)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_deactivate");
    api.requestColors = (Api::FnRequestColors)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_requestColors");
    api.updateScreenLayout = (Api::FnUpdateScreenLayout)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_updateScreenLayout");
    api.render = (Api::FnRender)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_render");
    api.touchDown = (Api::FnTouch)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touchDown");
    api.touch = (Api::FnTouch)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touch");
    api.touchUp = (Api::FnTouch)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touchUp");
    api.getSleepRecommendation = (Api::FnGetSleep)sym(api, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_getSleepRecommendation");

    // Even if some symbols are missing, keep the handle open. We guard every call.
    return true;
}

static Api snapshot_api() {
    pthread_mutex_lock(&g_mu);
    ensure_loaded_locked(g_api);
    Api api = g_api;
    pthread_mutex_unlock(&g_mu);
    return api;
}

static const char* safe_err(const Api& api) {
    return api.last_error ? api.last_error : "";
}

} // namespace

extern "C" {

JNIEXPORT jint JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_init(JNIEnv* env, jobject thiz, jobject assetManager) {
    Api api = snapshot_api();
    LOGI("init(am=%p)", assetManager);
    if (!api.init) {
        LOGE("init: missing symbol (%s)", safe_err(api));
        return -1;
    }
    jint ret = api.init(env, thiz, assetManager);
    LOGI("init -> %d", (int)ret);
    return ret;
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_activate(JNIEnv* env, jobject thiz, jint id) {
    Api api = snapshot_api();
    LOGI("activate(id=%d)", (int)id);
    if (!api.activate) {
        LOGE("activate: missing symbol (%s)", safe_err(api));
        return;
    }
    api.activate(env, thiz, id);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_deactivate(JNIEnv* env, jobject thiz, jint id) {
    Api api = snapshot_api();
    LOGI("deactivate(id=%d)", (int)id);
    if (!api.deactivate) {
        LOGE("deactivate: missing symbol (%s)", safe_err(api));
        return;
    }
    api.deactivate(env, thiz, id);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_requestColors(JNIEnv* env, jobject thiz, jint id, jobject assetManager, jint theme) {
    Api api = snapshot_api();
    LOGI("requestColors(id=%d, am=%p, theme=%d)", (int)id, assetManager, (int)theme);
    if (!api.requestColors) {
        LOGE("requestColors: missing symbol (%s)", safe_err(api));
        return;
    }
    api.requestColors(env, thiz, id, assetManager, theme);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_updateScreenLayout(JNIEnv* env, jobject thiz,
                                                                             jint id, jint x, jint y, jint w, jint h, jint sw, jint sh) {
    Api api = snapshot_api();
    LOGI("updateScreenLayout(id=%d, x=%d, y=%d, w=%d, h=%d, sw=%d, sh=%d)",
         (int)id, (int)x, (int)y, (int)w, (int)h, (int)sw, (int)sh);
    if (!api.updateScreenLayout) {
        LOGE("updateScreenLayout: missing symbol (%s)", safe_err(api));
        return;
    }
    api.updateScreenLayout(env, thiz, id, x, y, w, h, sw, sh);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_render(JNIEnv* env, jobject thiz, jint id, jobject assetManager) {
    Api api = snapshot_api();
    LOGI("render(id=%d, am=%p)", (int)id, assetManager);
    if (!api.render) {
        LOGE("render: missing symbol (%s)", safe_err(api));
        return;
    }
    api.render(env, thiz, id, assetManager);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touchDown(JNIEnv* env, jobject thiz, jint id, jfloat x, jfloat y) {
    Api api = snapshot_api();
    LOGI("touchDown(id=%d, x=%f, y=%f)", (int)id, (double)x, (double)y);
    if (!api.touchDown) {
        LOGE("touchDown: missing symbol (%s)", safe_err(api));
        return;
    }
    api.touchDown(env, thiz, id, x, y);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touch(JNIEnv* env, jobject thiz, jint id, jfloat x, jfloat y) {
    Api api = snapshot_api();
    LOGI("touch(id=%d, x=%f, y=%f)", (int)id, (double)x, (double)y);
    if (!api.touch) {
        LOGE("touch: missing symbol (%s)", safe_err(api));
        return;
    }
    api.touch(env, thiz, id, x, y);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touchUp(JNIEnv* env, jobject thiz, jint id, jfloat x, jfloat y) {
    Api api = snapshot_api();
    LOGI("touchUp(id=%d, x=%f, y=%f)", (int)id, (double)x, (double)y);
    if (!api.touchUp) {
        LOGE("touchUp: missing symbol (%s)", safe_err(api));
        return;
    }
    api.touchUp(env, thiz, id, x, y);
}

JNIEXPORT jint JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_getSleepRecommendation(JNIEnv* env, jobject thiz, jint id) {
    Api api = snapshot_api();
    LOGI("getSleepRecommendation(id=%d)", (int)id);
    if (!api.getSleepRecommendation) {
        LOGE("getSleepRecommendation: missing symbol (%s)", safe_err(api));
        return -1;
    }
    jint ret = api.getSleepRecommendation(env, thiz, id);
    LOGI("getSleepRecommendation -> %d", (int)ret);
    return ret;
}

} // extern "C"

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
    __android_log_print(ANDROID_LOG_INFO, "lwplocal_proxy", "JNI_OnLoad: lwplocal_proxy loaded");
    return JNI_VERSION_1_6;
}
