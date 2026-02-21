// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: lodepng  Functions: 17

//----- (00011524) --------------------------------------------------------
int __fastcall lodepng::save_file(int a1, _DWORD *a2)
{
  int v3; // r2
  const char *v4; // r1
  _BYTE v6[248]; // [sp+4h] [bp-F8h] BYREF

  std::ofstream::basic_ofstream(v6, *a2, 20);
  v3 = *(_DWORD *)(a1 + 4);
  if ( *(_DWORD *)a1 == v3 )
    v4 = 0;
  else
    v4 = *(const char **)a1;
  std::ostream::write((std::ostream *)v6, v4, v3 - *(_DWORD *)a1);
  return std::ofstream::~ofstream(v6);
}
// 7BC4: using guessed type int __fastcall std::ofstream::basic_ofstream(_DWORD, _DWORD, _DWORD);
// 7BDC: using guessed type int __fastcall std::ofstream::~ofstream(_DWORD);


//----- (000115E0) --------------------------------------------------------
int __fastcall lodepng::load_file(void **a1, _DWORD *a2)
{
  int v3; // r1
  _DWORD *v4; // r0
  int v5; // r1
  int v6; // r5
  _DWORD *v7; // r0
  _BYTE *v8; // r0
  unsigned int v9; // r7
  unsigned int v10; // r7
  unsigned int v11; // r0
  unsigned int v12; // r9
  char *v13; // r8
  char *v14; // r0
  char *v15; // r10
  _DWORD v17[4]; // [sp+8h] [bp-108h] BYREF
  _BYTE v18[248]; // [sp+18h] [bp-F8h] BYREF

  std::ifstream::basic_ifstream(v18, *a2, 14);
  v4 = (_DWORD *)std::istream::seekg(v18, v3, 0, 0, 2);
  if ( *(_DWORD *)((char *)v4 + *(_DWORD *)(*v4 - 12) + 20) )
  {
    v6 = 0;
  }
  else
  {
    std::istream::tellg((std::istream *)v17);
    v6 = v17[0];
  }
  v7 = (_DWORD *)std::istream::seekg(v18, v5, 0, 0, 0);
  if ( !*(_DWORD *)((char *)v7 + *(_DWORD *)(*v7 - 12) + 20) )
  {
    std::istream::tellg((std::istream *)v17);
    v6 -= v17[0];
  }
  v8 = a1[1];
  v9 = v8 - (_BYTE *)*a1;
  if ( v6 <= v9 )
  {
    if ( v6 < v9 )
      a1[1] = (char *)*a1 + v6;
  }
  else
  {
    v10 = v6 - v9;
    if ( v10 )
    {
      if ( (_BYTE *)a1[2] - v8 < v10 )
      {
        v11 = std::vector<unsigned char>::_M_check_len(a1, v10, "vector::_M_default_append");
        v12 = v11;
        if ( v11 )
          v13 = (char *)operator new(v11);
        else
          v13 = 0;
        v14 = (char *)std::__copy_move<true,true,std::random_access_iterator_tag>::__copy_m<unsigned char>(
                        *a1,
                        a1[1],
                        v13);
        v15 = &v14[v10];
        memset(v14, 0, v10);
        if ( *a1 )
          operator delete(*a1);
        *a1 = v13;
        a1[1] = v15;
        a1[2] = &v13[v12];
      }
      else
      {
        memset(v8, 0, v10);
        a1[1] = (char *)a1[1] + v10;
      }
    }
  }
  if ( v6 > 0 )
    std::istream::read((std::istream *)v18, (char *)*a1, v6);
  return std::ifstream::~ifstream(v18);
}
// 115FE: variable 'v3' is possibly undefined
// 11628: variable 'v5' is possibly undefined
// 7BF4: using guessed type int __fastcall std::ifstream::basic_ifstream(_DWORD, _DWORD, _DWORD);
// 7C00: using guessed type int __fastcall std::istream::seekg(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 7C24: using guessed type int __fastcall std::ifstream::~ifstream(_DWORD);


//----- (000117C0) --------------------------------------------------------
int __fastcall lodepng::decode(
        int a1,
        unsigned int *a2,
        unsigned int *a3,
        unsigned __int8 *a4,
        unsigned int a5,
        void *a6,
        void *a7)
{
  int v10; // r0
  int v11; // r9
  int v12; // r1
  int v13; // r0
  unsigned int raw_size; // r0
  char *v16; // [sp+10h] [bp-134h] BYREF
  void *v17[26]; // [sp+14h] [bp-130h] BYREF
  unsigned int v18[50]; // [sp+7Ch] [bp-C8h] BYREF

  v10 = lodepng_decode_memory((unsigned __int8 **)&v16, a2, a3, a4, a5, a6, a7);
  v11 = v10;
  if ( v16 && !v10 )
  {
    lodepng::State::State((lodepng::State *)v17);
    v12 = *a3;
    v13 = *a2;
    v18[0] = (unsigned int)a6;
    v18[1] = (unsigned int)a7;
    raw_size = lodepng_get_raw_size(v13, v12, v18);
    std::vector<unsigned char>::_M_range_insert<unsigned char *>((void **)a1, *(char **)(a1 + 4), v16, &v16[raw_size]);
    free(v16);
    lodepng::State::~State(v17);
  }
  return v11;
}


//----- (00011830) --------------------------------------------------------
int __fastcall lodepng::decode(int a1, unsigned int *a2, unsigned int *a3, unsigned __int8 **a4, void *a5, void *a6)
{
  unsigned __int8 *v6; // r4
  unsigned __int8 *v7; // r3
  unsigned __int8 *v8; // r3
  unsigned int v10; // [sp+0h] [bp-14h]

  v6 = *a4;
  v7 = a4[1];
  v10 = v7 - v6;
  if ( v6 == v7 )
    v8 = 0;
  else
    v8 = v6;
  return lodepng::decode(a1, a2, a3, v8, v10, a5, a6);
}


//----- (00011854) --------------------------------------------------------
int __fastcall lodepng::decode(int a1, unsigned int *a2, unsigned int *a3, _DWORD *a4, void *a5, void *a6)
{
  int v9; // r4
  void *v11[4]; // [sp+Ch] [bp-10h] BYREF

  memset(v11, 0, 12);
  lodepng::load_file(v11, a4);
  v9 = lodepng::decode(a1, a2, a3, (unsigned __int8 **)v11, a5, a6);
  if ( v11[0] )
    operator delete(v11[0]);
  return v9;
}


//----- (00011894) --------------------------------------------------------
int __fastcall lodepng::encode(int a1, unsigned __int8 *a2, void *a3, unsigned int a4, LodePNGState *a5)
{
  int v6; // r5
  void *p; // [sp+8h] [bp-8h] BYREF
  unsigned int v9; // [sp+Ch] [bp-4h] BYREF

  p = a3;
  v9 = a4;
  v6 = lodepng_encode((unsigned __int8 **)&p, &v9, a2, (unsigned int)a3, a4, a5);
  if ( p )
  {
    std::vector<unsigned char>::_M_range_insert<unsigned char *>(
      (void **)a1,
      *(char **)(a1 + 4),
      (char *)p,
      (char *)p + v9);
    free(p);
  }
  return v6;
}


//----- (000118D4) --------------------------------------------------------
int __fastcall lodepng::encode(int a1, unsigned __int8 **a2, void *a3, unsigned int a4, LodePNGState *a5)
{
  unsigned int raw_size; // r0
  unsigned __int8 *v10; // r1
  unsigned __int8 *v11; // r4
  unsigned __int8 *v12; // r1

  raw_size = lodepng_get_raw_size((int)a3, a4, (unsigned int *)a5 + 26);
  v10 = a2[1];
  v11 = *a2;
  if ( raw_size > v10 - v11 )
    return 84;
  if ( v11 == v10 )
    v12 = 0;
  else
    v12 = v11;
  return lodepng::encode(a1, v12, a3, a4, a5);
}


//----- (00011916) --------------------------------------------------------
void *__fastcall lodepng::encode(int a1, unsigned __int8 *a2, unsigned int a3, unsigned int a4, void *a5, void *a6)
{
  void *v7; // r5
  void *p; // [sp+10h] [bp-8h] BYREF
  unsigned int v10; // [sp+14h] [bp-4h] BYREF

  v7 = lodepng_encode_memory((unsigned __int8 **)&p, &v10, a2, a3, a4, a5, a6);
  if ( p )
  {
    std::vector<unsigned char>::_M_range_insert<unsigned char *>(
      (void **)a1,
      *(char **)(a1 + 4),
      (char *)p,
      (char *)p + v10);
    free(p);
  }
  return v7;
}


//----- (0001195C) --------------------------------------------------------
void *__fastcall lodepng::encode(int a1, unsigned __int8 **a2, unsigned int a3, unsigned int a4, void *a5, void *a6)
{
  unsigned int raw_size_lct; // r0
  unsigned __int8 *v11; // r1
  unsigned __int8 *v12; // r4
  unsigned __int8 *v13; // r1

  raw_size_lct = lodepng_get_raw_size_lct(a3, a4, (unsigned int)a5, (int)a6);
  v11 = a2[1];
  v12 = *a2;
  if ( raw_size_lct > v11 - v12 )
    return &dword_54;
  if ( v12 == v11 )
    v13 = 0;
  else
    v13 = v12;
  return lodepng::encode(a1, v13, a3, a4, a5, a6);
}
// 54: using guessed type int;


//----- (000119A6) --------------------------------------------------------
void *__fastcall lodepng::encode(_DWORD *a1, unsigned __int8 *a2, unsigned int a3, unsigned int a4, void *a5, void *a6)
{
  void *v7; // r4
  void *v9[3]; // [sp+Ch] [bp-Ch] BYREF

  memset(v9, 0, sizeof(v9));
  v7 = lodepng::encode((int)v9, a2, a3, a4, a5, a6);
  if ( !v7 )
    lodepng::save_file((int)v9, a1);
  if ( v9[0] )
    operator delete(v9[0]);
  return v7;
}


//----- (000119DE) --------------------------------------------------------
void *__fastcall lodepng::encode(
        _DWORD *a1,
        unsigned __int8 **a2,
        unsigned int a3,
        unsigned int a4,
        void *a5,
        void *a6)
{
  unsigned int raw_size_lct; // r0
  unsigned __int8 *v11; // r1
  unsigned __int8 *v12; // r4
  unsigned __int8 *v13; // r1

  raw_size_lct = lodepng_get_raw_size_lct(a3, a4, (unsigned int)a5, (int)a6);
  v11 = a2[1];
  v12 = *a2;
  if ( raw_size_lct > v11 - v12 )
    return &dword_54;
  if ( v12 == v11 )
    v13 = 0;
  else
    v13 = v12;
  return lodepng::encode(a1, v13, a3, a4, a5, a6);
}
// 54: using guessed type int dword_54;


//----- (00011A28) --------------------------------------------------------
int __fastcall lodepng::decompress(int a1, unsigned __int8 *a2, unsigned int a3, _DWORD *a4)
{
  int v5; // r5
  void *p; // [sp+8h] [bp-8h] BYREF
  unsigned int v8; // [sp+Ch] [bp-4h] BYREF

  p = 0;
  v8 = 0;
  v5 = sub_E004((int *)&p, &v8, a2, a3, a4);
  if ( p )
  {
    std::vector<unsigned char>::_M_range_insert<unsigned char *>(
      (void **)a1,
      *(char **)(a1 + 4),
      (char *)p,
      (char *)p + v8);
    free(p);
  }
  return v5;
}


//----- (00011A6A) --------------------------------------------------------
int __fastcall lodepng::decompress(int a1, unsigned __int8 **a2, _DWORD *a3)
{
  unsigned __int8 *v4; // r2
  unsigned __int8 *v5; // r5
  unsigned __int8 *v6; // r1

  v4 = *a2;
  v5 = a2[1];
  if ( *a2 == v5 )
    v6 = 0;
  else
    v6 = *a2;
  return lodepng::decompress(a1, v6, v5 - v4, a3);
}


//----- (00011A84) --------------------------------------------------------
int __fastcall lodepng::compress(int a1, unsigned __int8 *a2, unsigned int a3, int *a4)
{
  int v5; // r5
  void *p; // [sp+8h] [bp-8h] BYREF
  int v8; // [sp+Ch] [bp-4h] BYREF

  p = 0;
  v8 = 0;
  v5 = sub_E0B4((int *)&p, &v8, a2, a3, a4);
  if ( p )
  {
    std::vector<unsigned char>::_M_range_insert<unsigned char *>(
      (void **)a1,
      *(char **)(a1 + 4),
      (char *)p,
      (char *)p + v8);
    free(p);
  }
  return v5;
}


//----- (00011AC6) --------------------------------------------------------
int __fastcall lodepng::compress(int a1, unsigned __int8 **a2, int *a3)
{
  unsigned __int8 *v4; // r2
  unsigned __int8 *v5; // r5
  unsigned __int8 *v6; // r1

  v4 = *a2;
  v5 = a2[1];
  if ( *a2 == v5 )
    v6 = 0;
  else
    v6 = *a2;
  return lodepng::compress(a1, v6, v5 - v4, a3);
}


//----- (00011AE0) --------------------------------------------------------
int __fastcall lodepng::decode(
        int a1,
        unsigned int *a2,
        unsigned int *a3,
        unsigned int *a4,
        unsigned __int8 *a5,
        unsigned int a6)
{
  int v10; // r0
  int v11; // r5
  unsigned int raw_size; // r0
  void *p; // [sp+Ch] [bp-4h] BYREF

  p = a4;
  v10 = lodepng_decode((unsigned __int8 **)&p, a2, a3, (LodePNGState *)a4, a5, a6);
  v11 = v10;
  if ( p && !v10 )
  {
    raw_size = lodepng_get_raw_size(*a2, *a3, a4 + 26);
    std::vector<unsigned char>::_M_range_insert<unsigned char *>(
      (void **)a1,
      *(char **)(a1 + 4),
      (char *)p,
      (char *)p + raw_size);
    free(p);
  }
  return v11;
}


//----- (00011B30) --------------------------------------------------------
int __fastcall lodepng::decode(int a1, unsigned int *a2, unsigned int *a3, unsigned int *a4, int a5)
{
  int v5; // r5
  unsigned __int8 *v6; // r6

  v5 = *(_DWORD *)(a5 + 4);
  if ( *(_DWORD *)a5 == v5 )
    v6 = 0;
  else
    v6 = *(unsigned __int8 **)a5;
  return lodepng::decode(a1, a2, a3, a4, v6, v5 - *(_DWORD *)a5);
}


