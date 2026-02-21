// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: renderer  Functions: 6

//----- (000095E8) --------------------------------------------------------
void __fastcall renderer::init(renderer *this, ef2_AAssetManager *a2)
{
  Curve *v4; // r5

  v4 = (Curve *)operator new(0x178u);
  Curve::Curve(v4, a2);
  *((_DWORD *)this + 23) = v4;
}


//----- (0000961C) --------------------------------------------------------
std::string *__fastcall renderer::getfile(std::string *a1, int a2, ef2_AAssetManager *a3, const char **a4)
{
  AAsset *v7; // r0
  AAsset *v8; // r6
  const void *Buffer; // r7
  off_t Length; // r0
  std::string *v12; // [sp+0h] [bp-Ch] BYREF
  _DWORD v13[2]; // [sp+4h] [bp-8h] BYREF

  v12 = a1;
  v13[0] = a2;
  v13[1] = a3;
  std::string::string(a1, &unk_14A08, v13);
  v7 = ef2_AAssetManager_open(a3, *a4, 3);
  v8 = v7;
  if ( v7 )
  {
    Buffer = AAsset_getBuffer(v7);
    Length = AAsset_getLength(v8);
    std::string::string(v13, Buffer, Length, &v12);
    std::string::swap(a1, (std::string *)v13);
    std::string::~string((std::string *)v13);
    AAsset_close(v8);
  }
  return a1;
}
// 7918: using guessed type int __fastcall std::string::string(_DWORD, _DWORD, _DWORD);
// 79B4: using guessed type int __fastcall std::string::string(_DWORD, _DWORD, _DWORD, _DWORD);


//----- (00009674) --------------------------------------------------------
buffer *__fastcall renderer::createVertices(renderer *this, int a2, int a3)
{
  unsigned int v5; // r6
  unsigned int v6; // r0
  char *v7; // r0
  int v8; // r3
  int v9; // r2
  char *v10; // r4
  float *v11; // r5
  int i; // r0
  int v13; // s13
  buffer *v14; // r5

  v5 = 2 * (a2 + 1) * (a3 + 1);
  if ( v5 > 0x1FC00000 )
    v6 = -1;
  else
    v6 = 4 * v5;
  v7 = (char *)operator new[](v6);
  v8 = 0;
  v9 = 0;
  v10 = v7;
  while ( v8 <= a3 )
  {
    v11 = (float *)&v10[4 * v9];
    for ( i = 0; ; ++i )
    {
      v11 += 2;
      if ( i > a2 )
        break;
      v13 = i;
      v9 += 2;
      *(v11 - 2) = (float)v13 / (float)a2;
      *(v11 - 1) = (float)v8 / (float)a3;
    }
    ++v8;
  }
  v14 = (buffer *)operator new(0x20u);
  buffer::buffer(v14, 0x8892u, -1);
  buffer::set(v14, 4 * v5, v10, 0x88E4u);
  if ( v10 )
    operator delete[](v10);
  return v14;
}


//----- (00009716) --------------------------------------------------------
buffer *__fastcall renderer::createIndices(renderer *this, int a2, int a3)
{
  int v3; // r10
  __int16 v5; // r4
  unsigned int v6; // r8
  unsigned int v7; // r0
  _WORD *v8; // r0
  int v9; // r3
  _WORD *v10; // r5
  int i; // r0
  int v12; // r6
  char *j; // r7
  __int16 v14; // r1
  __int16 v15; // r11
  int v16; // r1
  buffer *v17; // r4

  v3 = a2 + 1;
  v5 = 0;
  v6 = a3 * 2 * (a2 + 2) - 2;
  if ( v6 > 0x3F800000 )
    v7 = -1;
  else
    v7 = 2 * v6;
  v8 = (_WORD *)operator new[](v7);
  v9 = 0;
  v10 = v8;
  for ( i = 0; i < a3; ++i )
  {
    if ( i > 0 )
      v10[v9++] = v5;
    v12 = 0;
    for ( j = (char *)&v10[v9]; ; *((_WORD *)j - 1) = v14 + v3 + v5 )
    {
      j += 4;
      if ( v12 >= v3 )
        break;
      v14 = v12;
      v9 += 2;
      v15 = v12++ + v5;
      *((_WORD *)j - 2) = v15;
    }
    v16 = v9;
    if ( i < a3 - 1 )
    {
      ++v9;
      v10[v16] = v5 + 2 * v3 - 1;
    }
    v5 += v3;
  }
  v17 = (buffer *)operator new(0x20u);
  buffer::buffer(v17, 0x8893u, -1);
  buffer::set(v17, 2 * v6, v10, 0x88E4u);
  if ( v10 )
    operator delete[](v10);
  return v17;
}


//----- (000099BC) --------------------------------------------------------
_DWORD *__fastcall renderer::buildShaderFile(
        _DWORD *a1,
        int a2,
        ef2_AAssetManager *a3,
        const std::string *a4,
        const std::string *a5)
{
  int *v8; // r0
  const char **v9; // r0
  _BYTE v12[4]; // [sp+4Ch] [bp-60h] BYREF
  const char *v13; // [sp+50h] [bp-5Ch] BYREF
  _BYTE v14[4]; // [sp+54h] [bp-58h] BYREF
  int v15; // [sp+58h] [bp-54h] BYREF
  _BYTE v16[4]; // [sp+5Ch] [bp-50h] BYREF
  int v17; // [sp+60h] [bp-4Ch] BYREF
  const char *v18; // [sp+64h] [bp-48h] BYREF
  _BYTE v19[4]; // [sp+68h] [bp-44h] BYREF
  int v20; // [sp+6Ch] [bp-40h] BYREF
  int v21; // [sp+70h] [bp-3Ch] BYREF
  _BYTE v22[4]; // [sp+74h] [bp-38h] BYREF
  const char *v23; // [sp+78h] [bp-34h] BYREF
  _BYTE v24[4]; // [sp+7Ch] [bp-30h] BYREF
  int v25; // [sp+80h] [bp-2Ch] BYREF
  int v26; // [sp+84h] [bp-28h] BYREF
  _BYTE v27[4]; // [sp+88h] [bp-24h] BYREF
  const char *v28; // [sp+8Ch] [bp-20h] BYREF
  _BYTE v29[4]; // [sp+90h] [bp-1Ch] BYREF
  int v30; // [sp+94h] [bp-18h] BYREF
  int v31; // [sp+98h] [bp-14h] BYREF
  _BYTE v32[4]; // [sp+9Ch] [bp-10h] BYREF
  const char *v33; // [sp+A0h] [bp-Ch] BYREF
  _BYTE v34[8]; // [sp+A4h] [bp-8h] BYREF

  std::string::string(&v13, "inputs.base", v12);
  renderer::getfile((std::string *)v14, a2, a3, &v13);
  std::operator+<char>(&v15, (std::string *)v14, "\n");
  std::string::string((std::string *)v16, a4);
  std::string::append((std::string *)v16, ".");
  v8 = (int *)std::string::append((std::string *)v16, a5);
  v17 = *v8;
  *v8 = (int)&std::string::_Rep::_S_empty_rep_storage + 12;
  std::operator+<char>(&v18, (std::string *)&v17, ".header");
  renderer::getfile((std::string *)v19, a2, a3, &v18);
  std::operator+<char>(&v20, (std::string *)&v15, (std::string *)v19);
  std::operator+<char>(&v21, (std::string *)&v20, "\n");
  std::operator+<char>((std::string *)v22, "header.", a5);
  std::operator+<char>(&v23, (std::string *)v22, ".base");
  renderer::getfile((std::string *)v24, a2, a3, &v23);
  std::operator+<char>(&v25, (std::string *)&v21, (std::string *)v24);
  std::operator+<char>(&v26, (std::string *)&v25, "\n");
  std::string::string((std::string *)v27, a4);
  std::string::append((std::string *)v27, ".");
  v9 = (const char **)std::string::append((std::string *)v27, a5);
  v28 = *v9;
  *v9 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
  renderer::getfile((std::string *)v29, a2, a3, &v28);
  std::operator+<char>(&v30, (std::string *)&v26, (std::string *)v29);
  std::operator+<char>(&v31, (std::string *)&v30, "\n");
  std::operator+<char>((std::string *)v32, "footer.", a5);
  std::operator+<char>(&v33, (std::string *)v32, ".base");
  renderer::getfile((std::string *)v34, a2, a3, &v33);
  std::operator+<char>(a1, (std::string *)&v31, (std::string *)v34);
  std::string::~string((std::string *)v34);
  std::string::~string((std::string *)&v33);
  std::string::~string((std::string *)v32);
  std::string::~string((std::string *)&v31);
  std::string::~string((std::string *)&v30);
  std::string::~string((std::string *)v29);
  std::string::~string((std::string *)&v28);
  std::string::~string((std::string *)v27);
  std::string::~string((std::string *)&v26);
  std::string::~string((std::string *)&v25);
  std::string::~string((std::string *)v24);
  std::string::~string((std::string *)&v23);
  std::string::~string((std::string *)v22);
  std::string::~string((std::string *)&v21);
  std::string::~string((std::string *)&v20);
  std::string::~string((std::string *)v19);
  std::string::~string((std::string *)&v18);
  std::string::~string((std::string *)&v17);
  std::string::~string((std::string *)v16);
  std::string::~string((std::string *)&v15);
  std::string::~string((std::string *)v14);
  std::string::~string((std::string *)&v13);
  return a1;
}
// 7918: using guessed type int __fastcall std::string::string(_DWORD, _DWORD, _DWORD);


//----- (0000A310) --------------------------------------------------------
void __fastcall renderer::render(render *this, ef2_AAssetManager *a2)
{
  void *v3; // r1
  void *v4; // r6
  void *v5; // r6
  void *v6; // r6
  void *v7; // r6
  GLuint *v8; // r6
  GLuint *v9; // r6
  int v10; // r0
  int **v11; // r0
  int v12; // r0
  int **v13; // r0
  buffer **v14; // r9
  buffer *v15; // r9
  buffer **v16; // r9
  buffer *v17; // r9
  buffer **v18; // r10
  buffer *v19; // r10
  buffer **v20; // r10
  buffer *v21; // r10
  unsigned int v22; // r10
  buffer *Indices; // r0
  buffer *Vertices; // r0
  unsigned int v25; // r11
  buffer *v26; // r0
  unsigned int v27; // r7
  buffer *v28; // r0
  double *i; // r6
  uniform *v30; // r0
  float v31; // s14
  float v32; // s14
  float v33; // s15
  float v34; // r1
  float v35; // s14
  uniform *v36; // r0
  int v37; // r0
  int v38; // r1
  int v39; // r0
  int v40; // r1
  int v41; // s21
  uniform *v42; // r0
  float v43; // s12
  uniform *v44; // r0
  uniform *v45; // r0
  uniform *v46; // r0
  uniform *v47; // r0
  int v48; // r2
  int v49; // s22
  uniform *v50; // r0
  int v51; // s14
  int v52; // r3
  float v53; // s22
  uniform *v54; // r0
  uniform *v55; // r0
  uniform *v56; // r0
  float v57; // s17
  uniform *v58; // r0
  int v59; // r2
  const std::string *v60; // r3
  double v61; // d8
  uniform *v62; // r0
  int v63; // r2
  const std::string *v64; // r3
  float v65; // s12
  float v66; // s27
  unsigned int v67; // s13
  float v68; // s29
  unsigned int v69; // s15
  uniform *v70; // r0
  float v71; // s25
  int v72; // r2
  const std::string *v73; // r3
  float v74; // s14
  int v75; // r2
  const std::string *v76; // r3
  float v77; // s28
  double v78; // d8
  int v79; // r2
  const std::string *v80; // r3
  double v81; // d7
  int v82; // r2
  const std::string *v83; // r3
  int v84; // r2
  const std::string *v85; // r3
  int v86; // r2
  const std::string *v87; // r3
  float v88; // s12
  float v89; // s16
  int v90; // r2
  const std::string *v91; // r3
  int v92; // r2
  const std::string *v93; // r3
  float v94; // s17
  double v95; // r0
  float *v96; // r2
  float v97; // s14
  float v98; // [sp+0h] [bp-ACCh]
  uniform *v99; // [sp+14h] [bp-AB8h]
  uniform *v100; // [sp+18h] [bp-AB4h]
  uniform *v101; // [sp+18h] [bp-AB4h]
  uniform *v102; // [sp+18h] [bp-AB4h]
  _BYTE v104[4]; // [sp+38h] [bp-A94h] BYREF
  _BYTE v105[4]; // [sp+3Ch] [bp-A90h] BYREF
  _BYTE v106[4]; // [sp+40h] [bp-A8Ch] BYREF
  _BYTE v107[4]; // [sp+44h] [bp-A88h] BYREF
  _BYTE v108[4]; // [sp+48h] [bp-A84h] BYREF
  _BYTE v109[4]; // [sp+4Ch] [bp-A80h] BYREF
  int v110; // [sp+50h] [bp-A7Ch] BYREF
  _BYTE v111[4]; // [sp+54h] [bp-A78h] BYREF
  _BYTE v112[4]; // [sp+58h] [bp-A74h] BYREF
  int v113; // [sp+5Ch] [bp-A70h] BYREF
  _BYTE v114[8]; // [sp+60h] [bp-A6Ch] BYREF
  double v115; // [sp+68h] [bp-A64h]
  int v116; // [sp+70h] [bp-A5Ch] BYREF
  _DWORD *v117[9]; // [sp+74h] [bp-A58h] BYREF
  float v118; // [sp+98h] [bp-A34h]
  float v119; // [sp+9Ch] [bp-A30h]
  float v120; // [sp+A0h] [bp-A2Ch]
  float v121; // [sp+A4h] [bp-A28h]
  float v122; // [sp+A8h] [bp-A24h]
  float v123; // [sp+ACh] [bp-A20h]
  float v124; // [sp+B0h] [bp-A1Ch]
  float v125; // [sp+B4h] [bp-A18h]
  float v126; // [sp+B8h] [bp-A14h]
  float v127; // [sp+BCh] [bp-A10h]
  float v128; // [sp+C0h] [bp-A0Ch]
  float v129; // [sp+C4h] [bp-A08h]
  char v130; // [sp+C8h] [bp-A04h]
  char v131; // [sp+C9h] [bp-A03h]
  void *v132; // [sp+CCh] [bp-A00h]
  void *v133; // [sp+D0h] [bp-9FCh]
  GLsizei v134; // [sp+E0h] [bp-9ECh]
  GLsizei v135; // [sp+E4h] [bp-9E8h]
  int v136; // [sp+E8h] [bp-9E4h]
  GLsizei v137; // [sp+F0h] [bp-9DCh]
  GLsizei v138; // [sp+F4h] [bp-9D8h]
  int v139; // [sp+F8h] [bp-9D4h]
  void *v140; // [sp+104h] [bp-9C8h] BYREF
  void *v141; // [sp+108h] [bp-9C4h]
  int v142; // [sp+10Ch] [bp-9C0h]

  Curve::updateRenderer((Curve *)v114, *((_DWORD *)this + 23));
  if ( v114[0] )
  {
    _android_log_print(4, "renderlib", "reset flag");
    v4 = (void *)*((_DWORD *)this + 20);
    if ( v4 )
    {
      program::~program(*((program **)this + 20), v3);
      operator delete(v4);
    }
    v5 = (void *)*((_DWORD *)this + 19);
    if ( v5 )
    {
      program::~program(*((program **)this + 19), v3);
      operator delete(v5);
    }
    v6 = (void *)*((_DWORD *)this + 21);
    if ( v6 )
    {
      glDeleteTextures(1, *((const GLuint **)this + 21));
      operator delete(v6);
    }
    v7 = (void *)*((_DWORD *)this + 22);
    if ( v7 )
    {
      glDeleteTextures(1, *((const GLuint **)this + 22));
      operator delete(v7);
    }
    v8 = (GLuint *)operator new(0x18u);
    texture::texture(v8);
    *((_DWORD *)this + 22) = v8;
    v9 = (GLuint *)operator new(0x18u);
    texture::texture(v9);
    *((_DWORD *)this + 21) = v9;
    v140 = 0;
    v141 = 0;
    v142 = 0;
    std::string::string(v108, "gfxbackground", v104);
    std::string::string(v109, "vert", v105);
    renderer::buildShaderFile(&v110, (int)this, a2, (const std::string *)v108, (const std::string *)v109);
    std::string::string(v111, "gfxbackground", v106);
    std::string::string(v112, "frag", v107);
    renderer::buildShaderFile(&v113, (int)this, a2, (const std::string *)v111, (const std::string *)v112);
    v10 = program::shader(35632, &v113, (int)&v140);
    v11 = (int **)program::shader(35633, &v110, v10);
    *((_DWORD *)this + 20) = program::createProgram(v11);
    std::string::~string((std::string *)&v113);
    std::string::~string((std::string *)v112);
    std::string::~string((std::string *)v111);
    std::string::~string((std::string *)&v110);
    std::string::~string((std::string *)v109);
    std::string::~string((std::string *)v108);
    v141 = v140;
    std::string::string(v108, "gfxline", v104);
    std::string::string(v109, "vert", v105);
    renderer::buildShaderFile(&v110, (int)this, a2, (const std::string *)v108, (const std::string *)v109);
    std::string::string(v111, "gfxlineB", v106);
    std::string::string(v112, "frag", v107);
    renderer::buildShaderFile(&v113, (int)this, a2, (const std::string *)v111, (const std::string *)v112);
    v12 = program::shader(35632, &v113, (int)&v140);
    v13 = (int **)program::shader(35633, &v110, v12);
    *((_DWORD *)this + 19) = program::createProgram(v13);
    std::string::~string((std::string *)&v113);
    std::string::~string((std::string *)v112);
    std::string::~string((std::string *)v111);
    std::string::~string((std::string *)&v110);
    std::string::~string((std::string *)v109);
    std::string::~string((std::string *)v108);
    *((_DWORD *)this + 14) = 1;
    *((_DWORD *)this + 16) = 20;
    *((_DWORD *)this + 15) = 2;
    *((_DWORD *)this + 17) = 3;
    std::string::string(&v113, "_index", v112);
    v14 = (buffer **)varray::getconfig(this, (const std::string *)&v113);
    std::string::~string((std::string *)&v113);
    v15 = *v14;
    if ( v15 )
    {
      buffer::~buffer(v15);
      operator delete(v15);
    }
    std::string::string(&v113, "linedata", v112);
    v16 = (buffer **)varray::getconfig(this, (const std::string *)&v113);
    std::string::~string((std::string *)&v113);
    v17 = *v16;
    if ( v17 )
    {
      buffer::~buffer(v17);
      operator delete(v17);
    }
    std::string::string(&v113, "_index", v112);
    v18 = (buffer **)varray::getconfig((_DWORD *)this + 7, (const std::string *)&v113);
    std::string::~string((std::string *)&v113);
    v19 = *v18;
    if ( v19 )
    {
      buffer::~buffer(v19);
      operator delete(v19);
    }
    std::string::string(&v113, "linedata", v112);
    v20 = (buffer **)varray::getconfig((_DWORD *)this + 7, (const std::string *)&v113);
    std::string::~string((std::string *)&v113);
    v21 = *v20;
    if ( v21 )
    {
      buffer::~buffer(v21);
      operator delete(v21);
    }
    std::string::string(&v113, "_index", v112);
    v22 = varray::getconfig(this, (const std::string *)&v113);
    Indices = renderer::createIndices(this, *((_DWORD *)this + 14), *((_DWORD *)this + 15));
    bufferconfig::set(v22, Indices, 0, 0);
    std::string::~string((std::string *)&v113);
    std::string::string(&v113, "linedata", v112);
    v100 = (uniform *)varray::getconfig(this, (const std::string *)&v113);
    Vertices = renderer::createVertices(this, *((_DWORD *)this + 14), *((_DWORD *)this + 15));
    bufferconfig::set((unsigned int)v100, Vertices, 0, 0);
    std::string::~string((std::string *)&v113);
    varray::update((int)this);
    std::string::string(&v113, "_index", v112);
    v25 = varray::getconfig((_DWORD *)this + 7, (const std::string *)&v113);
    v26 = renderer::createIndices(this, *((_DWORD *)this + 16), *((_DWORD *)this + 17));
    bufferconfig::set(v25, v26, 0, 0);
    std::string::~string((std::string *)&v113);
    std::string::string(&v113, "linedata", v112);
    v27 = varray::getconfig((_DWORD *)this + 7, (const std::string *)&v113);
    v28 = renderer::createVertices(this, *((_DWORD *)this + 16), *((_DWORD *)this + 17));
    bufferconfig::set(v27, v28, 0, 0);
    std::string::~string((std::string *)&v113);
    varray::update((int)this + 28);
    if ( v140 )
      operator delete(v140);
  }
  if ( v130 )
  {
    v140 = 0;
    if ( v132 )
    {
      if ( !v136 )
      {
        _android_log_print(3, "renderer", "bg texture: %d, %d, %p", v134, v135, v132);
        texture::set(*((GLuint **)this + 22), 6408, 0x1908u, 0x1401u, v134, v135, v132, 1);
      }
    }
    else
    {
      _android_log_print(3, "renderer", "remove bg texture");
      texture::set(*((GLuint **)this + 22), 6408, 0x1908u, 0x1401u, 1, 1, &v140, 1);
    }
  }
  if ( v131 )
  {
    v140 = 0;
    if ( v133 )
    {
      if ( !v139 )
      {
        _android_log_print(3, "renderer", "noise texture: %d, %d, %p", v137, v138, v133);
        texture::set(*((GLuint **)this + 21), 6408, 0x1908u, 0x1401u, v137, v138, v133, 1);
      }
    }
    else
    {
      _android_log_print(3, "renderer", "remove noise texture");
      texture::set(*((GLuint **)this + 21), 6408, 0x1908u, 0x1401u, 1, 1, &v140, 1);
    }
  }
  for ( i = (double *)v117[2]; i != (double *)v117; i = (double *)std::_Rb_tree_increment(i) )
  {
    if ( std::string::find((std::string *)(i + 2), ".", 0) )
    {
      std::string::string((std::string *)&v140, (const std::string *)(i + 2));
      v30 = (uniform *)program::getuniform((const std::string *)&v140);
      v31 = i[6];
      v98 = v31;
      v32 = i[3];
      v33 = i[4];
      v34 = v32;
      v35 = i[5];
      uniform::set<float>(v30, v34, v33, v35, v98);
      std::string::~string((std::string *)&v140);
    }
  }
  if ( v131 )
  {
    std::string::string(&v140, "noiseTextureScale", &v113);
    v36 = (uniform *)program::getuniform((const std::string *)&v140);
    uniform::set<float>(v36, v118 / (float)v137, v119 / (float)v138);
    std::string::~string((std::string *)&v140);
  }
  std::string::string(&v140, "noise", &v113);
  v37 = program::getuniform((const std::string *)&v140);
  v38 = *((_DWORD *)this + 21);
  if ( *(_DWORD *)(v37 + 4) )
  {
    **(_DWORD **)(v37 + 12) = 0;
    *(_DWORD *)(v37 + 16) = v38;
    uniform::touched((uniform *)v37);
  }
  std::string::~string((std::string *)&v140);
  std::string::string(&v140, "bg", &v113);
  v39 = program::getuniform((const std::string *)&v140);
  v40 = *((_DWORD *)this + 22);
  if ( *(_DWORD *)(v39 + 4) )
  {
    **(_DWORD **)(v39 + 12) = 1;
    *(_DWORD *)(v39 + 16) = v40;
    uniform::touched((uniform *)v39);
  }
  std::string::~string((std::string *)&v140);
  v41 = 0;
  std::string::string(&v140, "time", &v113);
  v42 = (uniform *)program::getuniform((const std::string *)&v140);
  v43 = v115 * 100.0;
  uniform::set<float>(v42, v43);
  std::string::~string((std::string *)&v140);
  std::string::string(&v140, "lsA", &v113);
  v44 = (uniform *)program::getuniform((const std::string *)&v140);
  uniform::set<float>(v44, *(float *)&v117[5], *(float *)&v117[6], *(float *)&v117[7], *(float *)&v117[8]);
  std::string::~string((std::string *)&v140);
  std::string::string(&v140, "lsB", &v113);
  v45 = (uniform *)program::getuniform((const std::string *)&v140);
  uniform::set<float>(v45, v118, v119, v120, v121);
  std::string::~string((std::string *)&v140);
  std::string::string(&v140, "lsByx", &v113);
  v46 = (uniform *)program::getuniform((const std::string *)&v140);
  uniform::set<float>(v46, (float)(v119 / v118) * 1.3);
  std::string::~string((std::string *)&v140);
  std::string::string(&v140, "l1", &v113);
  v47 = (uniform *)program::getuniform((const std::string *)&v140);
  uniform::set<float>(v47, v122, v126);
  std::string::~string((std::string *)&v140);
  v48 = (int)(v126 * 0.025);
  if ( v48 < 0 )
    v48 = -v48;
  v49 = v48;
  std::string::string(&v140, "l1m", &v113);
  v50 = (uniform *)program::getuniform((const std::string *)&v140);
  v51 = (int)(v126 * 0.1);
  v52 = v51;
  v53 = 1.0 / (float)((float)v49 + 1.0);
  if ( v51 < 0 )
    v52 = -v51;
  uniform::set<float>(v50, v53, 1.0 / (float)((float)v52 + 1.0));
  std::string::~string((std::string *)&v140);
  std::string::string(&v140, "l2", &v113);
  v54 = (uniform *)program::getuniform((const std::string *)&v140);
  uniform::set<float>(v54, v123, v127);
  std::string::~string((std::string *)&v140);
  std::string::string(&v140, "l3", &v113);
  v55 = (uniform *)program::getuniform((const std::string *)&v140);
  uniform::set<float>(v55, v124, v128);
  std::string::~string((std::string *)&v140);
  std::string::string(&v140, "l4", &v113);
  v56 = (uniform *)program::getuniform((const std::string *)&v140);
  uniform::set<float>(v56, v125, v129);
  std::string::~string((std::string *)&v140);
  v57 = (float)(v118 / v119) - 0.5625;
  if ( v57 <= 0.0 )
    v57 = 0.0;
  std::string::string(&v140, "precalc_ratio", &v113);
  v58 = (uniform *)program::getuniform((const std::string *)&v140);
  uniform::set<float>(v58, v57 + 1.0);
  std::string::~string((std::string *)&v140);
  glViewport(0, 0, (int)v118, (int)v119);
  glDisable(0xBE2u);
  varray::update((int)this);
  program::update(*((program **)this + 20));
  glDrawElements(5u, 2 * *((_DWORD *)this + 15) * (*((_DWORD *)this + 14) + 2) - 2, 0x1403u, 0);
  glEnable(0xBE2u);
  varray::update((int)this + 28);
  std::mersenne_twister_engine<unsigned int,32u,624u,397u,31u,2567483615u,11u,4294967295u,7u,2636928640u,15u,4022730752u,18u,1812433253u>::seed(
    &v140,
    5489);
  std::mersenne_twister_engine<unsigned int,32u,624u,397u,31u,2567483615u,11u,4294967295u,7u,2636928640u,15u,4022730752u,18u,1812433253u>::seed(
    &v140,
    1337);
  glBlendFunc(0x302u, 0x303u);
  while ( 1 )
  {
    std::string::string(&v113, "lineCount", v112);
    v61 = *(double *)std::map<std::string,themeparameter>::operator[](&v116, (const std::string *)&v113, v59, v60);
    std::string::~string((std::string *)&v113);
    if ( (double)v41 >= v61 )
      break;
    std::string::string(&v113, "ra", v112);
    v62 = (uniform *)program::getuniform((const std::string *)&v113);
    uniform::set<float>(v62, (float)v41);
    std::string::~string((std::string *)&v113);
    std::string::string(v112, "precalc_radlc", &v110);
    v101 = (uniform *)program::getuniform((const std::string *)v112);
    std::string::string(&v113, "lineCount", v111);
    v65 = *(double *)std::map<std::string,themeparameter>::operator[](&v116, (const std::string *)&v113, v63, v64);
    uniform::set<float>(v101, (float)v41 / v65);
    std::string::~string((std::string *)&v113);
    std::string::~string((std::string *)v112);
    v66 = (float)std::mersenne_twister_engine<unsigned int,32u,624u,397u,31u,2567483615u,11u,4294967295u,7u,2636928640u,15u,4022730752u,18u,1812433253u>::operator()(&v140)
        * 2.3283e-10;
    v67 = std::mersenne_twister_engine<unsigned int,32u,624u,397u,31u,2567483615u,11u,4294967295u,7u,2636928640u,15u,4022730752u,18u,1812433253u>::operator()(&v140);
    v68 = (float)std::mersenne_twister_engine<unsigned int,32u,624u,397u,31u,2567483615u,11u,4294967295u,7u,2636928640u,15u,4022730752u,18u,1812433253u>::operator()(&v140)
        * 2.3283e-10;
    v69 = std::mersenne_twister_engine<unsigned int,32u,624u,397u,31u,2567483615u,11u,4294967295u,7u,2636928640u,15u,4022730752u,18u,1812433253u>::operator()(&v140);
    std::string::string(&v113, "precalc_randval", v112);
    v70 = (uniform *)program::getuniform((const std::string *)&v113);
    v71 = (float)v69 * 2.3283e-10;
    uniform::set<float>(v70, v66, (float)v67 * 2.3283e-10, v68 * 0.13, v71);
    std::string::~string((std::string *)&v113);
    std::string::string(&v113, "lineCount", v112);
    v74 = *(double *)std::map<std::string,themeparameter>::operator[](&v116, (const std::string *)&v113, v72, v73);
    std::string::~string((std::string *)&v113);
    std::string::string(&v110, "precalc_car", v106);
    v99 = (uniform *)program::getuniform((const std::string *)&v110);
    std::string::string(v111, "curveAmplitudeRange", v107);
    v77 = (float)((float)((float)((float)v41 / v74) * 0.5) + 0.5) * v53;
    v78 = *((double *)std::map<std::string,themeparameter>::operator[](&v116, (const std::string *)v111, v75, v76) + 1);
    std::string::string(v112, "curveAmplitudeRange", v108);
    v81 = *(double *)std::map<std::string,themeparameter>::operator[](&v116, (const std::string *)v112, v79, v80);
    std::string::string(&v113, "curveAmplitudeRange", v109);
    *(float *)&v78 = v78 - v81;
    *(float *)&v81 = *(double *)std::map<std::string,themeparameter>::operator[](
                                  &v116,
                                  (const std::string *)&v113,
                                  v82,
                                  v83);
    uniform::set<float>(v99, (float)(*(float *)&v78 * v68) * v77, *(float *)&v81 * v77);
    std::string::~string((std::string *)&v113);
    std::string::~string((std::string *)v112);
    std::string::~string((std::string *)v111);
    std::string::~string((std::string *)&v110);
    std::string::string(v109, "precalc_curveParams", v104);
    v102 = (uniform *)program::getuniform((const std::string *)v109);
    std::string::string(&v110, "curveFrequencyRange", v105);
    *(float *)&v78 = *(double *)std::map<std::string,themeparameter>::operator[](
                                  &v116,
                                  (const std::string *)&v110,
                                  v84,
                                  v85);
    std::string::string(v111, "curveFrequencyRange", v106);
    v88 = *((double *)std::map<std::string,themeparameter>::operator[](&v116, (const std::string *)v111, v86, v87) + 1);
    v89 = mix(*(float *)&v78, v88, v66);
    std::string::string(v112, "curveSpeedRange", v107);
    *((float *)&v78 + 1) = *(double *)std::map<std::string,themeparameter>::operator[](
                                        &v116,
                                        (const std::string *)v112,
                                        v90,
                                        v91);
    std::string::string(&v113, "curveSpeedRange", v108);
    *(float *)&v81 = *((double *)std::map<std::string,themeparameter>::operator[](
                                   &v116,
                                   (const std::string *)&v113,
                                   v92,
                                   v93)
                     + 1);
    v94 = mix(*((float *)&v78 + 1), *(float *)&v81, (float)v67 * 2.3283e-10);
    v95 = cos(v71 * 3.14159);
    if ( *((_DWORD *)v102 + 1) )
    {
      v96 = (float *)*((_DWORD *)v102 + 3);
      if ( v96 )
      {
        v97 = v95;
        if ( *v96 != v89 || v96[1] != v94 || v96[2] != v97 )
        {
          *v96 = v89;
          if ( *((int *)v102 + 2) > 1 )
            *(float *)(*((_DWORD *)v102 + 3) + 4) = v94;
          if ( *((int *)v102 + 2) > 2 )
            *(float *)(*((_DWORD *)v102 + 3) + 8) = v97;
          uniform::touched(v102);
        }
      }
    }
    std::string::~string((std::string *)&v113);
    std::string::~string((std::string *)v112);
    std::string::~string((std::string *)v111);
    std::string::~string((std::string *)&v110);
    std::string::~string((std::string *)v109);
    program::update(*((program **)this + 19));
    glDrawElements(5u, 2 * *((_DWORD *)this + 17) * (*((_DWORD *)this + 16) + 2) - 2, 0x1403u, 0);
    ++v41;
  }
  std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_erase(
    (int)&v116,
    v117[1]);
}
// A34A: variable 'v3' is possibly undefined
// ABD8: variable 'v59' is possibly undefined
// ABD8: variable 'v60' is possibly undefined
// ACBE: variable 'v63' is possibly undefined
// ACBE: variable 'v64' is possibly undefined
// AD6C: variable 'v72' is possibly undefined
// AD6C: variable 'v73' is possibly undefined
// ADB4: variable 'v75' is possibly undefined
// ADB4: variable 'v76' is possibly undefined
// ADD6: variable 'v79' is possibly undefined
// ADD6: variable 'v80' is possibly undefined
// ADF4: variable 'v82' is possibly undefined
// ADF4: variable 'v83' is possibly undefined
// AE68: variable 'v84' is possibly undefined
// AE68: variable 'v85' is possibly undefined
// AE86: variable 'v86' is possibly undefined
// AE86: variable 'v87' is possibly undefined
// AEBE: variable 'v90' is possibly undefined
// AEBE: variable 'v91' is possibly undefined
// AEDC: variable 'v92' is possibly undefined
// AEDC: variable 'v93' is possibly undefined
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);
// 7918: using guessed type int __fastcall std::string::string(_DWORD, _DWORD, _DWORD);


