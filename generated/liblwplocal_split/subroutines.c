// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: subroutines  Functions: 82

//----- (000076D0) --------------------------------------------------------
void sub_76D0()
{
  JUMPOUT(0);
}
// 76DC: control flows out of bounds to 0


//----- (00007D18) --------------------------------------------------------
int __fastcall sub_7D18(unsigned __int8 **a1, unsigned __int8 *a2, unsigned int a3)
{
  unsigned int *v3; // r8
  unsigned __int8 *i; // r4
  int result; // r0

  v3 = (unsigned int *)(a1 + 1);
  for ( i = a2; i - a2 < a3; i = lodepng_chunk_next(i) )
  {
    result = lodepng_chunk_append(a1, v3, i);
    if ( result )
      return result;
    a1[2] = a1[1];
  }
  return 0;
}


//----- (00007D50) --------------------------------------------------------
int __fastcall sub_7D50(int a1, int a2)
{
  unsigned int v4; // r4
  int v5; // r4
  unsigned __int8 *v7; // [sp+4h] [bp+0h] BYREF
  unsigned int v8; // [sp+8h] [bp+4h]
  int v9; // [sp+Ch] [bp+8h]

  v4 = 0;
  v7 = 0;
  v9 = 0;
  v8 = 0;
  while ( v4 < 4 * *(_DWORD *)(a2 + 12) )
  {
    if ( (v4 & 3) != 3 )
      sub_C612(&v7, *(_BYTE *)(*(_DWORD *)(a2 + 8) + v4));
    ++v4;
  }
  v5 = sub_E2D8(a1, "PLTE", v7, v8);
  sub_C368((int)&v7);
  return v5;
}


//----- (00007DA0) --------------------------------------------------------
int __fastcall sub_7DA0(int a1, int *a2)
{
  int v4; // r3
  int v5; // r5
  int v6; // r3
  int v7; // r2
  int i; // r6
  int v9; // r3
  char v10; // r1
  int v11; // r4
  unsigned __int8 *v13; // [sp+4h] [bp-Ch] BYREF
  unsigned int v14; // [sp+8h] [bp-8h]
  int v15; // [sp+Ch] [bp-4h]

  v13 = 0;
  v15 = 0;
  v14 = 0;
  v4 = *a2;
  if ( *a2 != 3 )
  {
    if ( v4 )
    {
      if ( v4 != 2 || !a2[4] )
        goto LABEL_16;
      sub_C612(&v13, *((_BYTE *)a2 + 21));
      sub_C612(&v13, *((_BYTE *)a2 + 20));
      sub_C612(&v13, *((_BYTE *)a2 + 25));
      sub_C612(&v13, *((_BYTE *)a2 + 24));
      sub_C612(&v13, *((_BYTE *)a2 + 29));
      v10 = *((_BYTE *)a2 + 28);
    }
    else
    {
      if ( !a2[4] )
        goto LABEL_16;
      sub_C612(&v13, *((_BYTE *)a2 + 21));
      v10 = *((_BYTE *)a2 + 20);
    }
    sub_C612(&v13, v10);
    goto LABEL_16;
  }
  v5 = a2[3];
  v6 = 4 * v5;
  while ( v5 )
  {
    v7 = a2[2] + v6;
    v6 -= 4;
    if ( *(unsigned __int8 *)(v7 - 1) != 255 )
      break;
    --v5;
  }
  for ( i = 0; i != v5; ++i )
  {
    v9 = a2[2] + 4 * i;
    sub_C612(&v13, *(_BYTE *)(v9 + 3));
  }
LABEL_16:
  v11 = sub_E2D8(a1, "tRNS", v13, v14);
  sub_C368((int)&v13);
  return v11;
}


//----- (00007E5C) --------------------------------------------------------
int __fastcall sub_7E5C(int a1, int a2, int a3)
{
  int v6; // r4
  char v7; // r1
  int v8; // r5
  char v9; // r1
  int v10; // t1
  int v11; // r5
  unsigned __int8 *v13; // [sp+4h] [bp-Ch] BYREF
  unsigned int v14; // [sp+8h] [bp-8h]
  int v15; // [sp+Ch] [bp-4h]

  v6 = 0;
  v13 = 0;
  v15 = 0;
  v14 = 0;
  while ( 1 )
  {
    v7 = *(_BYTE *)(a2 + v6);
    if ( !v7 )
      break;
    ++v6;
    sub_C612(&v13, v7);
  }
  if ( (unsigned int)(v6 - 1) > 0x4E )
    return 89;
  v8 = a3 - 1;
  sub_C612(&v13, v7);
  while ( 1 )
  {
    v10 = *(unsigned __int8 *)++v8;
    v9 = v10;
    if ( !v10 )
      break;
    sub_C612(&v13, v9);
  }
  v11 = sub_E2D8(a1, "tEXt", v13, v14);
  sub_C368((int)&v13);
  return v11;
}


//----- (00007EC4) --------------------------------------------------------
int sub_7EC4()
{
  return _cxa_finalize(&unk_18000);
}


//----- (00007ED4) --------------------------------------------------------
int sub_7ED4()
{
  memset(&unk_18848, 0, 0x10u);
  dword_18858 = 0;
  dword_18850 = (int)&unk_18848;
  dword_18854 = (int)&unk_18848;
  _aeabi_atexit(&program::attribs, std::map<std::string,attribute *>::~map, &unk_18000);
  memset(&unk_18830, 0, 0x10u);
  dword_18840 = 0;
  dword_18838 = (int)&unk_18830;
  dword_1883C = (int)&unk_18830;
  return j___aeabi_atexit();
}
// 796C: using guessed type int __fastcall _aeabi_atexit(_DWORD, _DWORD, _DWORD);
// 8B92: using guessed type int std::map<std::string,attribute *>::~map();
// 8BC6: using guessed type int std::map<std::string,uniform *>::~map();
// 18838: using guessed type int dword_18838;
// 1883C: using guessed type int dword_1883C;
// 18840: using guessed type int dword_18840;
// 18850: using guessed type int dword_18850;
// 18854: using guessed type int dword_18854;
// 18858: using guessed type int dword_18858;


//----- (00007F48) --------------------------------------------------------
int sub_7F48()
{
  std::ios_base::Init::Init((std::ios_base::Init *)&unk_1885C);
  return j___aeabi_atexit();
}


//----- (00007F74) --------------------------------------------------------
int sub_7F74()
{
  std::ios_base::Init::Init((std::ios_base::Init *)&unk_1885D);
  return j___aeabi_atexit();
}


//----- (00007FA0) --------------------------------------------------------
int sub_7FA0()
{
  memset(&unk_18864, 0, 0x10u);
  dword_1886C = (int)&unk_18864;
  dword_18874 = 0;
  dword_18870 = (int)&unk_18864;
  return j___aeabi_atexit();
}
// AFFE: using guessed type int std::map<int,RendererInterface>::~map();
// 1886C: using guessed type int dword_1886C;
// 18870: using guessed type int dword_18870;
// 18874: using guessed type int dword_18874;


//----- (00007FDC) --------------------------------------------------------
int sub_7FDC()
{
  std::ios_base::Init::Init((std::ios_base::Init *)&unk_1887C);
  _aeabi_atexit(&unk_1887C, &std::ios_base::Init::~Init, &unk_18000);
  framebuffer::fbstack = 0;
  dword_18884 = 0;
  dword_18888 = 0;
  return j___aeabi_atexit();
}
// 796C: using guessed type int __fastcall _aeabi_atexit(_DWORD, _DWORD, _DWORD);
// 18880: using guessed type int framebuffer::fbstack;
// 18884: using guessed type int dword_18884;
// 18888: using guessed type int dword_18888;


//----- (0000802C) --------------------------------------------------------
int sub_802C()
{
  std::ios_base::Init::Init((std::ios_base::Init *)&unk_1888C);
  return j___aeabi_atexit();
}


//----- (0000806C) --------------------------------------------------------
int __fastcall sub_806C(void *a1)
{
  return _cxa_atexit((void (*)(void *))sub_8058, a1, &unk_18000);
}


//----- (0000B664) --------------------------------------------------------
int __fastcall sub_B664(_DWORD *a1, int a2, int a3)
{
  int v3; // r3
  int result; // r0
  int v6; // r7
  char v7; // r6
  int v8; // r6

  v3 = 0;
  result = 0;
  while ( v3 != a3 )
  {
    v6 = *(unsigned __int8 *)(a2 + (*a1 >> 3));
    v7 = (*a1)++ & 7;
    v8 = ((v6 >> v7) & 1) << v3++;
    result += v8;
  }
  return result;
}


//----- (0000B690) --------------------------------------------------------
int __fastcall sub_B690(int result, int a2)
{
  int i; // r3

  for ( i = 0; ; ++i )
  {
    result += 16;
    if ( i == a2 )
      break;
    *(_DWORD *)(result - 16) = 0;
    *(_DWORD *)(result - 8) = 0;
    *(_DWORD *)(result - 12) = 0;
  }
  return result;
}


//----- (0000B6AE) --------------------------------------------------------
unsigned int __fastcall sub_B6AE(int a1, unsigned int a2)
{
  unsigned int result; // r0
  int v5; // r7
  unsigned int v6; // r4
  float *v7; // r2
  float *v8; // r3
  float v9; // s15
  int v10; // r1
  int v11; // r7
  int v12; // [sp+0h] [bp-Ch]
  float v13; // [sp+4h] [bp-8h]

  result = a2;
  v5 = 0;
  while ( result > 1 || v5 )
  {
    result = 10 * result / 0xD;
    if ( result - 9 <= 1 )
    {
      result = 11;
    }
    else if ( !result )
    {
      result = 1;
    }
    v6 = 0;
    v7 = (float *)(a1 + 12);
    v8 = (float *)(16 * result + a1 + 12);
    v5 = 0;
    v12 = 4 * result;
    while ( v6 < a2 - result )
    {
      v9 = *v8;
      if ( *v8 < *v7 )
      {
        *v8 = *v7;
        *v7 = v9;
        v10 = *((_DWORD *)v7 - 2);
        *(v7 - 2) = *(v8 - 2);
        *((_DWORD *)v8 - 2) = v10;
        v13 = v8[-4 * result - 1];
        v8[-4 * result - 1] = v7[v12 - 1];
        v7[v12 - 1] = v13;
        v11 = *((_DWORD *)v7 - 3);
        *(v7 - 3) = *(v8 - 3);
        *((_DWORD *)v8 - 3) = v11;
        v5 = 1;
      }
      ++v6;
      v8 += 4;
      v7 += 4;
    }
  }
  return result;
}


//----- (0000B76A) --------------------------------------------------------
int __fastcall sub_B76A(int a1, unsigned int *a2, _DWORD *a3, unsigned int a4)
{
  unsigned int v4; // r5
  unsigned int v5; // r4
  unsigned int v7; // r5
  unsigned int v8; // r4

  v4 = 0;
  while ( 1 )
  {
    v5 = *a2;
    if ( *a2 >= a4 )
      return -1;
    v7 = *(_DWORD *)(*a3 + 4 * ((((int)*(unsigned __int8 *)(a1 + (v5 >> 3)) >> (v5 & 7)) & 1) + 2 * v4));
    *a2 = v5 + 1;
    v8 = a3[4];
    if ( v7 < v8 )
      break;
    v4 = v7 - v8;
    if ( v4 >= v8 )
      return -1;
  }
  return v7;
}


//----- (0000B7AA) --------------------------------------------------------
unsigned int __fastcall sub_B7AA(int a1, int a2, unsigned int a3)
{
  unsigned int v3; // r1
  unsigned int v4; // r4
  unsigned int v5; // r5
  unsigned int v6; // r3

  v3 = a2 - 1;
  v4 = v3;
  v5 = 1;
  while ( v5 <= v4 )
  {
    v6 = (v4 + v5) >> 1;
    if ( *(_DWORD *)(a1 + 4 * v6) > a3 )
    {
      v4 = v6 - 1;
      if ( *(_DWORD *)(a1 + 4 * v6 - 4) <= a3 )
        return v6 - 1;
    }
    else
    {
      v5 = v6 + 1;
    }
  }
  return v3;
}


//----- (0000B7DE) --------------------------------------------------------
int __fastcall sub_B7DE(_DWORD *a1, unsigned int a2, int a3, unsigned int a4)
{
  int result; // r0
  int v7; // r1
  int v8; // r3

  v7 = a2 % a4;
  result = a2 / a4;
  *(_DWORD *)(a1[1] + 4 * v7) = a3;
  v8 = *(_DWORD *)(*a1 + 4 * a3);
  if ( v8 != -1 )
    *(_WORD *)(a1[2] + 2 * v7) = v8;
  *(_DWORD *)(*a1 + 4 * a3) = v7;
  return result;
}


//----- (0000B80A) --------------------------------------------------------
int __fastcall sub_B80A(_DWORD *a1, int a2)
{
  int v2; // r1
  char v3; // r2

  v2 = *(unsigned __int8 *)(a2 + (*a1 >> 3));
  v3 = ~(unsigned __int8)(*a1)++ & 7;
  return (v2 >> v3) & 1;
}


//----- (0000B824) --------------------------------------------------------
int __fastcall sub_B824(_DWORD *a1, int a2, unsigned int a3)
{
  unsigned int v3; // r4
  int v7; // r5
  int v8; // r0

  v3 = a3 - 1;
  v7 = 0;
  while ( v3 < a3 )
  {
    v8 = sub_B80A(a1, a2) << v3--;
    v7 += v8;
  }
  return v7;
}


//----- (0000B84C) --------------------------------------------------------
unsigned int *__fastcall sub_B84C(unsigned int *result, int a2, int a3)
{
  unsigned int v3; // r3
  unsigned int v4; // r2
  int v5; // r3

  v3 = *result;
  if ( a3 )
  {
    v4 = v3 >> 3;
    v5 = (1 << (~(_BYTE)v3 & 7)) | *(unsigned __int8 *)(a2 + (v3 >> 3));
  }
  else
  {
    v4 = v3 >> 3;
    v5 = *(unsigned __int8 *)(a2 + (v3 >> 3)) & ~(1 << (~(_BYTE)v3 & 7));
  }
  *(_BYTE *)(a2 + v4) = v5;
  ++*result;
  return result;
}


//----- (0000B884) --------------------------------------------------------
int __fastcall sub_B884(int a1, int a2)
{
  int result; // r0

  switch ( a1 )
  {
    case 0:
      if ( (unsigned int)(a2 - 1) <= 1 || a2 == 4 )
        goto LABEL_14;
      goto LABEL_4;
    case 2:
    case 4:
    case 6:
LABEL_4:
      if ( a2 == 8 )
        goto LABEL_14;
      if ( a2 == 16 )
        result = 0;
      else
        result = 37;
      break;
    case 3:
      if ( (unsigned int)(a2 - 1) <= 1 || a2 == 4 )
      {
LABEL_14:
        result = 0;
      }
      else if ( a2 == 8 )
      {
        result = 0;
      }
      else
      {
        result = 37;
      }
      break;
    default:
      result = 31;
      break;
  }
  return result;
}


//----- (0000B8C8) --------------------------------------------------------
unsigned int __fastcall sub_B8C8(int a1, unsigned int a2, unsigned int a3, int a4)
{
  unsigned int result; // r0
  unsigned int v7; // r1
  int v8; // r3
  unsigned int v9; // r4

  v7 = a2 % (8 / a3);
  result = a2 / (8 / a3);
  v8 = (((1 << a3) - 1) & a4) << ((8 / a3 - 1 - v7) * a3);
  v9 = (a3 * a2) >> 3;
  if ( v7 )
    LOBYTE(v8) = v8 | *(_BYTE *)(a1 + v9);
  *(_BYTE *)(a1 + v9) = v8;
  return result;
}


//----- (0000B90A) --------------------------------------------------------
int __fastcall sub_B90A(int a1, int a2, int a3, int a4, unsigned __int8 a5)
{
  int v5; // r4

  v5 = 0;
  while ( 1 )
  {
    a1 = *(_DWORD *)(a1
                   + 4
                   * ((((int)a5 >> v5) & 1) + 2 * (((a4 >> v5) & 1) + 2 * (((a3 >> v5) & 1) + 2 * ((a2 >> v5) & 1)))));
    if ( !a1 )
      break;
    if ( ++v5 == 8 )
      return *(_DWORD *)(a1 + 64);
  }
  return -1;
}


//----- (0000B954) --------------------------------------------------------
int __fastcall sub_B954(_BYTE *a1, _BYTE *a2, _BYTE *a3, char *a4, int a5, int a6, int *a7, int a8)
{
  int v12; // r10
  int v13; // r11
  int v14; // r3
  bool v15; // zf
  char v16; // r3
  unsigned int v17; // r2
  int v18; // r5
  unsigned int v19; // r0
  _BYTE *v20; // r1
  int v21; // r3
  bool v22; // zf
  _BYTE *v23; // r3
  char v25; // r3
  unsigned int v26; // r2
  unsigned int v27; // r0
  char v28; // r3
  char v29; // r3
  _BYTE *v30; // r1
  _BYTE *v31; // r1
  int v32; // [sp+Ch] [bp-8h] BYREF

  v12 = *a7;
  if ( !*a7 )
  {
    v13 = a7[1];
    if ( v13 == 8 )
    {
      v14 = *(unsigned __int8 *)(a5 + a6);
      *a3 = v14;
      *a2 = v14;
      *a1 = v14;
      if ( a7[4] )
      {
        v15 = v14 == a7[5];
        goto LABEL_8;
      }
    }
    else
    {
      if ( v13 != 16 )
      {
        v17 = a7[1];
        v32 = v13 * a6;
        v18 = sub_B824(&v32, a5, v17);
        v19 = 255 * v18 / (unsigned int)((1 << v13) - 1);
        *a3 = v19;
        *a2 = v19;
        *a1 = v19;
        if ( !a7[4] || v18 != a7[5] )
        {
          *a4 = -1;
          return 0;
        }
        goto LABEL_13;
      }
      v16 = *(_BYTE *)(a5 + 2 * a6);
      *a3 = v16;
      *a2 = v16;
      *a1 = v16;
      if ( a7[4] )
      {
        v15 = *(unsigned __int8 *)(a5 + 2 * a6 + 1) + (*(unsigned __int8 *)(a5 + 2 * a6) << 8) == a7[5];
LABEL_8:
        if ( !v15 )
          goto LABEL_28;
LABEL_13:
        *a4 = 0;
        return 0;
      }
    }
LABEL_28:
    v25 = -1;
LABEL_48:
    *a4 = v25;
    return 0;
  }
  if ( v12 == 2 )
  {
    if ( a7[1] == 8 )
    {
      v20 = (_BYTE *)(a5 + 3 * a6);
      *a1 = *v20;
      *a2 = v20[1];
      v21 = (unsigned __int8)v20[2];
      *a3 = v21;
      if ( !a7[4] || (unsigned __int8)*a1 != a7[5] || (unsigned __int8)*a2 != a7[6] )
        goto LABEL_28;
      v22 = v21 == a7[7];
    }
    else
    {
      v23 = (_BYTE *)(a5 + 6 * a6);
      *a1 = *v23;
      *a2 = *(_BYTE *)(a5 + 6 * a6 + 2);
      *a3 = *(_BYTE *)(a5 + 6 * a6 + 4);
      if ( !a7[4]
        || (unsigned __int8)v23[1] + (*(unsigned __int8 *)(a5 + 6 * a6) << 8) != a7[5]
        || (unsigned __int8)v23[3] + (*(unsigned __int8 *)(a5 + 6 * a6 + 2) << 8) != a7[6] )
      {
        goto LABEL_28;
      }
      v22 = (unsigned __int8)v23[5] + (*(unsigned __int8 *)(a5 + 6 * a6 + 4) << 8) == a7[7];
    }
    if ( v22 )
    {
      *a4 = 0;
      return 0;
    }
    goto LABEL_28;
  }
  if ( v12 != 3 )
  {
    if ( v12 == 4 )
    {
      if ( a7[1] == 8 )
      {
        v28 = *(_BYTE *)(a5 + 2 * a6);
        *a3 = v28;
        *a2 = v28;
        *a1 = v28;
        v25 = *(_BYTE *)(a5 + 2 * a6 + 1);
      }
      else
      {
        v29 = *(_BYTE *)(a5 + 4 * a6);
        *a3 = v29;
        *a2 = v29;
        *a1 = v29;
        v25 = *(_BYTE *)(a5 + 4 * a6 + 2);
      }
      goto LABEL_48;
    }
    if ( v12 == 6 )
    {
      if ( a7[1] == 8 )
      {
        v30 = (_BYTE *)(a5 + 4 * a6);
        *a1 = *v30;
        *a2 = v30[1];
        *a3 = v30[2];
        v25 = v30[3];
      }
      else
      {
        v31 = (_BYTE *)(a5 + 8 * a6);
        *a1 = *v31;
        *a2 = v31[2];
        *a3 = v31[4];
        v25 = v31[6];
      }
      goto LABEL_48;
    }
    return 0;
  }
  v26 = a7[1];
  if ( v26 == 8 )
  {
    v27 = *(unsigned __int8 *)(a5 + a6);
  }
  else
  {
    v32 = a6 * v26;
    v27 = sub_B824(&v32, a5, v26);
  }
  if ( v27 < a7[3] )
  {
    *a1 = *(_BYTE *)(a7[2] + 4 * v27);
    *a2 = *(_BYTE *)(a7[2] + 4 * v27 + 1);
    *a3 = *(_BYTE *)(a7[2] + 4 * v27 + 2);
    v25 = *(_BYTE *)(4 * v27 + a7[2] + 3);
    goto LABEL_48;
  }
  if ( a8 )
  {
    *a3 = 0;
    *a2 = 0;
    *a1 = 0;
    *a4 = -1;
    return 0;
  }
  else if ( a7[1] == 8 )
  {
    return 46;
  }
  else
  {
    return 47;
  }
}


//----- (0000BB68) --------------------------------------------------------
int __fastcall sub_BB68(unsigned __int8 *a1, int a2, int a3, unsigned __int8 *a4, int *a5, int a6)
{
  int v10; // r9
  int v11; // r3
  int v12; // r2
  unsigned __int8 *v13; // r8
  unsigned __int8 v14; // t1
  char v15; // r3
  unsigned __int8 *v16; // r7
  unsigned __int8 v17; // r2
  char v18; // r2
  unsigned int v19; // r10
  int *v20; // r12
  unsigned int v21; // r0
  char v22; // r2
  unsigned __int8 *v23; // r7
  int i; // r2
  unsigned __int8 *v25; // r8
  int v26; // r0
  int v27; // r2
  int v28; // r3
  char v29; // r3
  char v30; // r3
  int v31; // r3
  int v32; // r10
  int v33; // r12
  unsigned int v34; // r2
  unsigned int v35; // r0
  int v37; // r3
  unsigned __int8 v38; // r2
  unsigned __int8 v39; // r2
  int v40; // r3
  int *v41; // [sp+4h] [bp-18h]
  int v42; // [sp+4h] [bp-18h]
  int v43; // [sp+8h] [bp-14h]
  int v44; // [sp+8h] [bp-14h]
  int v45; // [sp+Ch] [bp-10h]
  int v46; // [sp+14h] [bp-8h] BYREF

  if ( a3 )
    v10 = 4;
  else
    v10 = 3;
  v11 = *a5;
  if ( *a5 )
  {
    switch ( v11 )
    {
      case 2:
        if ( a5[1] == 8 )
        {
          v25 = &a4[3 * a2];
          while ( a4 != v25 )
          {
            v26 = *a4;
            *a1 = v26;
            v27 = a4[1];
            a1[1] = v27;
            v28 = a4[2];
            a1[2] = v28;
            if ( a3 )
            {
              if ( a5[4] && v26 == a5[5] && v27 == a5[6] )
              {
                if ( v28 == a5[7] )
                  v29 = 0;
                else
                  v29 = -1;
              }
              else
              {
                v29 = -1;
              }
              a1[3] = v29;
            }
            a1 += v10;
            a4 += 3;
          }
        }
        else
        {
          v23 = a4 + 5;
          for ( i = 0; i != a2; ++i )
          {
            *a1 = *(v23 - 5);
            a1[1] = *(v23 - 3);
            a1[2] = *(v23 - 1);
            if ( a3 )
            {
              if ( a5[4] && *(v23 - 4) + (*(v23 - 5) << 8) == a5[5] && *(v23 - 2) + (*(v23 - 3) << 8) == a5[6] )
              {
                if ( *v23 + (*(v23 - 1) << 8) == a5[7] )
                  v30 = 0;
                else
                  v30 = -1;
              }
              else
              {
                v30 = -1;
              }
              a1[3] = v30;
            }
            a1 += v10;
            v23 += 6;
          }
        }
        break;
      case 3:
        v31 = 0;
        v32 = 0;
        v33 = 255;
        v46 = 0;
        while ( v32 != a2 )
        {
          v34 = a5[1];
          if ( v34 == 8 )
          {
            v35 = a4[v32];
          }
          else
          {
            v44 = v31;
            v42 = v33;
            v35 = sub_B824(&v46, (int)a4, v34);
            v33 = v42;
            v31 = v44;
          }
          if ( v35 < a5[3] )
          {
            *a1 = *(_BYTE *)(a5[2] + 4 * v35);
            a1[1] = *(_BYTE *)(a5[2] + 4 * v35 + 1);
            a1[2] = *(_BYTE *)(a5[2] + 4 * v35 + 2);
            if ( a3 )
              a1[3] = *(_BYTE *)(4 * v35 + a5[2] + 3);
          }
          else
          {
            if ( !a6 )
            {
              if ( a5[1] == 8 )
                return 46;
              else
                return 47;
            }
            a1[2] = v31;
            a1[1] = v31;
            *a1 = v31;
            if ( a3 )
              a1[3] = v33;
          }
          ++v32;
          a1 += v10;
        }
        break;
      case 4:
        v37 = 0;
        if ( a5[1] == 8 )
        {
          while ( v37 != a2 )
          {
            v38 = *a4;
            a1[2] = *a4;
            a1[1] = v38;
            *a1 = v38;
            if ( a3 )
              a1[3] = a4[1];
            ++v37;
            a1 += v10;
            a4 += 2;
          }
        }
        else
        {
          while ( v37 != a2 )
          {
            v39 = *a4;
            a1[2] = *a4;
            a1[1] = v39;
            *a1 = v39;
            if ( a3 )
              a1[3] = a4[2];
            ++v37;
            a1 += v10;
            a4 += 4;
          }
        }
        break;
      case 6:
        v40 = 0;
        if ( a5[1] == 8 )
        {
          while ( v40 != a2 )
          {
            *a1 = *a4;
            a1[1] = a4[1];
            a1[2] = a4[2];
            if ( a3 )
              a1[3] = a4[3];
            ++v40;
            a1 += v10;
            a4 += 4;
          }
        }
        else
        {
          while ( v40 != a2 )
          {
            *a1 = *a4;
            a1[1] = a4[2];
            a1[2] = a4[4];
            if ( a3 )
              a1[3] = a4[6];
            ++v40;
            a1 += v10;
            a4 += 8;
          }
        }
        break;
    }
  }
  else
  {
    v12 = a5[1];
    if ( v12 == 8 )
    {
      v13 = &a4[a2];
      while ( a4 != v13 )
      {
        v14 = *a4++;
        a1[2] = v14;
        a1[1] = v14;
        *a1 = v14;
        if ( a3 )
        {
          if ( a5[4] )
          {
            if ( *(a4 - 1) == a5[5] )
              v15 = 0;
            else
              v15 = -1;
          }
          else
          {
            v15 = -1;
          }
          a1[3] = v15;
        }
        a1 += v10;
      }
    }
    else if ( v12 == 16 )
    {
      v16 = a4 + 1;
      while ( v11 != a2 )
      {
        v17 = *(v16 - 1);
        a1[2] = v17;
        a1[1] = v17;
        *a1 = v17;
        if ( a3 )
        {
          if ( a5[4] )
          {
            if ( *v16 + (*(v16 - 1) << 8) == a5[5] )
              v18 = 0;
            else
              v18 = -1;
          }
          else
          {
            v18 = -1;
          }
          a1[3] = v18;
        }
        ++v11;
        a1 += v10;
        v16 += 2;
      }
    }
    else
    {
      v19 = (1 << v12) - 1;
      v46 = *a5;
      v20 = &v46;
      while ( v11 != a2 )
      {
        v43 = v11;
        v41 = v20;
        v45 = sub_B824(v20, (int)a4, a5[1]);
        v21 = 255 * v45 / v19;
        v20 = v41;
        a1[2] = v21;
        a1[1] = v21;
        *a1 = v21;
        if ( a3 )
        {
          if ( a5[4] )
          {
            if ( v45 == a5[5] )
              v22 = 0;
            else
              v22 = -1;
          }
          else
          {
            v22 = -1;
          }
          a1[3] = v22;
        }
        v11 = v43 + 1;
        a1 += v10;
      }
    }
  }
  return 0;
}


//----- (0000BE38) --------------------------------------------------------
int __fastcall sub_BE38(int result, int a2, int a3)
{
  __int16 v3; // r3
  int v4; // r5
  __int16 v5; // r4

  v3 = a2 - a3;
  v4 = result + a2 - a3 - a3;
  if ( a2 - a3 < 0 )
    v3 = a3 - a2;
  if ( v4 < 0 )
    LOWORD(v4) = a3 - (result + a2 - a3);
  v5 = result - a3;
  if ( result - a3 < 0 )
    v5 = a3 - result;
  if ( (__int16)v4 < v3 && (__int16)v4 < v5 )
    return (unsigned __int8)a3;
  if ( v5 >= v3 )
    return (unsigned __int8)result;
  return (unsigned __int8)a2;
}


//----- (0000BE74) --------------------------------------------------------
_DWORD *__fastcall sub_BE74(int a1, int a2, _DWORD *a3, _DWORD *a4, _DWORD *a5, int a6, int a7, int a8)
{
  int i; // r4
  unsigned int v13; // r1
  unsigned int v14; // r0
  int v15; // r4
  unsigned int v16; // r3
  int v17; // r2
  _DWORD *result; // r0
  int v19; // r2
  int v20; // r3

  for ( i = 0; i != 28; i += 4 )
  {
    v13 = *(_DWORD *)((char *)&unk_15BA0 + i);
    *(_DWORD *)(a1 + i) = (unsigned int)(a6 - 1 + *(_DWORD *)&asc_15B68[i] - *(_DWORD *)((char *)&unk_15B84 + i))
                        / *(_DWORD *)&asc_15B68[i];
    v14 = (a7 - 1 + v13 - *(_DWORD *)((char *)&unk_15BBC + i)) / v13;
    *(_DWORD *)(a2 + i) = v14;
    if ( !*(_DWORD *)(a1 + i) )
      v14 = 0;
    *(_DWORD *)(a2 + i) = v14;
    if ( v14 )
      v14 = *(_DWORD *)(a1 + i);
    *(_DWORD *)(a1 + i) = v14;
  }
  v15 = 0;
  *a5 = 0;
  *a4 = 0;
  *a3 = 0;
  do
  {
    v16 = *(_DWORD *)(a1 + v15 * 4);
    if ( v16 )
    {
      v17 = *(_DWORD *)(a2 + v15 * 4);
      if ( v17 )
        v16 = (((v16 * a8 + 7) >> 3) + 1) * v17;
      else
        v16 = 0;
    }
    a3[v15 + 1] = v16 + a3[v15];
    a4[v15 + 1] = a4[v15] + *(_DWORD *)(a2 + v15 * 4) * ((unsigned int)(*(_DWORD *)(a1 + v15 * 4) * a8 + 7) >> 3);
    result = &a5[v15];
    v19 = *(_DWORD *)(a2 + v15 * 4) * *(_DWORD *)(a1 + v15 * 4) * a8;
    v20 = a5[v15++];
    result[1] = v20 + ((unsigned int)(v19 + 7) >> 3);
  }
  while ( v15 != 7 );
  return result;
}


//----- (0000BF58) --------------------------------------------------------
int __fastcall sub_BF58(int a1, int a2, int a3, int a4, int a5)
{
  int v5; // r5
  int v6; // r4
  int v7; // r11
  unsigned int v8; // r7
  unsigned int v9; // r8
  int v10; // r3
  int v11; // r9
  int v12; // r6
  int j; // r2
  int i; // r2
  unsigned int k; // r2
  int m; // r2
  int n; // r2
  unsigned int ii; // r2
  unsigned int jj; // r2
  int kk; // r2
  unsigned int v21; // r10
  unsigned int mm; // r2
  int v24; // [sp+4h] [bp-18h]
  char v25; // [sp+8h] [bp-14h]
  int v27; // [sp+14h] [bp-8h]

  v5 = 0;
  v6 = a2 + 1;
  v7 = 0;
  v8 = (unsigned int)(a5 + 7) >> 3;
  v9 = (unsigned int)(a3 * a5 + 7) >> 3;
  v10 = -v8;
  v11 = a1 - v8;
  while ( 2 )
  {
    if ( v7 != a4 )
    {
      v12 = v11 + v8;
      switch ( *(_BYTE *)(v6 - 1) )
      {
        case 0:
          for ( i = 0; i != v9; ++i )
            *(_BYTE *)(v12 + i) = *(_BYTE *)(v6 + i);
          goto LABEL_45;
        case 1:
          for ( j = 0; j != v8; ++j )
            *(_BYTE *)(v12 + j) = *(_BYTE *)(v6 + j);
          for ( k = (unsigned int)(a5 + 7) >> 3; k < v9; ++k )
            *(_BYTE *)(v12 + k) = *(_BYTE *)(v6 + k) + *(_BYTE *)(v11 + k);
          goto LABEL_45;
        case 2:
          if ( v5 )
          {
            for ( m = 0; m != v9; ++m )
              *(_BYTE *)(v12 + m) = *(_BYTE *)(v6 + m) + *(_BYTE *)(v5 + m);
          }
          else
          {
            while ( v5 != v9 )
            {
              *(_BYTE *)(v12 + v5) = *(_BYTE *)(v6 + v5);
              ++v5;
            }
          }
          goto LABEL_45;
        case 3:
          if ( v5 )
          {
            for ( n = 0; n != v8; ++n )
              *(_BYTE *)(v12 + n) = *(_BYTE *)(v6 + n) + (*(_BYTE *)(v5 + n) >> 1);
            for ( ii = (unsigned int)(a5 + 7) >> 3; ii < v9; ++ii )
              *(_BYTE *)(v12 + ii) = *(_BYTE *)(v6 + ii)
                                   + ((*(unsigned __int8 *)(v5 + ii) + (unsigned int)*(unsigned __int8 *)(v11 + ii)) >> 1);
          }
          else
          {
            while ( v5 != v8 )
            {
              *(_BYTE *)(v12 + v5) = *(_BYTE *)(v6 + v5);
              ++v5;
            }
            for ( jj = (unsigned int)(a5 + 7) >> 3; jj < v9; ++jj )
              *(_BYTE *)(v12 + jj) = *(_BYTE *)(v6 + jj) + (*(_BYTE *)(v11 + jj) >> 1);
          }
          goto LABEL_45;
        case 4:
          if ( v5 )
          {
            for ( kk = 0; kk != v8; ++kk )
              *(_BYTE *)(v12 + kk) = *(_BYTE *)(v6 + kk) + *(_BYTE *)(v5 + kk);
            v21 = (unsigned int)(a5 + 7) >> 3;
            v27 = v5 + v10;
            while ( v21 < v9 )
            {
              v24 = v10;
              v25 = *(_BYTE *)(v6 + v21);
              *(_BYTE *)(v12 + v21) = sub_BE38(
                                        *(unsigned __int8 *)(v11 + v21),
                                        *(unsigned __int8 *)(v5 + v21),
                                        *(unsigned __int8 *)(v27 + v21))
                                    + v25;
              v10 = v24;
              ++v21;
            }
          }
          else
          {
            while ( v5 != v8 )
            {
              *(_BYTE *)(v12 + v5) = *(_BYTE *)(v6 + v5);
              ++v5;
            }
            for ( mm = (unsigned int)(a5 + 7) >> 3; mm < v9; ++mm )
              *(_BYTE *)(v12 + mm) = *(_BYTE *)(v6 + mm) + *(_BYTE *)(v11 + mm);
          }
LABEL_45:
          ++v7;
          v11 += v9;
          v5 = v12;
          v6 += v9 + 1;
          continue;
        default:
          return 36;
      }
    }
    return 0;
  }
}


//----- (0000C0D2) --------------------------------------------------------
unsigned int *__fastcall sub_C0D2(unsigned int *result, int a2, unsigned int a3, int a4, int a5)
{
  int v5; // r11
  int v6; // r8
  int v9; // r5
  int i; // r4
  int v11; // r0
  int v12; // [sp+0h] [bp-Ch] BYREF
  unsigned int v13[2]; // [sp+4h] [bp-8h] BYREF

  v13[1] = a3;
  v5 = a4 - a3;
  v6 = (int)result;
  v9 = 0;
  v12 = 0;
  v13[0] = 0;
  while ( v9 != a5 )
  {
    for ( i = 0; i != a3; ++i )
    {
      v11 = sub_B80A(&v12, a2);
      result = sub_B84C(v13, v6, v11);
    }
    ++v9;
    v12 += v5;
  }
  return result;
}


//----- (0000C11E) --------------------------------------------------------
int __fastcall sub_C11E(int result, int a2, unsigned int a3, unsigned int a4, int a5, char a6)
{
  unsigned int v7; // r6
  int v8; // r5
  int i; // r3
  unsigned int j; // r3
  int v12; // r2
  int v13; // r3
  int k; // r3
  unsigned int m; // r3
  int v16; // r2
  int v17; // r3
  unsigned int n; // r8
  int v19; // r9
  unsigned int v20; // r10
  int v21; // r3

  v7 = a3;
  v8 = result;
  switch ( a6 )
  {
    case 0:
      for ( i = 0; i != a4; ++i )
        *(_BYTE *)(result + i) = *(_BYTE *)(a2 + i);
      break;
    case 1:
      if ( a3 )
      {
        for ( j = 0; j != a5; ++j )
          *(_BYTE *)(result + j) = *(_BYTE *)(a2 + j);
        v12 = a2 - j;
        while ( j < a4 )
        {
          result = *(unsigned __int8 *)(a2 + j);
          *(_BYTE *)(v8 + j) = result - *(_BYTE *)(v12 + j);
          ++j;
        }
      }
      else
      {
        while ( v7 != a5 )
        {
          *(_BYTE *)(result + v7) = *(_BYTE *)(a2 + v7);
          ++v7;
        }
        v13 = a2 - v7;
        while ( v7 < a4 )
        {
          *(_BYTE *)(result + v7) = *(_BYTE *)(a2 + v7) - *(_BYTE *)(v13 + v7);
          ++v7;
        }
      }
      break;
    case 2:
      if ( a3 )
      {
        for ( k = 0; k != a4; ++k )
          *(_BYTE *)(result + k) = *(_BYTE *)(a2 + k) - *(_BYTE *)(a3 + k);
      }
      else
      {
        while ( v7 != a4 )
        {
          *(_BYTE *)(result + v7) = *(_BYTE *)(a2 + v7);
          ++v7;
        }
      }
      break;
    case 3:
      if ( a3 )
      {
        for ( m = 0; m != a5; ++m )
        {
          result = *(unsigned __int8 *)(a2 + m);
          *(_BYTE *)(v8 + m) = result - (*(_BYTE *)(a3 + m) >> 1);
        }
        v16 = a2 - m;
        while ( m < a4 )
        {
          result = *(unsigned __int8 *)(a2 + m);
          *(_BYTE *)(v8 + m) = result
                             - ((*(unsigned __int8 *)(v7 + m) + (unsigned int)*(unsigned __int8 *)(v16 + m)) >> 1);
          ++m;
        }
      }
      else
      {
        while ( v7 != a5 )
        {
          *(_BYTE *)(result + v7) = *(_BYTE *)(a2 + v7);
          ++v7;
        }
        v17 = a2 - v7;
        while ( v7 < a4 )
        {
          *(_BYTE *)(result + v7) = *(_BYTE *)(a2 + v7) - (*(_BYTE *)(v17 + v7) >> 1);
          ++v7;
        }
      }
      break;
    case 4:
      if ( a3 )
      {
        for ( n = 0; n != a5; ++n )
          *(_BYTE *)(result + n) = *(_BYTE *)(a2 + n) - *(_BYTE *)(a3 + n);
        v19 = a2 - n;
        v20 = a3 - n;
        while ( n < a4 )
        {
          result = *(unsigned __int8 *)(a2 + n)
                 - sub_BE38(*(unsigned __int8 *)(v19 + n), *(unsigned __int8 *)(v7 + n), *(unsigned __int8 *)(v20 + n));
          *(_BYTE *)(v8 + n++) = result;
        }
      }
      else
      {
        while ( v7 != a5 )
        {
          *(_BYTE *)(result + v7) = *(_BYTE *)(a2 + v7);
          ++v7;
        }
        v21 = a2 - v7;
        while ( v7 < a4 )
        {
          *(_BYTE *)(result + v7) = *(_BYTE *)(a2 + v7) - *(_BYTE *)(v21 + v7);
          ++v7;
        }
      }
      break;
    default:
      return result;
  }
  return result;
}


//----- (0000C28E) --------------------------------------------------------
unsigned int *__fastcall sub_C28E(unsigned int *result, int a2, int a3, int a4, int a5)
{
  int v6; // r10
  int v7; // r6
  int v9; // r7
  int i; // r5
  int v11; // r0
  int j; // r5
  unsigned int v13; // [sp+0h] [bp-Ch] BYREF
  _DWORD v14[2]; // [sp+4h] [bp-8h] BYREF

  v14[1] = a3;
  v6 = a3 - a4;
  v7 = (int)result;
  v9 = 0;
  v13 = 0;
  v14[0] = 0;
  while ( v9 != a5 )
  {
    for ( i = 0; i != a4; ++i )
    {
      v11 = sub_B80A(v14, a2);
      result = sub_B84C(&v13, v7, v11);
    }
    for ( j = 0; j != v6; ++j )
      result = sub_B84C(&v13, v7, 0);
    ++v9;
  }
  return result;
}


//----- (0000C304) --------------------------------------------------------
void __fastcall sub_C304(int a1)
{
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 4) = 0;
  free(*(void **)a1);
  *(_DWORD *)a1 = 0;
}


//----- (0000C318) --------------------------------------------------------
void __fastcall sub_C318(int a1, int a2)
{
  int i; // r4
  int v5; // r0

  for ( i = 0; i != a2; ++i )
  {
    v5 = a1 + 16 * i;
    sub_C304(v5);
  }
}


//----- (0000C332) --------------------------------------------------------
void __fastcall sub_C332(void **a1)
{
  free(*a1);
  free(a1[1]);
  j_free(a1[2]);
}


//----- (0000C34C) --------------------------------------------------------
void __fastcall sub_C34C(int a1)
{
  int i; // r4

  for ( i = 0; i != 64; i += 4 )
  {
    if ( *(_DWORD *)(a1 + i) )
    {
      sub_C34C();
      free(*(void **)(a1 + i));
    }
  }
}


//----- (0000C368) --------------------------------------------------------
void __fastcall sub_C368(int a1)
{
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 4) = 0;
  free(*(void **)a1);
  *(_DWORD *)a1 = 0;
}


//----- (0000C37C) --------------------------------------------------------
_BYTE *__fastcall sub_C37C(void **a1, char *s)
{
  size_t v4; // r4
  _BYTE *result; // r0
  int v6; // r3

  v4 = strlen(s);
  result = realloc(*a1, v4 + 1);
  if ( result )
  {
    v6 = 0;
    result[v4] = 0;
    *a1 = result;
    while ( v6 != v4 )
    {
      *((_BYTE *)*a1 + v6) = s[v6];
      ++v6;
    }
  }
  return result;
}


//----- (0000C3AA) --------------------------------------------------------
int __fastcall sub_C3AA(int a1, unsigned int a2, int a3)
{
  bool v3; // cf
  int v4; // r3
  int v5; // r2
  int v6; // r4
  int v7; // r5
  char v8; // r0

  v3 = a3 + 3 >= a2;
  v4 = 0;
  if ( a3 + 3 >= a2 )
    a2 -= a3;
  v5 = a3 + a1;
  if ( !v3 )
    a2 = 3;
  v6 = 0;
  while ( v4 != a2 )
  {
    v7 = *(unsigned __int8 *)(v5 + v4);
    v8 = 2 * v4++;
    v6 ^= v7 << v8;
  }
  return (unsigned __int16)v6;
}


//----- (0000C3D8) --------------------------------------------------------
int __fastcall sub_C3D8(_DWORD *a1, _DWORD *a2)
{
  int v2; // r3
  int v3; // r3
  int v4; // r5
  int i; // r3

  if ( *a1 != *a2 )
    return 0;
  if ( a1[1] != a2[1] )
    return 0;
  v2 = a1[4];
  if ( v2 != a2[4] || v2 && (a1[5] != a2[5] || a1[6] != a2[6] || a1[7] != a2[7]) )
    return 0;
  v3 = a1[3];
  if ( v3 != a2[3] )
    return 0;
  v4 = 4 * v3;
  for ( i = 0; i != v4; ++i )
  {
    if ( *(unsigned __int8 *)(a1[2] + i) != *(unsigned __int8 *)(a2[2] + i) )
      return 0;
  }
  return 1;
}


//----- (0000C434) --------------------------------------------------------
int __fastcall sub_C434(_WORD *a1, _WORD *a2, _WORD *a3, __int16 *a4, int a5, int a6, int *a7)
{
  int v7; // r7
  int v8; // r8
  __int16 v9; // r12
  __int16 v11; // r2
  unsigned __int8 *v12; // r6
  __int16 v13; // r4
  __int16 v14; // r1
  __int16 v15; // r2
  unsigned __int8 *v16; // r6

  v7 = *a7;
  if ( !*a7 )
  {
    v8 = 2 * a6 + 1;
    v9 = *(unsigned __int8 *)(a5 + v8) + (*(unsigned __int8 *)(a5 + 2 * a6) << 8);
    *a3 = v9;
    *a2 = v9;
    *a1 = v9;
    if ( a7[4] && *(unsigned __int8 *)(a5 + v8) + (*(unsigned __int8 *)(a5 + 2 * a6) << 8) == a7[5] )
    {
      *a4 = 0;
      return 0;
    }
    goto LABEL_11;
  }
  switch ( v7 )
  {
    case 2:
      *a1 = *(unsigned __int8 *)(a5 + 6 * a6 + 1) + (*(unsigned __int8 *)(a5 + 6 * a6) << 8);
      *a2 = *(unsigned __int8 *)(a5 + 6 * a6 + 3) + (*(unsigned __int8 *)(a5 + 6 * a6 + 2) << 8);
      *a3 = *(unsigned __int8 *)(a5 + 6 * a6 + 5) + (*(unsigned __int8 *)(a5 + 6 * a6 + 4) << 8);
      if ( a7[4]
        && *(unsigned __int8 *)(a5 + 6 * a6 + 1) + (*(unsigned __int8 *)(a5 + 6 * a6) << 8) == a7[5]
        && *(unsigned __int8 *)(a5 + 6 * a6 + 3) + (*(unsigned __int8 *)(a5 + 6 * a6 + 2) << 8) == a7[6]
        && *(unsigned __int8 *)(a5 + 6 * a6 + 5) + (*(unsigned __int8 *)(a5 + 6 * a6 + 4) << 8) == a7[7] )
      {
        *a4 = 0;
        return 0;
      }
LABEL_11:
      v11 = -1;
LABEL_17:
      *a4 = v11;
      return 0;
    case 4:
      v12 = (unsigned __int8 *)(a5 + 4 * a6);
      v13 = v12[1] + (*v12 << 8);
      *a3 = v13;
      *a2 = v13;
      *a1 = v13;
      v14 = v12[2];
      v15 = v12[3];
LABEL_16:
      v11 = v15 + (v14 << 8);
      goto LABEL_17;
    case 6:
      v16 = (unsigned __int8 *)(a5 + 8 * a6);
      *a1 = v16[1] + (*v16 << 8);
      *a2 = v16[3] + (v16[2] << 8);
      *a3 = v16[5] + (v16[4] << 8);
      v14 = v16[6];
      v15 = v16[7];
      goto LABEL_16;
  }
  return 85;
}


//----- (0000C55E) --------------------------------------------------------
void *__fastcall sub_C55E(int a1, int a2)
{
  int v4; // r6
  void *result; // r0

  if ( *(_DWORD *)(a1 + 8) < (unsigned int)(4 * a2) )
  {
    v4 = 8 * a2;
    result = realloc(*(void **)a1, 8 * a2);
    if ( !result )
      return result;
    *(_DWORD *)(a1 + 8) = v4;
    *(_DWORD *)a1 = result;
  }
  *(_DWORD *)(a1 + 4) = a2;
  return &dword_0 + 1;
}
// 0: using guessed type int dword_0;


//----- (0000C582) --------------------------------------------------------
void *__fastcall sub_C582(_DWORD *a1, int a2)
{
  void *result; // r0

  result = sub_C55E((int)a1, a1[1] + 1);
  if ( result )
  {
    *(_DWORD *)(*a1 + 4 * (a1[1] + 0x3FFFFFFF)) = a2;
    return &dword_0 + 1;
  }
  return result;
}
// 0: using guessed type int dword_0;


//----- (0000C5A4) --------------------------------------------------------
int __fastcall sub_C5A4(int a1, int a2, int a3, unsigned int a4)
{
  int v4; // r5
  int i; // r4
  unsigned int v9; // r6
  int v10; // r0
  unsigned int v12; // [sp+4h] [bp-8h]

  v4 = 0;
  for ( i = 0; i != a3; ++i )
  {
    v9 = *(_DWORD *)(a2 + 4 * i);
    if ( v9 )
    {
      v10 = a1 + 16 * v4++;
      *(float *)(v10 + 12) = (float)v9 / (float)a4;
      v12 = a4;
      sub_C582((_DWORD *)v10, i);
      a4 = v12;
    }
  }
  return 0;
}


//----- (0000C5F0) --------------------------------------------------------
void *__fastcall sub_C5F0(int a1, unsigned int a2)
{
  int v4; // r6
  void *result; // r0

  if ( a2 > *(_DWORD *)(a1 + 8) )
  {
    v4 = 2 * a2;
    result = realloc(*(void **)a1, 2 * a2);
    if ( !result )
      return result;
    *(_DWORD *)(a1 + 8) = v4;
    *(_DWORD *)a1 = result;
  }
  *(_DWORD *)(a1 + 4) = a2;
  return &dword_0 + 1;
}
// 0: using guessed type int dword_0;


//----- (0000C612) --------------------------------------------------------
void *__fastcall sub_C612(_DWORD *a1, char a2)
{
  void *result; // r0

  result = sub_C5F0((int)a1, a1[1] + 1);
  if ( result )
  {
    *(_BYTE *)(a1[1] + *a1 - 1) = a2;
    return &dword_0 + 1;
  }
  return result;
}
// 0: using guessed type int dword_0;


//----- (0000C630) --------------------------------------------------------
int __fastcall sub_C630(_DWORD *a1, _DWORD *a2, int a3)
{
  int result; // r0

  if ( (*a1 & 7) == 0 )
    sub_C612(a2, 0);
  result = *a1 & 7;
  *(_BYTE *)(*a2 + a2[1] - 1) |= a3 << result;
  ++*a1;
  return result;
}


//----- (0000C662) --------------------------------------------------------
int __fastcall sub_C662(int result, _DWORD *a2, unsigned int a3, int a4)
{
  _DWORD *v4; // r5
  int i; // r4

  v4 = (_DWORD *)result;
  for ( i = 0; i != a4; ++i )
    result = sub_C630(v4, a2, (a3 >> i) & 1);
  return result;
}


//----- (0000C68C) --------------------------------------------------------
int __fastcall sub_C68C(int result, _DWORD *a2, unsigned int a3, int a4)
{
  int v4; // r4
  _DWORD *v5; // r5

  v4 = a4 - 1;
  v5 = (_DWORD *)result;
  while ( v4 != -1 )
    result = sub_C630(v5, a2, (a3 >> v4--) & 1);
  return result;
}


//----- (0000C6B0) --------------------------------------------------------
int __fastcall sub_C6B0(int result, _DWORD *a2, _DWORD *a3, int a4, int a5)
{
  int v5; // r5
  unsigned int i; // r4
  int v10; // r9
  unsigned int v11; // r7
  unsigned int *v12; // r3
  unsigned int v13; // r9
  int v14; // [sp+0h] [bp-Ch]
  unsigned int v15; // [sp+4h] [bp-8h]

  v5 = result;
  for ( i = 0; i < a3[1]; ++i )
  {
    v10 = 4 * i;
    v11 = *(_DWORD *)(*a3 + 4 * i);
    result = sub_C68C(v5, a2, *(_DWORD *)(*(_DWORD *)(a4 + 4) + 4 * v11), *(_DWORD *)(*(_DWORD *)(a4 + 8) + 4 * v11));
    if ( v11 > 0x100 )
    {
      i += 3;
      v12 = (unsigned int *)(*a3 + v10);
      v13 = v12[2];
      v15 = v12[3];
      v14 = *(_DWORD *)&asc_15B68[4 * v13 + 112];
      sub_C662(v5, a2, v12[1], *(_DWORD *)&asc_15B68[4 * v11 - 796]);
      sub_C68C(v5, a2, *(_DWORD *)(*(_DWORD *)(a5 + 4) + 4 * v13), *(_DWORD *)(*(_DWORD *)(a5 + 8) + 4 * v13));
      result = sub_C662(v5, a2, v15, v14);
    }
  }
  return result;
}


//----- (0000C758) --------------------------------------------------------
int __fastcall sub_C758(unsigned __int8 *a1, unsigned int a2)
{
  unsigned int v4; // r5
  unsigned int v5; // r4
  int v6; // r3
  unsigned __int8 *v7; // r3
  int v8; // t1

  v4 = 0;
  v5 = 1;
  while ( a2 )
  {
    if ( a2 >= 0x15AE )
      v6 = 5550;
    else
      v6 = a2;
    a2 -= v6;
    v7 = &a1[v6];
    do
    {
      v8 = *a1++;
      v5 += v8;
      v4 += v5;
    }
    while ( a1 != v7 );
    v5 %= 0xFFF1u;
    v4 %= 0xFFF1u;
  }
  return v5 | (v4 << 16);
}


//----- (0000C7A4) --------------------------------------------------------
void *__fastcall sub_C7A4(_DWORD *a1, unsigned int a2)
{
  unsigned int v4; // r4
  void *result; // r0
  int v6; // r3

  v4 = a1[1];
  result = sub_C55E((int)a1, a2);
  if ( result )
  {
    v6 = 4 * v4;
    while ( v4 < a2 )
    {
      ++v4;
      *(_DWORD *)(*a1 + v6) = 0;
      v6 += 4;
    }
    return &dword_0 + 1;
  }
  return result;
}
// 0: using guessed type int dword_0;


//----- (0000C7C8) --------------------------------------------------------
int __fastcall sub_C7C8(int *a1)
{
  int v2; // r0
  void *v3; // r0
  unsigned int v4; // r1
  unsigned int v5; // r5
  unsigned int i; // r3
  int v7; // r1
  unsigned int j; // r3
  unsigned int k; // r3
  int v10; // r2
  int v11; // lr
  int v12; // r1
  void *v13; // r0
  unsigned int v14; // r3
  unsigned int v15; // r2
  unsigned int v16; // r0
  unsigned int m; // r3
  unsigned int v18; // r1
  unsigned int v19; // r5
  int v20; // r6
  int v21; // r2
  int v22; // r7
  int v23; // r9
  _DWORD v25[3]; // [sp+0h] [bp-Ch] BYREF
  _DWORD v26[4]; // [sp+Ch] [bp+0h] BYREF

  v2 = a1[4];
  memset(v25, 0, sizeof(v25));
  memset(v26, 0, 12);
  v3 = malloc(4 * v2);
  v4 = a1[3] + 1;
  a1[1] = (int)v3;
  if ( v3 )
    v5 = 0;
  else
    v5 = 83;
  if ( sub_C7A4(v25, v4) && sub_C7A4(v26, a1[3] + 1) )
  {
    if ( !v5 )
    {
      for ( i = 0; i < a1[4]; ++i )
      {
        v7 = *(_DWORD *)(a1[2] + 4 * i);
        ++*(_DWORD *)(v25[0] + 4 * v7);
      }
      for ( j = 1; j <= a1[3]; ++j )
        *(_DWORD *)(v26[0] + 4 * j) = 2 * (*(_DWORD *)(v26[0] + 4 * j - 4) + *(_DWORD *)(v25[0] + 4 * j - 4));
      for ( k = 0; k < a1[4]; ++k )
      {
        v10 = *(_DWORD *)(a1[2] + 4 * k);
        if ( v10 )
        {
          v11 = a1[1];
          v12 = *(_DWORD *)(v26[0] + 4 * v10);
          *(_DWORD *)(v26[0] + 4 * v10) = v12 + 1;
          *(_DWORD *)(v11 + 4 * k) = v12;
        }
      }
    }
  }
  else
  {
    v5 = 83;
  }
  sub_C304((int)v25);
  sub_C304((int)v26);
  if ( v5 )
    return v5;
  v13 = malloc(8 * a1[4]);
  *a1 = (int)v13;
  if ( !v13 )
    return 83;
  while ( v5 < 2 * a1[4] )
    *(_DWORD *)(*a1 + 4 * v5++) = 0x7FFF;
  v14 = 0;
  v15 = 0;
  v16 = 0;
LABEL_24:
  if ( v14 < a1[4] )
  {
    v18 = 0;
    while ( 1 )
    {
      v19 = *(_DWORD *)(a1[2] + 4 * v14);
      if ( v18 >= v19 )
      {
        ++v14;
        goto LABEL_24;
      }
      v20 = a1[4];
      if ( v15 > v20 - 2 )
        return 55;
      v21 = ((*(_DWORD *)(a1[1] + 4 * v14) >> (v19 - 1 - v18)) & 1) + 2 * v15;
      v22 = *a1;
      ++v18;
      v23 = *(_DWORD *)(*a1 + 4 * v21);
      if ( v23 == 0x7FFF )
      {
        if ( v18 == v19 )
        {
          *(_DWORD *)(v22 + 4 * v21) = v14;
          v15 = 0;
        }
        else
        {
          ++v16;
          *(_DWORD *)(v22 + 4 * v21) = v20 + v16;
          v15 = v16;
        }
      }
      else
      {
        v15 = v23 - v20;
      }
    }
  }
  else
  {
    for ( m = 0; m < 2 * a1[4]; ++m )
    {
      if ( *(_DWORD *)(*a1 + 4 * m) == 0x7FFF )
        *(_DWORD *)(*a1 + 4 * m) = 0;
    }
    return 0;
  }
}


//----- (0000C956) --------------------------------------------------------
int __fastcall sub_C956(int *a1, int a2, int a3, int a4)
{
  int v4; // r7
  void *v9; // r0
  int i; // r5

  v4 = 4 * a3;
  v9 = malloc(4 * a3);
  a1[2] = (int)v9;
  if ( !v9 )
    return 83;
  for ( i = 0; i != v4; i += 4 )
    *(_DWORD *)(a1[2] + i) = *(_DWORD *)(a2 + i);
  a1[4] = a3;
  a1[3] = a4;
  return sub_C7C8(a1);
}


//----- (0000C996) --------------------------------------------------------
int __fastcall sub_C996(int *a1)
{
  char *v2; // r0
  void *v3; // r4
  int i; // r3
  int j; // r3
  char *v6; // r2
  int k; // r3
  char *v8; // r2
  int m; // r3
  char *v10; // r2
  int v11; // r5

  v2 = (char *)malloc(0x480u);
  v3 = v2;
  if ( !v2 )
    return 83;
  for ( i = 0; i != 576; i += 4 )
    *(_DWORD *)&v2[i] = 8;
  for ( j = 0; j != 448; j += 4 )
  {
    v6 = &v2[j];
    *((_DWORD *)v6 + 144) = 9;
  }
  for ( k = 0; k != 96; k += 4 )
  {
    v8 = &v2[k];
    *((_DWORD *)v8 + 256) = 7;
  }
  for ( m = 0; m != 32; m += 4 )
  {
    v10 = &v2[m];
    *((_DWORD *)v10 + 280) = 8;
  }
  v11 = sub_C956(a1, (int)v2, 288, 15);
  free(v3);
  return v11;
}


//----- (0000CA04) --------------------------------------------------------
int __fastcall sub_CA04(int *a1)
{
  char *v2; // r0
  void *v3; // r4
  int i; // r3
  int v5; // r5

  v2 = (char *)malloc(0x80u);
  v3 = v2;
  if ( !v2 )
    return 83;
  for ( i = 0; i != 128; i += 4 )
    *(_DWORD *)&v2[i] = 5;
  v5 = sub_C956(a1, (int)v2, 32, 15);
  free(v3);
  return v5;
}


//----- (0000CA78) --------------------------------------------------------
unsigned int __fastcall sub_CA78(_DWORD *a1, unsigned int a2)
{
  _BYTE *v5; // r3

  sub_C5F0((int)a1, a1[1] + 4);
  v5 = (_BYTE *)(*a1 + a1[1] - 4);
  *v5 = HIBYTE(a2);
  v5[3] = a2;
  v5[1] = BYTE2(a2);
  v5[2] = BYTE1(a2);
  return HIBYTE(a2);
}


//----- (0000CB04) --------------------------------------------------------
_BYTE *__fastcall sub_CB04(_DWORD *a1)
{
  _BYTE *result; // r0

  *a1 = 0;
  result = realloc(0, 1u);
  if ( result )
  {
    *result = 0;
    *a1 = result;
  }
  return result;
}


//----- (0000CB1C) --------------------------------------------------------
_DWORD *__fastcall sub_CB1C(_DWORD *result, int a2, int a3, int a4, unsigned __int8 a5, int a6)
{
  int v6; // r4
  _DWORD *v7; // r5
  int v10; // r6
  _DWORD *v11; // r2
  int i; // r5
  int v13; // [sp+8h] [bp-Ch]

  v6 = 0;
  v7 = result;
  do
  {
    v10 = (((int)a5 >> v6) & 1) + 2 * (((a4 >> v6) & 1) + 2 * (((a3 >> v6) & 1) + 2 * ((a2 >> v6) & 1)));
    v11 = &v7[v10];
    if ( !*v11 )
    {
      v13 = a4;
      result = malloc(0x44u);
      v7[v10] = result;
      a4 = v13;
      v11 = &v7[v10];
      for ( i = 0; i != 16; ++i )
        result[i] = 0;
      result[16] = -1;
    }
    ++v6;
    v7 = (_DWORD *)*v11;
  }
  while ( v6 != 8 );
  v7[16] = a6;
  return result;
}


//----- (0000CBA4) --------------------------------------------------------
int __fastcall sub_CBA4(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        unsigned int a4,
        unsigned int a5,
        unsigned int a6,
        unsigned int a7,
        unsigned int a8,
        int a9)
{
  int v12; // r8
  unsigned int v13; // r7
  unsigned int v14; // r5
  _BYTE *v15; // r3
  _BYTE *v16; // r1
  unsigned __int16 v17; // r2
  unsigned int v18; // r2
  unsigned int v19; // r3
  int v20; // r1
  unsigned int v21; // r12
  unsigned int v22; // r5
  unsigned int v23; // r6
  unsigned int v24; // r8
  int v25; // r2
  unsigned int v26; // r9
  unsigned int v27; // r0
  unsigned int v28; // r8
  unsigned __int8 *v29; // r9
  unsigned __int8 *v30; // r8
  int v31; // r8
  unsigned int v33; // r7
  int v34; // r8
  unsigned int v35; // r0
  int v36; // r1
  unsigned int v37; // r7
  int v38; // r9
  int v39; // r6
  unsigned int v40; // r6
  int v41; // r8
  unsigned int v42; // r8
  _BYTE *v43; // r3
  _BYTE *v44; // r2
  unsigned __int8 *v45; // [sp+4h] [bp-60h]
  unsigned int v46; // [sp+Ch] [bp-58h]
  int v48; // [sp+18h] [bp-4Ch]
  unsigned int v49; // [sp+1Ch] [bp-48h]
  int v50; // [sp+20h] [bp-44h]
  unsigned int v51; // [sp+2Ch] [bp-38h]
  unsigned int v52; // [sp+30h] [bp-34h]
  unsigned int v53; // [sp+34h] [bp-30h]
  int v54; // [sp+38h] [bp-2Ch]
  unsigned int v55; // [sp+40h] [bp-24h]
  unsigned int v56; // [sp+48h] [bp-1Ch]
  unsigned __int8 *v57; // [sp+58h] [bp-Ch]

  if ( a6 >= 0x2000 )
  {
    v12 = 258;
    v55 = a6;
  }
  else
  {
    v12 = 64;
    v55 = a6 >> 3;
  }
  v49 = 0;
  v52 = 0;
  v50 = 0;
  v51 = 0;
  v53 = v12;
  v56 = a5 + a3;
  while ( 1 )
  {
    if ( a4 >= a5 )
      return 0;
    v13 = a4 % a6;
    v48 = sub_C3AA(a3, a5, a4);
    sub_B7DE(a2, a4, v48, a6);
    if ( a6 >= 0x2000 && !v48 )
    {
      v14 = a3 + a4 + 258;
      if ( v14 >= v56 )
        v14 = v56;
      v15 = (_BYTE *)(a3 + a4);
      do
      {
        v16 = v15;
        if ( v15 == (_BYTE *)v14 )
          break;
        ++v15;
      }
      while ( !*v16 );
      v17 = (_WORD)v16 - (a3 + a4);
      v51 = v17;
      *(_WORD *)(a2[3] + 2 * v13) = v17;
    }
    v18 = *(unsigned __int16 *)(*a2 + 4 * v48);
    v54 = a2[2];
    v19 = *(unsigned __int16 *)(v54 + 2 * v18);
    if ( *(_DWORD *)(a2[1] + 4 * v13) == v48 )
    {
      v20 = 0;
      v21 = a3 + a4;
      v22 = 0;
      v23 = 0;
      if ( a4 + 258 > a5 )
        v24 = a3 + a5;
      else
        v24 = a4 + 258 + a3;
      v57 = (unsigned __int8 *)v24;
      while ( (v18 >= v13 || v19 <= v18 || v19 > v13) && (v18 <= v13 || v19 > v13 && v19 <= v18) && v20 != v55 )
      {
        v25 = v19 > v13 ? a6 + v13 - v19 : v13 - v19;
        if ( v25 )
        {
          v26 = a4 - v25 + a3;
          if ( a6 < 0x2000 || v48 || *(_DWORD *)(a2[1] + 4 * v19) )
          {
            v28 = a3 + a4;
          }
          else
          {
            v27 = *(unsigned __int16 *)(a2[3] + 2 * v19);
            if ( v27 >= v51 )
              v27 = v51;
            v26 += v27;
            v28 = v27 + v21;
          }
          v45 = (unsigned __int8 *)v28;
          v46 = v26 - 1;
          do
          {
            v29 = v45;
            if ( v45 == v57 )
              break;
            ++v45;
            v31 = *(unsigned __int8 *)++v46;
          }
          while ( v31 == *v29 );
          v30 = &v29[-v21];
          if ( (unsigned int)&v29[-v21] > v22 )
          {
            v22 = (unsigned int)&v29[-v21];
            v23 = v25;
            if ( (unsigned int)v30 >= a8 || v30 == (_BYTE *)&dword_100 + 2 )
              break;
          }
        }
        ++v20;
        if ( v19 == *(unsigned __int16 *)(v54 + 2 * v19) )
          break;
        v18 = v19;
        v19 = *(unsigned __int16 *)(v54 + 2 * v19);
      }
    }
    else
    {
      v22 = 0;
      v23 = 0;
    }
    if ( a9 )
    {
      if ( !v50 )
      {
        if ( v22 <= 2 )
          goto LABEL_66;
        if ( v22 <= v53 && v22 != 258 )
        {
          v49 = v23;
          v52 = v22;
          v50 = 1;
          goto LABEL_84;
        }
        goto LABEL_62;
      }
      if ( !a4 )
        return 81;
      if ( v22 <= v52 + 1 )
      {
        --a4;
        v22 = v52;
        v23 = v49;
        *(_DWORD *)(*a2 + 4 * v48) = -1;
        v50 = 0;
      }
      else
      {
        if ( !sub_C582(a1, *(unsigned __int8 *)(a3 + a4 - 1)) )
          return 83;
        v50 = 0;
      }
    }
    if ( v22 <= 2 )
      goto LABEL_66;
LABEL_62:
    if ( v23 > a6 )
      return 86;
    if ( v22 >= a7 && (v22 != 3 || v23 <= 0x1000) )
    {
      v33 = sub_B7AA((int)&unk_15CC4, 29, v22);
      v34 = v22 - *(_DWORD *)&asc_15B68[4 * v33 + 348];
      v35 = sub_B7AA((int)&unk_15D38, 30, v23);
      v36 = v33 + 257;
      v37 = a3 + a4;
      v38 = v35;
      v39 = v23 - *(_DWORD *)&asc_15B68[4 * v35 + 464];
      sub_C582(a1, v36);
      sub_C582(a1, v34);
      sub_C582(a1, v38);
      sub_C582(a1, v39);
      v40 = a4 + 1 + a3;
      do
      {
        a4 = v40 - a3;
        if ( v40 - a3 >= a5 )
          v41 = 0;
        else
          v41 = sub_C3AA(a3, a5, v40 - a3);
        sub_B7DE(a2, v40 - a3, v41, a6);
        if ( a6 >= 0x2000 && !v41 )
        {
          v42 = v40 + 258;
          if ( v56 < v40 + 258 )
            v42 = v56;
          v43 = (_BYTE *)v40;
          do
          {
            v44 = v43;
            if ( v43 == (_BYTE *)v42 )
              break;
            ++v43;
          }
          while ( !*v44 );
          *(_WORD *)(a2[3] + 2 * (a4 % a6)) = (_WORD)v44 - v40;
        }
        ++v40;
      }
      while ( v40 - v37 < v22 );
      goto LABEL_84;
    }
LABEL_66:
    if ( !sub_C582(a1, *(unsigned __int8 *)(a3 + a4)) )
      return 83;
LABEL_84:
    ++a4;
  }
}
// 100: using guessed type int;
// 1C8: using guessed type Elf32_Sym;


//----- (0000D1FE) --------------------------------------------------------
unsigned int __fastcall sub_D1FE(int a1, const unsigned int *a2, unsigned int a3, unsigned int a4, unsigned int a5)
{
  unsigned int v5; // r4
  const unsigned int *v6; // r3
  int v9; // t1
  void *v10; // r0
  unsigned int result; // r0

  v5 = a4;
  v6 = &a2[a4];
  while ( 1 )
  {
    v9 = *--v6;
    if ( v9 || v5 <= a3 )
      break;
    --v5;
  }
  *(_DWORD *)(a1 + 12) = a5;
  *(_DWORD *)(a1 + 16) = v5;
  v10 = realloc(*(void **)(a1 + 8), 4 * v5);
  *(_DWORD *)(a1 + 8) = v10;
  if ( !v10 )
    return 83;
  memset(v10, 0, 4 * v5);
  result = lodepng_huffman_code_lengths(*(unsigned int **)(a1 + 8), a2, v5, a5);
  if ( !result )
    return sub_C7C8((int *)a1);
  return result;
}


//----- (0000E004) --------------------------------------------------------
int __fastcall sub_E004(int *a1, unsigned int *a2, unsigned __int8 *a3, unsigned int a4, _DWORD *a5)
{
  int (__fastcall *v5)(int *, unsigned int *, unsigned __int8 *); // r5

  v5 = (int (__fastcall *)(int *, unsigned int *, unsigned __int8 *))a5[1];
  if ( v5 )
    return v5(a1, a2, a3);
  else
    return lodepng_zlib_decompress(a1, a2, a3, a4, a5);
}


//----- (0000E0B4) --------------------------------------------------------
int __fastcall sub_E0B4(int *a1, int *a2, unsigned __int8 *a3, unsigned int a4, int *a5)
{
  int (__fastcall *v5)(int *, int *, unsigned __int8 *); // r5

  v5 = (int (__fastcall *)(int *, int *, unsigned __int8 *))a5[6];
  if ( v5 )
    return v5(a1, a2, a3);
  else
    return lodepng_zlib_compress(a1, a2, a3, a4, a5);
}


//----- (0000E2D8) --------------------------------------------------------
int __fastcall sub_E2D8(int a1, char *a2, unsigned __int8 *a3, unsigned int a4)
{
  int result; // r0

  result = lodepng_chunk_create((unsigned __int8 **)a1, (unsigned int *)(a1 + 4), a4, a2, a3);
  if ( !result )
    *(_DWORD *)(a1 + 8) = *(_DWORD *)(a1 + 4);
  return result;
}


//----- (0000E3EC) --------------------------------------------------------
int __fastcall sub_E3EC(_BYTE *a1, int a2, int a3, int a4, unsigned int *a5, int *a6)
{
  int bpp; // r0
  int v10; // r3
  unsigned int v11; // r4
  _DWORD *v12; // r5
  int v13; // r7
  int v14; // r10
  int v15; // r5
  int v16; // r2
  int v17; // r2
  int v18; // r1
  int v19; // r7
  int v20; // r0
  int v21; // r3
  char v22; // r0
  _BYTE *v23; // r2
  int i; // r4
  _DWORD *v25; // r0
  int *v26; // r5
  float v28; // s15
  int v29; // r6
  unsigned int v30; // s18
  int v31; // r10
  unsigned int v32; // r11
  float v33; // s16
  int v34; // r5
  int j; // r3
  int k; // r2
  int v37; // r1
  int v38; // r3
  void **v39; // r2
  unsigned int v40; // r1
  float v41; // s14
  float v42; // s11
  float m; // s15
  float v44; // s14
  int v45; // r3
  char v46; // r0
  _BYTE *v47; // r2
  int n; // r4
  int *v49; // r0
  int v50; // r5
  _BYTE *v51; // r7
  unsigned int v52; // r2
  unsigned int v53; // r9
  int v54; // r0
  char v55; // r3
  int v56; // r1
  int v57; // r1
  int v58; // r2
  int v59; // r3
  int v60; // r1
  int v61; // r2
  int v62; // r3
  int v63; // r3
  _DWORD *v64; // r5
  int v65; // r0
  int v66; // r11
  int v67; // r6
  int *v68; // r8
  int v69; // r5
  int v70; // r3
  char v71; // r0
  _BYTE *v72; // r2
  int ii; // r4
  _DWORD *v74; // r0
  int v75; // r2
  _BYTE *v76; // r1
  int v77; // r3
  unsigned int v78; // [sp+Ch] [bp-488h]
  unsigned int v79; // [sp+Ch] [bp-488h]
  int v80; // [sp+Ch] [bp-488h]
  unsigned int v81; // [sp+10h] [bp-484h]
  unsigned int v83; // [sp+18h] [bp-47Ch]
  unsigned int v84; // [sp+1Ch] [bp-478h]
  unsigned int v85; // [sp+20h] [bp-474h]
  unsigned int v86; // [sp+24h] [bp-470h]
  unsigned int v87; // [sp+28h] [bp-46Ch]
  unsigned int v88; // [sp+2Ch] [bp-468h]
  void *p[6]; // [sp+3Ch] [bp-458h] BYREF
  int v90[6]; // [sp+54h] [bp-440h] BYREF
  int v91; // [sp+6Ch] [bp-428h]
  int v92; // [sp+70h] [bp-424h]
  int v93; // [sp+74h] [bp-420h]
  _DWORD v94[15]; // [sp+90h] [bp-404h] BYREF
  _BYTE v95[968]; // [sp+CCh] [bp-3C8h] BYREF

  bpp = lodepng_get_bpp(a5);
  v10 = a6[11];
  v11 = (unsigned int)(a3 * bpp + 7) >> 3;
  if ( a6[10] && (*a5 == 3 || a5[1] <= 7) )
  {
    if ( bpp )
    {
LABEL_91:
      v75 = 0;
      v76 = a1 + 1;
      while ( v75 != a4 )
      {
        v77 = 0;
        *(v76 - 1) = 0;
        while ( v77 != v11 )
        {
          v76[v77] = *(_BYTE *)(a2 + v77);
          ++v77;
        }
        ++v75;
        a2 += v11;
        v76 += v11 + 1;
      }
      return 0;
    }
    return 31;
  }
  if ( !bpp )
    return 31;
  if ( !v10 )
    goto LABEL_91;
  v84 = (unsigned int)(bpp + 7) >> 3;
  switch ( v10 )
  {
    case 1:
      v12 = v94;
      do
      {
        *v12 = 0;
        v12[2] = 0;
        v12[1] = 0;
        if ( !sub_C5F0((int)v12, v11) )
          return 83;
        v12 += 3;
      }
      while ( v12 != (_DWORD *)v95 );
      v13 = 0;
      v14 = 0;
      v81 = 0;
      v78 = 0;
LABEL_11:
      if ( v14 == a4 )
      {
        for ( i = 0; i != 15; i += 3 )
        {
          v25 = &v94[i];
          sub_C368((int)v25);
        }
        return 0;
      }
      v15 = 0;
      v86 = a2;
      while ( 1 )
      {
        sub_C11E(v94[3 * v15], a2, v78, v11, v84, v15);
        v16 = 0;
        v90[v15] = 0;
        if ( v15 )
        {
          while ( v16 != v11 )
          {
            v20 = *(char *)(v94[3 * v15] + v16++);
            if ( v20 < 0 )
              v20 = -v20;
            v90[v15] += v20;
          }
          if ( v90[v15] >= v81 )
            goto LABEL_23;
        }
        else
        {
          v17 = 0;
          v18 = v90[0];
          while ( v17 != v11 )
          {
            v19 = *(unsigned __int8 *)(v94[0] + v17++);
            v18 += v19;
          }
          v90[0] = v18;
        }
        v13 = v15;
        v81 = v90[v15];
LABEL_23:
        if ( ++v15 == 5 )
        {
          v21 = 0;
          *a1 = v13;
          while ( v21 != v11 )
          {
            v22 = *(_BYTE *)(v94[3 * v13] + v21);
            v23 = &a1[v21++];
            v23[1] = v22;
          }
          ++v14;
          a2 += v11;
          a1 += v11 + 1;
          v78 = v86;
          goto LABEL_11;
        }
      }
    case 2:
      v26 = v90;
      do
      {
        *v26 = 0;
        v26[2] = 0;
        v26[1] = 0;
        if ( !sub_C5F0((int)v26, v11) )
          return 83;
        v26 += 3;
      }
      while ( v26 != v94 );
      v28 = 0.0;
      v29 = 0;
      v30 = v11 + 1;
      v31 = 0;
      v32 = 0;
      while ( v31 != a4 )
      {
        v33 = v28;
        v34 = 0;
        v79 = a2;
        while ( 1 )
        {
          sub_C11E(v90[3 * v34], a2, v32, v11, v84, v34);
          for ( j = 0; j != 256; ++j )
            v94[j] = 0;
          for ( k = 0; k != v11; ++k )
          {
            v37 = *(unsigned __int8 *)(v90[3 * v34] + k);
            ++v94[v37];
          }
          ++v94[v34];
          v38 = 0;
          v39 = &p[v34 + 1];
          *v39 = 0;
          do
          {
            v40 = v94[v38];
            if ( v40 )
            {
              v41 = 0.0;
              v42 = (float)v40 / (float)v30;
              for ( m = 1.0 / v42; m > 32.0; m = m * 0.0625 )
                v41 = v41 + 4.0;
              while ( m > 2.0 )
              {
                v41 = v41 + 1.0;
                m = m * 0.5;
              }
              v44 = (float)(v41
                          + (float)((float)((float)((float)((float)((float)((float)(m * m) * m) / 3.0)
                                                          - (float)((float)((float)(m * 3.0) * m) * 0.5))
                                                  + (float)(m * 3.0))
                                          - 1.8333)
                                  * 1.4427))
                  * v42;
            }
            else
            {
              v44 = 0.0;
            }
            v28 = v44 + *(float *)v39;
            ++v38;
            *(float *)v39 = v28;
          }
          while ( v38 != 256 );
          if ( v34 && v28 >= v33 )
            v28 = v33;
          else
            v29 = v34;
          if ( ++v34 == 5 )
            break;
          v33 = v28;
        }
        v45 = 0;
        *a1 = v29;
        while ( v45 != v11 )
        {
          v46 = *(_BYTE *)(v90[3 * v29] + v45);
          v47 = &a1[v45++];
          v47[1] = v46;
        }
        ++v31;
        a2 += v11;
        v32 = v79;
        a1 += v30;
      }
      for ( n = 0; n != 15; n += 3 )
      {
        v49 = &v90[n];
        sub_C368((int)v49);
      }
      return 0;
    case 4:
      v50 = 0;
      v51 = a1 + 1;
      v52 = 0;
      while ( v50 != a4 )
      {
        v53 = a2;
        v54 = (int)v51;
        v55 = *(_BYTE *)(a6[12] + v50++);
        *(v51 - 1) = v55;
        v51 += v11 + 1;
        v56 = a2;
        a2 += v11;
        sub_C11E(v54, v56, v52, v11, v84, v55);
        v52 = v53;
      }
      return 0;
    case 3:
      v57 = a6[1];
      v58 = a6[2];
      v59 = a6[3];
      v90[0] = *a6;
      v90[1] = v57;
      v90[2] = v58;
      v90[3] = v59;
      v60 = a6[5];
      v61 = a6[6];
      v62 = a6[7];
      v90[4] = a6[4];
      v90[5] = v60;
      v91 = v61;
      v92 = v62;
      v63 = a6[8];
      v91 = 0;
      v93 = v63;
      v64 = v94;
      v92 = 0;
      v90[0] = 1;
      do
      {
        *v64 = 0;
        v65 = (int)v64;
        v64[2] = 0;
        v64[1] = 0;
        v64 += 3;
        sub_C5F0(v65, v11);
      }
      while ( v64 != (_DWORD *)v95 );
      v66 = a2;
      v67 = 0;
      v85 = 0;
      v80 = 0;
      v83 = 0;
      while ( v80 != a4 )
      {
        v68 = (int *)p;
        v69 = 0;
        v88 = v66;
        do
        {
          v87 = v94[3 * v69 + 1];
          sub_C11E(v94[3 * v69], v66, v83, v11, v84, v69);
          v68[1] = 0;
          ++v68;
          p[0] = 0;
          sub_E0B4((int *)p, v68, (unsigned __int8 *)v94[3 * v69], v87, v90);
          free(p[0]);
          if ( !v69 || *v68 < v85 )
          {
            v67 = v69;
            v85 = *v68;
          }
          ++v69;
        }
        while ( v69 != 5 );
        v70 = 0;
        *a1 = v67;
        while ( v70 != v11 )
        {
          v71 = *(_BYTE *)(v94[3 * v67] + v70);
          v72 = &a1[v70++];
          v72[1] = v71;
        }
        v66 += v11;
        v83 = v88;
        ++v80;
        a1 += v11 + 1;
      }
      for ( ii = 0; ii != 15; ii += 3 )
      {
        v74 = &v94[ii];
        sub_C368((int)v74);
      }
      return 0;
  }
  return 88;
}


//----- (0000E8AC) --------------------------------------------------------
int __fastcall sub_E8AC(_BYTE **a1, size_t *a2, int a3, int a4, int a5, int a6, int *a7)
{
  int bpp; // r0
  unsigned int v10; // r4
  int v11; // r8
  unsigned int v12; // r10
  size_t v13; // r9
  _BYTE *v14; // r0
  int v15; // r5
  size_t v16; // r0
  _BYTE *v17; // r0
  size_t v18; // r8
  int k; // r3
  int v20; // lr
  int v21; // r12
  int m; // r7
  unsigned int v23; // r2
  int v24; // r10
  char *v25; // r8
  int n; // r9
  int v27; // r9
  unsigned int v28; // r10
  int v29; // r8
  char *v30; // r12
  unsigned int i; // r7
  int j; // r3
  int v33; // r0
  unsigned int *v34; // r0
  unsigned int *v35; // r8
  void *v36; // r0
  unsigned int *v37; // r0
  int v38; // r4
  char *v40; // [sp+10h] [bp-174h]
  int v41; // [sp+14h] [bp-170h]
  char *p; // [sp+18h] [bp-16Ch]
  unsigned int *v43; // [sp+1Ch] [bp-168h]
  int v46; // [sp+38h] [bp-14Ch]
  int v47; // [sp+3Ch] [bp-148h]
  unsigned int v48; // [sp+44h] [bp-140h]
  unsigned int v49; // [sp+48h] [bp-13Ch] BYREF
  char v50; // [sp+4Ch] [bp-138h] BYREF
  _BYTE v51[28]; // [sp+50h] [bp-134h] BYREF
  _BYTE v52[28]; // [sp+6Ch] [bp-118h] BYREF
  _BYTE v53[28]; // [sp+88h] [bp-FCh] BYREF
  _BYTE v54[28]; // [sp+A4h] [bp-E0h] BYREF
  _DWORD v55[7]; // [sp+C0h] [bp-C4h] BYREF
  size_t byte_count; // [sp+DCh] [bp-A8h]
  _DWORD v57[8]; // [sp+E0h] [bp-A4h] BYREF
  size_t v58[8]; // [sp+100h] [bp-84h] BYREF
  int v59[8]; // [sp+120h] [bp-64h] BYREF
  int v60[8]; // [sp+140h] [bp-44h] BYREF
  _DWORD v61[9]; // [sp+160h] [bp-24h] BYREF

  v43 = (unsigned int *)(a6 + 12);
  bpp = lodepng_get_bpp((unsigned int *)(a6 + 12));
  v10 = bpp;
  if ( *(_DWORD *)(a6 + 8) )
  {
    sub_BE74((int)v51, (int)v52, v55, v57, v58, a4, a5, bpp);
    v16 = byte_count;
    *a2 = byte_count;
    v17 = malloc(v16);
    v18 = v58[7];
    *a1 = v17;
    if ( v17 )
      v15 = 0;
    else
      v15 = 83;
    p = (char *)malloc(v18);
    if ( p || !v18 )
    {
      if ( !v15 )
      {
        sub_BE74((int)v53, (int)v54, v59, v60, v61, a4, a5, v10);
        if ( v10 <= 7 )
        {
          do
          {
            v27 = 0;
            v28 = 0;
            v46 = *(_DWORD *)&v53[v15] * v10;
            while ( v28 < *(_DWORD *)&v54[v15] )
            {
              v29 = 0;
              v30 = &v50;
              for ( i = 0; i < *(_DWORD *)&v53[v15]; ++i )
              {
                *(_DWORD *)v30 = (*(_DWORD *)((char *)&unk_15BBC + v15) + *(_DWORD *)((char *)&unk_15BA0 + v15) * v28)
                               * a4
                               * v10
                               + v10 * (*(_DWORD *)((char *)&unk_15B84 + v15) + *(_DWORD *)&asc_15B68[v15] * i);
                v49 = v27 + 8 * *(_DWORD *)((char *)v61 + v15) + v29;
                for ( j = 0; j != v10; j = v41 + 1 )
                {
                  v41 = j;
                  v40 = v30;
                  v33 = sub_B80A(v30, a3);
                  sub_B84C(&v49, (int)p, v33);
                  v30 = v40;
                }
                v29 += v10;
              }
              ++v28;
              v27 += v46;
            }
            v15 += 4;
          }
          while ( v15 != 28 );
        }
        else
        {
          v48 = v10 >> 3;
          do
          {
            v47 = *(_DWORD *)&v54[v15];
            for ( k = 0; k != v47; ++k )
            {
              v20 = 0;
              v21 = *(_DWORD *)&v53[v15];
              for ( m = 0; m != v21; ++m )
              {
                v23 = 0;
                v24 = a3
                    + v48
                    * (*(_DWORD *)((char *)&unk_15B84 + v15)
                     + a4 * (*(_DWORD *)((char *)&unk_15BBC + v15) + *(_DWORD *)((char *)&unk_15BA0 + v15) * k)
                     + *(_DWORD *)&asc_15B68[v15] * m);
                v25 = &p[v48 * v21 * k + v20 + *(_DWORD *)((char *)v61 + v15)];
                do
                {
                  v25[v23] = *(_BYTE *)(v24 + v23);
                  ++v23;
                }
                while ( v23 < v48 );
                v20 += v48;
              }
            }
            v15 += 4;
          }
          while ( v15 != 28 );
        }
        for ( n = 0; n != 7; ++n )
        {
          if ( v10 <= 7 )
          {
            v34 = (unsigned int *)malloc(v57[n + 1] - v57[n]);
            v35 = v34;
            if ( !v34 )
              goto LABEL_10;
            sub_C28E(
              v34,
              (int)&p[v58[n]],
              (*(_DWORD *)&v51[n * 4] * v10 + 7) & 0xFFFFFFF8,
              *(_DWORD *)&v51[n * 4] * v10,
              *(_DWORD *)&v52[n * 4]);
            v15 = sub_E3EC(&(*a1)[v55[n]], (int)v35, *(_DWORD *)&v51[n * 4], *(_DWORD *)&v52[n * 4], v43, a7);
            free(v35);
          }
          else
          {
            v15 = sub_E3EC(&(*a1)[v55[n]], (int)&p[v57[n]], *(_DWORD *)&v51[n * 4], *(_DWORD *)&v52[n * 4], v43, a7);
          }
          if ( v15 )
            break;
        }
      }
    }
    else
    {
LABEL_10:
      v15 = 83;
    }
    v36 = p;
LABEL_42:
    free(v36);
    return v15;
  }
  v11 = a4 * bpp;
  v12 = (unsigned int)(a4 * bpp + 7) >> 3;
  v13 = a5 * (v12 + 1);
  *a2 = v13;
  v14 = malloc(v13);
  *a1 = v14;
  if ( v14 || !*a2 )
  {
    if ( v10 > 7 || v11 == 8 * v12 )
      return sub_E3EC(v14, a3, a4, a5, v43, a7);
    v37 = (unsigned int *)malloc(v13 - a5);
    v38 = (int)v37;
    if ( v37 )
    {
      sub_C28E(v37, a3, 8 * v12, v11, a5);
      v15 = sub_E3EC(*a1, v38, a4, a5, v43, a7);
    }
    else
    {
      v15 = 83;
    }
    v36 = (void *)v38;
    goto LABEL_42;
  }
  return 83;
}


//----- (00011E3C) --------------------------------------------------------
_DWORD *__fastcall sub_11E3C(_DWORD *a1, _DWORD *a2, const std::string *a3)
{
  while ( a1 )
  {
    if ( std::operator<<char>((std::string *)(a1 + 4), a3) )
    {
      a1 = (_DWORD *)a1[3];
    }
    else
    {
      a2 = a1;
      a1 = (_DWORD *)a1[2];
    }
  }
  return a2;
}


//----- (00013130) --------------------------------------------------------
int __fastcall sub_13130(int result, unsigned int a2)
{
  char v2; // nf
  int v3; // r12
  unsigned int v4; // r3
  char v5; // r0
  unsigned int v6; // r1
  unsigned int v7; // r2
  bool v8; // zf

  v3 = result ^ a2;
  if ( v2 )
    a2 = -a2;
  if ( a2 == 1 )
  {
    if ( (v3 ^ result) < 0 )
      return -result;
  }
  else
  {
    v4 = result;
    if ( result < 0 )
      v4 = -result;
    if ( v4 <= a2 )
    {
      if ( v4 < a2 )
        result = 0;
      if ( v4 == a2 )
        return (v3 >> 31) | 1;
    }
    else if ( (a2 & (a2 - 1)) != 0 )
    {
      v5 = __clz(a2) - __clz(v4);
      v6 = a2 << v5;
      v7 = 1 << v5;
      result = 0;
      while ( 1 )
      {
        if ( v4 >= v6 )
        {
          v4 -= v6;
          result |= v7;
        }
        if ( v4 >= v6 >> 1 )
        {
          v4 -= v6 >> 1;
          result |= v7 >> 1;
        }
        if ( v4 >= v6 >> 2 )
        {
          v4 -= v6 >> 2;
          result |= v7 >> 2;
        }
        if ( v4 >= v6 >> 3 )
        {
          v4 -= v6 >> 3;
          result |= v7 >> 3;
        }
        v8 = v4 == 0;
        if ( v4 )
        {
          v7 >>= 4;
          v8 = v7 == 0;
        }
        if ( v8 )
          break;
        v6 >>= 4;
      }
      if ( v3 < 0 )
        return -result;
    }
    else
    {
      result = v4 >> (31 - __clz(a2));
      if ( v3 < 0 )
        return -result;
    }
  }
  return result;
}
// 13134: variable 'v2' is possibly undefined


//----- (00013218) --------------------------------------------------------
char *__fastcall sub_13218(int *a1)
{
  int v1; // r3
  unsigned int v2; // r3

  v1 = *a1;
  if ( (*a1 & 0x40000000) != 0 )
    v2 = v1 | 0x80000000;
  else
    v2 = v1 & 0x7FFFFFFF;
  return (char *)a1 + v2;
}


//----- (0001322A) --------------------------------------------------------
int *__fastcall sub_1322A(int a1, int a2, unsigned int a3)
{
  int v5; // r8
  int v6; // r7
  int v7; // r10
  int v8; // r4
  int *v9; // r5
  char *v10; // r0
  char *v11; // r11
  char *v12; // r0

  if ( a2 )
  {
    v5 = a2 - 1;
    v6 = 0;
    v7 = a2 - 1;
    while ( 1 )
    {
      v8 = (v6 + v7) / 2;
      v9 = (int *)(a1 + 8 * v8);
      v10 = sub_13218(v9);
      v11 = v10;
      if ( v8 == v5 )
      {
        if ( a3 >= (unsigned int)v10 )
          return v9;
LABEL_5:
        if ( v8 == v6 )
          return 0;
        v7 = v8 - 1;
      }
      else
      {
        v12 = sub_13218((int *)(8 * v8 + 8 + a1));
        if ( a3 < (unsigned int)v11 )
          goto LABEL_5;
        if ( a3 <= (unsigned int)(v12 - 1) )
          return v9;
        v6 = v8 + 1;
      }
    }
  }
  return 0;
}


//----- (000132C4) --------------------------------------------------------
int __fastcall sub_132C4(_DWORD *a1, int a2)
{
  unsigned int v3; // r6
  int *exidx; // r0
  int *v5; // r5
  int *v6; // r0
  char *v8; // r0
  int v9; // r3
  int *v10; // r0
  int v11; // r3
  char *v12; // r0
  int *v13; // r0
  int (*v14)(); // r0
  int v15; // [sp+4h] [bp-4h] BYREF

  v15 = a2;
  v3 = a2 - 2;
  if ( &__gnu_Unwind_Find_exidx )
  {
    exidx = (int *)_gnu_Unwind_Find_exidx(a2 - 2, &v15);
    v5 = exidx;
    if ( !exidx )
      goto LABEL_6;
  }
  else
  {
    exidx = (int *)&unk_14124;
    v15 = (&unk_149EC - &unk_14124) >> 3;
  }
  v6 = sub_1322A((int)exidx, v15, v3);
  v5 = v6;
  if ( !v6 )
  {
LABEL_6:
    a1[4] = v5;
    return 9;
  }
  v8 = sub_13218(v6);
  v9 = v5[1];
  a1[18] = v8;
  if ( v9 == 1 )
  {
    a1[4] = 0;
    return 5;
  }
  else
  {
    v10 = v5 + 1;
    if ( v9 >= 0 )
    {
      v12 = sub_13218(v10);
      v11 = 0;
      a1[19] = v12;
    }
    else
    {
      a1[19] = v10;
      v11 = 1;
    }
    v13 = (int *)a1[19];
    a1[20] = v11;
    if ( *v13 >= 0 )
    {
      a1[4] = sub_13218(v13);
      return 0;
    }
    else
    {
      v14 = sub_13292(HIBYTE(*v13) & 0xF);
      a1[4] = v14;
      if ( v14 )
        return 0;
      else
        return 9;
    }
  }
}
// 7CE4: using guessed type int __fastcall _gnu_Unwind_Find_exidx(_DWORD, _DWORD);


//----- (00013368) --------------------------------------------------------
void __fastcall sub_13368(_DWORD *a1)
{
  if ( (*a1 & 1) == 0 )
  {
    if ( (*a1 & 2) != 0 )
      _gnu_Unwind_Restore_VFP_D();
    else
      _gnu_Unwind_Restore_VFP();
  }
  if ( (*a1 & 4) == 0 )
    _gnu_Unwind_Restore_VFP_D_16_to_31();
  if ( (*a1 & 8) == 0 )
    _gnu_Unwind_Restore_WMMXD(a1 + 84);
  if ( (*a1 & 0x10) == 0 )
    _gnu_Unwind_Restore_WMMXC(a1 + 116);
}


//----- (000133B6) --------------------------------------------------------
int __fastcall sub_133B6(_DWORD *a1)
{
  if ( *a1 )
    return *(_DWORD *)((char *)a1 + *a1);
  else
    return 0;
}


//----- (000133C2) --------------------------------------------------------
int sub_133C2()
{
  return 9;
}


//----- (000133C8) --------------------------------------------------------
int __fastcall sub_133C8(int a1, int a2)
{
  int v4; // r0
  int v5; // r1
  int v6; // r2
  int v7; // r3
  int savedregs; // [sp+0h] [bp+0h]

  do
  {
    if ( sub_132C4((_DWORD *)a1, *(_DWORD *)(a2 + 64)) )
      goto LABEL_2;
    *(_DWORD *)(a1 + 20) = *(_DWORD *)(a2 + 64);
    v4 = (*(int (__fastcall **)(int, int, int))(a1 + 16))(1, a1, a2);
  }
  while ( v4 == 8 );
  if ( v4 != 7 )
LABEL_2:
    abort();
  nullsub_1(0, *(_DWORD *)(a2 + 64));
  restore_core_regs(a2 + 4, v5, v6, v7, savedregs);
  return sub_13402();
}
// 133FE: variable 'v5' is possibly undefined
// 133FE: variable 'v6' is possibly undefined
// 133FE: variable 'v7' is possibly undefined
// 133FE: variable 'savedregs' is possibly undefined
// 133C6: using guessed type int __fastcall nullsub_1(_DWORD, _DWORD);
// 13402: using guessed type int sub_13402(void);


//----- (00013402) --------------------------------------------------------
int __fastcall sub_13402(int a1, int a2, int a3)
{
  int *v3; // r5
  int (__fastcall *v4)(int, int, int, int); // r8
  int v7; // r0
  int v8; // r1
  int v9; // r2
  int v10; // r3
  int v11; // r0
  int v12; // r1
  int v13; // r2
  int v14; // r3
  int v15; // r0
  int v16; // r1
  int v17; // r2
  int v18; // r3
  int v19; // r1
  int v20; // r2
  int v21; // r3
  int v22; // r11
  int v23; // r0
  int v24; // r10
  int v25; // r4
  int v26; // r0
  int v27; // r3
  int v28; // r1
  int v29; // r2
  int v30; // r3
  _DWORD v32[120]; // [sp+8h] [bp-3C4h] BYREF
  _DWORD v33[121]; // [sp+1E8h] [bp-1E4h] BYREF

  v3 = (int *)(a2 + 4);
  v4 = *(int (__fastcall **)(int, int, int, int))(a1 + 12);
  v7 = *(_DWORD *)(a2 + 4);
  v8 = *(_DWORD *)(a2 + 8);
  v9 = v3[2];
  v10 = v3[3];
  v3 += 4;
  v32[1] = v7;
  v32[2] = v8;
  v32[3] = v9;
  v32[4] = v10;
  v11 = *v3;
  v12 = v3[1];
  v13 = v3[2];
  v14 = v3[3];
  v3 += 4;
  v32[5] = v11;
  v32[6] = v12;
  v32[7] = v13;
  v32[8] = v14;
  v15 = *v3;
  v16 = v3[1];
  v17 = v3[2];
  v18 = v3[3];
  v3 += 4;
  v32[9] = v15;
  v32[10] = v16;
  v32[11] = v17;
  v32[12] = v18;
  v19 = v3[1];
  v20 = v3[2];
  v21 = v3[3];
  v32[13] = *v3;
  v32[14] = v19;
  v32[15] = v20;
  v32[16] = v21;
  v22 = 0;
  v32[0] = 0;
  while ( 1 )
  {
    v23 = sub_132C4((_DWORD *)a1, v32[16]);
    if ( a3 )
      v24 = 10;
    else
      v24 = 9;
    v25 = v23;
    if ( v23 )
    {
      v27 = v32[14];
      v24 |= 0x10u;
    }
    else
    {
      *(_DWORD *)(a1 + 20) = v32[16];
      memcpy(v33, v32, 0x1E0u);
      v26 = (*(int (__fastcall **)(int, int, _DWORD *))(a1 + 16))(v24, a1, v33);
      v27 = v33[14];
      v22 = v26;
    }
    v32[17] = v27;
    if ( v4(1, v24, a1, a1) )
      return 9;
    if ( v25 )
      break;
    memcpy(v32, v33, sizeof(v32));
    if ( v22 != 8 )
    {
      if ( v22 == 7 )
      {
        nullsub_1(0, v32[16]);
        restore_core_regs((int)&v32[1], v28, v29, v30, (int)v32);
      }
      return 9;
    }
    a3 = 0;
  }
  return v25;
}
// 134B2: variable 'v28' is possibly undefined
// 134B2: variable 'v29' is possibly undefined
// 134B2: variable 'v30' is possibly undefined
// 133C6: using guessed type int __fastcall nullsub_1(_DWORD, _DWORD);


//----- (000135CC) --------------------------------------------------------
int __fastcall sub_135CC(int a1, unsigned int a2, int a3, int a4)
{
  int v5; // [sp+Ch] [bp-4h] BYREF

  v5 = a4;
  Unwind_VRS_Get(a1, 0, a2, &v5);
  return v5;
}


//----- (00013610) --------------------------------------------------------
int __fastcall sub_13610(int a1, unsigned int a2, int a3)
{
  int v4; // [sp+Ch] [bp-4h] BYREF

  v4 = a3;
  return Unwind_VRS_Set(a1, 0, a2, &v4);
}


//----- (000136A4) --------------------------------------------------------
int __fastcall sub_136A4(char a1, void (__noreturn **a2)(void *), unsigned int *a3, int a4)
{
  int *v5; // r2
  int *v8; // r5
  int v9; // r10
  int v10; // r2
  int v12; // r3
  int v13; // r3
  int v14; // r9
  int v15; // r8
  int v16; // r3
  int *v17; // r5
  unsigned int v18; // r0
  int v19; // r8
  char *v20; // r0
  char *v21; // r5
  int v22; // r0
  unsigned int v23; // r1
  void (__noreturn **v24)(void *); // r2
  int v25; // r3
  int v26; // r0
  int v27; // r0
  void (__noreturn *v28)(void *); // r2
  void (__noreturn *v29)(void *); // r3
  void (__noreturn *v30)(void *); // r8
  int *v31; // r0
  char *v32; // r0
  int v34; // r3
  int v35; // r8
  int v36; // r12
  int v37; // r0
  int v38; // r0
  int v39; // r0
  int v40; // r8
  int v41; // r0
  int v42; // r2
  int v43; // r3
  int v44; // r0
  unsigned int v45; // [sp+0h] [bp-24h]
  int v46; // [sp+0h] [bp-24h]
  char v47; // [sp+4h] [bp-20h]
  int v48; // [sp+4h] [bp-20h]
  int v49; // [sp+4h] [bp-20h]
  void (__noreturn *v50)(void *); // [sp+8h] [bp-1Ch]
  void (__noreturn *v51)(void *); // [sp+10h] [bp-14h] BYREF
  int v52[2]; // [sp+14h] [bp-10h] BYREF
  char v53; // [sp+1Ch] [bp-8h]
  char v54; // [sp+1Dh] [bp-7h]

  v5 = (int *)a2[19];
  v8 = v5 + 1;
  v9 = a1 & 3;
  v10 = *v5;
  v52[1] = (int)v8;
  v52[0] = v10;
  if ( a4 )
  {
    if ( a4 <= 2 )
    {
      v54 = BYTE2(v10);
      v52[0] = v10 << 16;
      v12 = BYTE2(v10);
      v10 = 2;
      v53 = 2;
      v8 += v12;
    }
  }
  else
  {
    v10 <<= 8;
    v54 = 0;
    v52[0] = v10;
    v53 = 3;
  }
  v13 = (int)a2[20];
  if ( v9 == 2 )
    v8 = (int *)a2[14];
  v14 = (unsigned int)a2[20] & 1;
  if ( (v13 & 1) != 0 )
  {
    v14 = 0;
LABEL_59:
    if ( a4 <= 2 )
      v41 = _gnu_unwind_execute(a3, v52, v10, v13);
    else
      v41 = sub_133C2();
    if ( v41 )
      return 9;
    if ( !v14 )
      return 8;
    v44 = sub_135CC((int)a3, 0xFu, v42, v43);
    sub_13610((int)a3, 0xEu, v44);
    v22 = (int)a3;
    v23 = 15;
    v24 = &_cxa_call_unexpected;
LABEL_37:
    sub_13610(v22, v23, (int)v24);
    return 7;
  }
  v13 = (int)&v51;
  v50 = (void (__noreturn *)(void *))(a2 + 22);
  while ( 1 )
  {
    while ( 1 )
    {
      v15 = *v8;
      if ( !*v8 )
        goto LABEL_59;
      if ( a4 == 2 )
      {
        v16 = v8[1];
        v17 = v8 + 2;
      }
      else
      {
        v15 = *(unsigned __int16 *)v8;
        v17 = v8 + 1;
        v16 = *((unsigned __int16 *)v17 - 1);
      }
      v45 = (unsigned int)a2[18] + (v16 & 0xFFFFFFFE);
      v47 = v16;
      v18 = sub_135CC((int)a3, 0xFu, v45, v16);
      v10 = v45 <= v18 && v18 < v45 + (v15 & 0xFFFFFFFE);
      v13 = v47 & 1;
      v19 = v15 & 1 | (2 * v13);
      if ( v19 == 1 )
        break;
      if ( v19 )
      {
        if ( v19 != 2 )
          return 9;
        v34 = *v17;
        v35 = *v17 & 0x7FFFFFFF;
        if ( v9 )
        {
          v49 = (int)a2[8];
          if ( v49 != sub_135CC((int)a3, 0xDu, v10, v49) || v17 != (int *)a2[10] )
            goto LABEL_55;
          a2[12] = (void (__noreturn *)(void *))&byte_4;
          a2[10] = (void (__noreturn *)(void *))v35;
          a2[11] = 0;
          a2[13] = (void (__noreturn *)(void *))(v17 + 1);
          if ( *v17 < 0 )
          {
            v31 = &v17[v35 + 1];
            goto LABEL_36;
          }
          v14 = 1;
        }
        else if ( v10 && ((a1 & 8) == 0 || !v35) )
        {
          v36 = 0;
          while ( v36 != v35 )
          {
            v48 = v36 + 1;
            v51 = v50;
            v37 = sub_133B6(&v17[v36 + 1]);
            v38 = _cxa_type_match(a2, v37, 0, &v51);
            v36 = v48;
            if ( v38 )
              goto LABEL_55;
          }
          v39 = sub_135CC((int)a3, 0xDu, v10, v34);
          v29 = v51;
          a2[8] = (void (__noreturn *)(void *))v39;
LABEL_48:
          a2[9] = v29;
          goto LABEL_49;
        }
LABEL_55:
        v13 = *v17;
        v40 = v35 + 1;
        if ( *v17 < 0 )
          ++v17;
        v8 = &v17[v40];
      }
      else
      {
        if ( v9 && v10 )
        {
          v20 = sub_13218(v17);
          a2[14] = (void (__noreturn *)(void *))(v17 + 1);
          v21 = v20;
          if ( !_cxa_begin_cleanup(a2) )
            return 9;
          v22 = (int)a3;
          v23 = 15;
          v24 = (void (__noreturn **)(void *))v21;
          goto LABEL_37;
        }
        v8 = v17 + 1;
      }
    }
    if ( !v9 )
      break;
    v30 = a2[8];
    if ( v30 == (void (__noreturn *)(void *))sub_135CC((int)a3, 0xDu, v10, v13) )
    {
      v13 = (int)a2[10];
      if ( v17 == (int *)v13 )
      {
        v31 = v17;
LABEL_36:
        v32 = sub_13218(v31);
        sub_13610((int)a3, 0xFu, (int)v32);
        v22 = (int)a3;
        v23 = 0;
        v24 = a2;
        goto LABEL_37;
      }
    }
LABEL_38:
    v8 = v17 + 2;
  }
  if ( !v10 )
    goto LABEL_38;
  v25 = v17[1];
  v10 = (unsigned int)*v17 >> 31;
  if ( v25 == -2 )
    return 9;
  v13 = v25 + 1;
  v51 = v50;
  if ( v13 )
  {
    v46 = v10;
    v26 = sub_133B6(v17 + 1);
    v19 = _cxa_type_match(a2, v26, v46, &v51);
    if ( !v19 )
      goto LABEL_38;
  }
  v27 = sub_135CC((int)a3, 0xDu, v10, v13);
  v28 = v51;
  a2[8] = (void (__noreturn *)(void *))v27;
  if ( v19 == 2 )
  {
    a2[11] = v28;
    v29 = (void (__noreturn *)(void *))(a2 + 11);
    goto LABEL_48;
  }
  a2[9] = v28;
LABEL_49:
  a2[10] = (void (__noreturn *)(void *))v17;
  return 6;
}
// 137DE: variable 'v10' is possibly undefined
// 137DE: variable 'v13' is possibly undefined
// 13882: variable 'v34' is possibly undefined
// 13906: variable 'v42' is possibly undefined
// 13906: variable 'v43' is possibly undefined
// 4: using guessed type char;
// 7CFC: using guessed type int __fastcall _cxa_begin_cleanup(_DWORD);
// 7D08: using guessed type int __fastcall _cxa_type_match(_DWORD, _DWORD, _DWORD, _DWORD);


//----- (00013D08) --------------------------------------------------------
int __fastcall sub_13D08(int *a1)
{
  int *v1; // r3
  char v2; // r3
  unsigned int v3; // r3

  if ( *((_BYTE *)a1 + 8) )
  {
    v2 = *((_BYTE *)a1 + 8) - 1;
    goto LABEL_5;
  }
  if ( *((_BYTE *)a1 + 9) )
  {
    --*((_BYTE *)a1 + 9);
    v1 = (int *)a1[1];
    a1[1] = (int)(v1 + 1);
    *a1 = *v1;
    v2 = 3;
LABEL_5:
    *((_BYTE *)a1 + 8) = v2;
    v3 = *a1;
    *a1 <<= 8;
    return HIBYTE(v3);
  }
  return 176;
}


//----- (00013D34) --------------------------------------------------------
int __fastcall sub_13D34(int a1, int a2, int a3, int a4)
{
  int v5; // [sp+Ch] [bp-4h] BYREF

  v5 = a4;
  Unwind_VRS_Get(a1, 0, 0xCu, &v5);
  return v5;
}


