// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: Curve  Functions: 9

//----- (00011BA2) --------------------------------------------------------
_DWORD *__fastcall Curve::updateScreenLayout(_DWORD *this, int a2, int a3, int a4, int a5, int a6, int a7)
{
  *(_DWORD *)(*(this + 2) + 4) = a2;
  *(_DWORD *)(*(this + 2) + 8) = a3;
  *(_DWORD *)(*(this + 2) + 12) = a4;
  *(_DWORD *)(*(this + 2) + 16) = a5;
  *(this + 81) = a6;
  *(this + 82) = a7;
  return this;
}


//----- (00011BC4) --------------------------------------------------------
int __fastcall Curve::touchDown(Curve *this, int a2, float a3)
{
  int v3; // r3
  const timespec *v5; // r0
  int v6; // r4
  double v7; // r0
  int v8; // r3

  v3 = *((_DWORD *)this + 2);
  v5 = (Curve *)((char *)this + 184);
  *(_QWORD *)(v3 + 56) = 0;
  *(_QWORD *)(*((_DWORD *)v5 - 44) + 64) = 0;
  *(double *)(*((_DWORD *)v5 - 44) + 40) = (float)(*(float *)&a2 + (float)*(int *)(*((_DWORD *)v5 - 44) + 4));
  *(double *)(*((_DWORD *)v5 - 44) + 48) = (float)(a3 + (float)*(int *)(*((_DWORD *)v5 - 44) + 8));
  v6 = *((_DWORD *)v5 - 44);
  v7 = timesince(v5, a2);
  *(double *)(v6 + 32) = v7;
  *(_QWORD *)(*((_DWORD *)this + 2) + 24) = *(_QWORD *)(*((_DWORD *)this + 2) + 32);
  v8 = *((_DWORD *)this + 2);
  if ( !*(_BYTE *)(v8 + 80) )
    ++*((_DWORD *)this + 80);
  *(_BYTE *)(v8 + 80) = 1;
  return LODWORD(v7);
}


//----- (00011C48) --------------------------------------------------------
int __fastcall Curve::touch(double this, float a2)
{
  int v2; // r3
  int v3; // r4
  int v4; // r3
  double v5; // d7
  double v6; // d5
  double v7; // d6
  int v8; // r2
  double v9; // d5

  v2 = *(_DWORD *)(LODWORD(this) + 8);
  v3 = LODWORD(this);
  if ( *(_BYTE *)(v2 + 80) )
  {
    LODWORD(this) += 184;
    *(double *)(v2 + 56) = *(double *)(v2 + 40) - *((float *)&this + 1) - (double)*(int *)(v2 + 4);
    *(double *)(*(_DWORD *)(LODWORD(this) - 176) + 64) = *(double *)(*(_DWORD *)(LODWORD(this) - 176) + 48)
                                                       - a2
                                                       - (double)*(int *)(*(_DWORD *)(LODWORD(this) - 176) + 8);
    *(double *)(*(_DWORD *)(LODWORD(this) - 176) + 40) = (float)(*((float *)&this + 1)
                                                               + (float)*(int *)(*(_DWORD *)(LODWORD(this) - 176) + 4));
    *(double *)(*(_DWORD *)(LODWORD(this) - 176) + 48) = (float)(a2
                                                               + (float)*(int *)(*(_DWORD *)(LODWORD(this) - 176) + 8));
    this = timesince((const timespec *)LODWORD(this), SHIDWORD(this));
    *(double *)(*(_DWORD *)(v3 + 8) + 24) = this;
    v4 = *(_DWORD *)(v3 + 8);
    v5 = *(double *)(v4 + 56);
    v6 = v5 >= 0.0 ? *(double *)(v4 + 56) : -v5;
    if ( v6 <= 4000.0 )
    {
      v7 = *(double *)(v4 + 64);
      if ( v7 < 0.0 )
        v7 = -v7;
      if ( v7 <= 4000.0 )
      {
        v8 = *(_DWORD *)(v3 + 200);
        *(double *)(v3 + 208) = *(double *)(v3 + 208) + v5 / 320.0;
        if ( (v8 & 1) != 0 )
          v9 = 60.0;
        else
          v9 = 220.0;
        *(double *)(v3 + 216) = *(double *)(v3 + 216) + *(double *)(v4 + 64) / v9;
      }
    }
  }
  return LODWORD(this);
}


//----- (00011D80) --------------------------------------------------------
int __fastcall Curve::touchUp(double this, float a2)
{
  int v2; // r4
  int result; // r0
  int v4; // r3

  v2 = LODWORD(this);
  result = Curve::touch(this, a2);
  v4 = *(_DWORD *)(v2 + 8);
  if ( *(_BYTE *)(v4 + 80) )
    --*(_DWORD *)(v2 + 320);
  if ( *(int *)(v2 + 320) < 0 )
    *(_DWORD *)(v2 + 320) = 0;
  *(_BYTE *)(v4 + 80) = 0;
  return result;
}


//----- (00011DB0) --------------------------------------------------------
int __fastcall Curve::activate(int this)
{
  **(_BYTE **)(this + 8) = 0;
  return this;
}


//----- (00011DB8) --------------------------------------------------------
int __fastcall Curve::deactivate(int this)
{
  int v1; // r2
  int v2; // r3

  v1 = *(_DWORD *)(this + 8);
  if ( *(_BYTE *)(v1 + 80) )
  {
    v2 = *(_DWORD *)(this + 320) - 1;
    if ( v2 < 0 )
      v2 = 0;
    *(_DWORD *)(this + 320) = v2;
  }
  *(_BYTE *)(v1 + 80) = 0;
  **(_BYTE **)(this + 8) = 0;
  return this;
}


//----- (00011DE0) --------------------------------------------------------
int __fastcall Curve::getSleepRecommendation(Curve *this)
{
  return (int)(200000.0 / (*((double *)this + 39) * *((double *)this + 39) * 800.0 + 0.1));
}


//----- (00012188) --------------------------------------------------------
void __fastcall Curve::requestColors(Curve *this, ef2_AAssetManager *a2, int a3)
{
  int v6; // r0
  int v7; // r0
  _DWORD *v8; // r2
  char *v9; // r0
  int v10; // r2
  _DWORD *v11; // r1
  int v12; // [sp+0h] [bp-1Ch] BYREF
  char v13; // [sp+4h] [bp-18h] BYREF
  _DWORD *v14; // [sp+8h] [bp-14h]
  char *v15; // [sp+Ch] [bp-10h]
  char *v16; // [sp+10h] [bp-Ch]
  int v17; // [sp+14h] [bp-8h]

  v6 = std::operator<<<std::char_traits<char>>(&std::cout, "Requesting color: ");
  v7 = std::ostream::operator<<(v6, a3);
  std::endl<char,std::char_traits<char>>(v7);
  theme((ef2_AAssetManager *)&v12, a2, a3);
  std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_erase(
    (int)this + 32,
    *((_DWORD **)this + 10));
  v8 = v14;
  *((_DWORD *)this + 11) = (char *)this + 36;
  *((_DWORD *)this + 10) = 0;
  *((_DWORD *)this + 12) = (char *)this + 36;
  *((_DWORD *)this + 13) = 0;
  if ( v8 )
  {
    v9 = v15;
    *((_DWORD *)this + 10) = v8;
    *((_DWORD *)this + 11) = v9;
    *((_DWORD *)this + 12) = v16;
    v8[1] = (char *)this + 36;
    v14 = 0;
    v15 = &v13;
    v16 = &v13;
  }
  v10 = *((_DWORD *)this + 13);
  v11 = v14;
  *((_DWORD *)this + 13) = v17;
  v17 = v10;
  std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_erase(
    (int)&v12,
    v11);
}
// 7AEC: using guessed type int __fastcall std::operator<<<std::char_traits<char>>(_DWORD, _DWORD);
// 7B04: using guessed type int __fastcall std::endl<char,std::char_traits<char>>(_DWORD);
// 7C78: using guessed type int __fastcall std::ostream::operator<<(_DWORD, _DWORD);


//----- (000124F8) --------------------------------------------------------
Curve *__fastcall Curve::updateRenderer(Curve *this, int a2)
{
  int v4; // r1
  double v5; // r0
  double v6; // d5
  double v7; // d7
  float v8; // s12
  float v9; // s15
  bool v10; // zf
  int v11; // r5
  int i; // r3
  int v13; // r2
  int v14; // r6
  int v15; // r3
  double v16; // d13
  double v17; // d7
  int v18; // r3
  double v19; // d12
  double v20; // d15
  double v21; // d14
  double v22; // d0
  double v23; // d2
  double v24; // d4
  double v25; // d3
  double v26; // d6
  double v27; // d1
  double v28; // d9
  double v29; // d1
  double v30; // d4
  double v31; // d8
  double v32; // d11
  double v33; // d3
  double v34; // d8
  double v35; // d8
  double v36; // d5
  double v37; // d3
  double v38; // d5
  double v39; // d5
  double v40; // d9
  double v41; // d3
  double v42; // d5
  double v43; // d3
  double v44; // d3
  double v45; // d2
  double v46; // d3
  double v47; // d5
  double v48; // d3
  double v49; // d9
  double v50; // d10
  double v51; // d3
  double v52; // d5
  double v53; // d0
  double v54; // d7
  double v55; // d3
  double v56; // d0
  double v57; // d8
  double v58; // d0
  double v59; // d2
  double v60; // d3
  double v61; // d2
  double v62; // d8
  double v63; // d2
  double v64; // d8
  double v65; // d3
  double v66; // d8
  bool v67; // fnf
  double v68; // d0
  double v69; // d0
  double v70; // d8
  double v71; // d3
  double v72; // d8
  bool v73; // fnf
  double v74; // d2
  double v75; // d8
  double v76; // d2
  double v77; // d3
  double v78; // d8
  double v79; // d8
  double v80; // d0
  double v81; // d8
  double v82; // d3
  double v83; // d8
  double v84; // d8
  double v85; // d2
  double v86; // d3
  double v87; // d8
  double v88; // d2
  double v89; // d8
  double v90; // d8
  double v91; // d8
  double v92; // d9
  double v93; // d2
  double v94; // d9
  double v95; // d9
  double v96; // d2
  double v97; // d3
  double v98; // d4
  double v99; // d4
  float v100; // s0
  float v101; // s8
  double v102; // d4
  double v103; // d4
  double v104; // d4
  double v105; // d5
  double v106; // d5
  double v107; // d6
  double v108; // d6
  double v109; // d7
  double v110; // d6
  double v111; // d6
  float v112; // s14
  float v113; // s14
  float v114; // s14
  float v115; // s14
  float v116; // s14
  Curve *v117; // r9
  int v118; // r2
  const std::string *v119; // r3
  int v120; // s20
  double v121; // d9
  double v122; // d8
  int v123; // s24
  double v124; // d8
  int v125; // r1
  const std::string *v126; // r9
  int v127; // r0
  int v128; // r0
  int v129; // r0
  int v130; // r0
  int v131; // r0
  int v132; // r0
  Curve *v133; // r7
  int v134; // r2
  const std::string *v135; // r3
  double v136; // d11
  int v137; // r2
  const std::string *v138; // r3
  int v139; // r2
  const std::string *v140; // r3
  double v141; // d11
  int v142; // r2
  const std::string *v143; // r3
  int v144; // r2
  const std::string *v145; // r3
  double v146; // d11
  int v147; // r2
  const std::string *v148; // r3
  double *v149; // r9
  int v150; // r2
  const std::string *v151; // r3
  double v152; // d7
  int v153; // r2
  const std::string *v154; // r3
  int v155; // r3
  __int64 v156; // r2
  int v158; // r1
  double *v159; // [sp+Ch] [bp-198h]
  double *v160; // [sp+Ch] [bp-198h]
  double *v161; // [sp+Ch] [bp-198h]
  double v162; // [sp+10h] [bp-194h]
  int v163; // [sp+1Ch] [bp-188h]
  int v164; // [sp+28h] [bp-17Ch]
  _BYTE v165[4]; // [sp+30h] [bp-174h] BYREF
  _BYTE v166[4]; // [sp+34h] [bp-170h] BYREF
  _BYTE v167[4]; // [sp+38h] [bp-16Ch] BYREF
  _BYTE v168[176]; // [sp+3Ch] [bp-168h] BYREF
  _BYTE v169[4]; // [sp+ECh] [bp-B8h] BYREF
  _BYTE v170[180]; // [sp+F0h] [bp-B4h] BYREF

  rendererdata::rendererdata((int)this, a2 + 16);
  v5 = timesince((const timespec *)(a2 + 184), v4);
  *((double *)this + 1) = v5;
  *((float *)this + 10) = (float)*(int *)(*(_DWORD *)(a2 + 8) + 12);
  *((float *)this + 11) = (float)*(int *)(*(_DWORD *)(a2 + 8) + 16);
  *((float *)this + 12) = (float)*(int *)(*(_DWORD *)(a2 + 8) + 4);
  *((float *)this + 13) = (float)*(int *)(*(_DWORD *)(a2 + 8) + 8);
  *((float *)this + 14) = (float)*(int *)(a2 + 324);
  *((float *)this + 15) = (float)*(int *)(a2 + 328);
  v6 = 1.0;
  v7 = 1.0 - timesince((const timespec *)(a2 + 192), SHIDWORD(v5));
  if ( v7 < 0.0 )
    v7 = 0.0;
  if ( (*(_DWORD *)(a2 + 200) & 2) != 0 )
  {
    if ( (*(_DWORD *)(a2 + 204) & 1) == 0 )
      v6 = 0.0;
  }
  else
  {
    v6 = 0.0;
  }
  v8 = (double)(*(_DWORD *)(a2 + 200) & 1) + v7 * v6;
  v9 = 1.0;
  *((float *)this + 16) = v8;
  v10 = *(_DWORD *)(a2 + 180) == 0;
  *(_BYTE *)this = 0;
  if ( v10 )
    v9 = 0.0;
  *((float *)this + 16) = v8 * v9;
  if ( !**(_BYTE **)(a2 + 8) )
  {
    *(_BYTE *)this = 1;
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 84) = -1;
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 88) = -1;
  }
  v11 = *(_DWORD *)(a2 + 336);
  *((_BYTE *)this + 104) = 0;
  *((_BYTE *)this + 105) = 0;
  for ( i = *(unsigned __int8 *)this; ; i = 0 )
  {
    v13 = *(_DWORD *)(a2 + 8);
    v14 = *(_DWORD *)(a2 + 332);
    if ( *(_DWORD *)(v13 + 84) != v14 )
      goto LABEL_178;
    v11 = *(_DWORD *)(v13 + 88);
    if ( v11 == *(_DWORD *)(a2 + 336) )
      break;
    v11 = *(_DWORD *)(a2 + 336);
LABEL_178:
    *((_DWORD *)this + 28) = *(_DWORD *)(a2 + 176);
    *((_DWORD *)this + 27) = *(_DWORD *)(a2 + 180);
    _android_log_print(3, "renderlib", "nfd:%p, bgfd:%p", *(const void **)(a2 + 176), *(const void **)(a2 + 180));
    *((_DWORD *)this + 35) = *(_DWORD *)(a2 + 356);
    *((_DWORD *)this + 31) = *(_DWORD *)(a2 + 340);
    *((_DWORD *)this + 36) = *(_DWORD *)(a2 + 360);
    *((_DWORD *)this + 32) = *(_DWORD *)(a2 + 344);
    *((_DWORD *)this + 37) = *(_DWORD *)(a2 + 364);
    *((_DWORD *)this + 33) = *(_DWORD *)(a2 + 348);
    *((_DWORD *)this + 38) = *(_DWORD *)(a2 + 368);
    v155 = *(_DWORD *)(a2 + 352);
    *((_BYTE *)this + 104) = 1;
    *((_BYTE *)this + 105) = 1;
    *((_DWORD *)this + 34) = v155;
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 84) = v14;
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 88) = v11;
  }
  if ( i )
    goto LABEL_178;
  v15 = *(_DWORD *)(a2 + 320);
  v16 = *(double *)(a2 + 208);
  v17 = *(double *)(a2 + 216);
  *(double *)(a2 + 248) = v16;
  if ( !v15 )
    *(double *)(a2 + 256) = v17;
  v18 = *(_DWORD *)(a2 + 200);
  if ( (v18 & 2) != 0 )
  {
    v19 = 1.0;
    v20 = 5.35;
  }
  else
  {
    if ( (v18 & 1) != 0 )
    {
      v19 = 2.0;
      v20 = 4.35;
      v21 = 4.0;
      goto LABEL_24;
    }
    v19 = 1.0;
    v20 = 1.0;
  }
  v21 = v19;
LABEL_24:
  v22 = *(double *)(a2 + 224);
  v23 = *(double *)(a2 + 240);
  v24 = 1.0;
  if ( v16 - v22 < 0.0 )
    v25 = -1.0;
  else
    v25 = 1.0;
  v26 = v16 - v22 - v25 * 0.0;
  v27 = *(double *)(a2 + 256) - v23;
  if ( v27 < 0.0 )
    v24 = -1.0;
  v28 = *(double *)(a2 + 232);
  v29 = v27 - v24 * 0.0;
  v30 = *(double *)(a2 + 304);
  v31 = v26 * 4.0;
  if ( v26 * 4.0 < 0.0 )
    v31 = -v31;
  v32 = v16 - v28;
  v33 = v31 * (*((double *)this + 1) - v30);
  if ( v26 < 0.0 )
    v34 = -v26;
  else
    v34 = v26;
  if ( v34 < v33 )
    v33 = v34;
  v35 = 1.0;
  if ( v26 < 0.0 )
    v35 = -1.0;
  v36 = v32 * 4.0;
  *(double *)(a2 + 224) = v22 + v33 * v35;
  v162 = v22 + v33 * v35;
  if ( v32 * 4.0 < 0.0 )
    v36 = -v36;
  v37 = v36 * (*((double *)this + 1) - v30);
  if ( v32 < 0.0 )
    v38 = -v32;
  else
    v38 = v16 - v28;
  if ( v38 < v37 )
    v37 = v38;
  v39 = 1.0;
  if ( v32 < 0.0 )
    v39 = -1.0;
  v40 = v28 + v37 * v39;
  v41 = v29 + v29;
  *(double *)(a2 + 232) = v40;
  if ( v29 + v29 < 0.0 )
    v41 = -v41;
  v42 = v41 * (*((double *)this + 1) - v30);
  if ( v29 < 0.0 )
    v43 = -v29;
  else
    v43 = v29;
  if ( v43 < v42 )
    v42 = v43;
  v44 = 1.0;
  if ( v29 < 0.0 )
    v44 = -1.0;
  v45 = v23 + v42 * v44;
  v46 = v26 + v26;
  *(double *)(a2 + 240) = v45;
  if ( v26 + v26 < 0.0 )
    v46 = -v46;
  v47 = v46 * (*((double *)this + 1) - v30);
  if ( v26 < 0.0 )
    v48 = -v26;
  else
    v48 = v26;
  v49 = *(double *)(a2 + 288);
  v50 = *(double *)(a2 + 272);
  if ( v48 < v47 )
    v47 = v48;
  v51 = *(double *)(a2 + 296) + v47 * 0.1;
  v52 = v16 - v49;
  *(double *)(a2 + 296) = v51;
  v53 = (v16 - v49) * 24.0;
  if ( v53 < 0.0 )
    v53 = -v53;
  v54 = v17 - v50;
  v55 = v53 * (*((double *)this + 1) - v30);
  if ( v16 - v49 < 0.0 )
    v56 = -v52;
  else
    v56 = v16 - v49;
  v57 = -1.0;
  if ( v56 < v55 )
    v55 = v56;
  if ( v52 >= 0.0 )
    v57 = 1.0;
  v58 = *(double *)(a2 + 280) + v55 * v57;
  v59 = v54 * 24.0;
  *(double *)(a2 + 280) = v58;
  if ( v54 * 24.0 < 0.0 )
    v59 = -v59;
  v60 = v59 * (*((double *)this + 1) - v30);
  if ( v54 < 0.0 )
    v61 = -v54;
  else
    v61 = v54;
  v62 = -1.0;
  if ( v61 < v60 )
    v60 = v61;
  if ( v54 >= 0.0 )
    v62 = 1.0;
  v63 = *(double *)(a2 + 264) + v60 * v62;
  v64 = v58 * v21;
  *(double *)(a2 + 264) = v63;
  if ( v58 * v21 < 0.0 )
    v64 = -v64;
  v65 = v64 * (*((double *)this + 1) - v30);
  if ( v58 < 0.0 )
    v66 = -v58;
  else
    v66 = v58;
  v67 = v58 < 0.0;
  if ( v66 < v65 )
    v65 = v66;
  v68 = 1.0;
  if ( v67 )
    v68 = -1.0;
  *(double *)(a2 + 288) = v49 + v65 * v68;
  v69 = v49 + v65 * v68;
  v70 = v63 * v21;
  if ( v63 * v21 < 0.0 )
    v70 = -v70;
  v71 = v70 * (*((double *)this + 1) - v30);
  if ( v63 < 0.0 )
    v72 = -v63;
  else
    v72 = v63;
  v73 = v63 < 0.0;
  if ( v72 < v71 )
    v71 = v72;
  v74 = 1.0;
  if ( v73 )
    v74 = -1.0;
  v75 = v52 * v20;
  *(double *)(a2 + 272) = v50 + v71 * v74;
  if ( v52 * v20 < 0.0 )
    v75 = -v75;
  v76 = v50 + v71 * v74;
  v77 = v75 * (*((double *)this + 1) - v30);
  if ( v52 < 0.0 )
    v78 = -v52;
  else
    v78 = v16 - v49;
  if ( v78 < v77 )
    v77 = v78;
  v79 = 1.0;
  if ( v52 < 0.0 )
    v79 = -1.0;
  v80 = v69 + v77 * v79;
  v81 = v54 * v20;
  *(double *)(a2 + 288) = v80;
  if ( v54 * v20 < 0.0 )
    v81 = -v81;
  v82 = v81 * (*((double *)this + 1) - v30);
  if ( v54 < 0.0 )
    v83 = -v54;
  else
    v83 = v54;
  if ( v83 < v82 )
    v82 = v83;
  v84 = 1.0;
  if ( v54 < 0.0 )
    v84 = -1.0;
  v85 = v76 + v82 * v84;
  v86 = v54 * v19;
  *(double *)(a2 + 272) = v85;
  if ( v54 * v19 >= 0.0 )
    v87 = v54 * v19;
  else
    v87 = -v86;
  v88 = v87 * (*((double *)this + 1) - v30);
  if ( v54 >= 0.0 )
    v89 = v54;
  else
    v89 = -v54;
  if ( v89 < v88 )
    v88 = v89;
  v90 = 1.0;
  if ( v26 < 0.0 )
    v90 = -1.0;
  *(double *)(a2 + 224) = v162 + v88 * v90;
  v91 = v162 + v88 * v90;
  if ( v86 >= 0.0 )
    v92 = v54 * v19;
  else
    v92 = -v86;
  v93 = v92 * (*((double *)this + 1) - v30);
  if ( v54 >= 0.0 )
    v94 = v54;
  else
    v94 = -v54;
  if ( v94 < v93 )
    v93 = v94;
  v95 = 1.0;
  if ( v26 < 0.0 )
    v95 = -1.0;
  *(double *)(a2 + 208) = v16 + v93 * v95;
  if ( v86 >= 0.0 )
    v96 = v54 * v19;
  else
    v96 = -v86;
  v97 = v96 * (*((double *)this + 1) - v30);
  if ( v54 >= 0.0 )
    v98 = v54;
  else
    v98 = -v54;
  if ( v98 < v97 )
    v97 = v98;
  v99 = 1.0;
  if ( v26 < 0.0 )
    v99 = -1.0;
  *(double *)(a2 + 248) = v16 + v97 * v99;
  v100 = v80 - v91;
  *((float *)this + 18) = v100;
  v101 = *(double *)(a2 + 272) - *(double *)(a2 + 240);
  *((float *)this + 22) = v101;
  v102 = *(double *)(a2 + 288) - *(double *)(a2 + 224);
  if ( v32 < 0.0 )
    v32 = -v32;
  if ( v26 < 0.0 )
    v26 = -v26;
  if ( v102 < 0.0 )
    v102 = -v102;
  v103 = v26 + v102;
  if ( v52 < 0.0 )
    v52 = -v52;
  v104 = v103 + v52;
  v105 = *(double *)(a2 + 280);
  if ( v105 < 0.0 )
    v105 = -v105;
  v106 = v104 + v105;
  v107 = *(double *)(a2 + 272) - *(double *)(a2 + 240);
  if ( v29 < 0.0 )
    v29 = -v29;
  if ( v107 < 0.0 )
    v107 = -v107;
  v108 = v29 + v107;
  if ( v54 < 0.0 )
    v54 = -v54;
  v109 = v108 + v54;
  v110 = *(double *)(a2 + 264);
  if ( v110 < 0.0 )
    v110 = -v110;
  v111 = v109 + v110;
  if ( v106 < v111 )
    v106 = v111;
  if ( v32 >= v106 )
    v106 = v32;
  v112 = *(double *)(a2 + 208);
  *(double *)(a2 + 312) = v106 * 8.0;
  *((float *)this + 19) = v112;
  v113 = *(double *)(a2 + 216);
  *((float *)this + 23) = v113;
  v114 = *(double *)(a2 + 224);
  *((float *)this + 20) = v114;
  v115 = *(double *)(a2 + 240);
  *((float *)this + 24) = v115;
  v116 = *(double *)(a2 + 232);
  *((float *)this + 21) = v116;
  std::string::string(v169, ".transitions", v167);
  v117 = (Curve *)std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::find(
                    (int)this + 16,
                    (const std::string *)v169);
  std::string::~string((std::string *)v169);
  if ( v117 != (Curve *)((char *)this + 20) )
  {
    std::string::string(v169, ".transitions", v167);
    v120 = (int)*(double *)std::map<std::string,themeparameter>::operator[](
                             (_DWORD *)this + 4,
                             (const std::string *)v169,
                             v118,
                             v119);
    std::string::~string((std::string *)v169);
    v121 = fmod(*(double *)(a2 + 296), (double)v120);
    v122 = floor(v121);
    v123 = (int)v122;
    v124 = v121 - v122;
    v125 = (int)ceil(v121) % v120;
    v163 = *(_DWORD *)(a2 + 44);
    v164 = v125;
    while ( v163 != a2 + 36 )
    {
      v126 = (const std::string *)(v163 + 16);
      if ( std::string::find((std::string *)(v163 + 16), ".", 0) )
      {
        std::ostringstream::basic_ostringstream(v167, 16);
        std::ostringstream::basic_ostringstream(v169, 16);
        v127 = std::operator<<<std::char_traits<char>>(v167, ".");
        v128 = std::ostream::operator<<(v127, v123);
        v129 = std::operator<<<std::char_traits<char>>(v128, ".");
        std::operator<<<char>(v129, v126);
        v130 = std::operator<<<std::char_traits<char>>(v169, ".");
        v131 = std::ostream::operator<<(v130, v164);
        v132 = std::operator<<<std::char_traits<char>>(v131, ".");
        std::operator<<<char>(v132, v126);
        std::stringbuf::str(v166, v168);
        v133 = (Curve *)std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::find(
                          (int)this + 16,
                          (const std::string *)v166);
        std::string::~string((std::string *)v166);
        if ( v133 != (Curve *)((char *)this + 20) )
        {
          v159 = (double *)std::map<std::string,themeparameter>::operator[]((int)this + 16, v126);
          std::stringbuf::str(v165, v168);
          v136 = *(double *)std::map<std::string,themeparameter>::operator[](
                              (_DWORD *)this + 4,
                              (const std::string *)v165,
                              v134,
                              v135);
          std::stringbuf::str(v166, v170);
          *v159 = (1.0 - v124) * v136
                + v124
                * *(double *)std::map<std::string,themeparameter>::operator[](
                               (_DWORD *)this + 4,
                               (const std::string *)v166,
                               v137,
                               v138);
          std::string::~string((std::string *)v166);
          std::string::~string((std::string *)v165);
          v160 = (double *)std::map<std::string,themeparameter>::operator[]((int)this + 16, v126);
          std::stringbuf::str(v165, v168);
          v141 = *((double *)std::map<std::string,themeparameter>::operator[](
                               (_DWORD *)this + 4,
                               (const std::string *)v165,
                               v139,
                               v140)
                 + 1);
          std::stringbuf::str(v166, v170);
          v160[1] = (1.0 - v124) * v141
                  + v124
                  * *((double *)std::map<std::string,themeparameter>::operator[](
                                  (_DWORD *)this + 4,
                                  (const std::string *)v166,
                                  v142,
                                  v143)
                    + 1);
          std::string::~string((std::string *)v166);
          std::string::~string((std::string *)v165);
          v161 = (double *)std::map<std::string,themeparameter>::operator[]((int)this + 16, v126);
          std::stringbuf::str(v165, v168);
          v146 = *((double *)std::map<std::string,themeparameter>::operator[](
                               (_DWORD *)this + 4,
                               (const std::string *)v165,
                               v144,
                               v145)
                 + 2);
          std::stringbuf::str(v166, v170);
          v161[2] = (1.0 - v124) * v146
                  + v124
                  * *((double *)std::map<std::string,themeparameter>::operator[](
                                  (_DWORD *)this + 4,
                                  (const std::string *)v166,
                                  v147,
                                  v148)
                    + 2);
          std::string::~string((std::string *)v166);
          std::string::~string((std::string *)v165);
          v149 = (double *)std::map<std::string,themeparameter>::operator[]((int)this + 16, v126);
          std::stringbuf::str(v165, v168);
          v152 = *((double *)std::map<std::string,themeparameter>::operator[](
                               (_DWORD *)this + 4,
                               (const std::string *)v165,
                               v150,
                               v151)
                 + 3);
          std::stringbuf::str(v166, v170);
          v149[3] = (1.0 - v124) * v152
                  + v124
                  * *((double *)std::map<std::string,themeparameter>::operator[](
                                  (_DWORD *)this + 4,
                                  (const std::string *)v166,
                                  v153,
                                  v154)
                    + 3);
          std::string::~string((std::string *)v166);
          std::string::~string((std::string *)v165);
        }
        std::ostringstream::~ostringstream(v169);
        std::ostringstream::~ostringstream(v167);
      }
      v163 = std::_Rb_tree_increment(v163);
    }
  }
  v156 = *((_QWORD *)this + 1);
  v158 = *(_DWORD *)(a2 + 8);
  *(_QWORD *)(a2 + 304) = v156;
  *(_QWORD *)(v158 + 72) = v156;
  **(_BYTE **)(a2 + 8) = 1;
  return this;
}
// 12514: variable 'v4' is possibly undefined
// 12D8A: variable 'v118' is possibly undefined
// 12D8A: variable 'v119' is possibly undefined
// 12EA0: variable 'v134' is possibly undefined
// 12EA0: variable 'v135' is possibly undefined
// 12EBC: variable 'v137' is possibly undefined
// 12EBC: variable 'v138' is possibly undefined
// 12EF2: variable 'v139' is possibly undefined
// 12EF2: variable 'v140' is possibly undefined
// 12F0A: variable 'v142' is possibly undefined
// 12F0A: variable 'v143' is possibly undefined
// 12F40: variable 'v144' is possibly undefined
// 12F40: variable 'v145' is possibly undefined
// 12F58: variable 'v147' is possibly undefined
// 12F58: variable 'v148' is possibly undefined
// 12F8C: variable 'v150' is possibly undefined
// 12F8C: variable 'v151' is possibly undefined
// 12FA4: variable 'v153' is possibly undefined
// 12FA4: variable 'v154' is possibly undefined
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);
// 7918: using guessed type int __fastcall std::string::string(_DWORD, _DWORD, _DWORD);
// 7AEC: using guessed type int __fastcall std::operator<<<std::char_traits<char>>(_DWORD, _DWORD);
// 7AF8: using guessed type int __fastcall std::operator<<<char>(_DWORD, _DWORD);
// 7C6C: using guessed type int __fastcall std::ostringstream::basic_ostringstream(_DWORD, _DWORD);
// 7C78: using guessed type int __fastcall std::ostream::operator<<(_DWORD, _DWORD);
// 7C84: using guessed type int __fastcall std::stringbuf::str(_DWORD, _DWORD);
// 7CA8: using guessed type int __fastcall std::ostringstream::~ostringstream(_DWORD);


