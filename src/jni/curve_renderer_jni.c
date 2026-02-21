#include <jni.h>
#include <android/asset_manager_jni.h>

#include "ef2/renderer.h"

#include <stdlib.h>
#include <string.h>

// This JNI layer mirrors the original design:
// - init(AssetManager) returns an integer "handle" (id)
// - subsequent calls take that id as the first argument.

typedef struct ef2_JniSlot {
  int id;
  ef2_Renderer* r;
} ef2_JniSlot;

static ef2_JniSlot* g_slots = NULL;
static size_t g_slots_count = 0;
static size_t g_slots_cap = 0;
// NOTE (static analysis of the 95KB liblwplocal.so):
// CurveRenderer.init() returns the pre-increment value of a counter stored in a
// global struct (offset +0x18). That counter is 0-based, so id==0 is valid.
static int g_next_id = 0;

static ef2_Renderer* slot_get(int id)
{
  if (id < 0) return NULL;
  {
    size_t i;
    for (i = 0; i < g_slots_count; ++i) {
      if (g_slots[i].id == id) return g_slots[i].r;
    }
  }
  return NULL;
}

static int slot_put(ef2_Renderer* r)
{
  if (!r) return -1;
  if (g_slots_count == g_slots_cap) {
    size_t ncap = (g_slots_cap == 0) ? 8 : g_slots_cap * 2;
    ef2_JniSlot* ns = (ef2_JniSlot*)realloc(g_slots, ncap * sizeof(*ns));
    if (!ns) return -1;
    g_slots = ns;
    g_slots_cap = ncap;
  }
  int id = g_next_id++;
  // Avoid compound literals (keep compatibility with older C modes).
  g_slots[g_slots_count].id = id;
  g_slots[g_slots_count].r = r;
  g_slots_count++;
  return id;
}

JNIEXPORT jint JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_init(JNIEnv* env, jobject thiz, jobject assetManager)
{
  (void)env; (void)thiz;

  AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);

  ef2_Renderer* r = (ef2_Renderer*)malloc(sizeof(*r));
  if (r) memset(r, 0, sizeof(*r));
  if (!r) return -1;

  ef2_Renderer_init(r, mgr);

  int id = slot_put(r);
  if (id < 0) {
    ef2_Renderer_deinit(r);
    free(r);
    return -1;
  }
  return (jint)id;
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_render(JNIEnv* env, jobject thiz, jint id, jobject assetManager)
{
  (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return;

  AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
  ef2_Renderer_render(r, mgr);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_requestColors(JNIEnv* env, jobject thiz, jint id, jobject assetManager, jint themeId)
{
  (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return;

  AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
  ef2_Renderer_requestColors(r, mgr, (int)themeId);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_updateScreenLayout(JNIEnv* env, jobject thiz,
                                                                            jint id,
                                                                            jint x, jint y, jint w, jint h,
                                                                            jint screenW, jint screenH)
{
  (void)env; (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return;
  ef2_Renderer_updateScreenLayout(r, (int)x, (int)y, (int)w, (int)h, (int)screenW, (int)screenH);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touchDown(JNIEnv* env, jobject thiz, jint id, jfloat x, jfloat y)
{
  (void)env; (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return;
  ef2_Renderer_touchDown(r, (float)x, (float)y);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touch(JNIEnv* env, jobject thiz, jint id, jfloat x, jfloat y)
{
  (void)env; (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return;
  ef2_Renderer_touch(r, (float)x, (float)y);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touchUp(JNIEnv* env, jobject thiz, jint id, jfloat x, jfloat y)
{
  (void)env; (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return;
  ef2_Renderer_touchUp(r, (float)x, (float)y);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_activate(JNIEnv* env, jobject thiz, jint id)
{
  (void)env; (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return;
  ef2_Renderer_activate(r);
}

JNIEXPORT void JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_deactivate(JNIEnv* env, jobject thiz, jint id)
{
  (void)env; (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return;
  ef2_Renderer_deactivate(r);
}

JNIEXPORT jint JNICALL
Java_com_sonymobile_experienceflow_renderer_CurveRenderer_getSleepRecommendation(JNIEnv* env, jobject thiz, jint id)
{
  (void)env; (void)thiz;
  ef2_Renderer* r = slot_get((int)id);
  if (!r) return 0;
  return (jint)ef2_Renderer_getSleepRecommendation(r);
}

// NOTE: The original app doesn't expose a native "destroy" call.
// If you add one on the Java side, you can wire it to free native state here.
