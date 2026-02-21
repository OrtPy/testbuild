// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: jni  Functions: 10

//----- (0000B1A8) --------------------------------------------------------
int __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_init(JNIEnv *a1, int a2, void *a3, _DWORD *a4)
{
  _DWORD *v6; // r4
  ef2_AAssetManager *v7; // r6
  renderer *v8; // r5

  v6 = std::map<int,RendererInterface>::operator[](&dword_18860, &dword_18878, (int)a3, a4);
  v7 = ef2_AAssetManager_fromJava(a1, a3);
  if ( !*((_BYTE *)v6 + 4) )
  {
    *((_BYTE *)v6 + 4) = 1;
    v8 = (renderer *)operator new(0x60u);
    renderer::renderer(v8);
    *v6 = v8;
    renderer::init(v8, v7);
  }
  return dword_18878++;
}
// 18860: using guessed type _DWORD dword_18860;
// 18878: using guessed type int dword_18878;


//----- (0000B1F8) --------------------------------------------------------
void __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_render(
        JNIEnv *a1,
        int a2,
        int a3,
        _DWORD *a4)
{
  render **v6; // r5
  ef2_AAssetManager *v7; // r0
  int v8; // [sp+4h] [bp-4h] BYREF

  v8 = a3;
  v6 = (render **)std::map<int,RendererInterface>::operator[](&dword_18860, &v8, a3, a4);
  v7 = ef2_AAssetManager_fromJava(a1, a4);
  renderer::render(*v6, v7);
}
// 18860: using guessed type _DWORD dword_18860;


//----- (0000B228) --------------------------------------------------------
void __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_requestColors(
        JNIEnv *a1,
        int a2,
        int a3,
        _DWORD *a4,
        int a5)
{
  _DWORD *v7; // r5
  ef2_AAssetManager *v8; // r0
  int v9; // [sp+4h] [bp-4h] BYREF

  v9 = a3;
  v7 = std::map<int,RendererInterface>::operator[](&dword_18860, &v9, a3, a4);
  v8 = ef2_AAssetManager_fromJava(a1, a4);
  Curve::requestColors(*(Curve **)(*v7 + 92), v8, a5);
}
// 18860: using guessed type _DWORD dword_18860;


//----- (0000B25C) --------------------------------------------------------
_DWORD *__fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_updateScreenLayout(
        int a1,
        int a2,
        int a3,
        _DWORD *a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9)
{
  _DWORD *v10; // r0
  int v12; // [sp+14h] [bp-4h] BYREF

  v12 = a3;
  v10 = std::map<int,RendererInterface>::operator[](&dword_18860, &v12, a3, a4);
  return Curve::updateScreenLayout(*(_DWORD **)(*v10 + 92), (int)a4, a5, a6, a7, a8, a9);
}
// 18860: using guessed type _DWORD dword_18860;


//----- (0000B294) --------------------------------------------------------
int __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touchDown(
        int a1,
        int a2,
        int a3,
        _DWORD *a4,
        float a5)
{
  _DWORD *v6; // r0
  int v8; // [sp+4h] [bp-4h] BYREF

  v8 = a3;
  v6 = std::map<int,RendererInterface>::operator[](&dword_18860, &v8, a3, a4);
  return Curve::touchDown(*(Curve **)(*v6 + 92), (int)a4, a5);
}
// 18860: using guessed type _DWORD dword_18860;


//----- (0000B2BC) --------------------------------------------------------
int __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touch(
        int a1,
        int a2,
        int a3,
        _DWORD *a4,
        float a5)
{
  double v6; // r0
  int v8; // [sp+4h] [bp-4h] BYREF

  v8 = a3;
  v6 = COERCE_DOUBLE(
         __PAIR64__(
           (unsigned int)a4,
           (unsigned int)std::map<int,RendererInterface>::operator[](&dword_18860, &v8, a3, a4)));
  LODWORD(v6) = *(_DWORD *)(*(_DWORD *)LODWORD(v6) + 92);
  return Curve::touch(v6, a5);
}
// 18860: using guessed type _DWORD dword_18860;


//----- (0000B2E4) --------------------------------------------------------
int __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_touchUp(
        int a1,
        int a2,
        int a3,
        _DWORD *a4,
        float a5)
{
  double v6; // r0
  int v8; // [sp+4h] [bp-4h] BYREF

  v8 = a3;
  v6 = COERCE_DOUBLE(
         __PAIR64__(
           (unsigned int)a4,
           (unsigned int)std::map<int,RendererInterface>::operator[](&dword_18860, &v8, a3, a4)));
  LODWORD(v6) = *(_DWORD *)(*(_DWORD *)LODWORD(v6) + 92);
  return Curve::touchUp(v6, a5);
}
// 18860: using guessed type _DWORD dword_18860;


//----- (0000B30C) --------------------------------------------------------
int __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_activate(int a1, int a2, int a3, _DWORD *a4)
{
  _DWORD *v4; // r0
  _DWORD v6[2]; // [sp+4h] [bp-8h] BYREF

  v6[1] = a3;
  v6[0] = a3;
  v4 = std::map<int,RendererInterface>::operator[](&dword_18860, v6, a3, a4);
  return Curve::activate(*(_DWORD *)(*v4 + 92));
}
// 18860: using guessed type _DWORD dword_18860;


//----- (0000B330) --------------------------------------------------------
int __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_deactivate(int a1, int a2, int a3, _DWORD *a4)
{
  _DWORD *v4; // r0
  _DWORD v6[2]; // [sp+4h] [bp-8h] BYREF

  v6[1] = a3;
  v6[0] = a3;
  v4 = std::map<int,RendererInterface>::operator[](&dword_18860, v6, a3, a4);
  return Curve::deactivate(*(_DWORD *)(*v4 + 92));
}
// 18860: using guessed type _DWORD dword_18860;


//----- (0000B354) --------------------------------------------------------
int __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_getSleepRecommendation(
        int a1,
        int a2,
        int a3,
        _DWORD *a4)
{
  _DWORD *v4; // r0
  _DWORD v6[2]; // [sp+4h] [bp-8h] BYREF

  v6[1] = a3;
  v6[0] = a3;
  v4 = std::map<int,RendererInterface>::operator[](&dword_18860, v6, a3, a4);
  return Curve::getSleepRecommendation(*(Curve **)(*v4 + 92));
}
// 18860: using guessed type _DWORD dword_18860;


