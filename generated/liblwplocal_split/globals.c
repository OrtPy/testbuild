// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: globals  Functions: 190

//----- (00008058) --------------------------------------------------------
int (*__fastcall sub_8058(int (*result)(void)))(void)
{
  if ( result )
    return (int (*)(void))result();
  return result;
}


//----- (0000808C) --------------------------------------------------------
// Alternative name is '_ZN6varrayC1Ev'
void __fastcall varray::varray(varray *this)
{
  memset((char *)this + 8, 0, 0x10u);
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 4) = (char *)this + 8;
  *((_DWORD *)this + 5) = (char *)this + 8;
}


//----- (0000814E) --------------------------------------------------------
// Alternative name is '_ZN6bufferC1Eji'
void __fastcall buffer::buffer(buffer *this, unsigned int a2, int a3)
{
  char *v3; // r5

  v3 = (char *)this + 4;
  memset((char *)this + 4, 0, 0x10u);
  *((_DWORD *)this + 7) = a3;
  *((_DWORD *)this + 3) = v3;
  *((_DWORD *)this + 5) = 0;
  *((_DWORD *)this + 4) = v3;
  *((_DWORD *)this + 6) = a2;
  if ( a3 == -1 )
    glGenBuffers(1, (char *)this + 28);
}
// 772C: using guessed type int __fastcall glGenBuffers(_DWORD, _DWORD);


//----- (00008182) --------------------------------------------------------
void __fastcall std::_Rb_tree<bufferconfig *,bufferconfig *,std::_Identity<bufferconfig *>,std::less<bufferconfig *>,std::allocator<bufferconfig *>>::_M_erase(
        int a1,
        _DWORD *a2)
{
  _DWORD *v4; // r6

  while ( a2 )
  {
    std::_Rb_tree<bufferconfig *,bufferconfig *,std::_Identity<bufferconfig *>,std::less<bufferconfig *>,std::allocator<bufferconfig *>>::_M_erase(
      a1,
      a2[3]);
    v4 = (_DWORD *)a2[2];
    operator delete(a2);
    a2 = v4;
  }
}


//----- (000081A0) --------------------------------------------------------
// Alternative name is '_ZNSt6vectorIP12bufferconfigSaIS1_EE19_M_emplace_back_auxIJRKS1_EEEvDpOT_'
void __fastcall std::vector<bufferconfig *>::_M_emplace_back_aux<bufferconfig * const&>(int a1, _DWORD *a2)
{
  int v4; // r6
  int v5; // r3
  bool v6; // cf
  unsigned int v7; // r3
  int v8; // r6
  _DWORD *v9; // r5
  int v10; // r3
  size_t v11; // r7
  int v12; // r7

  v4 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( v4 )
    v5 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  else
    v5 = 1;
  v6 = __CFADD__(v5, v4);
  v7 = v5 + v4;
  v8 = 0x3FFFFFFF;
  if ( v6 )
    goto LABEL_8;
  if ( v7 < 0x3FFFFFFF )
    v8 = v7;
  if ( v8 )
LABEL_8:
    v9 = (_DWORD *)operator new(4 * v8);
  else
    v9 = 0;
  v10 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( &v9[v10] )
    v9[v10] = *a2;
  v11 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2 )
    memmove(v9, *(const void **)a1, v11 * 4);
  v12 = (int)&v9[v11 + 1];
  if ( *(_DWORD *)a1 )
    operator delete(*(void **)a1);
  *(_DWORD *)a1 = v9;
  *(_DWORD *)(a1 + 4) = v12;
  *(_DWORD *)(a1 + 8) = &v9[v8];
}


//----- (00008368) --------------------------------------------------------
int __fastcall std::operator<<char>(std::string *a1, const std::string *a2)
{
  return std::string::compare(a1, a2) >> 31;
}


//----- (00008372) --------------------------------------------------------
int *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_get_insert_unique_pos(
        int *a1,
        int a2,
        std::string *a3)
{
  int v3; // r4
  _DWORD *v4; // r6
  int v8; // r0
  _DWORD *v9; // r3
  int v10; // r9

  v3 = a2 + 4;
  v4 = *(_DWORD **)(a2 + 8);
  v8 = 1;
  while ( v4 )
  {
    v8 = std::operator<<char>(a3, (const std::string *)(v4 + 4));
    if ( v8 )
      v9 = (_DWORD *)v4[2];
    else
      v9 = (_DWORD *)v4[3];
    v3 = (int)v4;
    v4 = v9;
  }
  v10 = v3;
  if ( v8 )
  {
    if ( v3 == *(_DWORD *)(a2 + 12) )
    {
      *a1 = 0;
      a1[1] = v3;
      return a1;
    }
    v3 = std::_Rb_tree_decrement(v3);
  }
  if ( std::operator<<char>((std::string *)(v3 + 16), a3) )
  {
    *a1 = 0;
    a1[1] = v10;
  }
  else
  {
    *a1 = v3;
    a1[1] = 0;
  }
  return a1;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);


//----- (000083D2) --------------------------------------------------------
// Alternative name is '_ZNSt8_Rb_treeISsSt4pairIKSsP9attributeESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_'
_DWORD *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string const&>,std::tuple<>>(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        const std::string **a4)
{
  _DWORD *v7; // r0
  _DWORD *v8; // r9
  std::string *v9; // r5
  int v10; // r4
  int v11; // r7
  int v12; // r8
  int v13; // r0
  _DWORD *v15; // [sp+0h] [bp-Ch] BYREF
  int v16; // [sp+4h] [bp-8h]
  int v17; // [sp+8h] [bp-4h]

  v15 = a1;
  v16 = (int)a2;
  v17 = a3;
  v7 = (_DWORD *)operator new(0x18u);
  v8 = v7;
  v9 = (std::string *)(v7 + 4);
  if ( v7 )
  {
    memset(v7, 0, 0x10u);
    std::string::string(v9, *a4);
    v8[5] = 0;
  }
  v10 = (int)a2;
  if ( a2 != a1 + 1 )
  {
    v11 = std::operator<<char>(v9, (const std::string *)(a2 + 4));
    if ( v11 )
    {
      if ( a2 == (_DWORD *)a1[3] )
      {
        v12 = (int)a2;
      }
      else
      {
        v12 = std::_Rb_tree_decrement(a2);
        if ( std::operator<<char>((std::string *)(v12 + 16), v9) )
        {
          if ( *(_DWORD *)(v12 + 12) )
            v12 = (int)a2;
          else
            v10 = 0;
        }
        else
        {
          std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_get_insert_unique_pos(
            (int *)&v15,
            (int)a1,
            v9);
          v10 = (int)v15;
          v12 = v16;
        }
      }
      v11 = v10;
      v10 = v12;
      goto LABEL_23;
    }
    if ( !std::operator<<char>((std::string *)(a2 + 4), v9) )
      goto LABEL_30;
    if ( a2 == (_DWORD *)a1[4] )
      goto LABEL_23;
    v11 = std::_Rb_tree_increment(a2);
    if ( std::operator<<char>(v9, (const std::string *)(v11 + 16)) )
    {
      if ( a2[3] )
        v10 = v11;
      else
        v11 = 0;
      goto LABEL_23;
    }
LABEL_22:
    std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_get_insert_unique_pos(
      (int *)&v15,
      (int)a1,
      v9);
    v11 = (int)v15;
    v10 = v16;
LABEL_23:
    if ( v10 )
    {
      if ( v11 )
        goto LABEL_27;
      goto LABEL_25;
    }
    v10 = v11;
    goto LABEL_30;
  }
  if ( !a1[5] )
    goto LABEL_22;
  v10 = a1[4];
  if ( !std::operator<<char>((std::string *)(v10 + 16), v9) )
    goto LABEL_22;
  if ( v10 )
  {
LABEL_25:
    if ( (_DWORD *)v10 != a1 + 1 )
    {
      v13 = std::operator<<char>(v9, (const std::string *)(v10 + 16));
LABEL_28:
      std::_Rb_tree_insert_and_rebalance(v13, v8, v10, a1 + 1);
      ++a1[5];
      return v8;
    }
LABEL_27:
    v13 = 1;
    goto LABEL_28;
  }
LABEL_30:
  std::string::~string(v9);
  operator delete(v8);
  return (_DWORD *)v10;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


//----- (00008614) --------------------------------------------------------
int *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,bufferconfig *>,std::_Select1st<std::pair<std::string const,bufferconfig *>>,std::less<std::string>,std::allocator<std::pair<std::string const,bufferconfig *>>>::_M_get_insert_unique_pos(
        int *a1,
        int a2,
        std::string *a3)
{
  int v3; // r4
  _DWORD *v4; // r6
  int v8; // r0
  _DWORD *v9; // r3
  int v10; // r9

  v3 = a2 + 4;
  v4 = *(_DWORD **)(a2 + 8);
  v8 = 1;
  while ( v4 )
  {
    v8 = std::operator<<char>(a3, (const std::string *)(v4 + 4));
    if ( v8 )
      v9 = (_DWORD *)v4[2];
    else
      v9 = (_DWORD *)v4[3];
    v3 = (int)v4;
    v4 = v9;
  }
  v10 = v3;
  if ( v8 )
  {
    if ( v3 == *(_DWORD *)(a2 + 12) )
    {
      *a1 = 0;
      a1[1] = v3;
      return a1;
    }
    v3 = std::_Rb_tree_decrement(v3);
  }
  if ( std::operator<<char>((std::string *)(v3 + 16), a3) )
  {
    *a1 = 0;
    a1[1] = v10;
  }
  else
  {
    *a1 = v3;
    a1[1] = 0;
  }
  return a1;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);


//----- (00008674) --------------------------------------------------------
// Alternative name is '_ZNSt8_Rb_treeISsSt4pairIKSsP12bufferconfigESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_'
_DWORD *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,bufferconfig *>,std::_Select1st<std::pair<std::string const,bufferconfig *>>,std::less<std::string>,std::allocator<std::pair<std::string const,bufferconfig *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string const&>,std::tuple<>>(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        const std::string **a4)
{
  _DWORD *v7; // r0
  _DWORD *v8; // r9
  std::string *v9; // r5
  int v10; // r4
  int v11; // r7
  int v12; // r8
  int v13; // r0
  _DWORD *v15; // [sp+0h] [bp-Ch] BYREF
  int v16; // [sp+4h] [bp-8h]
  int v17; // [sp+8h] [bp-4h]

  v15 = a1;
  v16 = (int)a2;
  v17 = a3;
  v7 = (_DWORD *)operator new(0x18u);
  v8 = v7;
  v9 = (std::string *)(v7 + 4);
  if ( v7 )
  {
    memset(v7, 0, 0x10u);
    std::string::string(v9, *a4);
    v8[5] = 0;
  }
  v10 = (int)a2;
  if ( a2 != a1 + 1 )
  {
    v11 = std::operator<<char>(v9, (const std::string *)(a2 + 4));
    if ( v11 )
    {
      if ( a2 == (_DWORD *)a1[3] )
      {
        v12 = (int)a2;
      }
      else
      {
        v12 = std::_Rb_tree_decrement(a2);
        if ( std::operator<<char>((std::string *)(v12 + 16), v9) )
        {
          if ( *(_DWORD *)(v12 + 12) )
            v12 = (int)a2;
          else
            v10 = 0;
        }
        else
        {
          std::_Rb_tree<std::string,std::pair<std::string const,bufferconfig *>,std::_Select1st<std::pair<std::string const,bufferconfig *>>,std::less<std::string>,std::allocator<std::pair<std::string const,bufferconfig *>>>::_M_get_insert_unique_pos(
            (int *)&v15,
            (int)a1,
            v9);
          v10 = (int)v15;
          v12 = v16;
        }
      }
      v11 = v10;
      v10 = v12;
      goto LABEL_23;
    }
    if ( !std::operator<<char>((std::string *)(a2 + 4), v9) )
      goto LABEL_30;
    if ( a2 == (_DWORD *)a1[4] )
      goto LABEL_23;
    v11 = std::_Rb_tree_increment(a2);
    if ( std::operator<<char>(v9, (const std::string *)(v11 + 16)) )
    {
      if ( a2[3] )
        v10 = v11;
      else
        v11 = 0;
      goto LABEL_23;
    }
LABEL_22:
    std::_Rb_tree<std::string,std::pair<std::string const,bufferconfig *>,std::_Select1st<std::pair<std::string const,bufferconfig *>>,std::less<std::string>,std::allocator<std::pair<std::string const,bufferconfig *>>>::_M_get_insert_unique_pos(
      (int *)&v15,
      (int)a1,
      v9);
    v11 = (int)v15;
    v10 = v16;
LABEL_23:
    if ( v10 )
    {
      if ( v11 )
        goto LABEL_27;
      goto LABEL_25;
    }
    v10 = v11;
    goto LABEL_30;
  }
  if ( !a1[5] )
    goto LABEL_22;
  v10 = a1[4];
  if ( !std::operator<<char>((std::string *)(v10 + 16), v9) )
    goto LABEL_22;
  if ( v10 )
  {
LABEL_25:
    if ( (_DWORD *)v10 != a1 + 1 )
    {
      v13 = std::operator<<char>(v9, (const std::string *)(v10 + 16));
LABEL_28:
      std::_Rb_tree_insert_and_rebalance(v13, v8, v10, a1 + 1);
      ++a1[5];
      return v8;
    }
LABEL_27:
    v13 = 1;
    goto LABEL_28;
  }
LABEL_30:
  std::string::~string(v9);
  operator delete(v8);
  return (_DWORD *)v10;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


//----- (000087A0) --------------------------------------------------------
_DWORD *__fastcall std::map<std::string,bufferconfig *>::operator[](
        _DWORD *a1,
        const std::string *a2,
        int a3,
        const std::string *a4)
{
  _DWORD *v4; // r8
  _DWORD *v5; // r5
  _DWORD *v8; // r4
  _DWORD *v9; // r3
  const std::string *v11; // [sp+Ch] [bp-4h] BYREF

  v11 = a4;
  v4 = a1 + 1;
  v5 = (_DWORD *)a1[2];
  v8 = a1 + 1;
  while ( v5 )
  {
    if ( std::operator<<char>((std::string *)(v5 + 4), a2) )
    {
      v9 = (_DWORD *)v5[3];
      v5 = v8;
    }
    else
    {
      v9 = (_DWORD *)v5[2];
    }
    v8 = v5;
    v5 = v9;
  }
  if ( v8 == v4 || std::operator<<char>(a2, (const std::string *)(v8 + 4)) )
  {
    v11 = a2;
    v8 = std::_Rb_tree<std::string,std::pair<std::string const,bufferconfig *>,std::_Select1st<std::pair<std::string const,bufferconfig *>>,std::less<std::string>,std::allocator<std::pair<std::string const,bufferconfig *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string const&>,std::tuple<>>(
           a1,
           v8,
           (int)&unk_149EC,
           &v11);
  }
  return v8 + 5;
}


//----- (00008868) --------------------------------------------------------
// Alternative name is '_ZN7programC1ERj'
void __fastcall program::program(program *this, unsigned int *a2)
{
  *(_DWORD *)this = *a2;
  memset((char *)this + 8, 0, 0x10u);
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 4) = (char *)this + 8;
  *((_DWORD *)this + 5) = (char *)this + 8;
}


//----- (000089D6) --------------------------------------------------------
int __fastcall std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::_M_insert_unique<uniformconfig * const&>(
        int a1,
        _DWORD *a2,
        _DWORD *a3)
{
  _DWORD *v3; // r9
  _DWORD *v4; // r5
  _DWORD *v8; // r4
  int v9; // r3
  _DWORD *v10; // r2
  int v11; // r0
  char v12; // r3
  _BOOL4 v14; // r10
  _DWORD *v15; // r0
  _DWORD *v16; // r5
  int v17; // r3

  v3 = a2 + 1;
  v4 = (_DWORD *)a2[2];
  v8 = a2 + 1;
  v9 = 1;
  while ( v4 )
  {
    v8 = v4;
    if ( *a3 >= v4[4] )
    {
      v10 = (_DWORD *)v4[3];
      v9 = 0;
    }
    else
    {
      v10 = (_DWORD *)v4[2];
      v9 = 1;
    }
    v4 = v10;
  }
  if ( v9 )
  {
    if ( v8 == (_DWORD *)a2[3] )
      goto LABEL_14;
    v11 = std::_Rb_tree_decrement(v8);
  }
  else
  {
    v11 = (int)v8;
  }
  if ( *(_DWORD *)(v11 + 16) >= *a3 )
  {
    v12 = 0;
    *(_DWORD *)a1 = v11;
    goto LABEL_13;
  }
LABEL_14:
  v14 = v8 == v3 || *a3 < v8[4];
  v15 = (_DWORD *)operator new(0x14u);
  v16 = v15;
  if ( v15 )
  {
    memset(v15, 0, 0x10u);
    v16[4] = *a3;
  }
  std::_Rb_tree_insert_and_rebalance(v14, v16, v8, v3);
  v17 = a2[5];
  *(_DWORD *)a1 = v16;
  a2[5] = v17 + 1;
  v12 = 1;
LABEL_13:
  *(_BYTE *)(a1 + 4) = v12;
  return a1;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);


//----- (00008A78) --------------------------------------------------------
// Alternative name is '_ZNSt6vectorIjSaIjEE19_M_emplace_back_auxIJRKjEEEvDpOT_'
void __fastcall std::vector<unsigned int>::_M_emplace_back_aux<unsigned int const&>(int a1, _DWORD *a2)
{
  int v4; // r6
  int v5; // r3
  bool v6; // cf
  unsigned int v7; // r3
  int v8; // r6
  _DWORD *v9; // r5
  int v10; // r3
  size_t v11; // r7
  int v12; // r7

  v4 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( v4 )
    v5 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  else
    v5 = 1;
  v6 = __CFADD__(v5, v4);
  v7 = v5 + v4;
  v8 = 0x3FFFFFFF;
  if ( v6 )
    goto LABEL_8;
  if ( v7 < 0x3FFFFFFF )
    v8 = v7;
  if ( v8 )
LABEL_8:
    v9 = (_DWORD *)operator new(4 * v8);
  else
    v9 = 0;
  v10 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( &v9[v10] )
    v9[v10] = *a2;
  v11 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2 )
    memmove(v9, *(const void **)a1, v11 * 4);
  v12 = (int)&v9[v11 + 1];
  if ( *(_DWORD *)a1 )
    operator delete(*(void **)a1);
  *(_DWORD *)a1 = v9;
  *(_DWORD *)(a1 + 4) = v12;
  *(_DWORD *)(a1 + 8) = &v9[v8];
}


//----- (00008B6C) --------------------------------------------------------
void __fastcall std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_erase(
        int a1,
        _DWORD *a2)
{
  _DWORD *v4; // r6

  while ( a2 )
  {
    std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_erase(
      a1,
      a2[3]);
    v4 = (_DWORD *)a2[2];
    std::string::~string((std::string *)(a2 + 4));
    operator delete(a2);
    a2 = v4;
  }
}


//----- (00008B92) --------------------------------------------------------
// Alternative name is '_ZNSt3mapISsP9attributeSt4lessISsESaISt4pairIKSsS1_EEED1Ev'
int __fastcall std::map<std::string,attribute *>::~map(int a1)
{
  std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_erase(
    a1,
    *(_DWORD **)(a1 + 8));
  return a1;
}


//----- (00008BA0) --------------------------------------------------------
void __fastcall std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_erase(
        int a1,
        _DWORD *a2)
{
  _DWORD *v4; // r6

  while ( a2 )
  {
    std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_erase(
      a1,
      a2[3]);
    v4 = (_DWORD *)a2[2];
    std::string::~string((std::string *)(a2 + 4));
    operator delete(a2);
    a2 = v4;
  }
}


//----- (00008BC6) --------------------------------------------------------
// Alternative name is '_ZNSt3mapISsP7uniformSt4lessISsESaISt4pairIKSsS1_EEED1Ev'
int __fastcall std::map<std::string,uniform *>::~map(int a1)
{
  std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_erase(
    a1,
    *(_DWORD **)(a1 + 8));
  return a1;
}


//----- (00008BD4) --------------------------------------------------------
int *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_get_insert_unique_pos(
        int *a1,
        int a2,
        std::string *a3)
{
  int v3; // r4
  _DWORD *v4; // r6
  int v8; // r0
  _DWORD *v9; // r3
  int v10; // r9

  v3 = a2 + 4;
  v4 = *(_DWORD **)(a2 + 8);
  v8 = 1;
  while ( v4 )
  {
    v8 = std::operator<<char>(a3, (const std::string *)(v4 + 4));
    if ( v8 )
      v9 = (_DWORD *)v4[2];
    else
      v9 = (_DWORD *)v4[3];
    v3 = (int)v4;
    v4 = v9;
  }
  v10 = v3;
  if ( v8 )
  {
    if ( v3 == *(_DWORD *)(a2 + 12) )
    {
      *a1 = 0;
      a1[1] = v3;
      return a1;
    }
    v3 = std::_Rb_tree_decrement(v3);
  }
  if ( std::operator<<char>((std::string *)(v3 + 16), a3) )
  {
    *a1 = 0;
    a1[1] = v10;
  }
  else
  {
    *a1 = v3;
    a1[1] = 0;
  }
  return a1;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);


//----- (00008C34) --------------------------------------------------------
// Alternative name is '_ZNSt8_Rb_treeISsSt4pairIKSsP7uniformESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOSsEESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_'
_DWORD *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string &&>,std::tuple<>>(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        _DWORD **a4)
{
  _DWORD *v7; // r0
  _DWORD *v8; // r9
  _DWORD *v9; // r2
  int v10; // r4
  int v11; // r7
  int v12; // r8
  int v13; // r0
  _DWORD *v15; // [sp+0h] [bp-Ch] BYREF
  int v16; // [sp+4h] [bp-8h]
  int v17; // [sp+8h] [bp-4h]

  v15 = a1;
  v16 = (int)a2;
  v17 = a3;
  v7 = (_DWORD *)operator new(0x18u);
  v8 = v7;
  if ( v7 )
  {
    memset(v7, 0, 0x10u);
    v9 = *a4;
    v8[4] = **a4;
    *v9 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
    v8[5] = 0;
  }
  v10 = (int)a2;
  if ( a2 != a1 + 1 )
  {
    v11 = std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(a2 + 4));
    if ( v11 )
    {
      if ( a2 == (_DWORD *)a1[3] )
      {
        v12 = (int)a2;
      }
      else
      {
        v12 = std::_Rb_tree_decrement(a2);
        if ( std::operator<<char>((std::string *)(v12 + 16), (const std::string *)(v8 + 4)) )
        {
          if ( *(_DWORD *)(v12 + 12) )
            v12 = (int)a2;
          else
            v10 = 0;
        }
        else
        {
          std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_get_insert_unique_pos(
            (int *)&v15,
            (int)a1,
            (std::string *)(v8 + 4));
          v10 = (int)v15;
          v12 = v16;
        }
      }
      v11 = v10;
      v10 = v12;
      goto LABEL_23;
    }
    if ( !std::operator<<char>((std::string *)(a2 + 4), (const std::string *)(v8 + 4)) )
      goto LABEL_30;
    if ( a2 == (_DWORD *)a1[4] )
      goto LABEL_23;
    v11 = std::_Rb_tree_increment(a2);
    if ( std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(v11 + 16)) )
    {
      if ( a2[3] )
        v10 = v11;
      else
        v11 = 0;
      goto LABEL_23;
    }
LABEL_22:
    std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_get_insert_unique_pos(
      (int *)&v15,
      (int)a1,
      (std::string *)(v8 + 4));
    v11 = (int)v15;
    v10 = v16;
LABEL_23:
    if ( v10 )
    {
      if ( v11 )
        goto LABEL_27;
      goto LABEL_25;
    }
    v10 = v11;
    goto LABEL_30;
  }
  if ( !a1[5] )
    goto LABEL_22;
  v10 = a1[4];
  if ( !std::operator<<char>((std::string *)(v10 + 16), (const std::string *)(v8 + 4)) )
    goto LABEL_22;
  if ( v10 )
  {
LABEL_25:
    if ( (_DWORD *)v10 != a1 + 1 )
    {
      v13 = std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(v10 + 16));
LABEL_28:
      std::_Rb_tree_insert_and_rebalance(v13, v8, v10, a1 + 1);
      ++a1[5];
      return v8;
    }
LABEL_27:
    v13 = 1;
    goto LABEL_28;
  }
LABEL_30:
  std::string::~string((std::string *)(v8 + 4));
  operator delete(v8);
  return (_DWORD *)v10;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


//----- (00008D6C) --------------------------------------------------------
_DWORD *__fastcall std::map<std::string,uniform *>::operator[](
        _DWORD *a1,
        const std::string *a2,
        int a3,
        const std::string *a4)
{
  _DWORD *v4; // r8
  _DWORD *v5; // r5
  _DWORD *v8; // r4
  _DWORD *v9; // r3
  const std::string *v11; // [sp+Ch] [bp-4h] BYREF

  v11 = a4;
  v4 = a1 + 1;
  v5 = (_DWORD *)a1[2];
  v8 = a1 + 1;
  while ( v5 )
  {
    if ( std::operator<<char>((std::string *)(v5 + 4), a2) )
    {
      v9 = (_DWORD *)v5[3];
      v5 = v8;
    }
    else
    {
      v9 = (_DWORD *)v5[2];
    }
    v8 = v5;
    v5 = v9;
  }
  if ( v8 == v4 || std::operator<<char>(a2, (const std::string *)(v8 + 4)) )
  {
    v11 = a2;
    v8 = std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string &&>,std::tuple<>>(
           a1,
           v8,
           (int)&unk_15B62,
           (_DWORD **)&v11);
  }
  return v8 + 5;
}


//----- (00008DD0) --------------------------------------------------------
// Alternative name is '_ZNSt8_Rb_treeISsSt4pairIKSsP9attributeESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOSsEESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_'
_DWORD *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string &&>,std::tuple<>>(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        _DWORD **a4)
{
  _DWORD *v7; // r0
  _DWORD *v8; // r9
  _DWORD *v9; // r2
  int v10; // r4
  int v11; // r7
  int v12; // r8
  int v13; // r0
  _DWORD *v15; // [sp+0h] [bp-Ch] BYREF
  int v16; // [sp+4h] [bp-8h]
  int v17; // [sp+8h] [bp-4h]

  v15 = a1;
  v16 = (int)a2;
  v17 = a3;
  v7 = (_DWORD *)operator new(0x18u);
  v8 = v7;
  if ( v7 )
  {
    memset(v7, 0, 0x10u);
    v9 = *a4;
    v8[4] = **a4;
    *v9 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
    v8[5] = 0;
  }
  v10 = (int)a2;
  if ( a2 != a1 + 1 )
  {
    v11 = std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(a2 + 4));
    if ( v11 )
    {
      if ( a2 == (_DWORD *)a1[3] )
      {
        v12 = (int)a2;
      }
      else
      {
        v12 = std::_Rb_tree_decrement(a2);
        if ( std::operator<<char>((std::string *)(v12 + 16), (const std::string *)(v8 + 4)) )
        {
          if ( *(_DWORD *)(v12 + 12) )
            v12 = (int)a2;
          else
            v10 = 0;
        }
        else
        {
          std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_get_insert_unique_pos(
            (int *)&v15,
            (int)a1,
            (std::string *)(v8 + 4));
          v10 = (int)v15;
          v12 = v16;
        }
      }
      v11 = v10;
      v10 = v12;
      goto LABEL_23;
    }
    if ( !std::operator<<char>((std::string *)(a2 + 4), (const std::string *)(v8 + 4)) )
      goto LABEL_30;
    if ( a2 == (_DWORD *)a1[4] )
      goto LABEL_23;
    v11 = std::_Rb_tree_increment(a2);
    if ( std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(v11 + 16)) )
    {
      if ( a2[3] )
        v10 = v11;
      else
        v11 = 0;
      goto LABEL_23;
    }
LABEL_22:
    std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_get_insert_unique_pos(
      (int *)&v15,
      (int)a1,
      (std::string *)(v8 + 4));
    v11 = (int)v15;
    v10 = v16;
LABEL_23:
    if ( v10 )
    {
      if ( v11 )
        goto LABEL_27;
      goto LABEL_25;
    }
    v10 = v11;
    goto LABEL_30;
  }
  if ( !a1[5] )
    goto LABEL_22;
  v10 = a1[4];
  if ( !std::operator<<char>((std::string *)(v10 + 16), (const std::string *)(v8 + 4)) )
    goto LABEL_22;
  if ( v10 )
  {
LABEL_25:
    if ( (_DWORD *)v10 != a1 + 1 )
    {
      v13 = std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(v10 + 16));
LABEL_28:
      std::_Rb_tree_insert_and_rebalance(v13, v8, v10, a1 + 1);
      ++a1[5];
      return v8;
    }
LABEL_27:
    v13 = 1;
    goto LABEL_28;
  }
LABEL_30:
  std::string::~string((std::string *)(v8 + 4));
  operator delete(v8);
  return (_DWORD *)v10;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


//----- (00008F08) --------------------------------------------------------
_DWORD *__fastcall std::map<std::string,attribute *>::operator[](
        _DWORD *a1,
        const std::string *a2,
        int a3,
        const std::string *a4)
{
  _DWORD *v4; // r8
  _DWORD *v5; // r5
  _DWORD *v8; // r4
  _DWORD *v9; // r3
  const std::string *v11; // [sp+Ch] [bp-4h] BYREF

  v11 = a4;
  v4 = a1 + 1;
  v5 = (_DWORD *)a1[2];
  v8 = a1 + 1;
  while ( v5 )
  {
    if ( std::operator<<char>((std::string *)(v5 + 4), a2) )
    {
      v9 = (_DWORD *)v5[3];
      v5 = v8;
    }
    else
    {
      v9 = (_DWORD *)v5[2];
    }
    v8 = v5;
    v5 = v9;
  }
  if ( v8 == v4 || std::operator<<char>(a2, (const std::string *)(v8 + 4)) )
  {
    v11 = a2;
    v8 = std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string &&>,std::tuple<>>(
           a1,
           v8,
           (int)&unk_15B62,
           (_DWORD **)&v11);
  }
  return v8 + 5;
}


//----- (0000953C) --------------------------------------------------------
// Alternative name is '_ZN8fsshaderC1EP7program'
void __fastcall fsshader::fsshader(fsshader *this, program *a2)
{
  buffer *v3; // r5
  varray *v4; // r6
  unsigned int v5; // r0
  fsshader *v6; // [sp+0h] [bp-8h] BYREF
  program *v7; // [sp+4h] [bp-4h] BYREF

  v6 = this;
  v7 = a2;
  *((_DWORD *)this + 2) = a2;
  v3 = (buffer *)operator new(0x20u);
  buffer::buffer(v3, 0x8892u, -1);
  *(_DWORD *)this = v3;
  buffer::set(v3, 0x40u, &unk_18008, 0x88E4u);
  v4 = (varray *)operator new(0x1Cu);
  varray::varray(v4);
  *((_DWORD *)this + 1) = v4;
  std::string::string(&v7, "transition_position", &v6);
  v5 = varray::getconfig(v4, (const std::string *)&v7);
  bufferconfig::set(v5, *(_DWORD **)this, 0, 0);
  std::string::~string((std::string *)&v7);
}
// 7918: using guessed type int __fastcall std::string::string(_DWORD, _DWORD, _DWORD);


//----- (000095CA) --------------------------------------------------------
// Alternative name is '_ZN8rendererC1Ev'
void __fastcall renderer::renderer(renderer *this)
{
  varray::varray(this);
  varray::varray((renderer *)((char *)this + 28));
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 20) = 0;
  *((_DWORD *)this + 21) = 0;
  *((_DWORD *)this + 22) = 0;
}


//----- (00009602) --------------------------------------------------------
float __fastcall mix(float a1, float a2, float a3)
{
  return (float)(a1 - (float)(a3 * a1)) + (float)(a2 * a3);
}


//----- (000097E0) --------------------------------------------------------
unsigned int __fastcall std::mersenne_twister_engine<unsigned int,32u,624u,397u,31u,2567483615u,11u,4294967295u,7u,2636928640u,15u,4022730752u,18u,1812433253u>::seed(
        _DWORD *a1,
        int a2)
{
  int v3; // r4
  _DWORD *v4; // r5
  unsigned int v5; // t1
  unsigned int v6; // r0
  unsigned int result; // r0
  unsigned int v8; // r1

  v3 = 1;
  *a1 = a2;
  v4 = a1 - 1;
  do
  {
    v5 = v4[1];
    ++v4;
    v6 = v3++;
    v8 = v6 % 0x270;
    result = v6 / 0x270;
    v4[1] = v8 + 1812433253 * (v5 ^ (v5 >> 30));
  }
  while ( v3 != 624 );
  a1[624] = 624;
  return result;
}


//----- (00009820) --------------------------------------------------------
unsigned int __fastcall std::mersenne_twister_engine<unsigned int,32u,624u,397u,31u,2567483615u,11u,4294967295u,7u,2636928640u,15u,4022730752u,18u,1812433253u>::operator()(
        _DWORD *a1)
{
  _DWORD *v1; // r2
  int i; // r3
  int v3; // r1
  unsigned int v4; // r1
  int v5; // r4
  int v6; // r1
  _DWORD *v7; // r3
  int v8; // r2
  int v9; // r4
  int v10; // r1
  unsigned int v11; // r1
  int v12; // r4
  int v13; // r1
  int v14; // r3
  int v15; // r3
  int v16; // r0

  if ( a1[624] > 0x26Fu )
  {
    v1 = a1;
    for ( i = 0; i != 227; ++i )
    {
      v3 = v1[1];
      ++v1;
      v4 = v3 & 0x7FFFFFFF | a1[i] & 0x80000000;
      v5 = v1[396] ^ (v4 >> 1);
      if ( (v4 & 1) != 0 )
        v6 = -1727483681;
      else
        v6 = 0;
      a1[i] = v5 ^ v6;
    }
    v7 = a1;
    v8 = 227;
    do
    {
      v9 = v7[227];
      ++v8;
      v10 = v7[228];
      ++v7;
      v11 = v10 & 0x7FFFFFFF | v9 & 0x80000000;
      v12 = *(v7 - 1) ^ (v11 >> 1);
      if ( (v11 & 1) != 0 )
        v13 = -1727483681;
      else
        v13 = 0;
      v7[226] = v12 ^ v13;
    }
    while ( v8 != 623 );
    v14 = -1727483681;
    if ( (*a1 & 1) == 0 )
      v14 = 0;
    a1[623] = a1[396] ^ ((*a1 & 0x7FFFFFFF | a1[623] & 0x80000000) >> 1) ^ v14;
    a1[624] = 0;
  }
  v15 = a1[624];
  a1[624] = v15 + 1;
  v16 = a1[v15] ^ (a1[v15] >> 11);
  return (((v16 << 7) & 0x9D2C5680 ^ v16) << 15)
       & 0xEFC60000
       ^ (v16 << 7)
       & 0x9D2C5680
       ^ v16
       ^ (((((v16 << 7) & 0x9D2C5680 ^ v16) << 15) & 0xEFC60000 ^ (v16 << 7) & 0x9D2C5680 ^ v16) >> 18);
}


//----- (00009904) --------------------------------------------------------
_DWORD *__fastcall std::operator+<char>(_DWORD *a1, std::string *this, char *a3)
{
  _DWORD *v4; // r0

  v4 = (_DWORD *)std::string::append(this, a3);
  *a1 = *v4;
  *v4 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
  return a1;
}


//----- (00009928) --------------------------------------------------------
_DWORD *__fastcall std::operator+<char>(_DWORD *a1, std::string *a2, std::string *this)
{
  unsigned int v5; // r4
  unsigned int v6; // r1
  _DWORD *v7; // r0

  v5 = *(_DWORD *)(*(_DWORD *)a2 - 8);
  v6 = *(_DWORD *)(*(_DWORD *)a2 - 12) + *(_DWORD *)(*(_DWORD *)this - 12);
  if ( v6 > v5 && v6 <= *(_DWORD *)(*(_DWORD *)this - 8) )
    v7 = (_DWORD *)std::string::insert(this, 0, a2);
  else
    v7 = (_DWORD *)std::string::append(a2, this);
  *a1 = *v7;
  *v7 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
  return a1;
}


//----- (00009978) --------------------------------------------------------
std::string *__fastcall std::operator+<char>(std::string *a1, char *s, const std::string *a3)
{
  size_t v6; // r0
  unsigned int v7; // r7

  v6 = strlen(s);
  *(_DWORD *)a1 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
  v7 = v6;
  std::string::reserve(a1, *(_DWORD *)(*(_DWORD *)a3 - 12) + v6);
  std::string::append(a1, s, v7);
  std::string::append(a1, a3);
  return a1;
}


//----- (00009C10) --------------------------------------------------------
// Alternative name is '_ZN6bufferD1Ev'
void __fastcall buffer::~buffer(buffer *this)
{
  glDeleteBuffers(1, (char *)this + 28);
  std::_Rb_tree<bufferconfig *,bufferconfig *,std::_Identity<bufferconfig *>,std::less<bufferconfig *>,std::allocator<bufferconfig *>>::_M_erase(
    (int)this,
    *((_DWORD **)this + 2));
}
// 7A20: using guessed type int __fastcall glDeleteBuffers(_DWORD, _DWORD);


//----- (00009C2A) --------------------------------------------------------
void __fastcall std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::_M_erase(
        int a1,
        _DWORD *a2)
{
  _DWORD *v4; // r6

  while ( a2 )
  {
    std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::_M_erase(
      a1,
      a2[3]);
    v4 = (_DWORD *)a2[2];
    operator delete(a2);
    a2 = v4;
  }
}


//----- (00009C48) --------------------------------------------------------
// Alternative name is '_ZNSt6vectorIP13uniformconfigSaIS1_EE19_M_emplace_back_auxIJRKS1_EEEvDpOT_'
void __fastcall std::vector<uniformconfig *>::_M_emplace_back_aux<uniformconfig * const&>(int a1, _DWORD *a2)
{
  int v4; // r6
  int v5; // r3
  bool v6; // cf
  unsigned int v7; // r3
  int v8; // r6
  _DWORD *v9; // r5
  int v10; // r3
  size_t v11; // r7
  int v12; // r7

  v4 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( v4 )
    v5 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  else
    v5 = 1;
  v6 = __CFADD__(v5, v4);
  v7 = v5 + v4;
  v8 = 0x3FFFFFFF;
  if ( v6 )
    goto LABEL_8;
  if ( v7 < 0x3FFFFFFF )
    v8 = v7;
  if ( v8 )
LABEL_8:
    v9 = (_DWORD *)operator new(4 * v8);
  else
    v9 = 0;
  v10 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( &v9[v10] )
    v9[v10] = *a2;
  v11 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2 )
    memmove(v9, *(const void **)a1, v11 * 4);
  v12 = (int)&v9[v11 + 1];
  if ( *(_DWORD *)a1 )
    operator delete(*(void **)a1);
  *(_DWORD *)a1 = v9;
  *(_DWORD *)(a1 + 4) = v12;
  *(_DWORD *)(a1 + 8) = &v9[v8];
}


//----- (00009CBA) --------------------------------------------------------
int __fastcall std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::erase(
        _DWORD *a1,
        unsigned int *a2)
{
  _DWORD *v2; // r7
  _DWORD *v3; // r9
  _DWORD *v5; // r6
  _DWORD *i; // r4
  unsigned int v7; // r3
  unsigned int v8; // r0
  _DWORD *v9; // r3
  _DWORD *v10; // r2
  _DWORD *v11; // r3
  _DWORD *v12; // r12
  _DWORD *v13; // r2
  int v14; // r8
  int v15; // r9
  void *v16; // r0

  v2 = a1 + 1;
  v3 = (_DWORD *)a1[2];
  v5 = a1 + 1;
  for ( i = v3; ; i = v9 )
  {
    if ( !i )
    {
      i = v5;
      goto LABEL_20;
    }
    v7 = i[4];
    v8 = *a2;
    if ( v7 < *a2 )
    {
      v9 = (_DWORD *)i[3];
      i = v5;
      goto LABEL_18;
    }
    if ( v8 >= v7 )
      break;
    v9 = (_DWORD *)i[2];
LABEL_18:
    v5 = i;
  }
  v10 = (_DWORD *)i[2];
  v11 = (_DWORD *)i[3];
  while ( v10 )
  {
    if ( v10[4] >= v8 )
    {
      v12 = (_DWORD *)v10[2];
    }
    else
    {
      v12 = (_DWORD *)v10[3];
      v10 = i;
    }
    i = v10;
    v10 = v12;
  }
  while ( v11 )
  {
    if ( v8 < v11[4] )
    {
      v13 = (_DWORD *)v11[2];
    }
    else
    {
      v13 = (_DWORD *)v11[3];
      v11 = v5;
    }
    v5 = v11;
    v11 = v13;
  }
LABEL_20:
  v14 = a1[5];
  if ( i == (_DWORD *)a1[3] && v5 == v2 )
  {
    std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::_M_erase(
      (int)a1,
      v3);
    a1[3] = v5;
    a1[2] = 0;
    a1[4] = v5;
    a1[5] = 0;
  }
  else
  {
    while ( i != v5 )
    {
      v15 = std::_Rb_tree_increment(i);
      v16 = (void *)std::_Rb_tree_rebalance_for_erase(i, v2);
      i = (_DWORD *)v15;
      operator delete(v16);
      --a1[5];
    }
  }
  return v14 - a1[5];
}
// 7750: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);
// 775C: using guessed type int __fastcall std::_Rb_tree_rebalance_for_erase(_DWORD, _DWORD);


//----- (00009D68) --------------------------------------------------------
// Alternative name is '_ZN7programD1Ev'
void __fastcall program::~program(program *this, void *a2)
{
  void **i; // r5
  int v4; // r0
  void *v5; // [sp+4h] [bp-4h] BYREF

  v5 = a2;
  glDeleteProgram(*(_DWORD *)this);
  for ( i = (void **)*((_DWORD *)this + 4); i != (void **)((char *)this + 8); i = (void **)std::_Rb_tree_increment(i) )
  {
    v4 = *((_DWORD *)i[4] + 2);
    v5 = i[4];
    std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::erase(
      (_DWORD *)(v4 + 20),
      (unsigned int *)&v5);
    operator delete(v5);
  }
  std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::_M_erase(
    (int)this + 4,
    *((_DWORD **)this + 3));
  *((_DWORD *)this + 4) = i;
  *((_DWORD *)this + 3) = 0;
  *((_DWORD *)this + 5) = i;
  *((_DWORD *)this + 6) = 0;
  std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::_M_erase(
    (int)this + 4,
    0);
}
// 7750: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);
// 7A2C: using guessed type int __fastcall glDeleteProgram(_DWORD);


//----- (00009E42) --------------------------------------------------------
void __fastcall uniform::set<float>(uniform *this, float a2)
{
  float *v2; // r3

  if ( *((_DWORD *)this + 1) )
  {
    v2 = (float *)*((_DWORD *)this + 3);
    if ( v2 )
    {
      if ( *v2 != a2 )
      {
        *v2 = a2;
        uniform::touched(this);
      }
    }
  }
}


//----- (00009E64) --------------------------------------------------------
void __fastcall uniform::set<float>(uniform *this, float a2, float a3, float a4, float a5)
{
  float *v6; // r3

  if ( *((_DWORD *)this + 1) )
  {
    v6 = (float *)*((_DWORD *)this + 3);
    if ( v6 )
    {
      if ( *v6 != a2 || v6[1] != a3 || v6[2] != a4 || v6[3] != a5 )
      {
        *v6 = a2;
        if ( *((int *)this + 2) > 1 )
          *(float *)(*((_DWORD *)this + 3) + 4) = a3;
        if ( *((int *)this + 2) > 2 )
          *(float *)(*((_DWORD *)this + 3) + 8) = a4;
        if ( *((int *)this + 2) > 3 )
          *(float *)(*((_DWORD *)this + 3) + 12) = a5;
        uniform::touched(this);
      }
    }
  }
}


//----- (00009EE2) --------------------------------------------------------
void __fastcall uniform::set<float>(uniform *this, float a2, float a3)
{
  float *v3; // r3

  if ( *((_DWORD *)this + 1) )
  {
    v3 = (float *)*((_DWORD *)this + 3);
    if ( v3 )
    {
      if ( *v3 != a2 || v3[1] != a3 )
      {
        *v3 = a2;
        if ( *((int *)this + 2) > 1 )
          *(float *)(*((_DWORD *)this + 3) + 4) = a3;
        uniform::touched(this);
      }
    }
  }
}


//----- (00009F24) --------------------------------------------------------
void __fastcall std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_erase(
        int a1,
        _DWORD *a2)
{
  _DWORD *v4; // r6

  while ( a2 )
  {
    std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_erase(
      a1,
      a2[3]);
    v4 = (_DWORD *)a2[2];
    std::string::~string((std::string *)(a2 + 4));
    operator delete(a2);
    a2 = v4;
  }
}


//----- (00009F4A) --------------------------------------------------------
// Alternative name is '_ZNSt8_Rb_treeISsSt4pairIKSsP7uniformESt10_Select1stIS4_ESt4lessISsESaIS4_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESF_IJEEEEESt17_Rb_tree_iteratorIS4_ESt23_Rb_tree_const_iteratorIS4_EDpOT_'
_DWORD *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string const&>,std::tuple<>>(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        const std::string **a4)
{
  _DWORD *v7; // r0
  _DWORD *v8; // r9
  std::string *v9; // r5
  int v10; // r4
  int v11; // r7
  int v12; // r8
  int v13; // r0
  _DWORD *v15; // [sp+0h] [bp-Ch] BYREF
  int v16; // [sp+4h] [bp-8h]
  int v17; // [sp+8h] [bp-4h]

  v15 = a1;
  v16 = (int)a2;
  v17 = a3;
  v7 = (_DWORD *)operator new(0x18u);
  v8 = v7;
  v9 = (std::string *)(v7 + 4);
  if ( v7 )
  {
    memset(v7, 0, 0x10u);
    std::string::string(v9, *a4);
    v8[5] = 0;
  }
  v10 = (int)a2;
  if ( a2 != a1 + 1 )
  {
    v11 = std::operator<<char>(v9, (const std::string *)(a2 + 4));
    if ( v11 )
    {
      if ( a2 == (_DWORD *)a1[3] )
      {
        v12 = (int)a2;
      }
      else
      {
        v12 = std::_Rb_tree_decrement(a2);
        if ( std::operator<<char>((std::string *)(v12 + 16), v9) )
        {
          if ( *(_DWORD *)(v12 + 12) )
            v12 = (int)a2;
          else
            v10 = 0;
        }
        else
        {
          std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_get_insert_unique_pos(
            (int *)&v15,
            (int)a1,
            v9);
          v10 = (int)v15;
          v12 = v16;
        }
      }
      v11 = v10;
      v10 = v12;
      goto LABEL_23;
    }
    if ( !std::operator<<char>((std::string *)(a2 + 4), v9) )
      goto LABEL_30;
    if ( a2 == (_DWORD *)a1[4] )
      goto LABEL_23;
    v11 = std::_Rb_tree_increment(a2);
    if ( std::operator<<char>(v9, (const std::string *)(v11 + 16)) )
    {
      if ( a2[3] )
        v10 = v11;
      else
        v11 = 0;
      goto LABEL_23;
    }
LABEL_22:
    std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_get_insert_unique_pos(
      (int *)&v15,
      (int)a1,
      v9);
    v11 = (int)v15;
    v10 = v16;
LABEL_23:
    if ( v10 )
    {
      if ( v11 )
        goto LABEL_27;
      goto LABEL_25;
    }
    v10 = v11;
    goto LABEL_30;
  }
  if ( !a1[5] )
    goto LABEL_22;
  v10 = a1[4];
  if ( !std::operator<<char>((std::string *)(v10 + 16), v9) )
    goto LABEL_22;
  if ( v10 )
  {
LABEL_25:
    if ( (_DWORD *)v10 != a1 + 1 )
    {
      v13 = std::operator<<char>(v9, (const std::string *)(v10 + 16));
LABEL_28:
      std::_Rb_tree_insert_and_rebalance(v13, v8, v10, a1 + 1);
      ++a1[5];
      return v8;
    }
LABEL_27:
    v13 = 1;
    goto LABEL_28;
  }
LABEL_30:
  std::string::~string(v9);
  operator delete(v8);
  return (_DWORD *)v10;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


//----- (0000A118) --------------------------------------------------------
int *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_get_insert_unique_pos(
        int *a1,
        int a2,
        std::string *a3)
{
  int v3; // r4
  _DWORD *v4; // r6
  int v8; // r0
  _DWORD *v9; // r3
  int v10; // r9

  v3 = a2 + 4;
  v4 = *(_DWORD **)(a2 + 8);
  v8 = 1;
  while ( v4 )
  {
    v8 = std::operator<<char>(a3, (const std::string *)(v4 + 4));
    if ( v8 )
      v9 = (_DWORD *)v4[2];
    else
      v9 = (_DWORD *)v4[3];
    v3 = (int)v4;
    v4 = v9;
  }
  v10 = v3;
  if ( v8 )
  {
    if ( v3 == *(_DWORD *)(a2 + 12) )
    {
      *a1 = 0;
      a1[1] = v3;
      return a1;
    }
    v3 = std::_Rb_tree_decrement(v3);
  }
  if ( std::operator<<char>((std::string *)(v3 + 16), a3) )
  {
    *a1 = 0;
    a1[1] = v10;
  }
  else
  {
    *a1 = v3;
    a1[1] = 0;
  }
  return a1;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);


//----- (0000A178) --------------------------------------------------------
// Alternative name is '_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOSsEESE_IJEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_'
int __fastcall std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string &&>,std::tuple<>>(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        _DWORD **a4)
{
  _DWORD *v7; // r0
  _DWORD *v8; // r9
  _DWORD *v9; // r2
  int v10; // r4
  int v11; // r7
  int v12; // r8
  int v13; // r0
  _DWORD *v15; // [sp+0h] [bp-Ch] BYREF
  int v16; // [sp+4h] [bp-8h]
  int v17; // [sp+8h] [bp-4h]

  v15 = a1;
  v16 = (int)a2;
  v17 = a3;
  v7 = (_DWORD *)operator new(0x38u);
  v8 = v7;
  if ( v7 )
  {
    memset(v7, 0, 0x10u);
    v9 = *a4;
    v8[4] = **a4;
    *v9 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
  }
  v10 = (int)a2;
  if ( a2 != a1 + 1 )
  {
    v11 = std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(a2 + 4));
    if ( v11 )
    {
      if ( a2 == (_DWORD *)a1[3] )
      {
        v12 = (int)a2;
      }
      else
      {
        v12 = std::_Rb_tree_decrement(a2);
        if ( std::operator<<char>((std::string *)(v12 + 16), (const std::string *)(v8 + 4)) )
        {
          if ( *(_DWORD *)(v12 + 12) )
            v12 = (int)a2;
          else
            v10 = 0;
        }
        else
        {
          std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_get_insert_unique_pos(
            (int *)&v15,
            (int)a1,
            (std::string *)(v8 + 4));
          v10 = (int)v15;
          v12 = v16;
        }
      }
      v11 = v10;
      v10 = v12;
      goto LABEL_23;
    }
    if ( !std::operator<<char>((std::string *)(a2 + 4), (const std::string *)(v8 + 4)) )
      goto LABEL_30;
    if ( a2 == (_DWORD *)a1[4] )
      goto LABEL_23;
    v11 = std::_Rb_tree_increment(a2);
    if ( std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(v11 + 16)) )
    {
      if ( a2[3] )
        v10 = v11;
      else
        v11 = 0;
      goto LABEL_23;
    }
LABEL_22:
    std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_get_insert_unique_pos(
      (int *)&v15,
      (int)a1,
      (std::string *)(v8 + 4));
    v11 = (int)v15;
    v10 = v16;
LABEL_23:
    if ( v10 )
    {
      if ( v11 )
        goto LABEL_27;
      goto LABEL_25;
    }
    v10 = v11;
    goto LABEL_30;
  }
  if ( !a1[5] )
    goto LABEL_22;
  v10 = a1[4];
  if ( !std::operator<<char>((std::string *)(v10 + 16), (const std::string *)(v8 + 4)) )
    goto LABEL_22;
  if ( v10 )
  {
LABEL_25:
    if ( (_DWORD *)v10 != a1 + 1 )
    {
      v13 = std::operator<<char>((std::string *)(v8 + 4), (const std::string *)(v10 + 16));
LABEL_28:
      std::_Rb_tree_insert_and_rebalance(v13, v8, v10, a1 + 1);
      ++a1[5];
      return (int)v8;
    }
LABEL_27:
    v13 = 1;
    goto LABEL_28;
  }
LABEL_30:
  std::string::~string((std::string *)(v8 + 4));
  operator delete(v8);
  return v10;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


//----- (0000A2AC) --------------------------------------------------------
_DWORD *__fastcall std::map<std::string,themeparameter>::operator[](
        _DWORD *a1,
        const std::string *a2,
        int a3,
        const std::string *a4)
{
  _DWORD *v4; // r8
  _DWORD *v5; // r5
  _DWORD *v8; // r4
  _DWORD *v9; // r3
  const std::string *v11; // [sp+Ch] [bp-4h] BYREF

  v11 = a4;
  v4 = a1 + 1;
  v5 = (_DWORD *)a1[2];
  v8 = a1 + 1;
  while ( v5 )
  {
    if ( std::operator<<char>((std::string *)(v5 + 4), a2) )
    {
      v9 = (_DWORD *)v5[3];
      v5 = v8;
    }
    else
    {
      v9 = (_DWORD *)v5[2];
    }
    v8 = v5;
    v5 = v9;
  }
  if ( v8 == v4 || std::operator<<char>(a2, (const std::string *)(v8 + 4)) )
  {
    v11 = a2;
    v8 = (_DWORD *)std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string &&>,std::tuple<>>(
                     a1,
                     v8,
                     (int)&unk_15B63,
                     (_DWORD **)&v11);
  }
  return v8 + 6;
}


//----- (0000AFE0) --------------------------------------------------------
void __fastcall std::_Rb_tree<int,std::pair<int const,RendererInterface>,std::_Select1st<std::pair<int const,RendererInterface>>,std::less<int>,std::allocator<std::pair<int const,RendererInterface>>>::_M_erase(
        int a1,
        _DWORD *a2)
{
  _DWORD *v4; // r6

  while ( a2 )
  {
    std::_Rb_tree<int,std::pair<int const,RendererInterface>,std::_Select1st<std::pair<int const,RendererInterface>>,std::less<int>,std::allocator<std::pair<int const,RendererInterface>>>::_M_erase(
      a1,
      a2[3]);
    v4 = (_DWORD *)a2[2];
    operator delete(a2);
    a2 = v4;
  }
}


//----- (0000AFFE) --------------------------------------------------------
// Alternative name is '_ZNSt3mapIi17RendererInterfaceSt4lessIiESaISt4pairIKiS0_EEED1Ev'
int __fastcall std::map<int,RendererInterface>::~map(int a1)
{
  std::_Rb_tree<int,std::pair<int const,RendererInterface>,std::_Select1st<std::pair<int const,RendererInterface>>,std::less<int>,std::allocator<std::pair<int const,RendererInterface>>>::_M_erase(
    a1,
    *(_DWORD **)(a1 + 8));
  return a1;
}


//----- (0000B00C) --------------------------------------------------------
int *__fastcall std::_Rb_tree<int,std::pair<int const,RendererInterface>,std::_Select1st<std::pair<int const,RendererInterface>>,std::less<int>,std::allocator<std::pair<int const,RendererInterface>>>::_M_get_insert_unique_pos(
        int *a1,
        int a2,
        _DWORD *a3)
{
  _DWORD *v4; // r0
  int v5; // r3
  int v7; // r5
  _DWORD *v8; // r2
  int v9; // r7
  int v10; // r2
  bool v11; // cc

  v4 = *(_DWORD **)(a2 + 8);
  v5 = a2 + 4;
  v7 = 1;
  while ( v4 )
  {
    v5 = (int)v4;
    if ( *a3 >= v4[4] )
    {
      v8 = (_DWORD *)v4[3];
      v7 = 0;
    }
    else
    {
      v8 = (_DWORD *)v4[2];
      v7 = 1;
    }
    v4 = v8;
  }
  v9 = v5;
  if ( v7 )
  {
    if ( v5 == *(_DWORD *)(a2 + 12) )
    {
      *a1 = 0;
      a1[1] = v5;
      return a1;
    }
    v5 = std::_Rb_tree_decrement(v5);
  }
  v10 = *(_DWORD *)(v5 + 16);
  v11 = v10 < *a3;
  if ( v10 < *a3 )
  {
    *a1 = 0;
    a1[1] = v9;
  }
  else
  {
    *a1 = v5;
  }
  if ( !v11 )
    a1[1] = 0;
  return a1;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);


//----- (0000B060) --------------------------------------------------------
// Alternative name is '_ZNSt8_Rb_treeIiSt4pairIKi17RendererInterfaceESt10_Select1stIS3_ESt4lessIiESaIS3_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESE_IJEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_'
int __fastcall std::_Rb_tree<int,std::pair<int const,RendererInterface>,std::_Select1st<std::pair<int const,RendererInterface>>,std::less<int>,std::allocator<std::pair<int const,RendererInterface>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<int const&>,std::tuple<>>(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        _DWORD **a4)
{
  _DWORD *v7; // r0
  _DWORD *v8; // r7
  int v9; // r4
  _DWORD *v10; // r2
  int v11; // r5
  int v12; // r3
  int v13; // r0
  int v14; // r0
  _BOOL4 v15; // r0
  _DWORD *v17; // [sp+0h] [bp-8h] BYREF
  int v18; // [sp+4h] [bp-4h]

  v17 = a1;
  v18 = (int)a2;
  v7 = (_DWORD *)operator new(0x1Cu);
  v8 = v7;
  if ( v7 )
  {
    memset(v7, 0, 0x10u);
    v8[4] = **a4;
    *((_BYTE *)v8 + 24) = 0;
  }
  v9 = (int)a2;
  if ( a2 == a1 + 1 )
  {
    if ( a1[5] )
    {
      v10 = (_DWORD *)a1[4];
      if ( v10[4] < v8[4] )
      {
LABEL_25:
        if ( v10 != a1 + 1 )
        {
          v15 = v8[4] < v10[4];
LABEL_28:
          std::_Rb_tree_insert_and_rebalance(v15, v8, v10, a1 + 1);
          ++a1[5];
          return (int)v8;
        }
LABEL_27:
        v15 = 1;
        goto LABEL_28;
      }
    }
LABEL_30:
    std::_Rb_tree<int,std::pair<int const,RendererInterface>,std::_Select1st<std::pair<int const,RendererInterface>>,std::less<int>,std::allocator<std::pair<int const,RendererInterface>>>::_M_get_insert_unique_pos(
      (int *)&v17,
      (int)a1,
      v8 + 4);
    v9 = (int)v17;
    v10 = (_DWORD *)v18;
    goto LABEL_23;
  }
  v11 = v8[4];
  v12 = a2[4];
  if ( v11 >= v12 )
  {
    if ( v12 >= v11 )
      goto LABEL_29;
    if ( a2 == (_DWORD *)a1[4] )
    {
      v14 = 0;
    }
    else
    {
      v14 = std::_Rb_tree_increment(a2);
      if ( v11 >= *(_DWORD *)(v14 + 16) )
      {
        std::_Rb_tree<int,std::pair<int const,RendererInterface>,std::_Select1st<std::pair<int const,RendererInterface>>,std::less<int>,std::allocator<std::pair<int const,RendererInterface>>>::_M_get_insert_unique_pos(
          (int *)&v17,
          (int)a1,
          v8 + 4);
        v14 = (int)v17;
        v9 = v18;
      }
      else if ( a2[3] )
      {
        v9 = v14;
      }
      else
      {
        v14 = 0;
      }
    }
    v10 = (_DWORD *)v9;
    v9 = v14;
  }
  else
  {
    if ( a2 == (_DWORD *)a1[3] )
    {
      v10 = a2;
      goto LABEL_23;
    }
    v13 = std::_Rb_tree_decrement(a2);
    v10 = (_DWORD *)v13;
    if ( *(_DWORD *)(v13 + 16) >= v11 )
      goto LABEL_30;
    if ( *(_DWORD *)(v13 + 12) )
      v10 = a2;
    else
      v9 = 0;
  }
LABEL_23:
  if ( v10 )
  {
    if ( v9 )
      goto LABEL_27;
    goto LABEL_25;
  }
LABEL_29:
  operator delete(v8);
  return v9;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


//----- (0000B158) --------------------------------------------------------
_DWORD *__fastcall std::map<int,RendererInterface>::operator[](_DWORD *a1, _DWORD *a2, int a3, _DWORD *a4)
{
  _DWORD *v4; // r3
  _DWORD *v6; // r1
  _DWORD *v7; // r5
  _DWORD *v9; // [sp+Ch] [bp-4h] BYREF

  v9 = a4;
  v4 = (_DWORD *)a1[2];
  v6 = a1 + 1;
  while ( v4 )
  {
    if ( v4[4] >= *a2 )
    {
      v7 = (_DWORD *)v4[2];
    }
    else
    {
      v7 = (_DWORD *)v4[3];
      v4 = v6;
    }
    v6 = v4;
    v4 = v7;
  }
  if ( v6 == a1 + 1 || *a2 < v6[4] )
  {
    v9 = a2;
    v6 = (_DWORD *)std::_Rb_tree<int,std::pair<int const,RendererInterface>,std::_Select1st<std::pair<int const,RendererInterface>>,std::less<int>,std::allocator<std::pair<int const,RendererInterface>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<int const&>,std::tuple<>>(
                     a1,
                     v6,
                     (int)&unk_15B64,
                     &v9);
  }
  return v6 + 5;
}


//----- (0000B378) --------------------------------------------------------
// Alternative name is '_ZNSt6vectorIP11framebufferSaIS1_EED1Ev'
void **__fastcall std::vector<framebuffer *>::~vector(void **a1)
{
  void *v2; // r0

  v2 = *a1;
  if ( v2 )
    operator delete(v2);
  return a1;
}


//----- (0000B388) --------------------------------------------------------
// Alternative name is '_ZN7textureC2Ev'
GLuint *__fastcall texture::texture(GLuint *textures)
{
  textures[1] = -1;
  textures[2] = -1;
  glGenTextures(1, textures);
  return textures;
}


//----- (0000B3A0) --------------------------------------------------------
// Alternative name is '_ZN7textureC1Ej'
void __fastcall texture::texture(texture *this, unsigned int a2)
{
  *(_DWORD *)this = a2;
  *((_DWORD *)this + 1) = -1;
  *((_DWORD *)this + 2) = -1;
}


//----- (0000B524) --------------------------------------------------------
// Alternative name is '_ZN11framebufferC1Ev'
void __fastcall framebuffer::framebuffer(framebuffer *this)
{
  memset((char *)this + 8, 0, 0x10u);
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 4) = (char *)this + 8;
  *((_DWORD *)this + 5) = (char *)this + 8;
  glGenFramebuffers(1, this);
}
// 7B1C: using guessed type int __fastcall glGenFramebuffers(_DWORD, _DWORD);


//----- (0000B5A0) --------------------------------------------------------
// Alternative name is '_ZNSt6vectorIP11framebufferSaIS1_EE19_M_emplace_back_auxIJRKS1_EEEvDpOT_'
void __fastcall std::vector<framebuffer *>::_M_emplace_back_aux<framebuffer * const&>(int a1, _DWORD *a2)
{
  int v4; // r6
  int v5; // r3
  bool v6; // cf
  unsigned int v7; // r3
  int v8; // r6
  _DWORD *v9; // r5
  int v10; // r3
  size_t v11; // r7
  int v12; // r7

  v4 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( v4 )
    v5 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  else
    v5 = 1;
  v6 = __CFADD__(v5, v4);
  v7 = v5 + v4;
  v8 = 0x3FFFFFFF;
  if ( v6 )
    goto LABEL_8;
  if ( v7 < 0x3FFFFFFF )
    v8 = v7;
  if ( v8 )
LABEL_8:
    v9 = (_DWORD *)operator new(4 * v8);
  else
    v9 = 0;
  v10 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( &v9[v10] )
    v9[v10] = *a2;
  v11 = (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2;
  if ( (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) >> 2 )
    memmove(v9, *(const void **)a1, v11 * 4);
  v12 = (int)&v9[v11 + 1];
  if ( *(_DWORD *)a1 )
    operator delete(*(void **)a1);
  *(_DWORD *)a1 = v9;
  *(_DWORD *)(a1 + 4) = v12;
  *(_DWORD *)(a1 + 8) = &v9[v8];
}


//----- (0000B654) --------------------------------------------------------
// Alternative name is '_ZN12LodePNGStateD1Ev'
void __fastcall LodePNGState::~LodePNGState(LodePNGState *this)
{
  *(_DWORD *)this = &off_17C58;
}
// 17C58: using guessed type _UNKNOWN *;


//----- (0000C2E8) --------------------------------------------------------
void __fastcall LodePNGState::~LodePNGState(LodePNGState *this)
{
  *(_DWORD *)this = &off_17C58;
  operator delete(this);
}
// 17C58: using guessed type _UNKNOWN *off_17C58;


//----- (0000CA3A) --------------------------------------------------------
void __fastcall lodepng_clear_text(int a1)
{
  unsigned int i; // r4
  int v3; // r7
  int v4; // r7

  for ( i = 0; i < *(_DWORD *)(a1 + 60); ++i )
  {
    v3 = *(_DWORD *)(a1 + 64);
    free(*(void **)(v3 + 4 * i));
    *(_DWORD *)(v3 + 4 * i) = 0;
    v4 = *(_DWORD *)(a1 + 68);
    free(*(void **)(v4 + 4 * i));
    *(_DWORD *)(v4 + 4 * i) = 0;
  }
  free(*(void **)(a1 + 64));
  j_free(*(void **)(a1 + 68));
}


//----- (0000CA9E) --------------------------------------------------------
void __fastcall lodepng_clear_itext(int a1)
{
  unsigned int i; // r4
  int v3; // r7
  int v4; // r7
  int v5; // r7
  int v6; // r7

  for ( i = 0; i < *(_DWORD *)(a1 + 72); ++i )
  {
    v3 = *(_DWORD *)(a1 + 76);
    free(*(void **)(v3 + 4 * i));
    *(_DWORD *)(v3 + 4 * i) = 0;
    v4 = *(_DWORD *)(a1 + 80);
    free(*(void **)(v4 + 4 * i));
    *(_DWORD *)(v4 + 4 * i) = 0;
    v5 = *(_DWORD *)(a1 + 84);
    free(*(void **)(v5 + 4 * i));
    *(_DWORD *)(v5 + 4 * i) = 0;
    v6 = *(_DWORD *)(a1 + 88);
    free(*(void **)(v6 + 4 * i));
    *(_DWORD *)(v6 + 4 * i) = 0;
  }
  free(*(void **)(a1 + 76));
  free(*(void **)(a1 + 80));
  free(*(void **)(a1 + 84));
  j_free(*(void **)(a1 + 88));
}


//----- (0000CF08) --------------------------------------------------------
unsigned int __fastcall lodepng_read32bitInt(const unsigned __int8 *a1)
{
  return _byteswap_ulong(*(_DWORD *)a1);
}


//----- (0000CF20) --------------------------------------------------------
int __fastcall lodepng_load_file(unsigned __int8 **a1, unsigned int *a2, const char *filename)
{
  FILE *v5; // r0
  FILE *v6; // r5
  size_t v7; // r4
  unsigned __int8 *v8; // r0

  *a1 = 0;
  *a2 = 0;
  v5 = fopen(filename, "rb");
  v6 = v5;
  if ( !v5 )
    return 78;
  fseek(v5, 0, 2);
  v7 = ftell(v6);
  rewind(v6);
  *a2 = 0;
  v8 = (unsigned __int8 *)malloc(v7);
  *a1 = v8;
  if ( v7 && v8 )
    *a2 = fread(v8, 1u, v7, v6);
  fclose(v6);
  if ( *a1 )
    return 0;
  if ( v7 )
    return 83;
  return 0;
}


//----- (0000CF98) --------------------------------------------------------
int __fastcall lodepng_save_file(const unsigned __int8 *a1, size_t a2, const char *filename)
{
  FILE *v5; // r0
  FILE *v6; // r4

  v5 = fopen(filename, "wb");
  v6 = v5;
  if ( !v5 )
    return 79;
  fwrite(a1, 1u, a2, v5);
  fclose(v6);
  return 0;
}


//----- (0000CFCC) --------------------------------------------------------
unsigned int __fastcall lodepng_huffman_code_lengths(unsigned int *a1, const unsigned int *a2, int a3, unsigned int a4)
{
  unsigned int result; // r0
  unsigned int v7; // r4
  unsigned int v8; // r10
  int i; // r3
  unsigned int v10; // r2
  int v11; // r3
  int v12; // r11
  float *v13; // r6
  float *v14; // r5
  unsigned int v15; // r7
  int v16; // r3
  float *v17; // r2
  int v18; // r3
  void *v19; // r0
  float *v20; // r2
  float *v21; // r3
  unsigned int m; // r1
  unsigned int v23; // r12
  float v24; // s15
  unsigned int v25; // r12
  float *v26; // r2
  unsigned int n; // r3
  int v28; // r0
  int v29; // r3
  int v30; // r1
  int v31; // r3
  unsigned int v32; // [sp+0h] [bp-24h]
  unsigned int v33; // [sp+0h] [bp-24h]
  int v34; // [sp+4h] [bp-20h]
  float *v35; // [sp+4h] [bp-20h]
  float *v36; // [sp+4h] [bp-20h]
  float *v37; // [sp+8h] [bp-1Ch]
  float *v38; // [sp+8h] [bp-1Ch]
  unsigned int j; // [sp+Ch] [bp-18h]
  unsigned int k; // [sp+14h] [bp-10h]
  unsigned int v42; // [sp+18h] [bp-Ch]

  if ( !a3 )
    return 80;
  v7 = 0;
  v8 = 0;
  for ( i = 0; i != a3; ++i )
  {
    v10 = a2[i];
    if ( v10 )
    {
      ++v7;
      v8 += v10;
    }
  }
  v11 = 0;
  v42 = v7;
  do
    a1[v11++] = 0;
  while ( v11 != a3 );
  if ( v7 )
  {
    if ( v7 == 1 )
    {
      v29 = 0;
      while ( 1 )
      {
        v30 = v29;
        result = a2[v29];
        if ( result )
          break;
        if ( ++v29 == a3 )
          return result;
      }
      if ( v29 )
        v31 = 0;
      else
        v31 = 1;
      a1[v30] = 1;
      a1[v31] = 1;
      return 0;
    }
    else
    {
      v12 = 2 * v7;
      v13 = (float *)malloc(32 * v7);
      v14 = (float *)malloc(32 * v7);
      if ( v13 && v14 )
      {
        sub_B690((int)v13, 2 * v7);
        sub_B690((int)v14, 2 * v7);
        v15 = sub_C5A4((int)v13, (int)a2, a3, v8);
        sub_B6AE((int)v13, v7);
        if ( !v15 )
        {
          v16 = 0;
          for ( j = 1; j <= a4; ++j )
          {
            if ( v15 )
              goto LABEL_39;
            v34 = v16;
            sub_C318((int)v14, v16);
            sub_B690((int)v14, v34);
            v17 = v13 + 7;
            v18 = (int)v14;
            for ( k = 1; k < v7; k += 2 )
            {
              *(float *)(v18 + 12) = *(v17 - 4);
              v37 = v17;
              v35 = (float *)v18;
              v19 = sub_C55E(v18, *((_DWORD *)v17 - 6));
              v20 = v37;
              v21 = v35;
              if ( v19 )
              {
                for ( m = 0; m < *((_DWORD *)v37 - 6); ++m )
                  *(_DWORD *)(*(_DWORD *)v35 + 4 * m) = *(_DWORD *)(*((_DWORD *)v37 - 7) + 4 * m);
              }
              v23 = 0;
              while ( v23 < *((_DWORD *)v20 - 2) )
              {
                v38 = v20;
                v36 = v21;
                v32 = v23;
                sub_C582(v21, *(_DWORD *)(*((_DWORD *)v20 - 3) + 4 * v23));
                v21 = v36;
                v23 = v32 + 1;
                v20 = v38;
              }
              v24 = v21[3] + *v20;
              v17 = v20 + 8;
              v18 = (int)(v21 + 4);
              *(float *)(v18 - 4) = v24;
            }
            v25 = v7 >> 1;
            if ( j < a4 )
            {
              v15 = sub_C5A4((int)&v14[4 * v25], (int)a2, a3, v8);
              v25 = (v7 >> 1) + v42;
            }
            v33 = v25;
            sub_B6AE((int)v14, v25);
            v26 = v13;
            v16 = v7;
            v13 = v14;
            v14 = v26;
            v7 = v33;
          }
          if ( !v15 )
          {
            while ( v15 < v42 - 1 )
            {
              for ( n = 0; n < LODWORD(v13[4 * v15 + 1]); ++n )
              {
                v28 = *(_DWORD *)(LODWORD(v13[4 * v15]) + 4 * n);
                ++a1[v28];
              }
              ++v15;
            }
            v15 = 0;
          }
        }
LABEL_39:
        sub_C318((int)v13, v12);
        free(v13);
        sub_C318((int)v14, v12);
        free(v14);
        return v15;
      }
      else
      {
        free(v13);
        free(v14);
        return 83;
      }
    }
  }
  else
  {
    a1[1] = 1;
    *a1 = 1;
    return 0;
  }
}


//----- (0000D258) --------------------------------------------------------
int __fastcall lodepng_inflate(int *a1, unsigned int *a2, int a3, unsigned int a4)
{
  unsigned int v5; // r7
  unsigned int v7; // r3
  unsigned int v8; // r10
  unsigned int v9; // r2
  unsigned int v10; // r3
  char v11; // r0
  unsigned int v12; // r1
  int v13; // r3
  unsigned int v14; // r9
  int v15; // r4
  unsigned int v16; // r1
  int i; // r3
  int v18; // r4
  int v19; // r0
  int v20; // r2
  unsigned int v21; // r4
  int v22; // r0
  unsigned int v23; // r5
  int v24; // r9
  _DWORD *v25; // r8
  char *v26; // r0
  _DWORD *v27; // r9
  int j; // r3
  int k; // r3
  unsigned int v30; // r5
  unsigned int v31; // r0
  unsigned int v32; // r3
  unsigned int v33; // r0
  int v34; // r1
  unsigned int m; // r2
  int v36; // r0
  unsigned int v37; // r2
  unsigned int v38; // r0
  int v39; // r0
  unsigned int v40; // r2
  unsigned int v41; // r0
  unsigned int v42; // r0
  char v43; // r9
  unsigned int v44; // r8
  char *v45; // r3
  int v46; // r8
  int v47; // r8
  unsigned int v48; // r0
  char *v49; // r0
  int v50; // r9
  unsigned int v51; // r0
  unsigned int v52; // r9
  unsigned int v53; // r2
  unsigned int v54; // r3
  char v55; // r0
  int result; // r0
  _DWORD *p; // [sp+8h] [bp-8Ch]
  unsigned int v58; // [sp+Ch] [bp-88h]
  int v59; // [sp+10h] [bp-84h]
  unsigned int v60; // [sp+10h] [bp-84h]
  int v61; // [sp+14h] [bp-80h]
  int v63; // [sp+1Ch] [bp-78h]
  int v66; // [sp+34h] [bp-60h]
  unsigned int v67; // [sp+44h] [bp-50h] BYREF
  int v68; // [sp+48h] [bp-4Ch] BYREF
  unsigned int v69; // [sp+4Ch] [bp-48h]
  unsigned int v70; // [sp+50h] [bp-44h]
  void *v71[5]; // [sp+54h] [bp-40h] BYREF
  void *v72[5]; // [sp+68h] [bp-2Ch] BYREF
  void *v73[6]; // [sp+7Ch] [bp-18h] BYREF

  v5 = 0;
  v7 = *a2;
  v8 = 8 * a4;
  v68 = *a1;
  v69 = v7;
  v70 = v7;
  v67 = 0;
  do
  {
    v9 = v67 + 2;
    if ( v67 + 2 >= v8 )
    {
      result = 52;
      goto LABEL_128;
    }
    v66 = ((int)*(unsigned __int8 *)(a3 + (v67 >> 3)) >> (v67 & 7)) & 1;
    v10 = (v67 + 1) >> 3;
    v11 = (v67 + 1) & 7;
    v12 = v67 + 3;
    v67 += 3;
    v13 = (((int)*(unsigned __int8 *)(a3 + v10) >> v11) & 1)
        + 2 * (((int)*(unsigned __int8 *)(a3 + (v9 >> 3)) >> (v9 & 7)) & 1);
    if ( v13 == 3 )
    {
      result = 20;
      goto LABEL_128;
    }
    if ( !v13 )
    {
      while ( v12 << 29 )
        ++v12;
      v14 = v12 >> 3;
      v67 = v12;
      if ( v12 >> 3 >= a4 - 4 )
      {
        v18 = 52;
      }
      else
      {
        v15 = *(unsigned __int8 *)(a3 + v14) + (*(unsigned __int8 *)(a3 + v14 + 1) << 8);
        if ( *(unsigned __int8 *)(a3 + v14 + 2) + (*(unsigned __int8 *)(a3 + v14 + 3) << 8) + v15 == 0xFFFF )
        {
          if ( v15 + v5 < v69 || sub_C5F0((int)&v68, v15 + v5) )
          {
            v16 = v14 + 4 + v15;
            if ( v16 <= a4 )
            {
              for ( i = 0; ; ++i )
              {
                v19 = i + v5;
                if ( i == v15 )
                  break;
                v20 = a3 + v14 + i;
                *(_BYTE *)(v68 + v19) = *(_BYTE *)(v20 + 4);
              }
              v5 += v15;
              v67 = 8 * v16;
              continue;
            }
            v18 = 23;
          }
          else
          {
            v18 = 83;
          }
        }
        else
        {
          v18 = 21;
        }
      }
LABEL_127:
      result = v18;
      goto LABEL_128;
    }
    v21 = 0;
    memset(v71, 0, 12);
    memset(v72, 0, 12);
    if ( v13 == 1 )
    {
      sub_C996((int *)v71);
      sub_CA04((int *)v72);
      goto LABEL_92;
    }
    if ( a4 - 2 <= v12 >> 3 )
    {
      v18 = 49;
      goto LABEL_120;
    }
    v61 = sub_B664(&v67, a3, 5);
    v59 = sub_B664(&v67, a3, 5);
    v22 = sub_B664(&v67, a3, 4);
    memset(v73, 0, 12);
    v23 = v22 + 4;
    p = malloc(0x4Cu);
    if ( p )
    {
      do
      {
        if ( v21 >= v23 )
        {
          p[dword_15DB0[v21]] = 0;
        }
        else
        {
          v24 = dword_15DB0[v21];
          p[v24] = sub_B664(&v67, a3, 3);
        }
        ++v21;
      }
      while ( v21 != 19 );
      v18 = sub_C956((int *)v73, (int)p, 19, 7);
      if ( v18 )
      {
        v27 = 0;
        v25 = 0;
        goto LABEL_89;
      }
      v25 = malloc(0x480u);
      v26 = (char *)malloc(0x80u);
      v27 = v26;
      if ( v25 && v26 )
      {
        for ( j = 0; j != 288; ++j )
          v25[j] = 0;
        for ( k = 0; k != 128; k += 4 )
          *(_DWORD *)&v26[k] = 0;
        v30 = 0;
        v58 = v61 + 257;
        v63 = 0x3FFFFFFF * v61;
        v60 = v61 + 257 + v59 + 1;
        while ( v30 < v60 )
        {
          v31 = sub_B76A(a3, &v67, v73, v8);
          if ( v31 > 0xF )
          {
            if ( v31 == 16 )
            {
              if ( v67 >= v8 )
                goto LABEL_130;
              if ( !v30 )
              {
                v18 = 54;
                goto LABEL_89;
              }
              v33 = sub_B664(&v67, a3, 2) + 3;
              if ( v30 >= v61 + 258 )
                v34 = v27[1073741566 - v61 + v30];
              else
                v34 = v25[v30 - 1];
              for ( m = 0; ; ++m )
              {
                v32 = m + v30;
                if ( m >= v33 )
                  break;
                if ( m == v60 - v30 )
                {
                  v18 = 13;
                  break;
                }
                if ( v32 >= v58 )
                  v27[v63 - 257 + v30 + m] = v34;
                else
                  v25[v30 + m] = v34;
              }
            }
            else if ( v31 == 17 )
            {
              if ( v67 >= v8 )
                goto LABEL_130;
              v36 = sub_B664(&v67, a3, 3);
              v37 = 0;
              v38 = v36 + 3;
              while ( 1 )
              {
                v32 = v37 + v30;
                if ( v37 >= v38 )
                  break;
                if ( v37 == v60 - v30 )
                {
                  v18 = 14;
                  break;
                }
                if ( v32 >= v58 )
                  v27[v63 - 257 + v30 + v37] = 0;
                else
                  v25[v30 + v37] = 0;
                ++v37;
              }
            }
            else
            {
              if ( v31 != 18 )
              {
                if ( v31 == -1 )
                {
                  if ( v67 > v8 )
                    v18 = 10;
                  else
                    v18 = 11;
                }
                else
                {
                  v18 = 16;
                }
                goto LABEL_89;
              }
              if ( v67 >= v8 )
              {
LABEL_130:
                v18 = 50;
                goto LABEL_89;
              }
              v39 = sub_B664(&v67, a3, 7);
              v40 = 0;
              v41 = v39 + 11;
              while ( 1 )
              {
                v32 = v40 + v30;
                if ( v40 >= v41 )
                  break;
                if ( v40 == v60 - v30 )
                {
                  v18 = 15;
                  break;
                }
                if ( v32 >= v58 )
                  v27[v63 - 257 + v30 + v40] = 0;
                else
                  v25[v30 + v40] = 0;
                ++v40;
              }
            }
          }
          else
          {
            if ( v30 >= v58 )
              v27[v30 - v58] = v31;
            else
              v25[v30] = v31;
            v32 = v30 + 1;
          }
          v30 = v32;
        }
        if ( !v18 )
        {
          if ( v25[256] )
          {
            v18 = sub_C956((int *)v71, (int)v25, 288, 15);
            if ( !v18 )
              v18 = sub_C956((int *)v72, (int)v27, 32, 15);
          }
          else
          {
            v18 = 64;
          }
        }
        goto LABEL_89;
      }
    }
    else
    {
      v27 = 0;
      v25 = 0;
    }
    v18 = 83;
LABEL_89:
    free(p);
    free(v25);
    free(v27);
    sub_C332(v73);
    if ( v18 )
      goto LABEL_120;
    while ( 1 )
    {
LABEL_92:
      v42 = sub_B76A(a3, &v67, v71, v8);
      v43 = v42;
      if ( v42 <= 0xFF )
      {
        v44 = v5 + 1;
        if ( v5 >= v69 && !sub_C5F0((int)&v68, 2 * v44) )
          goto LABEL_118;
        *(_BYTE *)(v68 + v5) = v43;
        goto LABEL_114;
      }
      if ( v42 - 257 > 0x1C )
        break;
      v45 = &asc_15B68[4 * v42 - 1028];
      if ( v67 >= v8 )
        goto LABEL_116;
      v46 = *((_DWORD *)v45 + 87);
      v47 = v46 + sub_B664(&v67, a3, *((_DWORD *)v45 + 58));
      v48 = sub_B76A(a3, &v67, v72, v8);
      if ( v48 > 0x1D )
      {
        v18 = 18;
        goto LABEL_120;
      }
      v49 = &asc_15B68[4 * v48];
      if ( v67 >= v8 )
      {
LABEL_116:
        v18 = 51;
        goto LABEL_120;
      }
      v50 = *((_DWORD *)v49 + 116);
      v51 = sub_B664(&v67, a3, *((_DWORD *)v49 + 28)) + v50;
      if ( v51 > v5 )
      {
        v18 = 52;
        goto LABEL_120;
      }
      v44 = v47 + v5;
      v52 = v5 - v51;
      if ( v44 >= v69 && !sub_C5F0((int)&v68, 2 * v44) )
      {
LABEL_118:
        v18 = 83;
        goto LABEL_120;
      }
      v53 = v5;
      v54 = v52;
      while ( v53 != v44 )
      {
        v55 = *(_BYTE *)(v68 + v54++);
        if ( v54 >= v5 )
          v54 = v52;
        *(_BYTE *)(v68 + v53++) = v55;
      }
LABEL_114:
      v5 = v44;
    }
    if ( v42 == 256 )
    {
      v18 = 0;
    }
    else if ( v67 > v8 )
    {
      v18 = 10;
    }
    else
    {
      v18 = 11;
    }
LABEL_120:
    sub_C332(v71);
    sub_C332(v72);
    if ( v18 )
      goto LABEL_127;
  }
  while ( !v66 );
  if ( sub_C5F0((int)&v68, v5) )
    result = 0;
  else
    result = 83;
LABEL_128:
  *a1 = v68;
  *a2 = v69;
  return result;
}
// 15DB0: using guessed type _DWORD dword_15DB0[277];


//----- (0000D810) --------------------------------------------------------
int __fastcall lodepng_deflate(int *a1, int *a2, int a3, unsigned int a4, int *a5)
{
  int v5; // r4
  int v6; // r2
  bool v7; // cc
  unsigned int v8; // r6
  unsigned int v9; // r11
  int v10; // r9
  unsigned int v11; // r7
  __int16 v12; // r3
  __int16 v13; // r8
  unsigned int v14; // r8
  unsigned int v15; // r0
  int v16; // r4
  void *v17; // r0
  int i; // r3
  int j; // r3
  int k; // r3
  unsigned int v21; // r10
  int v22; // r3
  _BOOL4 v23; // r6
  unsigned int v24; // r9
  unsigned int v25; // r3
  unsigned int v26; // r3
  int v27; // r9
  int v28; // r4
  int v29; // r3
  int v30; // r3
  int v31; // r1
  unsigned int m; // r3
  int v33; // r4
  unsigned int v34; // r2
  const unsigned int *v35; // r1
  int v36; // r10
  int v37; // r11
  int v38; // r1
  int n; // r4
  int v40; // r1
  unsigned int v41; // r7
  int v42; // r2
  int *v43; // r1
  unsigned int v44; // r9
  int v45; // r3
  int v46; // lr
  unsigned int v47; // r8
  int v48; // r1
  unsigned int v49; // r8
  int kk; // r2
  unsigned int ii; // r3
  unsigned int jj; // r3
  unsigned int v53; // r8
  int v54; // r3
  unsigned int v55; // r11
  unsigned int v56; // r2
  unsigned int v57; // r8
  int v58; // r3
  int v59; // t1
  unsigned int v60; // r10
  unsigned int v61; // r2
  unsigned int v62; // r8
  int v63; // r10
  int v64; // r1
  unsigned int v65; // r2
  int v66; // r3
  unsigned int v68; // [sp+4h] [bp-108h]
  int v70; // [sp+20h] [bp-ECh]
  char v71; // [sp+21h] [bp-EBh]
  unsigned int v72; // [sp+24h] [bp-E8h]
  int v74; // [sp+30h] [bp-DCh]
  unsigned int v75; // [sp+3Ch] [bp-D0h]
  unsigned int v76; // [sp+40h] [bp-CCh]
  int v79; // [sp+58h] [bp-B4h] BYREF
  int v80; // [sp+5Ch] [bp-B0h] BYREF
  int v81; // [sp+60h] [bp-ACh]
  int v82; // [sp+64h] [bp-A8h]
  int v83; // [sp+68h] [bp-A4h] BYREF
  unsigned int v84; // [sp+6Ch] [bp-A0h]
  int v85; // [sp+70h] [bp-9Ch]
  int v86; // [sp+74h] [bp-98h] BYREF
  unsigned int v87; // [sp+78h] [bp-94h]
  int v88; // [sp+7Ch] [bp-90h]
  const unsigned int *v89; // [sp+80h] [bp-8Ch] BYREF
  unsigned int v90; // [sp+84h] [bp-88h]
  int v91; // [sp+88h] [bp-84h]
  const unsigned int *v92; // [sp+8Ch] [bp-80h] BYREF
  unsigned int v93; // [sp+90h] [bp-7Ch]
  int v94; // [sp+94h] [bp-78h]
  int v95; // [sp+98h] [bp-74h] BYREF
  unsigned int v96; // [sp+9Ch] [bp-70h]
  int v97; // [sp+A0h] [bp-6Ch]
  int v98; // [sp+A4h] [bp-68h] BYREF
  unsigned int v99; // [sp+A8h] [bp-64h]
  int v100; // [sp+ACh] [bp-60h]
  int v101; // [sp+B0h] [bp-5Ch] BYREF
  unsigned int v102; // [sp+B4h] [bp-58h]
  int v103; // [sp+B8h] [bp-54h]
  void *p; // [sp+BCh] [bp-50h] BYREF
  void *v105; // [sp+C0h] [bp-4Ch]
  void *v106; // [sp+C4h] [bp-48h]
  void *v107; // [sp+C8h] [bp-44h]
  void *v108; // [sp+CCh] [bp-40h] BYREF
  int v109; // [sp+D0h] [bp-3Ch]
  int v110; // [sp+D4h] [bp-38h]
  unsigned int v111; // [sp+DCh] [bp-30h]
  void *v112; // [sp+E0h] [bp-2Ch] BYREF
  int v113; // [sp+E4h] [bp-28h]
  int v114; // [sp+E8h] [bp-24h]
  unsigned int v115; // [sp+F0h] [bp-1Ch]
  void *v116; // [sp+F4h] [bp-18h] BYREF
  int v117; // [sp+F8h] [bp-14h]
  int v118; // [sp+FCh] [bp-10h]
  unsigned int v119; // [sp+104h] [bp-8h]

  v5 = *a5;
  v6 = *a1;
  v7 = (unsigned int)*a5 > 2;
  v81 = *a2;
  v82 = v81;
  v80 = v6;
  v79 = 0;
  if ( v7 )
  {
    v5 = 61;
    goto LABEL_137;
  }
  v8 = a4;
  if ( v5 )
  {
    if ( v5 != 1 )
    {
      v8 = (a4 >> 3) + 8;
      if ( v8 <= 0xFFFE )
        v8 = 0xFFFF;
    }
    v72 = v8;
    v15 = (a4 - 1 + v8) / v8;
    v16 = a5[2];
    if ( !v15 )
      v15 = 1;
    v75 = v15;
    p = malloc(0x40000u);
    v105 = malloc(4 * v16);
    v106 = malloc(2 * v16);
    v17 = malloc(2 * v16);
    v107 = v17;
    if ( !p || !v105 || !v106 || !v17 )
    {
      v5 = 83;
      goto LABEL_137;
    }
    for ( i = 0; i != 0x40000; i += 4 )
      *(_DWORD *)((char *)p + i) = -1;
    for ( j = 0; j != v16; ++j )
      *((_DWORD *)v105 + j) = -1;
    for ( k = 0; k != v16; ++k )
      *((_WORD *)v106 + k) = k;
    v21 = 0;
    v74 = 0;
    while ( 1 )
    {
      v22 = *a5;
      v23 = v74 == v75 - 1;
      v24 = v72 + v21;
      v76 = v72 + v21;
      if ( v72 + v21 >= a4 )
        v24 = a4;
      if ( v22 == 1 )
        break;
      if ( v22 == 2 )
      {
        v29 = a5[1];
        v83 = 0;
        v85 = 0;
        v84 = 0;
        v108 = 0;
        v109 = 0;
        v110 = 0;
        v112 = 0;
        v113 = 0;
        v114 = 0;
        v116 = 0;
        v117 = 0;
        v118 = 0;
        v86 = 0;
        v88 = 0;
        v87 = 0;
        v89 = 0;
        v91 = 0;
        v90 = 0;
        v92 = 0;
        v94 = 0;
        v93 = 0;
        v95 = 0;
        v97 = 0;
        v96 = 0;
        v98 = 0;
        v100 = 0;
        v99 = 0;
        v101 = 0;
        v103 = 0;
        v102 = 0;
        if ( v29 )
        {
          v27 = sub_CBA4(&v83, &p, a3, v21, v24, a5[2], a5[3], a5[4], a5[5]);
          if ( v27 )
            goto LABEL_113;
        }
        else
        {
          if ( !sub_C55E((int)&v83, v24 - v21) )
            goto LABEL_51;
          v30 = 4 * v21;
          while ( v21 < v24 )
          {
            v31 = *(unsigned __int8 *)(a3 + v21++);
            *(_DWORD *)(v83 + v30) = v31;
            v30 += 4;
          }
        }
        if ( !sub_C7A4(&v86, 0x11Eu) || !sub_C7A4(&v89, 0x1Eu) )
          goto LABEL_51;
        for ( m = 0; m < v84; ++m )
        {
          v33 = 4 * m;
          v34 = *(_DWORD *)(v83 + 4 * m);
          ++*(_DWORD *)(v86 + 4 * v34);
          if ( v34 > 0x100 )
          {
            m += 3;
            ++v89[*(_DWORD *)(v83 + v33 + 8)];
          }
        }
        v35 = (const unsigned int *)v86;
        *(_DWORD *)(v86 + 1024) = 1;
        v27 = sub_D1FE((int)&v108, v35, 0x101u, v87, 0xFu);
        if ( !v27 )
        {
          v27 = sub_D1FE((int)&v112, v89, 2u, v90, 0xFu);
          if ( !v27 )
          {
            if ( v111 >= 0x11E )
              v36 = 286;
            else
              v36 = v111;
            if ( v115 >= 0x1E )
              v37 = 30;
            else
              v37 = v115;
            while ( v27 != v36 )
            {
              v38 = *(_DWORD *)(v110 + 4 * v27++);
              sub_C582(&v95, v38);
            }
            for ( n = 0; n != v37; ++n )
            {
              v40 = *(_DWORD *)(v114 + 4 * n);
              sub_C582(&v95, v40);
            }
            v41 = 0;
            while ( 2 )
            {
              if ( v41 >= v96 )
              {
                if ( !sub_C7A4(&v92, 0x13u) )
                  goto LABEL_51;
                for ( ii = 0; ii < v99; ++ii )
                {
                  ++v92[*(_DWORD *)(v98 + 4 * ii)];
                  if ( *(_DWORD *)(v98 + 4 * ii) > 0xFu )
                    ++ii;
                }
                v27 = sub_D1FE((int)&v116, v92, v93, v93, 7u);
                if ( !v27 )
                {
                  if ( sub_C55E((int)&v101, v119) )
                  {
                    for ( jj = 0; jj < v119; ++jj )
                      *(_DWORD *)(v101 + 4 * jj) = *(_DWORD *)(v118 + 4 * dword_15DB0[jj]);
                    while ( !*(_DWORD *)(v101 + 4 * (v102 + 0x3FFFFFFF)) && v102 > 4 )
                    {
                      if ( !sub_C55E((int)&v101, v102 - 1) )
                        goto LABEL_51;
                    }
                    v55 = v37 - 1;
                    sub_C630(&v79, &v80, v23);
                    sub_C630(&v79, &v80, 0);
                    sub_C630(&v79, &v80, 1);
                    v56 = v36 - 257;
                    v57 = v102 - 4;
                    v58 = v101 + 4 * v102;
                    while ( 1 )
                    {
                      v59 = *(_DWORD *)(v58 - 4);
                      v58 -= 4;
                      if ( v59 || !v57 )
                        break;
                      --v57;
                    }
                    v60 = 0;
                    sub_C662((int)&v79, &v80, v56, 5);
                    sub_C662((int)&v79, &v80, v55, 5);
                    v61 = v57;
                    v62 = v57 + 4;
                    sub_C662((int)&v79, &v80, v61, 4);
                    while ( v60 < v62 )
                      sub_C662((int)&v79, &v80, *(_DWORD *)(v101 + 4 * v60++), 3);
                    v53 = 0;
                    while ( 2 )
                    {
                      if ( v53 >= v99 )
                      {
                        sub_C6B0((int)&v79, &v80, &v83, (int)&v108, (int)&v112);
                        v54 = *(unsigned __int32 *)((char *)&stru_3F8.st_size + v110);
                        if ( v54 )
                          sub_C68C((int)&v79, &v80, *(unsigned __int32 *)((char *)&stru_3F8.st_size + v109), v54);
                        else
                          v27 = 64;
                        goto LABEL_113;
                      }
                      v63 = 4 * v53;
                      sub_C68C(
                        (int)&v79,
                        &v80,
                        *(_DWORD *)(v117 + 4 * *(_DWORD *)(v98 + 4 * v53)),
                        *(_DWORD *)(v118 + 4 * *(_DWORD *)(v98 + 4 * v53)));
                      v64 = *(_DWORD *)(v98 + 4 * v53);
                      switch ( v64 )
                      {
                        case 16:
                          ++v53;
                          v65 = *(_DWORD *)(v98 + v63 + 4);
                          v66 = 2;
                          goto LABEL_134;
                        case 17:
                          ++v53;
                          v65 = *(_DWORD *)(v98 + v63 + 4);
                          v66 = 3;
                          goto LABEL_134;
                        case 18:
                          ++v53;
                          v65 = *(_DWORD *)(v98 + v63 + 4);
                          v66 = 7;
LABEL_134:
                          sub_C662((int)&v79, &v80, v65, v66);
                          break;
                      }
                      ++v53;
                      continue;
                    }
                  }
LABEL_51:
                  v27 = 83;
                  break;
                }
                break;
              }
              v42 = 1;
              v43 = (int *)(v95 + 4 * v41);
              do
              {
                v44 = v42 - 1;
                v45 = *v43;
                if ( v42 == v96 - v41 )
                  break;
                v46 = v43[v42++];
              }
              while ( v46 == v45 );
              if ( v45 )
              {
                if ( v44 > 2 )
                {
                  v49 = v44 % 6;
                  sub_C582(&v98, *v43);
                  for ( kk = 0; kk != v44 / 6; kk = v70 + 1 )
                  {
                    v70 = kk;
                    sub_C582(&v98, 16);
                    sub_C582(&v98, 3);
                  }
                  if ( v49 <= 2 )
                  {
                    v44 -= v49;
                  }
                  else
                  {
                    sub_C582(&v98, 16);
                    sub_C582(&v98, v49 - 3);
                  }
                  v41 += v44;
                  goto LABEL_97;
                }
              }
              else if ( v44 > 1 )
              {
                v47 = v44 + 1;
                if ( v44 + 1 > 0xA )
                {
                  if ( v47 >= 0x8A )
                    v47 = 138;
                  sub_C582(&v98, 18);
                  v48 = v47 - 11;
                }
                else
                {
                  sub_C582(&v98, 17);
                  v48 = v44 - 2;
                }
                sub_C582(&v98, v48);
                v41 = v41 - 1 + v47;
                goto LABEL_97;
              }
              sub_C582(&v98, *v43);
LABEL_97:
              ++v41;
              continue;
            }
          }
        }
LABEL_113:
        sub_C304((int)&v83);
        sub_C332(&v108);
        sub_C332(&v112);
        sub_C332(&v116);
        sub_C304((int)&v86);
        sub_C304((int)&v89);
        sub_C304((int)&v92);
        sub_C304((int)&v98);
        sub_C304((int)&v95);
        sub_C304((int)&v101);
      }
      else
      {
        v27 = 0;
      }
LABEL_115:
      if ( ++v74 >= v75 || v27 )
      {
        v5 = v27;
        free(p);
        free(v105);
        free(v106);
        free(v107);
        goto LABEL_137;
      }
      v21 = v76;
    }
    v112 = 0;
    v113 = 0;
    v114 = 0;
    v116 = 0;
    v117 = 0;
    v118 = 0;
    sub_C996((int *)&v112);
    sub_CA04((int *)&v116);
    sub_C630(&v79, &v80, v23);
    sub_C630(&v79, &v80, 1);
    sub_C630(&v79, &v80, 0);
    if ( a5[1] )
    {
      v25 = a5[2];
      v108 = 0;
      v110 = 0;
      v68 = v25;
      v26 = a5[3];
      v109 = 0;
      v27 = sub_CBA4(&v108, &p, a3, v21, v24, v68, v26, a5[4], a5[5]);
      if ( !v27 )
        sub_C6B0((int)&v79, &v80, &v108, (int)&v112, (int)&v116);
      sub_C304((int)&v108);
      if ( v27 )
        goto LABEL_40;
    }
    else
    {
      while ( v21 < v24 )
      {
        v28 = *(unsigned __int8 *)(a3 + v21++);
        sub_C68C((int)&v79, &v80, *(_DWORD *)(v113 + 4 * v28), *(_DWORD *)(v114 + 4 * v28));
      }
    }
    v27 = 0;
    sub_C68C(
      (int)&v79,
      &v80,
      *(unsigned __int32 *)((char *)&stru_3F8.st_size + v113),
      *(unsigned __int32 *)((char *)&stru_3F8.st_size + v114));
LABEL_40:
    sub_C332(&v112);
    sub_C332(&v116);
    goto LABEL_115;
  }
  v9 = 0;
  v10 = 0;
  v11 = (a4 + 65534) / 0xFFFF;
  while ( v10 != v11 )
  {
    sub_C612(&v80, v10 == v11 - 1);
    v12 = a4 - v9;
    if ( a4 - v9 > 0xFFFE )
      v12 = -1;
    v71 = HIBYTE(v12);
    v13 = -1 - v12;
    sub_C612(&v80, v12);
    sub_C612(&v80, v71);
    sub_C612(&v80, v13);
    sub_C612(&v80, SHIBYTE(v13));
    v14 = v9 + 0xFFFF;
    do
    {
      if ( v9 >= a4 )
        break;
      ++v9;
      sub_C612(&v80, *(_BYTE *)(a3 + v9 - 1));
    }
    while ( v9 != v14 );
    ++v10;
  }
LABEL_137:
  *a1 = v80;
  *a2 = v81;
  return v5;
}
// 3F8: using guessed type Elf32_Sym stru_3F8;
// 15DB0: using guessed type _DWORD dword_15DB0[277];


//----- (0000DF74) --------------------------------------------------------
int __fastcall lodepng_zlib_decompress(int *a1, unsigned int *a2, unsigned __int8 *a3, unsigned int a4, _DWORD *a5)
{
  unsigned int v9; // r9
  int v10; // r10
  int (__fastcall *v11)(int *, unsigned int *, int, unsigned int, _DWORD *, unsigned int *); // r12
  int v12; // r2
  unsigned int v13; // r3
  int result; // r0
  unsigned int v15; // r4

  if ( a4 <= 1 )
    return 53;
  v9 = *a3;
  v10 = a3[1];
  if ( (int)(v10 + (v9 << 8)) % 31 )
    return 24;
  if ( (v9 & 0xF) != 8 || v9 > 0x7F )
    return 25;
  if ( (v10 & 0x20) != 0 )
    return 26;
  v11 = (int (__fastcall *)(int *, unsigned int *, int, unsigned int, _DWORD *, unsigned int *))a5[2];
  v12 = (int)(a3 + 2);
  v13 = a4 - 2;
  if ( v11 )
    result = v11(a1, a2, v12, v13, a5, a2);
  else
    result = lodepng_inflate(a1, a2, v12, v13);
  if ( !result && !*a5 )
  {
    v15 = lodepng_read32bitInt(&a3[a4 - 4]);
    if ( sub_C758((unsigned __int8 *)*a1, *a2) == v15 )
      return 0;
    else
      return 58;
  }
  return result;
}


//----- (0000E020) --------------------------------------------------------
int __fastcall lodepng_zlib_compress(int *a1, int *a2, unsigned __int8 *a3, unsigned int a4, int *a5)
{
  int v7; // r2
  int v9; // r3
  int (__fastcall *v11)(void **, unsigned int *, unsigned __int8 *, unsigned int, int *); // r12
  int v12; // r0
  int v13; // r4
  int v14; // r0
  unsigned int v15; // r6
  unsigned int v16; // r7
  char v17; // r1
  void *p; // [sp+Ch] [bp-18h] BYREF
  unsigned int v20; // [sp+10h] [bp-14h] BYREF
  int v21; // [sp+14h] [bp-10h] BYREF
  int v22; // [sp+18h] [bp-Ch]
  int v23; // [sp+1Ch] [bp-8h]

  v7 = *a1;
  p = 0;
  v20 = 0;
  v9 = *a2;
  v21 = v7;
  v22 = v9;
  v23 = v9;
  sub_C612(&v21, 120);
  sub_C612(&v21, 1);
  v11 = (int (__fastcall *)(void **, unsigned int *, unsigned __int8 *, unsigned int, int *))a5[7];
  if ( v11 )
    v12 = v11(&p, &v20, a3, a4, a5);
  else
    v12 = lodepng_deflate((int *)&p, (int *)&v20, (int)a3, a4, a5);
  v13 = v12;
  if ( !v12 )
  {
    v14 = sub_C758(a3, a4);
    v15 = 0;
    v16 = v14;
    while ( v15 < v20 )
    {
      v17 = *((_BYTE *)p + v15++);
      sub_C612(&v21, v17);
    }
    free(p);
    sub_CA78(&v21, v16);
  }
  *a1 = v21;
  *a2 = v22;
  return v13;
}


//----- (0000E0D0) --------------------------------------------------------
_DWORD *__fastcall lodepng_compress_settings_init(_DWORD *result)
{
  *result = 2;
  result[2] = 2048;
  result[1] = 1;
  result[3] = 3;
  result[5] = 1;
  result[4] = 128;
  result[6] = 0;
  result[7] = 0;
  result[8] = 0;
  return result;
}


//----- (0000E0F2) --------------------------------------------------------
_DWORD *__fastcall lodepng_decompress_settings_init(_DWORD *result)
{
  *result = 0;
  result[1] = 0;
  result[2] = 0;
  result[3] = 0;
  return result;
}


//----- (0000E100) --------------------------------------------------------
int __fastcall lodepng_crc32(const unsigned __int8 *a1, unsigned int a2)
{
  int v2; // r2
  unsigned int v3; // r3
  unsigned __int8 v4; // r5

  v2 = 0;
  v3 = -1;
  while ( v2 != a2 )
  {
    v4 = a1[v2++];
    v3 = *(_DWORD *)&asc_15B68[4 * (unsigned __int8)(v4 ^ v3) + 660] ^ (v3 >> 8);
  }
  return ~v3;
}


//----- (0000E134) --------------------------------------------------------
int __fastcall lodepng_chunk_type(int result, const unsigned __int8 *a2)
{
  int i; // r3

  for ( i = 0; i != 4; ++i )
    *(_BYTE *)(result + i) = a2[i + 4];
  *(_BYTE *)(result + 4) = 0;
  return result;
}


//----- (0000E148) --------------------------------------------------------
int __fastcall lodepng_chunk_type_equals(const unsigned __int8 *a1, const char *s)
{
  if ( strlen(s) == 4
    && a1[4] == *(unsigned __int8 *)s
    && a1[5] == *((unsigned __int8 *)s + 1)
    && a1[6] == *((unsigned __int8 *)s + 2) )
  {
    return a1[7]
         - *((unsigned __int8 *)s + 3)
         + (a1[7] == *((unsigned __int8 *)s + 3))
         + *((unsigned __int8 *)s + 3)
         - a1[7];
  }
  else
  {
    return 0;
  }
}


//----- (0000E180) --------------------------------------------------------
int __fastcall lodepng_chunk_ancillary(const unsigned __int8 *a1)
{
  return (a1[4] >> 5) & 1;
}


//----- (0000E188) --------------------------------------------------------
int __fastcall lodepng_chunk_private(const unsigned __int8 *a1)
{
  return (a1[6] >> 5) & 1;
}


//----- (0000E190) --------------------------------------------------------
int __fastcall lodepng_chunk_safetocopy(const unsigned __int8 *a1)
{
  return (a1[7] >> 5) & 1;
}


//----- (0000E198) --------------------------------------------------------
unsigned __int8 *__fastcall lodepng_chunk_data(unsigned __int8 *a1)
{
  return a1 + 8;
}


//----- (0000E19C) --------------------------------------------------------
const unsigned __int8 *__fastcall lodepng_chunk_data_const(const unsigned __int8 *a1)
{
  return a1 + 8;
}


//----- (0000E1A0) --------------------------------------------------------
bool __fastcall lodepng_chunk_check_crc(const unsigned __int8 *a1)
{
  int v2; // r5
  unsigned int v3; // r6

  v2 = lodepng_chunk_length(a1);
  v3 = lodepng_read32bitInt(&a1[v2 + 8]);
  return v3 != lodepng_crc32(a1 + 4, v2 + 4);
}


//----- (0000E1C4) --------------------------------------------------------
int __fastcall lodepng_chunk_generate_crc(unsigned __int8 *a1)
{
  int v2; // r0
  int v3; // r5
  int result; // r0
  unsigned __int8 *v5; // r2

  v2 = lodepng_chunk_length(a1);
  v3 = v2 + 8;
  result = lodepng_crc32(a1 + 4, v2 + 4);
  v5 = &a1[v3];
  a1[v3] = HIBYTE(result);
  v5[3] = result;
  v5[1] = BYTE2(result);
  v5[2] = BYTE1(result);
  return result;
}


//----- (0000E1EA) --------------------------------------------------------
unsigned __int8 *__fastcall lodepng_chunk_next(unsigned __int8 *a1)
{
  return &a1[lodepng_chunk_length(a1) + 12];
}


//----- (0000E1F8) --------------------------------------------------------
const unsigned __int8 *__fastcall lodepng_chunk_next_const(const unsigned __int8 *a1)
{
  return &a1[lodepng_chunk_length(a1) + 12];
}


//----- (0000E206) --------------------------------------------------------
int __fastcall lodepng_chunk_append(unsigned __int8 **a1, unsigned int *a2, const unsigned __int8 *a3)
{
  int v6; // r0
  size_t v7; // r5
  unsigned int v8; // r4
  size_t v9; // r7
  unsigned __int8 *v10; // r0
  unsigned __int8 *v11; // r5
  unsigned int i; // r3

  v6 = lodepng_chunk_length(a3);
  v7 = *a2;
  v8 = v6 + 12;
  v9 = v6 + 12 + *a2;
  if ( __CFADD__(v6 + 12, *a2) || v9 < v7 )
    return 77;
  v10 = (unsigned __int8 *)realloc(*a1, v9);
  if ( !v10 )
    return 83;
  *a1 = v10;
  *a2 = v9;
  v11 = &(*a1)[v7];
  for ( i = 0; i < v8; ++i )
    v11[i] = a3[i];
  return 0;
}


//----- (0000E25C) --------------------------------------------------------
int __fastcall lodepng_chunk_create(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned int a3,
        const char *a4,
        const unsigned __int8 *a5)
{
  unsigned int v8; // r7
  unsigned __int8 *v10; // r0
  unsigned __int8 *v11; // r0
  int i; // r3
  unsigned __int8 v13; // r1
  unsigned __int8 *v14; // r2

  v8 = *a2 + a3 + 12;
  if ( __CFADD__(*a2, a3 + 12) || v8 < *a2 )
    return 77;
  v10 = (unsigned __int8 *)realloc(*a1, *a2 + a3 + 12);
  if ( !v10 )
    return 83;
  *a1 = v10;
  *a2 = v8;
  v11 = &(*a1)[v8 + -12 - a3];
  *v11 = HIBYTE(a3);
  v11[3] = a3;
  v11[1] = BYTE2(a3);
  v11[2] = BYTE1(a3);
  v11[4] = *a4;
  v11[5] = a4[1];
  v11[6] = a4[2];
  v11[7] = a4[3];
  for ( i = 0; i != a3; ++i )
  {
    v13 = a5[i];
    v14 = &v11[i];
    v14[8] = v13;
  }
  lodepng_chunk_generate_crc(v11);
  return 0;
}


//----- (0000E2F4) --------------------------------------------------------
_DWORD *__fastcall lodepng_color_mode_init(_DWORD *result)
{
  result[4] = 0;
  result[7] = 0;
  result[6] = 0;
  result[5] = 0;
  *result = 6;
  result[1] = 8;
  result[2] = 0;
  result[3] = 0;
  return result;
}


//----- (0000E30C) --------------------------------------------------------
void __fastcall lodepng_palette_clear(int a1)
{
  void *v2; // r0

  v2 = *(void **)(a1 + 8);
  if ( v2 )
    free(v2);
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 12) = 0;
}


//----- (0000E324) --------------------------------------------------------
int __fastcall lodepng_color_mode_copy(_DWORD *a1, int *a2)
{
  int *v3; // r5
  int v5; // r0
  int v6; // r1
  int v7; // r2
  int v8; // r3
  int v9; // r1
  int v10; // r2
  int v11; // r3
  void *v13; // r0
  unsigned int i; // r3

  v3 = a2;
  lodepng_color_mode_cleanup();
  v5 = *v3;
  v6 = v3[1];
  v7 = v3[2];
  v8 = v3[3];
  v3 += 4;
  *a1 = v5;
  a1[1] = v6;
  a1[2] = v7;
  a1[3] = v8;
  v9 = v3[1];
  v10 = v3[2];
  v11 = v3[3];
  a1[4] = *v3;
  a1[5] = v9;
  a1[6] = v10;
  a1[7] = v11;
  if ( !a2[2] )
    return 0;
  v13 = malloc(0x400u);
  a1[2] = v13;
  if ( v13 || !a2[3] )
  {
    for ( i = 0; i < 4 * a2[3]; ++i )
      *(_BYTE *)(a1[2] + i) = *(_BYTE *)(a2[2] + i);
    return 0;
  }
  return 83;
}
// E320: using guessed type int lodepng_color_mode_cleanup(void);


//----- (0000E370) --------------------------------------------------------
int __fastcall lodepng_palette_add(int a1, char a2, char a3, char a4, char a5)
{
  void *v9; // r0

  if ( *(_DWORD *)(a1 + 8) )
    goto LABEL_4;
  v9 = realloc(0, 0x400u);
  if ( v9 )
  {
    *(_DWORD *)(a1 + 8) = v9;
LABEL_4:
    *(_BYTE *)(*(_DWORD *)(a1 + 8) + 4 * *(_DWORD *)(a1 + 12)) = a2;
    *(_BYTE *)(*(_DWORD *)(a1 + 8) + 4 * *(_DWORD *)(a1 + 12) + 1) = a3;
    *(_BYTE *)(*(_DWORD *)(a1 + 8) + 4 * *(_DWORD *)(a1 + 12) + 2) = a4;
    *(_BYTE *)(*(_DWORD *)(a1 + 8) + 4 * (*(_DWORD *)(a1 + 12))++ + 3) = a5;
    return 0;
  }
  return 83;
}


//----- (0000E3CC) --------------------------------------------------------
int __fastcall lodepng_get_bpp(unsigned int *a1)
{
  unsigned int v1; // r3
  unsigned int v2; // r0
  int v3; // r3

  v1 = *a1;
  v2 = a1[1];
  if ( v1 > 6 )
    v3 = 0;
  else
    v3 = (unsigned __int8)asc_15B68[v1 + 1684];
  return v2 * v3;
}


//----- (0000EBE0) --------------------------------------------------------
int __fastcall lodepng_get_channels(_DWORD *a1)
{
  if ( *a1 > 6u )
    return 0;
  else
    return (unsigned __int8)asc_15B68[*a1 + 1684];
}


//----- (0000EBFC) --------------------------------------------------------
bool __fastcall lodepng_is_greyscale_type(int *a1)
{
  int v1; // r0

  v1 = *a1;
  return !v1 || v1 == 4;
}


//----- (0000EC0C) --------------------------------------------------------
int __fastcall lodepng_is_alpha_type(_DWORD *a1)
{
  return (*a1 >> 2) & 1;
}


//----- (0000EC14) --------------------------------------------------------
bool __fastcall lodepng_is_palette_type(_DWORD *a1)
{
  return *a1 == 3;
}


//----- (0000EC1E) --------------------------------------------------------
int __fastcall lodepng_has_palette_alpha(int a1)
{
  int i; // r3

  for ( i = 0; ; ++i )
  {
    if ( i == *(_DWORD *)(a1 + 12) )
      return 0;
    if ( *(unsigned __int8 *)(*(_DWORD *)(a1 + 8) + 4 * i + 3) != 255 )
      break;
  }
  return 1;
}


//----- (0000EC3E) --------------------------------------------------------
bool __fastcall lodepng_can_have_alpha(_DWORD *a1)
{
  return a1[4] || lodepng_is_alpha_type(a1) || lodepng_has_palette_alpha((int)a1) != 0;
}


//----- (0000EC60) --------------------------------------------------------
unsigned int __fastcall lodepng_get_raw_size(int a1, int a2, unsigned int *a3)
{
  return (unsigned int)(lodepng_get_bpp(a3) * a2 * a1 + 7) >> 3;
}


//----- (0000EC74) --------------------------------------------------------
unsigned int __fastcall lodepng_get_raw_size_lct(int a1, int a2, unsigned int a3, int a4)
{
  int v4; // r2

  if ( a3 > 6 )
    v4 = 0;
  else
    v4 = (unsigned __int8)asc_15B68[a3 + 1684];
  return (unsigned int)(a1 * a2 * a4 * v4 + 7) >> 3;
}


//----- (0000EC9C) --------------------------------------------------------
int __fastcall lodepng_add_text(int a1, char *a2, char *a3)
{
  _DWORD *v6; // r5
  void *v7; // r0
  void *v8; // r6
  int v10; // r0

  v6 = realloc(*(void **)(a1 + 64), 4 * (*(_DWORD *)(a1 + 60) + 1));
  v7 = realloc(*(void **)(a1 + 68), 4 * (*(_DWORD *)(a1 + 60) + 1));
  v8 = v7;
  if ( v6 && v7 )
  {
    v10 = *(_DWORD *)(a1 + 60);
    *(_DWORD *)(a1 + 64) = v6;
    *(_DWORD *)(a1 + 68) = v8;
    *(_DWORD *)(a1 + 60) = v10 + 1;
    sub_CB04(&v6[v10]);
    sub_C37C((void **)(*(_DWORD *)(a1 + 64) + 4 * (*(_DWORD *)(a1 + 60) + 0x3FFFFFFF)), a2);
    sub_CB04((_DWORD *)(*(_DWORD *)(a1 + 68) + 4 * (*(_DWORD *)(a1 + 60) + 0x3FFFFFFF)));
    sub_C37C((void **)(*(_DWORD *)(a1 + 68) + 4 * (*(_DWORD *)(a1 + 60) + 0x3FFFFFFF)), a3);
    return 0;
  }
  else
  {
    free(v6);
    free(v8);
    return 83;
  }
}


//----- (0000ED2E) --------------------------------------------------------
int __fastcall lodepng_add_itext(int a1, char *a2, char *a3, char *a4, char *s)
{
  _DWORD *v9; // r5
  void *v10; // r7
  void *v11; // r6
  void *v12; // r0
  void *v13; // r8
  int v15; // r0

  v9 = realloc(*(void **)(a1 + 76), 4 * (*(_DWORD *)(a1 + 72) + 1));
  v10 = realloc(*(void **)(a1 + 80), 4 * (*(_DWORD *)(a1 + 72) + 1));
  v11 = realloc(*(void **)(a1 + 84), 4 * (*(_DWORD *)(a1 + 72) + 1));
  v12 = realloc(*(void **)(a1 + 88), 4 * (*(_DWORD *)(a1 + 72) + 1));
  v13 = v12;
  if ( v9 && v10 && v11 && v12 )
  {
    v15 = *(_DWORD *)(a1 + 72);
    *(_DWORD *)(a1 + 76) = v9;
    *(_DWORD *)(a1 + 80) = v10;
    *(_DWORD *)(a1 + 72) = v15 + 1;
    *(_DWORD *)(a1 + 84) = v11;
    *(_DWORD *)(a1 + 88) = v13;
    sub_CB04(&v9[v15]);
    sub_C37C((void **)(*(_DWORD *)(a1 + 76) + 4 * (*(_DWORD *)(a1 + 72) + 0x3FFFFFFF)), a2);
    sub_CB04((_DWORD *)(*(_DWORD *)(a1 + 80) + 4 * (*(_DWORD *)(a1 + 72) + 0x3FFFFFFF)));
    sub_C37C((void **)(*(_DWORD *)(a1 + 80) + 4 * (*(_DWORD *)(a1 + 72) + 0x3FFFFFFF)), a3);
    sub_CB04((_DWORD *)(*(_DWORD *)(a1 + 84) + 4 * (*(_DWORD *)(a1 + 72) + 0x3FFFFFFF)));
    sub_C37C((void **)(*(_DWORD *)(a1 + 84) + 4 * (*(_DWORD *)(a1 + 72) + 0x3FFFFFFF)), a4);
    sub_CB04((_DWORD *)(*(_DWORD *)(a1 + 88) + 4 * (*(_DWORD *)(a1 + 72) + 0x3FFFFFFF)));
    sub_C37C((void **)(*(_DWORD *)(a1 + 88) + 4 * (*(_DWORD *)(a1 + 72) + 0x3FFFFFFF)), s);
    return 0;
  }
  else
  {
    free(v9);
    free(v10);
    free(v11);
    free(v13);
    return 83;
  }
}


//----- (0000EE3C) --------------------------------------------------------
_DWORD *__fastcall lodepng_info_init(_DWORD *a1)
{
  _DWORD *result; // r0

  result = lodepng_color_mode_init(a1 + 3);
  a1[2] = 0;
  *a1 = 0;
  a1[1] = 0;
  a1[11] = 0;
  a1[14] = 0;
  a1[13] = 0;
  a1[12] = 0;
  a1[15] = 0;
  a1[16] = 0;
  a1[17] = 0;
  a1[18] = 0;
  a1[19] = 0;
  a1[20] = 0;
  a1[21] = 0;
  a1[22] = 0;
  a1[23] = 0;
  a1[30] = 0;
  a1[34] = 0;
  a1[35] = 0;
  a1[36] = 0;
  a1[37] = 0;
  a1[38] = 0;
  a1[39] = 0;
  return result;
}


//----- (0000EE84) --------------------------------------------------------
void __fastcall lodepng_info_cleanup(void **a1)
{
  lodepng_color_mode_cleanup(a1 + 3);
  lodepng_clear_text((int)a1);
  lodepng_clear_itext((int)a1);
  free(a1[34]);
  free(a1[35]);
  j_free(a1[36]);
}
// E320: using guessed type int __fastcall lodepng_color_mode_cleanup(_DWORD);


//----- (0000EEB6) --------------------------------------------------------
int __fastcall lodepng_info_copy(void **a1, int *a2)
{
  int v2; // r4
  _DWORD *v4; // r6
  int v5; // r0
  unsigned int v6; // r7
  int v7; // r6
  unsigned int v8; // r7
  int v9; // r7
  void *v10; // r0
  unsigned int i; // r3

  v2 = (int)a1;
  v4 = a1 + 3;
  lodepng_info_cleanup(a1);
  memcpy((void *)v2, a2, 0xA0u);
  lodepng_color_mode_init(v4);
  v5 = lodepng_color_mode_copy(v4, a2 + 3);
  if ( v5 )
    return v5;
  v6 = 0;
  *(_DWORD *)(v2 + 64) = 0;
  *(_DWORD *)(v2 + 68) = 0;
  *(_DWORD *)(v2 + 60) = 0;
  while ( v6 < a2[15] )
  {
    v5 = lodepng_add_text(v2, *(char **)(a2[16] + 4 * v6), *(char **)(a2[17] + 4 * v6));
    if ( v5 )
      return v5;
    ++v6;
  }
  v8 = 0;
  *(_DWORD *)(v2 + 76) = 0;
  *(_DWORD *)(v2 + 80) = 0;
  *(_DWORD *)(v2 + 84) = 0;
  *(_DWORD *)(v2 + 88) = 0;
  *(_DWORD *)(v2 + 72) = 0;
  while ( v8 < a2[18] )
  {
    v5 = lodepng_add_itext(
           v2,
           *(char **)(a2[19] + 4 * v8),
           *(char **)(a2[20] + 4 * v8),
           *(char **)(a2[21] + 4 * v8),
           *(char **)(a2[22] + 4 * v8));
    if ( v5 )
      return v5;
    ++v8;
  }
  *(_DWORD *)(v2 + 136) = 0;
  *(_DWORD *)(v2 + 140) = 0;
  v7 = 3;
  *(_DWORD *)(v2 + 144) = 0;
  *(_DWORD *)(v2 + 148) = 0;
  *(_DWORD *)(v2 + 152) = 0;
  *(_DWORD *)(v2 + 156) = 0;
  free(0);
  free(*(void **)(v2 + 140));
  free(*(void **)(v2 + 144));
  while ( 1 )
  {
    v9 = a2[37];
    *(_DWORD *)(v2 + 148) = v9;
    v10 = malloc(a2[37]);
    *(_DWORD *)(v2 + 136) = v10;
    if ( !v10 )
    {
      if ( v9 )
        break;
    }
    for ( i = 0; i < a2[37]; ++i )
      *(_BYTE *)(*(_DWORD *)(v2 + 136) + i) = *(_BYTE *)(a2[34] + i);
    --v7;
    ++a2;
    v2 += 4;
    if ( !v7 )
      return v7;
  }
  return 83;
}


//----- (0000EFC0) --------------------------------------------------------
void *__fastcall lodepng_info_swap(void *a1, void *a2)
{
  _BYTE v5[160]; // [sp+0h] [bp-A4h] BYREF

  memcpy(v5, a1, sizeof(v5));
  memcpy(a1, a2, 0xA0u);
  return memcpy(a2, v5, 0xA0u);
}


//----- (0000EFEC) --------------------------------------------------------
int __fastcall lodepng_convert(
        unsigned __int8 *a1,
        unsigned __int8 *a2,
        int *a3,
        unsigned int *a4,
        int a5,
        int a6,
        int a7)
{
  int v11; // r0
  unsigned int raw_size; // r0
  int i; // r3
  int v14; // r3
  int v15; // r11
  int v16; // r3
  int v17; // r8
  int v18; // r6
  unsigned __int8 *v19; // r6
  unsigned __int8 *v20; // r8
  int j; // r9
  __int16 v22; // r0
  __int16 v23; // r12
  __int16 v24; // r2
  __int16 v25; // r3
  int v26; // r1
  unsigned __int8 *v27; // r2
  int v28; // r0
  unsigned __int8 *v29; // r9
  int v30; // r6
  int v31; // r0
  unsigned __int8 v32; // r1
  unsigned __int8 v33; // r2
  unsigned __int8 v34; // r3
  unsigned __int8 v35; // r12
  unsigned int v36; // r2
  int v37; // r0
  unsigned int v38; // r1
  int v39; // r3
  unsigned __int8 *v40; // r1
  unsigned __int8 *v41; // r0
  int v42; // r0
  int v43; // r3
  unsigned __int8 *v44; // r3
  unsigned __int8 *v45; // r1
  int v47; // [sp+10h] [bp-64h]
  __int16 v48; // [sp+24h] [bp-50h] BYREF
  __int16 v49; // [sp+26h] [bp-4Eh] BYREF
  __int16 v50; // [sp+28h] [bp-4Ch] BYREF
  __int16 v51; // [sp+2Ah] [bp-4Ah] BYREF
  _DWORD v52[18]; // [sp+2Ch] [bp-48h] BYREF

  v11 = sub_C3D8(a3, a4);
  if ( v11 )
  {
    raw_size = lodepng_get_raw_size(a5, a6, a4);
    for ( i = 0; i != raw_size; ++i )
      a1[i] = a2[i];
    return 0;
  }
  if ( *a3 == 3 )
  {
    if ( 1 << a3[1] >= (unsigned int)a3[3] )
      v17 = a3[3];
    else
      v17 = 1 << a3[1];
    do
    {
      *(_DWORD *)((char *)v52 + v11) = 0;
      v11 += 4;
    }
    while ( v11 != 64 );
    v18 = 0;
    v52[16] = -1;
    while ( v18 != v17 )
    {
      sub_CB1C(
        v52,
        *(unsigned __int8 *)(a3[2] + 4 * v18),
        *(unsigned __int8 *)(a3[2] + 4 * v18 + 1),
        *(unsigned __int8 *)(a3[2] + 4 * v18 + 2),
        *(_BYTE *)(a3[2] + 4 * v18 + 3),
        v18);
      ++v18;
    }
  }
  v15 = a6 * a5;
  v16 = a3[1];
  if ( a4[1] == 16 && v16 == 16 )
  {
    v19 = a1;
    v20 = a1;
    for ( j = 0; ; ++j )
    {
      v14 = 0;
      if ( j == v15 )
        break;
      v48 = 0;
      v49 = 0;
      v50 = 0;
      v51 = 0;
      if ( a4[1] != 16 )
        goto LABEL_30;
      v14 = sub_C434(&v48, &v49, &v50, &v51, (int)a2, j, (int *)a4);
      if ( v14 )
        goto LABEL_67;
      v22 = v48;
      v23 = v49;
      v24 = v50;
      v25 = v51;
      if ( a3[1] != 16 )
      {
LABEL_30:
        v14 = 85;
        goto LABEL_67;
      }
      v26 = *a3;
      if ( *a3 )
      {
        switch ( v26 )
        {
          case 2:
            v20[1] = v48;
            *v20 = HIBYTE(v22);
            v20[3] = v23;
            v20[2] = HIBYTE(v23);
            v20[5] = v24;
            v20[4] = HIBYTE(v24);
            break;
          case 4:
            a1[4 * j] = HIBYTE(v48);
            v27 = &a1[4 * j];
            v27[1] = v22;
            v27[2] = HIBYTE(v25);
            v27[3] = v25;
            break;
          case 6:
            v19[5] = v50;
            *v19 = HIBYTE(v22);
            v19[1] = v22;
            v19[2] = HIBYTE(v23);
            v19[3] = v23;
            v19[4] = HIBYTE(v24);
            v19[6] = HIBYTE(v25);
            v19[7] = v25;
            break;
        }
      }
      else
      {
        a1[2 * j] = HIBYTE(v48);
        a1[2 * j + 1] = v22;
      }
      v19 += 8;
      v20 += 6;
    }
    goto LABEL_67;
  }
  if ( v16 != 8 )
  {
LABEL_37:
    v29 = a1;
    v30 = 0;
    LOBYTE(v48) = 0;
    LOBYTE(v49) = 0;
    LOBYTE(v50) = 0;
    LOBYTE(v51) = 0;
    while ( 1 )
    {
      if ( v30 == v15 )
      {
        v14 = 0;
        goto LABEL_67;
      }
      v14 = sub_B954(&v48, &v49, &v50, (char *)&v51, (int)a2, v30, (int *)a4, a7);
      if ( v14 )
        goto LABEL_67;
      v31 = *a3;
      v32 = v48;
      v33 = v49;
      v34 = v50;
      v35 = v51;
      if ( !*a3 )
        break;
      switch ( v31 )
      {
        case 2:
          if ( a3[1] == 8 )
          {
            a1[3 * v30] = v48;
            v40 = &a1[3 * v30];
            v40[1] = v33;
            v40[2] = v34;
          }
          else
          {
            v41 = &a1[6 * v30];
            v41[1] = v48;
            *v41 = v32;
            v41[3] = v33;
            v41[2] = v33;
            v41[5] = v34;
            v41[4] = v34;
          }
          break;
        case 3:
          v42 = sub_B90A((int)v52, (unsigned __int8)v48, (unsigned __int8)v49, (unsigned __int8)v50, v51);
          v39 = v42;
          if ( v42 < 0 )
          {
            v14 = 82;
            goto LABEL_67;
          }
          v36 = a3[1];
          if ( v36 == 8 )
          {
            a1[v30] = v42;
            break;
          }
          v37 = (int)a1;
          v38 = v30;
          goto LABEL_55;
        case 4:
          v43 = a3[1];
          if ( v43 == 8 )
          {
            a1[2 * v30] = v48;
            a1[2 * v30 + 1] = v35;
          }
          else if ( v43 == 16 )
          {
            v44 = &a1[4 * v30];
            v44[1] = v48;
            *v44 = v32;
            v44[3] = v35;
            v44[2] = v35;
          }
          break;
        case 6:
          if ( a3[1] == 8 )
          {
            a1[4 * v30] = v48;
            v45 = &a1[4 * v30];
            v45[1] = v33;
            v45[2] = v34;
            v45[3] = v35;
          }
          else
          {
            v29[1] = v48;
            *v29 = v32;
            v29[3] = v33;
            v29[2] = v33;
            v29[5] = v34;
            v29[4] = v34;
            v29[7] = v35;
            v29[6] = v35;
          }
          break;
      }
LABEL_70:
      ++v30;
      v29 += 8;
    }
    v36 = a3[1];
    if ( v36 == 8 )
    {
      a1[v30] = v48;
      goto LABEL_70;
    }
    if ( v36 == 16 )
    {
      a1[2 * v30 + 1] = v48;
      a1[2 * v30] = v32;
      goto LABEL_70;
    }
    v37 = (int)a1;
    v38 = v30;
    v39 = (unsigned __int8)(((1 << v36) - 1) & ((int)(unsigned __int8)v48 >> (8 - v36)));
LABEL_55:
    sub_B8C8(v37, v38, v36, v39);
    goto LABEL_70;
  }
  if ( *a3 != 6 )
  {
    if ( *a3 == 2 )
    {
      v28 = sub_BB68(a1, a6 * a5, 0, a2, (int *)a4, a7);
      goto LABEL_36;
    }
    goto LABEL_37;
  }
  v28 = sub_BB68(a1, a6 * a5, 1, a2, (int *)a4, a7);
LABEL_36:
  v14 = v28;
LABEL_67:
  if ( *a3 == 3 )
  {
    v47 = v14;
    sub_C34C((int)v52);
    return v47;
  }
  return v14;
}


//----- (0000F334) --------------------------------------------------------
int __fastcall getValueRequiredBits(unsigned int a1)
{
  if ( !a1 || a1 == 255 )
    return 1;
  if ( a1 % 0x11 )
    return 8;
  if ( a1 % 0x55 )
    return 4;
  return 2;
}


//----- (0000F364) --------------------------------------------------------
int __fastcall lodepng_auto_choose_color(int *a1, int a2, int a3, int a4, int *a5, int a6)
{
  int v9; // r3
  _BOOL4 have_alpha; // r0
  unsigned int *v11; // r3
  void *v12; // r0
  int bpp; // r0
  int v14; // r0
  int j; // r8
  int v16; // r6
  unsigned int v17; // r0
  int v18; // r10
  int v19; // r9
  unsigned int v20; // r3
  char *v21; // r2
  char *v22; // r3
  unsigned int ValueRequiredBits; // r0
  int i; // r8
  int v25; // r10
  int v26; // r9
  unsigned int v27; // r3
  char *v28; // r2
  char *v29; // r3
  int v30; // r3
  int v31; // r2
  int v32; // r3
  int v33; // r0
  int v34; // r1
  int v35; // r3
  int v36; // r2
  int v37; // r3
  int v38; // r3
  int v39; // r1
  int v40; // r2
  _BOOL4 v41; // r1
  unsigned int v42; // r8
  _BOOL4 v43; // r2
  unsigned int v44; // r2
  int v45; // r3
  int v46; // r0
  char *v47; // r7
  unsigned int k; // r9
  char v49; // r0
  int v50; // r0
  int v51; // r3
  int v52; // r3
  unsigned __int8 v53; // r1
  unsigned __int8 v54; // r2
  unsigned int m; // r3
  int v57; // [sp+14h] [bp-A0h]
  int v58; // [sp+14h] [bp-A0h]
  unsigned __int8 v59; // [sp+1Ch] [bp-98h]
  unsigned __int8 v60; // [sp+1Ch] [bp-98h]
  unsigned int v61; // [sp+20h] [bp-94h]
  _BOOL4 v62; // [sp+24h] [bp-90h]
  unsigned __int16 v64; // [sp+3Ch] [bp-78h] BYREF
  unsigned __int16 v65; // [sp+3Eh] [bp-76h] BYREF
  unsigned __int16 v66; // [sp+40h] [bp-74h] BYREF
  unsigned __int16 v67; // [sp+42h] [bp-72h] BYREF
  unsigned __int8 v68; // [sp+44h] [bp-70h]
  bool v69; // [sp+45h] [bp-6Fh]
  unsigned __int8 v70; // [sp+46h] [bp-6Eh]
  bool is_greyscale_type; // [sp+47h] [bp-6Dh]
  unsigned __int8 v72; // [sp+48h] [bp-6Ch]
  unsigned __int16 v73; // [sp+4Ah] [bp-6Ah]
  unsigned __int16 v74; // [sp+4Ch] [bp-68h]
  unsigned __int16 v75; // [sp+4Eh] [bp-66h]
  char v76; // [sp+50h] [bp-64h]
  bool v77; // [sp+51h] [bp-63h]
  unsigned int v78; // [sp+54h] [bp-60h] BYREF
  _DWORD v79[15]; // [sp+58h] [bp-5Ch] BYREF
  _DWORD v80[2]; // [sp+94h] [bp-20h] BYREF
  void *p; // [sp+9Ch] [bp-18h]
  unsigned int v82; // [sp+A0h] [bp-14h]
  char v83; // [sp+A4h] [bp-10h]
  unsigned int v84; // [sp+A8h] [bp-Ch]
  bool v85; // [sp+ACh] [bp-8h]

  if ( a6 == 3 )
  {
    v62 = 1;
  }
  else
  {
    if ( a6 == 1 && (*a1 & 0xFFFFFFFD) != 4 )
      return 0;
    v62 = a6 == 5;
  }
  v9 = a5[1];
  v68 = 0;
  v70 = 0;
  v69 = v9 != 16;
  v72 = 0;
  v76 = 0;
  is_greyscale_type = lodepng_is_greyscale_type(a5);
  have_alpha = lodepng_can_have_alpha(a5);
  v11 = &v78;
  v78 = 0;
  v77 = !have_alpha;
  do
  {
    v11[1] = 0;
    ++v11;
  }
  while ( v11 != v80 );
  v80[1] = -1;
  v12 = malloc(0x400u);
  v82 = 257;
  p = v12;
  if ( (unsigned int)lodepng_get_bpp((unsigned int *)a5) <= 8 )
  {
    bpp = lodepng_get_bpp((unsigned int *)a5);
    switch ( bpp )
    {
      case 1:
        v14 = 2;
        break;
      case 2:
        v14 = 4;
        break;
      case 4:
        v14 = 16;
        break;
      default:
        v14 = 256;
        break;
    }
    v82 = v14;
  }
  v83 = 0;
  v84 = 1;
  v85 = lodepng_get_bpp((unsigned int *)a5) == 1;
  if ( a6 == 1 )
  {
    is_greyscale_type = 1;
    v85 = 1;
    v83 = 1;
    v69 = 1;
  }
  v61 = a4 * a3;
  if ( a5[1] != 16 )
  {
    for ( i = 0; ; ++i )
    {
      if ( i == v61 )
        goto LABEL_84;
      LOBYTE(v67) = 0;
      LOBYTE(v64) = 0;
      LOBYTE(v65) = 0;
      LOBYTE(v66) = 0;
      v16 = sub_B954(&v64, &v65, &v66, (char *)&v67, a2, i, a5, 0);
      if ( v16 )
        goto LABEL_113;
      if ( !is_greyscale_type
        && ((unsigned __int8)v65 != (unsigned __int8)v64 || (unsigned __int8)v66 != (unsigned __int8)v65) )
      {
        v70 = 1;
        is_greyscale_type = 1;
        v85 = 1;
      }
      if ( !v77 && (unsigned __int8)v67 != 255 )
      {
        if ( (_BYTE)v67 )
          goto LABEL_97;
        if ( v72 )
        {
          if ( (unsigned __int8)v64 != v73 || (unsigned __int8)v65 != v74 || (unsigned __int8)v66 != v75 )
          {
LABEL_97:
            v76 = 1;
            v77 = 1;
            v85 = 1;
          }
        }
        else
        {
          v73 = (unsigned __int8)v64;
          v72 = 1;
          v74 = (unsigned __int8)v65;
          v75 = (unsigned __int8)v66;
        }
      }
      if ( !v77
        && (unsigned __int8)v67 == 255
        && v72
        && (unsigned __int8)v64 == v73
        && (unsigned __int8)v65 == v74
        && (unsigned __int8)v66 == v75 )
      {
        v76 = 1;
        v77 = 1;
        v85 = 1;
      }
      if ( !v85 )
      {
        ValueRequiredBits = getValueRequiredBits((unsigned __int8)v64);
        if ( ValueRequiredBits > v84 )
          v84 = ValueRequiredBits;
        if ( v84 > 7 )
          v85 = 1;
      }
      if ( !v83 )
      {
        v25 = (unsigned __int8)v64;
        v26 = (unsigned __int8)v65;
        v60 = v67;
        v58 = (unsigned __int8)v66;
        if ( sub_B90A((int)v79, (unsigned __int8)v64, (unsigned __int8)v65, (unsigned __int8)v66, v67) < 0 )
        {
          sub_CB1C(v79, v25, v26, v58, v60, v78);
          v27 = v78;
          if ( v78 <= 0xFF )
          {
            v28 = (char *)p;
            *((_BYTE *)p + 4 * v78) = v64;
            v29 = &v28[4 * v27];
            v29[1] = v65;
            v29[2] = v66;
            v29[3] = v67;
          }
          if ( ++v78 >= v82 )
            v83 = 1;
        }
      }
      if ( v77 && v83 && is_greyscale_type && v85 )
        goto LABEL_113;
    }
  }
  for ( j = 0; j != v61; ++j )
  {
    if ( a5[1] != 16 )
    {
      v16 = 85;
      goto LABEL_113;
    }
    v16 = sub_C434(&v64, &v65, &v66, (__int16 *)&v67, a2, j, a5);
    if ( v16 )
      goto LABEL_113;
    if ( !v69
      && ((unsigned __int8)v64 != HIBYTE(v64)
       || (unsigned __int8)v65 != HIBYTE(v65)
       || (unsigned __int8)v66 != HIBYTE(v66)) )
    {
      v68 = 1;
      v69 = 1;
      v85 = 1;
      v83 = 1;
    }
    if ( !is_greyscale_type && (v65 != v64 || v66 != v65) )
    {
      v70 = 1;
      is_greyscale_type = 1;
      v85 = 1;
    }
    if ( !v77 && v67 != 0xFFFF )
    {
      if ( !v67 && v61 > 0x10 && (!v72 || v64 == v73 && v65 == v74 && v66 == v75) )
      {
        if ( !v76 && !v72 )
        {
          v72 = 1;
          v73 = v64;
          v74 = v65;
          v75 = v66;
        }
      }
      else
      {
        v76 = 1;
        v77 = 1;
        v85 = 1;
      }
    }
    if ( !v77 && v67 == 0xFFFF && v72 && v64 == v73 && v65 == v74 && v66 == v75 )
    {
      v76 = 1;
      v77 = 1;
      v85 = 1;
    }
    if ( !v85 )
    {
      v17 = getValueRequiredBits(v64);
      if ( v17 > v84 )
        v84 = v17;
      if ( v84 > 7 )
        v85 = 1;
    }
    if ( !v83 )
    {
      v18 = (unsigned __int8)v64;
      v19 = (unsigned __int8)v65;
      v59 = v67;
      v57 = (unsigned __int8)v66;
      if ( sub_B90A((int)v79, (unsigned __int8)v64, (unsigned __int8)v65, (unsigned __int8)v66, v67) < 0 )
      {
        sub_CB1C(v79, v18, v19, v57, v59, v78);
        v20 = v78;
        if ( v78 <= 0xFF )
        {
          v21 = (char *)p;
          *((_BYTE *)p + 4 * v78) = v64;
          v22 = &v21[4 * v20];
          v22[1] = v65;
          v22[2] = v66;
          v22[3] = v67;
        }
        if ( ++v78 >= v82 )
          v83 = 1;
      }
    }
    if ( v77 && v83 && is_greyscale_type && v69 && v85 )
      goto LABEL_113;
  }
LABEL_84:
  v16 = 0;
LABEL_113:
  if ( (unsigned int)a5[1] <= 0xF )
  {
    v73 *= 257;
    v74 *= 257;
    v75 *= 257;
  }
  if ( v16 )
    goto LABEL_170;
  if ( a6 == 1 )
  {
    if ( v76 )
      goto LABEL_170;
    v30 = *a1 == 6 ? 2 : 0;
    *a1 = v30;
    if ( !v72 )
      goto LABEL_170;
    v31 = v75;
    v32 = (1 << a1[1]) - 1;
    v33 = (unsigned __int16)(v73 & v32);
    v34 = (unsigned __int16)(v74 & v32);
    a1[4] = 1;
    v35 = v32 & v31;
    a1[5] = v33;
    a1[6] = v34;
    goto LABEL_169;
  }
  v36 = v68;
  a1[4] = 0;
  v37 = v70;
  if ( v36 )
  {
    a1[1] = 16;
    if ( !v76 )
    {
      if ( v37 )
        v38 = 2;
      else
        v38 = 0;
      *a1 = v38;
      if ( !v72 )
        goto LABEL_170;
      v39 = v73;
      v40 = v74;
      v35 = v75;
      a1[4] = 1;
      a1[5] = v39;
      a1[6] = v40;
      goto LABEL_169;
    }
LABEL_160:
    if ( v37 )
      v51 = 6;
    else
      v51 = 4;
    *a1 = v51;
    goto LABEL_170;
  }
  if ( (unsigned int)(a6 - 4) <= 1 )
  {
    v41 = 0;
  }
  else
  {
    if ( v78 > 0x100 )
    {
      v41 = 0;
      goto LABEL_137;
    }
    v41 = v61 > 2 * v78;
  }
  if ( v78 > 2 )
  {
LABEL_137:
    if ( v78 <= 4 )
    {
      v42 = 2;
    }
    else if ( v78 <= 0x10 )
    {
      v42 = 4;
    }
    else
    {
      v42 = 8;
    }
    goto LABEL_143;
  }
  v42 = 1;
LABEL_143:
  if ( v70 )
    v43 = 0;
  else
    v43 = v76 == 0;
  if ( v41 )
  {
    if ( !v43 || v84 > v42 )
    {
      v47 = (char *)p;
      lodepng_palette_clear((int)a1);
      for ( k = 0; k < v78; ++k )
      {
        v49 = v47[3];
        v47 += 4;
        v50 = lodepng_palette_add((int)a1, *(v47 - 4), *(v47 - 3), *(v47 - 2), v49);
        if ( v50 )
          goto LABEL_158;
      }
      v50 = 0;
LABEL_158:
      v16 = v50;
      *a1 = 3;
      a1[1] = v42;
      goto LABEL_170;
    }
    goto LABEL_151;
  }
  if ( v43 )
  {
LABEL_151:
    v44 = v84;
    *a1 = 0;
    v45 = v72;
    v46 = v73;
    a1[1] = v44;
    if ( !v45 )
      goto LABEL_170;
    a1[4] = 1;
    v35 = ((1 << v44) - 1) & v46;
    a1[5] = v35;
    a1[6] = v35;
    goto LABEL_169;
  }
  a1[1] = 8;
  if ( v76 )
    goto LABEL_160;
  if ( v37 )
    v52 = 2;
  else
    v52 = 0;
  *a1 = v52;
  if ( !v72 )
    goto LABEL_170;
  v53 = v73;
  v54 = v74;
  v35 = (unsigned __int8)v75;
  a1[4] = 1;
  a1[5] = v53;
  a1[6] = v54;
LABEL_169:
  a1[7] = v35;
LABEL_170:
  sub_C34C((int)v79);
  free(p);
  if ( *a1 == 3 && a5[3] == a1[3] )
  {
    for ( m = 0; m < 4 * a5[3]; ++m )
      *(_BYTE *)(a1[2] + m) = *(_BYTE *)(a5[2] + m);
  }
  if ( v62 && (unsigned int)a1[1] <= 7 )
    a1[1] = 8;
  return v16;
}


//----- (0000FACA) --------------------------------------------------------
int __fastcall lodepng_inspect(
        unsigned int *a1,
        unsigned int *a2,
        LodePNGState *a3,
        const unsigned __int8 *a4,
        unsigned int a5)
{
  int result; // r0
  _DWORD *v10; // r6
  unsigned int v11; // r6

  if ( a5 && a4 )
  {
    if ( a5 > 0x1C )
    {
      v10 = (_DWORD *)((char *)a3 + 136);
      lodepng_info_cleanup((void **)a3 + 34);
      lodepng_info_init(v10);
      if ( *a4 == 137
        && a4[1] == 80
        && a4[2] == 78
        && a4[3] == 71
        && a4[4] == 13
        && a4[5] == 10
        && a4[6] == 26
        && a4[7] == 10 )
      {
        if ( a4[12] == 73 && a4[13] == 72 && a4[14] == 68 && a4[15] == 82 )
        {
          *a1 = lodepng_read32bitInt(a4 + 16);
          *a2 = lodepng_read32bitInt(a4 + 20);
          *((_DWORD *)a3 + 38) = a4[24];
          *((_DWORD *)a3 + 37) = a4[25];
          *((_DWORD *)a3 + 34) = a4[26];
          *((_DWORD *)a3 + 35) = a4[27];
          *((_DWORD *)a3 + 36) = a4[28];
          if ( *((_DWORD *)a3 + 5) || (v11 = lodepng_read32bitInt(a4 + 29), v11 == lodepng_crc32(a4 + 12, 0x11u)) )
          {
            if ( *((_DWORD *)a3 + 34) )
            {
              result = 32;
            }
            else if ( *((_DWORD *)a3 + 35) )
            {
              result = 33;
            }
            else if ( *((_DWORD *)a3 + 36) <= 1u )
            {
              result = sub_B884(*((_DWORD *)a3 + 37), *((_DWORD *)a3 + 38));
            }
            else
            {
              result = 34;
            }
          }
          else
          {
            result = 57;
          }
        }
        else
        {
          result = 29;
        }
      }
      else
      {
        result = 28;
      }
    }
    else
    {
      result = 27;
    }
  }
  else
  {
    result = 48;
  }
  *((_DWORD *)a3 + 74) = result;
  return result;
}


//----- (0000FBD0) --------------------------------------------------------
int __fastcall lodepng_decode(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned int *a3,
        LodePNGState *a4,
        unsigned __int8 *a5,
        unsigned int a6)
{
  int v7; // r0
  const unsigned __int8 *v8; // r7
  int v9; // r8
  unsigned int v10; // r5
  int v11; // r3
  int v12; // r0
  unsigned int v13; // r6
  const unsigned __int8 *v14; // r5
  unsigned int v15; // r11
  int v16; // r5
  void *v17; // r0
  unsigned int v18; // r6
  void *v19; // r0
  int v20; // r3
  unsigned int v21; // r1
  int v22; // r2
  int v23; // r3
  int i; // r3
  unsigned __int8 v25; // r1
  int v26; // r2
  int v27; // r3
  int v28; // r9
  int v29; // r3
  int v30; // r3
  unsigned int v31; // r3
  int v32; // r11
  int v33; // r3
  unsigned int v34; // r8
  char *v35; // r0
  int v36; // r3
  char *v37; // r11
  unsigned int v38; // r8
  char *v39; // r0
  char *v40; // r6
  const unsigned __int8 *v41; // r9
  int v42; // r3
  char *v43; // r9
  unsigned int v44; // r8
  char *v45; // r0
  char *v46; // r9
  int v47; // r2
  char *v48; // r0
  char *v49; // r10
  unsigned int v50; // r8
  char *v51; // r0
  char *v52; // r3
  int v53; // r11
  int v54; // r3
  char *v55; // r0
  int v56; // r1
  char *v57; // r8
  int v58; // r3
  char *v59; // r1
  char *v60; // r0
  int v61; // r2
  char *v62; // r2
  unsigned int v63; // r6
  int v64; // r0
  int v65; // r0
  int v66; // r1
  unsigned int raw_size; // r0
  int v68; // r0
  int v69; // r1
  unsigned int v70; // r0
  unsigned int v71; // r9
  unsigned int v72; // r10
  int v73; // r7
  int v74; // r10
  int v75; // r8
  unsigned int bpp; // r0
  unsigned int v77; // r5
  unsigned int v78; // r6
  unsigned int v79; // r9
  int v80; // r0
  int v81; // r6
  _BYTE *v82; // r12
  _BYTE *v83; // r12
  unsigned int v84; // r3
  unsigned int m; // r1
  unsigned int n; // r2
  unsigned int v87; // r0
  char *v88; // r9
  unsigned int v89; // r0
  char *v90; // lr
  unsigned int v91; // r6
  int v92; // r3
  unsigned int k; // r9
  int v94; // r7
  unsigned int v95; // r7
  int v96; // r0
  int result; // r0
  _DWORD *v98; // r0
  int *v99; // r1
  unsigned __int8 *v100; // r7
  size_t v101; // r0
  unsigned __int8 *v102; // r0
  unsigned int v103; // [sp+14h] [bp-198h]
  int v104; // [sp+1Ch] [bp-190h]
  int v105; // [sp+1Ch] [bp-190h]
  int v106; // [sp+1Ch] [bp-190h]
  char *v107; // [sp+20h] [bp-18Ch]
  char *v108; // [sp+20h] [bp-18Ch]
  _BYTE *v109; // [sp+20h] [bp-18Ch]
  _BYTE *v110; // [sp+20h] [bp-18Ch]
  int v111; // [sp+24h] [bp-188h]
  int v112; // [sp+28h] [bp-184h]
  unsigned int v113; // [sp+28h] [bp-184h]
  unsigned int j; // [sp+28h] [bp-184h]
  unsigned int *v115; // [sp+2Ch] [bp-180h]
  int v116; // [sp+30h] [bp-17Ch]
  int v117; // [sp+30h] [bp-17Ch]
  char *s; // [sp+48h] [bp-164h]
  int v122; // [sp+4Ch] [bp-160h]
  int v123; // [sp+50h] [bp-15Ch] BYREF
  unsigned __int8 *v124; // [sp+54h] [bp-158h] BYREF
  unsigned int v125; // [sp+58h] [bp-154h]
  int v126; // [sp+5Ch] [bp-150h]
  int v127; // [sp+60h] [bp-14Ch] BYREF
  unsigned int v128[2]; // [sp+64h] [bp-148h] BYREF
  unsigned __int8 *v129; // [sp+6Ch] [bp-140h] BYREF
  unsigned int v130; // [sp+70h] [bp-13Ch]
  int v131; // [sp+74h] [bp-138h]
  _BYTE v132[28]; // [sp+78h] [bp-134h] BYREF
  _BYTE v133[28]; // [sp+94h] [bp-118h] BYREF
  _BYTE v134[28]; // [sp+B0h] [bp-FCh] BYREF
  _BYTE v135[28]; // [sp+CCh] [bp-E0h] BYREF
  _DWORD v136[8]; // [sp+E8h] [bp-C4h] BYREF
  _DWORD v137[8]; // [sp+108h] [bp-A4h] BYREF
  _DWORD v138[8]; // [sp+128h] [bp-84h] BYREF
  int v139[8]; // [sp+148h] [bp-64h] BYREF
  int v140[8]; // [sp+168h] [bp-44h] BYREF
  char *v141; // [sp+188h] [bp-24h] BYREF
  unsigned int v142; // [sp+18Ch] [bp-20h] BYREF
  unsigned int v143; // [sp+190h] [bp-1Ch]

  *a1 = 0;
  v7 = lodepng_inspect(a2, a3, a4, a5, a6);
  *((_DWORD *)a4 + 74) = v7;
  if ( v7 )
    goto LABEL_235;
  v112 = 1;
  v8 = a5 + 33;
  v124 = 0;
  v126 = 0;
  v125 = 0;
  v116 = 0;
  while ( 1 )
  {
    v9 = *((_DWORD *)a4 + 74);
    if ( v9 )
      break;
    v10 = v8 - a5 + 12;
    if ( v10 > a6 || v8 < a5 )
    {
      v11 = 30;
LABEL_9:
      *((_DWORD *)a4 + 74) = v11;
      break;
    }
    v12 = lodepng_chunk_length(v8);
    v13 = v12;
    if ( v12 < 0 )
    {
      v11 = 63;
      goto LABEL_9;
    }
    if ( v10 + v12 > a6 || a5 > &v8[v12 + 12] )
    {
      v11 = 64;
      goto LABEL_9;
    }
    v14 = lodepng_chunk_data_const(v8);
    if ( lodepng_chunk_type_equals(v8, "IDAT") )
    {
      v15 = v125;
      if ( !sub_C5F0((int)&v124, v13 + v125) )
      {
        v11 = 83;
        goto LABEL_9;
      }
      while ( v9 != v13 )
      {
        v124[v15 + v9] = v14[v9];
        ++v9;
      }
      v112 = 3;
      goto LABEL_19;
    }
    if ( lodepng_chunk_type_equals(v8, "IEND") )
    {
      v16 = 1;
      goto LABEL_175;
    }
    if ( lodepng_chunk_type_equals(v8, "PLTE") )
    {
      v17 = (void *)*((_DWORD *)a4 + 39);
      if ( v17 )
        free(v17);
      *((_DWORD *)a4 + 40) = v13 / 3;
      v18 = v13 / 3;
      v19 = malloc(4 * v18);
      *((_DWORD *)a4 + 39) = v19;
      if ( v19 )
      {
        if ( v18 <= 0x100 )
          goto LABEL_26;
        v9 = 38;
      }
      else if ( v18 )
      {
        *((_DWORD *)a4 + 40) = 0;
        v9 = 83;
      }
      else
      {
LABEL_26:
        v20 = 1;
        v21 = 0;
        while ( 1 )
        {
          v14 += 3;
          if ( v21 >= *((_DWORD *)a4 + 40) )
            break;
          *(_BYTE *)(*((_DWORD *)a4 + 39) + 4 * v21++) = *(v14 - 3);
          *(_BYTE *)(*((_DWORD *)a4 + 39) + v20) = *(v14 - 2);
          *(_BYTE *)(*((_DWORD *)a4 + 39) + v20 + 1) = *(v14 - 1);
          v22 = *((_DWORD *)a4 + 39) + v20;
          v20 += 4;
          *(_BYTE *)(v22 + 2) = -1;
        }
      }
      *((_DWORD *)a4 + 74) = v9;
      if ( v9 )
        break;
      v112 = 2;
LABEL_19:
      v16 = 0;
      goto LABEL_175;
    }
    if ( lodepng_chunk_type_equals(v8, "tRNS") )
    {
      v23 = *((_DWORD *)a4 + 37);
      if ( v23 == 3 )
      {
        if ( v13 > *((_DWORD *)a4 + 40) )
        {
          v9 = 38;
        }
        else
        {
          for ( i = 0; i != v13; ++i )
          {
            v25 = v14[i];
            v26 = *((_DWORD *)a4 + 39) + 4 * i;
            *(_BYTE *)(v26 + 3) = v25;
          }
        }
      }
      else if ( v23 )
      {
        if ( v23 == 2 )
        {
          if ( v13 == 6 )
          {
            *((_DWORD *)a4 + 41) = 1;
            *((_DWORD *)a4 + 42) = v14[1] + (*v14 << 8);
            *((_DWORD *)a4 + 43) = v14[3] + (v14[2] << 8);
            *((_DWORD *)a4 + 44) = v14[5] + (v14[4] << 8);
          }
          else
          {
            v9 = 41;
          }
        }
        else
        {
          v9 = 42;
        }
      }
      else if ( v13 == 2 )
      {
        *((_DWORD *)a4 + 41) = 1;
        v27 = v14[1] + (*v14 << 8);
        *((_DWORD *)a4 + 44) = v27;
        *((_DWORD *)a4 + 43) = v27;
        *((_DWORD *)a4 + 42) = v27;
      }
      else
      {
        v9 = 30;
      }
      goto LABEL_165;
    }
    v28 = lodepng_chunk_type_equals(v8, "bKGD");
    if ( v28 )
    {
      v29 = *((_DWORD *)a4 + 37);
      if ( v29 == 3 )
      {
        if ( v13 != 1 )
        {
          v9 = 43;
          goto LABEL_165;
        }
        *((_DWORD *)a4 + 45) = 1;
        v30 = *v14;
      }
      else
      {
        v31 = v29 & 0xFFFFFFFB;
        if ( v31 )
        {
          if ( v31 == 2 )
          {
            if ( v13 == 6 )
            {
              *((_DWORD *)a4 + 45) = 1;
              *((_DWORD *)a4 + 46) = v14[1] + (*v14 << 8);
              *((_DWORD *)a4 + 47) = v14[3] + (v14[2] << 8);
              *((_DWORD *)a4 + 48) = v14[5] + (v14[4] << 8);
            }
            else
            {
              v9 = 45;
            }
          }
LABEL_165:
          *((_DWORD *)a4 + 74) = v9;
          if ( v9 )
            break;
          goto LABEL_19;
        }
        if ( v13 != 2 )
        {
          v9 = 44;
          goto LABEL_165;
        }
        *((_DWORD *)a4 + 45) = 1;
        v30 = v14[1] + (*v14 << 8);
      }
      *((_DWORD *)a4 + 48) = v30;
      *((_DWORD *)a4 + 47) = v30;
      *((_DWORD *)a4 + 46) = v30;
      goto LABEL_165;
    }
    v32 = lodepng_chunk_type_equals(v8, "tEXt");
    if ( v32 )
    {
      v33 = *((_DWORD *)a4 + 8);
      if ( !v33 )
        goto LABEL_174;
      while ( v28 != v13 && v14[v28] )
        ++v28;
      if ( (unsigned int)(v28 - 1) > 0x4E )
      {
        v40 = 0;
        v16 = 89;
        v37 = 0;
      }
      else
      {
        v34 = v28 + 1;
        v35 = (char *)malloc(v28 + 1);
        v36 = 0;
        v37 = v35;
        if ( v35 )
        {
          v35[v28] = 0;
          do
          {
            v35[v36] = v14[v36];
            ++v36;
          }
          while ( v36 != v28 );
          if ( v13 < v34 )
            v38 = 0;
          else
            v38 = v13 - v34;
          v39 = (char *)malloc(v38 + 1);
          v40 = v39;
          if ( v39 )
          {
            v41 = &v14[v28];
            v42 = 0;
            v39[v38] = 0;
            while ( v42 != v38 )
            {
              v39[v42] = v41[v42 + 1];
              ++v42;
            }
            v16 = lodepng_add_text((int)a4 + 136, v37, v39);
            goto LABEL_85;
          }
        }
        else
        {
          v40 = 0;
        }
        v16 = 83;
      }
LABEL_85:
      free(v37);
      free(v40);
      goto LABEL_155;
    }
    v43 = (char *)lodepng_chunk_type_equals(v8, "zTXt");
    if ( !v43 )
    {
      if ( !lodepng_chunk_type_equals(v8, "iTXt") )
      {
        if ( lodepng_chunk_type_equals(v8, "tIME") )
        {
          if ( v13 == 7 )
          {
            *((_DWORD *)a4 + 57) = 1;
            *((_DWORD *)a4 + 58) = v14[1] + (*v14 << 8);
            *((_DWORD *)a4 + 59) = v14[2];
            *((_DWORD *)a4 + 60) = v14[3];
            *((_DWORD *)a4 + 61) = v14[4];
            *((_DWORD *)a4 + 62) = v14[5];
            *((_DWORD *)a4 + 63) = v14[6];
          }
          else
          {
            v9 = 73;
          }
        }
        else
        {
          if ( !lodepng_chunk_type_equals(v8, "pHYs") )
          {
            if ( !lodepng_chunk_ancillary(v8) )
            {
              v11 = 69;
              goto LABEL_9;
            }
            v33 = *((_DWORD *)a4 + 9);
            if ( !v33 )
            {
              v116 = 1;
LABEL_174:
              v16 = v33;
              goto LABEL_175;
            }
            v64 = lodepng_chunk_append((unsigned __int8 **)a4 + v112 + 67, (unsigned int *)a4 + v112 + 70, v8);
            *((_DWORD *)a4 + 74) = v64;
            if ( v64 )
              break;
            v116 = 1;
            goto LABEL_19;
          }
          if ( v13 == 9 )
          {
            *((_DWORD *)a4 + 64) = 1;
            *((_DWORD *)a4 + 65) = v14[3] + ((v14[2] + ((v14[1] + (*v14 << 8)) << 8)) << 8);
            *((_DWORD *)a4 + 66) = v14[7] + ((v14[6] + ((v14[5] + (v14[4] << 8)) << 8)) << 8);
            *((_DWORD *)a4 + 67) = v14[8];
          }
          else
          {
            v9 = 74;
          }
        }
        goto LABEL_165;
      }
      v33 = *((_DWORD *)a4 + 8);
      if ( !v33 )
        goto LABEL_174;
      v141 = 0;
      v143 = 0;
      v49 = 0;
      v142 = 0;
      if ( v13 > 4 )
      {
        do
        {
          if ( !v49[(_DWORD)v14] )
            break;
          ++v49;
        }
        while ( v49 != (char *)v13 );
        v50 = (unsigned int)(v49 + 3);
        if ( (unsigned int)(v49 + 3) >= v13 )
        {
          v49 = 0;
          v16 = 75;
          v57 = 0;
          v43 = 0;
          goto LABEL_153;
        }
        if ( (unsigned int)(v49 - 1) > 0x4E )
        {
          v49 = 0;
          v16 = 89;
          v57 = 0;
          v43 = 0;
          goto LABEL_153;
        }
        v51 = (char *)malloc((size_t)(v49 + 1));
        v52 = 0;
        v43 = v51;
        if ( v51 )
        {
          v49[(_DWORD)v51] = 0;
          do
          {
            v52[(_DWORD)v51] = v52[(_DWORD)v14];
            ++v52;
          }
          while ( v52 != v49 );
          v53 = (unsigned __int8)v49[(_DWORD)v14 + 1];
          v54 = (unsigned __int8)v49[(_DWORD)v14 + 2];
          if ( v49[(_DWORD)v14 + 2] )
          {
            v49 = 0;
            v16 = 72;
            v57 = 0;
            goto LABEL_153;
          }
          do
          {
            if ( !v14[v50] )
              break;
            ++v50;
            ++v54;
          }
          while ( v50 < v13 );
          v104 = v54;
          v55 = (char *)malloc(v54 + 1);
          v56 = 0;
          v57 = v55;
          if ( v55 )
          {
            v55[v104] = 0;
            while ( v56 != v104 )
            {
              v55[v56] = v49[(_DWORD)v14 + 3 + v56];
              ++v56;
            }
            v58 = 0;
            v59 = &v49[v56 + 4];
            while ( (unsigned int)&v59[v58] < v13 && v59[(_DWORD)v14 + v58] )
              ++v58;
            v107 = v59;
            v105 = v58;
            v60 = (char *)malloc(v58 + 1);
            v49 = v60;
            if ( v60 )
            {
              v61 = 0;
              v60[v105] = 0;
              while ( v61 != v105 )
              {
                v60[v61] = v107[(_DWORD)v14 + v61];
                ++v61;
              }
              v62 = &v107[v61 + 1];
              if ( v13 < (unsigned int)v62 )
                v63 = 0;
              else
                v63 = v13 - (_DWORD)v62;
              if ( v53 )
              {
                v16 = sub_E004((int *)&v141, &v142, (unsigned __int8 *)&v14[(_DWORD)v62], v63, (_DWORD *)a4 + 1);
                if ( !v16 )
                {
                  if ( v143 < v142 )
                    v143 = v142;
                  sub_C612(&v141, 0);
LABEL_145:
                  v16 = lodepng_add_itext((int)a4 + 136, v43, v57, v49, v141);
                }
LABEL_153:
                free(v43);
                free(v57);
                v48 = v49;
                goto LABEL_154;
              }
              v108 = v62;
              if ( sub_C5F0((int)&v141, v63 + 1) )
              {
                v141[v63] = 0;
                while ( v53 != v63 )
                {
                  v141[v53] = v14[(_DWORD)v108 + v53];
                  ++v53;
                }
                goto LABEL_145;
              }
            }
          }
          else
          {
            v49 = 0;
          }
        }
        else
        {
          v49 = 0;
          v57 = 0;
        }
        v16 = 83;
        goto LABEL_153;
      }
      v57 = 0;
      v16 = 30;
      goto LABEL_153;
    }
    v33 = *((_DWORD *)a4 + 8);
    if ( !v33 )
      goto LABEL_174;
    v141 = 0;
    v143 = 0;
    v142 = 0;
    while ( v32 != v13 && v14[v32] )
      ++v32;
    v44 = v32 + 2;
    if ( v32 + 2 >= v13 )
    {
      v46 = 0;
LABEL_106:
      v16 = 75;
      goto LABEL_107;
    }
    if ( (unsigned int)(v32 - 1) > 0x4E )
    {
      v46 = 0;
      v16 = 89;
    }
    else
    {
      v45 = (char *)malloc(v32 + 1);
      v46 = v45;
      if ( v45 )
      {
        v47 = 0;
        v45[v32] = 0;
        do
        {
          v45[v47] = v14[v47];
          ++v47;
        }
        while ( v47 != v32 );
        if ( !v14[v32 + 1] )
        {
          if ( v44 <= v13 )
          {
            v16 = sub_E004((int *)&v141, &v142, (unsigned __int8 *)&v14[v44], v13 - v44, (_DWORD *)a4 + 1);
            if ( !v16 )
            {
              sub_C612(&v141, 0);
              v16 = lodepng_add_text((int)a4 + 136, v46, v141);
            }
            goto LABEL_107;
          }
          goto LABEL_106;
        }
        v16 = 72;
      }
      else
      {
        v16 = 83;
      }
    }
LABEL_107:
    v48 = v46;
LABEL_154:
    free(v48);
    sub_C368((int)&v141);
LABEL_155:
    *((_DWORD *)a4 + 74) = v16;
    if ( v16 )
      break;
LABEL_175:
    if ( !*((_DWORD *)a4 + 5) && !v116 && lodepng_chunk_check_crc(v8) )
    {
      v11 = 57;
      goto LABEL_9;
    }
    if ( v16 )
      break;
    v8 = lodepng_chunk_next_const(v8);
  }
  if ( !*((_DWORD *)a4 + 74) )
  {
    v127 = 0;
    v65 = *a2;
    v66 = *a3;
    v128[1] = 0;
    v128[0] = 0;
    raw_size = lodepng_get_raw_size(v65, v66, (unsigned int *)a4 + 37);
    if ( !sub_C5F0((int)&v127, *a3 + raw_size) )
      *((_DWORD *)a4 + 74) = 83;
    if ( !*((_DWORD *)a4 + 74) )
      *((_DWORD *)a4 + 74) = sub_E004(&v127, v128, v124, v125, (_DWORD *)a4 + 1);
    if ( !*((_DWORD *)a4 + 74) )
    {
      v129 = 0;
      v68 = *a2;
      v69 = *a3;
      v131 = 0;
      v130 = 0;
      v70 = lodepng_get_raw_size(v68, v69, (unsigned int *)a4 + 37);
      v71 = v130;
      v72 = v70;
      if ( sub_C5F0((int)&v129, v70) )
      {
        while ( v71 < v72 )
          v129[v71++] = 0;
      }
      else
      {
        *((_DWORD *)a4 + 74) = 83;
      }
      v111 = *((_DWORD *)a4 + 74);
      if ( !v111 )
      {
        v115 = (unsigned int *)v129;
        v73 = *a2;
        v74 = v127;
        v75 = *a3;
        bpp = lodepng_get_bpp((unsigned int *)a4 + 37);
        v77 = bpp;
        if ( bpp )
        {
          if ( *((_DWORD *)a4 + 36) )
          {
            sub_BE74((int)v132, (int)v133, v136, v137, v138, v73, v75, bpp);
            v81 = 0;
            v82 = v133;
            while ( 1 )
            {
              v109 = v82;
              v80 = sub_BF58(v137[v81] + v74, v136[v81] + v74, *(_DWORD *)&v132[v81 * 4], *(_DWORD *)&v82[v81 * 4], v77);
              v82 = v109;
              if ( v80 )
                break;
              if ( v77 <= 7 )
              {
                sub_C0D2(
                  (unsigned int *)(v138[v81] + v74),
                  v137[v81] + v74,
                  *(_DWORD *)&v132[v81 * 4] * v77,
                  (*(_DWORD *)&v132[v81 * 4] * v77 + 7) & 0xFFFFFFF8,
                  *(_DWORD *)&v109[v81 * 4]);
                v82 = v109;
              }
              if ( ++v81 == 7 )
              {
                sub_BE74((int)v134, (int)v135, v139, v140, &v141, v73, v75, v77);
                v83 = v134;
                if ( v77 <= 7 )
                {
                  v91 = 0;
                  v122 = v73 * v77;
                  do
                  {
                    s = (char *)(*(_DWORD *)&v83[v91] * v77);
                    v92 = 0;
                    for ( j = 0; j < *(_DWORD *)&v135[v91]; ++j )
                    {
                      v117 = 0;
                      for ( k = 0; k < *(_DWORD *)&v83[v91]; ++k )
                      {
                        v94 = *(_DWORD *)((char *)&unk_15B84 + v91);
                        v123 = v92 + 8 * (_DWORD)(&v141)[v91 / 4] + v117;
                        v95 = (*(_DWORD *)((char *)&unk_15BBC + v91) + *(_DWORD *)((char *)&unk_15BA0 + v91) * j) * v122
                            + v77 * (v94 + *(_DWORD *)&asc_15B68[v91] * k);
                        v103 = v95 + v77;
                        do
                        {
                          v106 = v92;
                          v110 = v83;
                          v96 = sub_B80A(&v123, v74);
                          v92 = v106;
                          v83 = v110;
                          if ( v96 )
                            *((_BYTE *)v115 + (v95 >> 3)) |= (_BYTE)v96 << (~(_BYTE)v95 & 7);
                          ++v95;
                        }
                        while ( v95 != v103 );
                        v117 += v77;
                      }
                      v92 += (int)s;
                    }
                    v91 += 4;
                  }
                  while ( v91 != 28 );
                }
                else
                {
                  v84 = 0;
                  v113 = v77 >> 3;
                  do
                  {
                    for ( m = 0; m < *(_DWORD *)&v135[v84]; ++m )
                    {
                      for ( n = 0; ; ++n )
                      {
                        v87 = *(_DWORD *)&v134[v84];
                        if ( n >= v87 )
                          break;
                        v88 = &(&v141)[v84 / 4][v113 * (n + v87 * m) + v74];
                        v89 = 0;
                        v90 = (char *)v115
                            + v113
                            * (*(_DWORD *)((char *)&unk_15B84 + v84)
                             + v73 * (*(_DWORD *)((char *)&unk_15BBC + v84) + *(_DWORD *)((char *)&unk_15BA0 + v84) * m)
                             + *(_DWORD *)&asc_15B68[v84] * n);
                        do
                        {
                          v90[v89] = v88[v89];
                          ++v89;
                        }
                        while ( v89 < v113 );
                      }
                    }
                    v84 += 4;
                  }
                  while ( v84 != 28 );
                }
                goto LABEL_231;
              }
            }
          }
          else if ( bpp > 7 || (v78 = v73 * bpp, v79 = (v73 * bpp + 7) & 0xFFFFFFF8, v73 * bpp == v79) )
          {
            v80 = sub_BF58((int)v115, v74, v73, v75, bpp);
          }
          else
          {
            v80 = sub_BF58(v74, v74, v73, v75, bpp);
            if ( !v80 )
            {
              sub_C0D2(v115, v74, v78, v79, v75);
              goto LABEL_231;
            }
          }
          v111 = v80;
        }
        else
        {
          v111 = 31;
        }
LABEL_231:
        *((_DWORD *)a4 + 74) = v111;
      }
      *a1 = v129;
    }
    sub_C368((int)&v127);
  }
  sub_C368((int)&v124);
LABEL_235:
  result = *((_DWORD *)a4 + 74);
  if ( !result )
  {
    v98 = (_DWORD *)((char *)a4 + 104);
    v99 = (int *)((char *)a4 + 148);
    if ( *((_DWORD *)a4 + 7) )
    {
      if ( sub_C3D8(v98, v99) )
        return *((_DWORD *)a4 + 74);
      v100 = *a1;
      if ( (*((_DWORD *)a4 + 26) & 0xFFFFFFFB) == 2 || *((_DWORD *)a4 + 27) == 8 )
      {
        v101 = lodepng_get_raw_size(*a2, *a3, (unsigned int *)a4 + 26);
        v102 = (unsigned __int8 *)malloc(v101);
        *a1 = v102;
        if ( v102 )
          *((_DWORD *)a4 + 74) = lodepng_convert(
                                   v102,
                                   v100,
                                   (int *)a4 + 26,
                                   (unsigned int *)a4 + 37,
                                   *a2,
                                   *a3,
                                   *((_DWORD *)a4 + 6));
        else
          *((_DWORD *)a4 + 74) = 83;
        free(v100);
        return *((_DWORD *)a4 + 74);
      }
      else
      {
        return 56;
      }
    }
    else
    {
      result = lodepng_color_mode_copy(v98, v99);
      *((_DWORD *)a4 + 74) = result;
      if ( !result )
        return *((_DWORD *)a4 + 74);
    }
  }
  return result;
}


//----- (00010700) --------------------------------------------------------
_DWORD *__fastcall lodepng_decoder_settings_init(_DWORD *result)
{
  result[6] = 1;
  result[7] = 1;
  result[8] = 0;
  result[4] = 0;
  result[5] = 0;
  return lodepng_decompress_settings_init(result);
}


//----- (00010712) --------------------------------------------------------
void __fastcall lodepng_state_cleanup(void **a1)
{
  lodepng_color_mode_cleanup(a1 + 26);
  lodepng_info_cleanup(a1 + 34);
}
// E320: using guessed type int __fastcall lodepng_color_mode_cleanup(_DWORD);


//----- (00010728) --------------------------------------------------------
// Alternative name is '_ZN7lodepng5StateD1Ev'
void __fastcall lodepng::State::~State(void **this)
{
  *this = &off_17C68;
  lodepng_state_cleanup(this);
  *this = &off_17C58;
}
// 17C58: using guessed type _UNKNOWN *off_17C58;
// 17C68: using guessed type _UNKNOWN *;


//----- (00010750) --------------------------------------------------------
void __fastcall lodepng::State::~State(void **this)
{
  lodepng::State::~State(this);
  operator delete(this);
}


//----- (00010762) --------------------------------------------------------
int __fastcall lodepng_state_copy(void **a1, const LodePNGState *a2)
{
  void **v3; // r5
  void *v5; // r0
  void *v6; // r1
  void *v7; // r2
  void *v8; // r3
  void *v9; // r1
  void *v10; // r2
  void *v11; // r3
  void *v12; // r1
  void *v13; // r2
  void *v14; // r3
  void *v15; // r1
  void *v16; // r2
  void *v17; // r3
  void *v18; // r1
  void *v19; // r2
  void *v20; // r3
  void *v21; // r1
  void *v22; // r2
  void *v23; // r3
  void *v24; // r1
  void *v25; // r2
  void *v26; // r3
  void *v27; // r1
  void *v28; // r2
  void *v29; // r3
  int result; // r0

  v3 = (void **)((char *)a2 + 4);
  lodepng_state_cleanup(a1);
  v5 = *v3;
  v6 = v3[1];
  v7 = v3[2];
  v8 = v3[3];
  v3 += 4;
  a1[1] = v5;
  a1[2] = v6;
  a1[3] = v7;
  a1[4] = v8;
  v9 = v3[1];
  v10 = v3[2];
  v11 = v3[3];
  a1[5] = *v3;
  a1[6] = v9;
  a1[7] = v10;
  a1[8] = v11;
  a1[9] = v3[4];
  v12 = (void *)*((_DWORD *)a2 + 11);
  v13 = (void *)*((_DWORD *)a2 + 12);
  v14 = (void *)*((_DWORD *)a2 + 13);
  a1[10] = (void *)*((_DWORD *)a2 + 10);
  a1[11] = v12;
  a1[12] = v13;
  a1[13] = v14;
  v15 = (void *)*((_DWORD *)a2 + 15);
  v16 = (void *)*((_DWORD *)a2 + 16);
  v17 = (void *)*((_DWORD *)a2 + 17);
  a1[14] = (void *)*((_DWORD *)a2 + 14);
  a1[15] = v15;
  a1[16] = v16;
  a1[17] = v17;
  v18 = (void *)*((_DWORD *)a2 + 19);
  v19 = (void *)*((_DWORD *)a2 + 20);
  v20 = (void *)*((_DWORD *)a2 + 21);
  a1[18] = (void *)*((_DWORD *)a2 + 18);
  a1[19] = v18;
  a1[20] = v19;
  a1[21] = v20;
  v21 = (void *)*((_DWORD *)a2 + 23);
  v22 = (void *)*((_DWORD *)a2 + 24);
  v23 = (void *)*((_DWORD *)a2 + 25);
  a1[22] = (void *)*((_DWORD *)a2 + 22);
  a1[23] = v21;
  a1[24] = v22;
  a1[25] = v23;
  v24 = (void *)*((_DWORD *)a2 + 27);
  v25 = (void *)*((_DWORD *)a2 + 28);
  v26 = (void *)*((_DWORD *)a2 + 29);
  a1[26] = (void *)*((_DWORD *)a2 + 26);
  a1[27] = v24;
  a1[28] = v25;
  a1[29] = v26;
  v27 = (void *)*((_DWORD *)a2 + 31);
  v28 = (void *)*((_DWORD *)a2 + 32);
  v29 = (void *)*((_DWORD *)a2 + 33);
  a1[30] = (void *)*((_DWORD *)a2 + 30);
  a1[31] = v27;
  a1[32] = v28;
  a1[33] = v29;
  memcpy(a1 + 34, (char *)a2 + 136, 0xA4u);
  lodepng_color_mode_init(a1 + 26);
  lodepng_info_init(a1 + 34);
  result = lodepng_color_mode_copy(a1 + 26, (int *)a2 + 26);
  a1[74] = (void *)result;
  if ( !result )
  {
    result = lodepng_info_copy(a1 + 34, (int *)a2 + 34);
    a1[74] = (void *)result;
  }
  return result;
}


//----- (000107F8) --------------------------------------------------------
int __fastcall lodepng_encode(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned __int8 *a3,
        unsigned int a4,
        unsigned int a5,
        LodePNGState *a6)
{
  int result; // r0
  int v9; // r3
  size_t v10; // r10
  unsigned __int8 *v11; // r0
  unsigned __int8 *v12; // r9
  int v13; // r9
  char v14; // r10
  int v15; // r0
  int v16; // r1
  int v17; // r12
  int v18; // lr
  int v19; // r3
  unsigned int i; // r2
  unsigned __int8 *v21; // r7
  unsigned __int8 *v22; // r7
  char v23; // r1
  int v24; // r7
  int v25; // r0
  unsigned __int8 *v26; // r0
  unsigned __int8 *v27; // r7
  unsigned int v28; // r2
  unsigned __int8 v29; // r3
  unsigned int j; // r7
  const char *v31; // r10
  int v32; // r3
  size_t v33; // r0
  int v34; // r2
  unsigned int k; // r10
  char v36; // r1
  int v37; // r7
  int v38; // r8
  unsigned int m; // r8
  const char *v40; // r10
  int v41; // r3
  char *v42; // r9
  size_t v43; // r0
  int v44; // r2
  int v45; // r2
  int v46; // r10
  char v47; // r1
  int v48; // t1
  char *n; // r3
  char *v50; // r3
  int v51; // t1
  char v52; // r1
  char *v53; // r9
  int v54; // r10
  unsigned int ii; // r9
  char v56; // r1
  char v57; // r1
  int v58; // t1
  int v59; // r0
  char v60; // [sp+10h] [bp-58h]
  char v61; // [sp+10h] [bp-58h]
  char v62; // [sp+10h] [bp-58h]
  char *v63; // [sp+10h] [bp-58h]
  char v64; // [sp+14h] [bp-54h]
  int v65; // [sp+14h] [bp-54h]
  int v66; // [sp+14h] [bp-54h]
  unsigned int v67; // [sp+18h] [bp-50h]
  char *v68; // [sp+18h] [bp-50h]
  int v69; // [sp+18h] [bp-50h]
  int v70; // [sp+18h] [bp-50h]
  int *v71; // [sp+1Ch] [bp-4Ch]
  unsigned int v72; // [sp+20h] [bp-48h]
  int v73; // [sp+20h] [bp-48h]
  char *v74; // [sp+24h] [bp-44h]
  unsigned int v77; // [sp+30h] [bp-38h]
  void *p; // [sp+3Ch] [bp-2Ch] BYREF
  size_t v79; // [sp+40h] [bp-28h] BYREF
  unsigned __int8 *v80; // [sp+44h] [bp-24h] BYREF
  unsigned int v81; // [sp+48h] [bp-20h]
  int v82; // [sp+4Ch] [bp-1Ch]
  unsigned __int8 *v83; // [sp+50h] [bp-18h] BYREF
  unsigned int v84; // [sp+54h] [bp-14h]
  int v85; // [sp+58h] [bp-10h]
  unsigned __int8 *v86; // [sp+5Ch] [bp-Ch] BYREF
  unsigned int v87; // [sp+60h] [bp-8h] BYREF
  int v88; // [sp+64h] [bp-4h]
  void *v89[2]; // [sp+68h] [bp+0h] BYREF
  int v90; // [sp+70h] [bp+8h]
  int v91; // [sp+74h] [bp+Ch] BYREF
  int v92; // [sp+78h] [bp+10h]
  int v93; // [sp+7Ch] [bp+14h]
  unsigned int v94; // [sp+80h] [bp+18h]
  int v95; // [sp+84h] [bp+1Ch]
  int v96; // [sp+94h] [bp+2Ch]
  char v97; // [sp+98h] [bp+30h]
  char v98; // [sp+99h] [bp+31h]
  char v99; // [sp+9Ch] [bp+34h]
  char v100; // [sp+9Dh] [bp+35h]
  char v101; // [sp+A0h] [bp+38h]
  char v102; // [sp+A1h] [bp+39h]
  unsigned int v103; // [sp+A4h] [bp+3Ch]
  int v104; // [sp+A8h] [bp+40h]
  int v105; // [sp+ACh] [bp+44h]
  unsigned int v106; // [sp+B0h] [bp+48h]
  int v107; // [sp+B4h] [bp+4Ch]
  int v108; // [sp+B8h] [bp+50h]
  int v109; // [sp+BCh] [bp+54h]
  int v110; // [sp+C0h] [bp+58h]
  int v111; // [sp+C4h] [bp+5Ch]
  unsigned int v112; // [sp+C8h] [bp+60h]
  int v113; // [sp+CCh] [bp+64h]
  int v114; // [sp+D0h] [bp+68h]
  int v115; // [sp+D4h] [bp+6Ch]
  int v116; // [sp+D8h] [bp+70h]
  int v117; // [sp+DCh] [bp+74h]
  int v118; // [sp+E0h] [bp+78h]
  unsigned int v119; // [sp+E4h] [bp+7Ch]
  unsigned int v120; // [sp+E8h] [bp+80h]
  char v121; // [sp+ECh] [bp+84h]
  unsigned __int8 *v122; // [sp+F0h] [bp+88h]
  unsigned __int8 *v123; // [sp+F4h] [bp+8Ch]
  unsigned __int8 *v124; // [sp+F8h] [bp+90h]
  unsigned int v125; // [sp+FCh] [bp+94h]
  unsigned int v126; // [sp+100h] [bp+98h]
  unsigned int v127; // [sp+104h] [bp+9Ch]

  *a1 = 0;
  *a2 = 0;
  *((_DWORD *)a6 + 74) = 0;
  p = 0;
  v79 = 0;
  lodepng_info_init(v89);
  lodepng_info_copy(v89, (int *)a6 + 34);
  if ( (v91 == 3 || *((_DWORD *)a6 + 23)) && v94 - 1 > 0xFF )
  {
    result = 68;
LABEL_14:
    *((_DWORD *)a6 + 74) = result;
    return result;
  }
  v9 = *((_DWORD *)a6 + 19);
  if ( v9 )
    *((_DWORD *)a6 + 74) = lodepng_auto_choose_color(&v91, (int)a3, a4, a5, (int *)a6 + 26, v9);
  result = *((_DWORD *)a6 + 74);
  if ( !result )
  {
    if ( *((_DWORD *)a6 + 12) > 0x8000u )
    {
      result = 60;
      goto LABEL_14;
    }
    if ( *((_DWORD *)a6 + 10) > 2u )
    {
      result = 61;
      goto LABEL_14;
    }
    if ( *((_DWORD *)a6 + 36) > 1u )
    {
      result = 71;
      goto LABEL_14;
    }
    result = sub_B884(v91, v92);
    *((_DWORD *)a6 + 74) = result;
    if ( !result )
    {
      result = sub_B884(*((_DWORD *)a6 + 26), *((_DWORD *)a6 + 27));
      *((_DWORD *)a6 + 74) = result;
      if ( !result )
      {
        if ( sub_C3D8((_DWORD *)a6 + 26, &v91) )
        {
          sub_E8AC((_BYTE **)&p, &v79, (int)a3, a4, a5, (int)v89, (int *)a6 + 10);
        }
        else
        {
          v10 = (lodepng_get_bpp((unsigned int *)&v91) * a5 * a4 + 7) >> 3;
          v11 = (unsigned __int8 *)malloc(v10);
          v12 = v11;
          if ( !v11 && v10 )
            *((_DWORD *)a6 + 74) = 83;
          if ( !*((_DWORD *)a6 + 74) )
            *((_DWORD *)a6 + 74) = lodepng_convert(v11, a3, &v91, (unsigned int *)a6 + 26, a4, a5, 0);
          if ( !*((_DWORD *)a6 + 74) )
            sub_E8AC((_BYTE **)&p, &v79, (int)v12, a4, a5, (int)v89, (int *)a6 + 10);
          free(v12);
        }
        v13 = *((_DWORD *)a6 + 74);
        v80 = 0;
        v82 = 0;
        v81 = 0;
        if ( v13 )
          goto LABEL_134;
        sub_C612(&v80, 137);
        sub_C612(&v80, 80);
        sub_C612(&v80, 78);
        sub_C612(&v80, 71);
        sub_C612(&v80, 13);
        sub_C612(&v80, 10);
        sub_C612(&v80, 26);
        sub_C612(&v80, 10);
        v14 = v91;
        v60 = v90;
        v64 = v92;
        v86 = 0;
        v88 = 0;
        v87 = 0;
        sub_CA78(&v86, a4);
        sub_CA78(&v86, a5);
        sub_C612(&v86, v64);
        sub_C612(&v86, v14);
        sub_C612(&v86, 0);
        sub_C612(&v86, 0);
        sub_C612(&v86, v60);
        sub_E2D8((int)&v80, "IHDR", v86, v87);
        sub_C368((int)&v86);
        if ( v122 )
        {
          v15 = sub_7D18(&v80, v122, v125);
          *((_DWORD *)a6 + 74) = v15;
          if ( v15 )
          {
LABEL_134:
            lodepng_info_cleanup(v89);
            free(p);
            *a1 = v80;
            *a2 = v81;
            return *((_DWORD *)a6 + 74);
          }
        }
        if ( v91 == 3 )
          sub_7D50((int)&v80, (int)&v91);
        if ( *((_DWORD *)a6 + 23) && (v91 & 0xFFFFFFFB) == 2 )
          sub_7D50((int)&v80, (int)&v91);
        if ( v91 == 3 )
        {
          v16 = 0;
          v17 = 0;
          v18 = 0;
          v19 = 0;
          for ( i = 0; i < v94; ++i )
          {
            if ( v19 || (v21 = (unsigned __int8 *)(v93 + 4 * i), v21[3]) )
            {
              v22 = (unsigned __int8 *)(v93 + 4 * i);
              if ( v22[3] != 255 )
                goto LABEL_135;
              if ( v19 )
              {
                if ( v18 == *(unsigned __int8 *)(v93 + 4 * i) && v17 == v22[1] && v16 == v22[2] )
                  goto LABEL_135;
                v19 = 1;
              }
            }
            else
            {
              v18 = *(unsigned __int8 *)(v93 + 4 * i);
              v19 = 1;
              v17 = v21[1];
              i = -1;
              v16 = v21[2];
            }
          }
          if ( !v19 )
            goto LABEL_50;
LABEL_135:
          sub_7DA0((int)&v80, &v91);
        }
LABEL_50:
        if ( (v91 & 0xFFFFFFFD) == 0 && v95 )
          sub_7DA0((int)&v80, &v91);
        if ( !v96 )
        {
LABEL_62:
          if ( v118 )
          {
            v86 = 0;
            v88 = 0;
            v87 = 0;
            sub_CA78(&v86, v119);
            sub_CA78(&v86, v120);
            sub_C612(&v86, v121);
            sub_E2D8((int)&v80, "pHYs", v86, v87);
            sub_C368((int)&v86);
          }
          if ( !v123 || (v25 = sub_7D18(&v80, v123, v126), (*((_DWORD *)a6 + 74) = v25) == 0) )
          {
            v71 = (int *)((char *)a6 + 40);
            v86 = 0;
            v88 = 0;
            v87 = 0;
            v24 = sub_E0B4((int *)&v86, (int *)&v87, (unsigned __int8 *)p, v79, (int *)a6 + 10);
            if ( !v24 )
              v24 = sub_E2D8((int)&v80, "IDAT", v86, v87);
            sub_C368((int)&v86);
            *((_DWORD *)a6 + 74) = v24;
            if ( !v24 )
            {
              if ( v111 )
              {
                v26 = (unsigned __int8 *)malloc(7u);
                v27 = v26;
                if ( v26 )
                {
                  v28 = v112 >> 8;
                  v26[1] = v112;
                  v29 = v113;
                  *v26 = v28;
                  v26[2] = v29;
                  v26[3] = v114;
                  v26[4] = v115;
                  v26[5] = v116;
                  v26[6] = v117;
                  sub_E2D8((int)&v80, "tIME", v26, 7u);
                  free(v27);
                }
              }
              for ( j = 0; ; ++j )
              {
                v67 = v103;
                if ( j >= v103 )
                  goto LABEL_93;
                v31 = *(const char **)(v104 + 4 * j);
                if ( strlen(v31) > 0x4F )
                  break;
                if ( !*v31 )
                {
                  v32 = 67;
                  goto LABEL_79;
                }
                if ( *((_DWORD *)a6 + 25) )
                {
                  v68 = *(char **)(v105 + 4 * j);
                  v33 = strlen(v68);
                  v34 = 0;
                  v83 = 0;
                  v85 = 0;
                  v84 = 0;
                  v86 = 0;
                  v88 = 0;
                  v87 = 0;
                  v72 = v33;
                  while ( v31[v34] )
                  {
                    v65 = v34;
                    sub_C612(&v83, v31[v34]);
                    v34 = v65 + 1;
                  }
                  if ( (unsigned int)(v34 - 1) <= 0x4E )
                  {
                    v61 = v31[v34];
                    sub_C612(&v83, v61);
                    sub_C612(&v83, v61);
                    if ( !sub_E0B4((int *)&v86, (int *)&v87, (unsigned __int8 *)v68, v72, v71) )
                    {
                      for ( k = 0; k < v87; ++k )
                      {
                        v36 = v86[k];
                        sub_C612(&v83, v36);
                      }
                      sub_E2D8((int)&v80, "zTXt", v83, v84);
                    }
                    sub_C368((int)&v86);
                    sub_C368((int)&v83);
                  }
                }
                else
                {
                  sub_7E5C((int)&v80, (int)v31, *(_DWORD *)(v105 + 4 * j));
                }
              }
              v32 = 66;
LABEL_79:
              *((_DWORD *)a6 + 74) = v32;
LABEL_93:
              if ( *((_DWORD *)a6 + 24) )
              {
                v37 = 0;
                v38 = v104;
                while ( v37 != v67 )
                {
                  if ( !strcmp(*(const char **)(v38 + 4 * v37), "LodePNG") )
                    goto LABEL_99;
                  ++v37;
                }
                sub_7E5C((int)&v80, (int)"LodePNG", (int)"20131115");
              }
LABEL_99:
              for ( m = 0; ; ++m )
              {
                if ( m >= v106 )
                {
LABEL_131:
                  if ( !v124 || (v59 = sub_7D18(&v80, v124, v127), (*((_DWORD *)a6 + 74) = v59) == 0) )
                    sub_E2D8((int)&v80, "IEND", 0, 0);
                  goto LABEL_134;
                }
                v40 = *(const char **)(v107 + 4 * m);
                if ( strlen(v40) > 0x4F )
                {
                  v41 = 66;
LABEL_105:
                  *((_DWORD *)a6 + 74) = v41;
                  goto LABEL_131;
                }
                if ( !*v40 )
                {
                  v41 = 67;
                  goto LABEL_105;
                }
                v69 = *((_DWORD *)a6 + 25);
                v73 = *(_DWORD *)(v108 + 4 * m);
                v74 = *(char **)(v109 + 4 * m);
                v42 = *(char **)(v110 + 4 * m);
                v43 = strlen(v42);
                v44 = 0;
                v83 = 0;
                v85 = 0;
                v84 = 0;
                v77 = v43;
                while ( v40[v44] )
                {
                  v66 = v44;
                  sub_C612(&v83, v40[v44]);
                  v44 = v66 + 1;
                }
                if ( (unsigned int)(v44 - 1) <= 0x4E )
                  break;
LABEL_130:
                ;
              }
              v62 = v40[v44];
              sub_C612(&v83, v62);
              v45 = v69;
              if ( v69 )
                v45 = 1;
              v70 = v45;
              sub_C612(&v83, v45);
              sub_C612(&v83, v62);
              v46 = v73 - 1;
              while ( 1 )
              {
                v48 = *(unsigned __int8 *)++v46;
                v47 = v48;
                if ( !v48 )
                  break;
                sub_C612(&v83, v47);
              }
              sub_C612(&v83, 0);
              for ( n = v74 - 1; ; n = v63 )
              {
                v51 = (unsigned __int8)n[1];
                v50 = n + 1;
                v52 = v51;
                if ( !v51 )
                  break;
                v63 = v50;
                sub_C612(&v83, v52);
              }
              sub_C612(&v83, 0);
              if ( v70 )
              {
                v86 = 0;
                v88 = 0;
                v87 = 0;
                v54 = sub_E0B4((int *)&v86, (int *)&v87, (unsigned __int8 *)v42, v77, v71);
                if ( !v54 )
                {
                  for ( ii = 0; ii < v87; ++ii )
                  {
                    v56 = v86[ii];
                    sub_C612(&v83, v56);
                  }
                }
                sub_C368((int)&v86);
                if ( v54 )
                  goto LABEL_129;
              }
              else
              {
                v53 = v42 - 1;
                while ( 1 )
                {
                  v58 = (unsigned __int8)*++v53;
                  v57 = v58;
                  if ( !v58 )
                    break;
                  sub_C612(&v83, v57);
                }
              }
              sub_E2D8((int)&v80, "iTXt", v83, v84);
LABEL_129:
              sub_C368((int)&v83);
              goto LABEL_130;
            }
          }
          goto LABEL_134;
        }
        v86 = 0;
        v88 = 0;
        v87 = 0;
        if ( (v91 & 0xFFFFFFFB) != 0 )
        {
          if ( (v91 & 0xFFFFFFFB) == 2 )
          {
            sub_C612(&v86, v98);
            sub_C612(&v86, v97);
            sub_C612(&v86, v100);
            sub_C612(&v86, v99);
            sub_C612(&v86, v102);
            v23 = v101;
LABEL_60:
            sub_C612(&v86, v23);
            goto LABEL_61;
          }
          if ( v91 != 3 )
          {
LABEL_61:
            sub_E2D8((int)&v80, "bKGD", v86, v87);
            sub_C368((int)&v86);
            goto LABEL_62;
          }
        }
        else
        {
          sub_C612(&v86, v98);
        }
        v23 = v97;
        goto LABEL_60;
      }
    }
  }
  return result;
}


//----- (00010F34) --------------------------------------------------------
_DWORD *__fastcall lodepng_encoder_settings_init(_DWORD *a1)
{
  _DWORD *result; // r0

  result = lodepng_compress_settings_init(a1);
  a1[10] = 1;
  a1[9] = 2;
  a1[11] = 1;
  a1[13] = 0;
  a1[12] = 0;
  a1[14] = 0;
  a1[15] = 1;
  return result;
}


//----- (00010F52) --------------------------------------------------------
_DWORD *__fastcall lodepng_state_init(LodePNGState *a1)
{
  _DWORD *result; // r0

  lodepng_decoder_settings_init((_DWORD *)a1 + 1);
  lodepng_encoder_settings_init((_DWORD *)a1 + 10);
  lodepng_color_mode_init((_DWORD *)a1 + 26);
  result = lodepng_info_init((_DWORD *)a1 + 34);
  *((_DWORD *)a1 + 74) = 1;
  return result;
}


//----- (00010F7C) --------------------------------------------------------
int __fastcall lodepng_decode_memory(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned int *a3,
        unsigned __int8 *a4,
        unsigned int a5,
        void *a6,
        void *a7)
{
  int v11; // r5
  void *v13[75]; // [sp+Ch] [bp-12Ch] BYREF

  v13[0] = &off_17C58;
  lodepng_state_init((LodePNGState *)v13);
  v13[26] = a6;
  v13[27] = a7;
  v11 = lodepng_decode(a1, a2, a3, (LodePNGState *)v13, a4, a5);
  lodepng_state_cleanup(v13);
  return v11;
}
// 17C58: using guessed type _UNKNOWN *off_17C58;


//----- (00010FCC) --------------------------------------------------------
int __fastcall lodepng_decode32(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned int *a3,
        unsigned __int8 *a4,
        unsigned int a5)
{
  return lodepng_decode_memory(a1, a2, a3, a4, a5, &byte_6, &byte_8);
}
// 6: using guessed type char byte_6;
// 8: using guessed type char byte_8;


//----- (00010FE2) --------------------------------------------------------
int __fastcall lodepng_decode24(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned int *a3,
        unsigned __int8 *a4,
        unsigned int a5)
{
  return lodepng_decode_memory(a1, a2, a3, a4, a5, (char *)&dword_0 + 2, &byte_8);
}
// 0: using guessed type int dword_0;
// 8: using guessed type char byte_8;


//----- (00010FF8) --------------------------------------------------------
int __fastcall lodepng_decode_file(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned int *a3,
        char *filename,
        void *a5,
        void *a6)
{
  int v9; // r4
  void *p; // [sp+10h] [bp-Ch] BYREF
  unsigned int v12; // [sp+14h] [bp-8h] BYREF

  v9 = lodepng_load_file((unsigned __int8 **)&p, &v12, filename);
  if ( !v9 )
    v9 = lodepng_decode_memory(a1, a2, a3, (unsigned __int8 *)p, v12, a5, a6);
  free(p);
  return v9;
}


//----- (00011036) --------------------------------------------------------
int __fastcall lodepng_decode32_file(unsigned __int8 **a1, unsigned int *a2, unsigned int *a3, char *a4)
{
  return lodepng_decode_file(a1, a2, a3, a4, &byte_6, &byte_8);
}
// 6: using guessed type char byte_6;
// 8: using guessed type char byte_8;


//----- (0001104A) --------------------------------------------------------
int __fastcall lodepng_decode24_file(unsigned __int8 **a1, unsigned int *a2, unsigned int *a3, char *a4)
{
  return lodepng_decode_file(a1, a2, a3, a4, (char *)&dword_0 + 2, &byte_8);
}
// 0: using guessed type int dword_0;
// 8: using guessed type char byte_8;


//----- (00011060) --------------------------------------------------------
void *__fastcall lodepng_encode_memory(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned __int8 *a3,
        unsigned int a4,
        unsigned int a5,
        void *a6,
        void *a7)
{
  void *v11; // r5
  void *v13[75]; // [sp+Ch] [bp-12Ch] BYREF

  v13[0] = &off_17C58;
  lodepng_state_init((LodePNGState *)v13);
  v13[27] = a7;
  v13[38] = a7;
  v13[26] = a6;
  v13[37] = a6;
  lodepng_encode(a1, a2, a3, a4, a5, (LodePNGState *)v13);
  v11 = v13[74];
  lodepng_state_cleanup(v13);
  return v11;
}
// 17C58: using guessed type _UNKNOWN *off_17C58;


//----- (000110B4) --------------------------------------------------------
void *__fastcall lodepng_encode32(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned __int8 *a3,
        unsigned int a4,
        unsigned int a5)
{
  return lodepng_encode_memory(a1, a2, a3, a4, a5, &byte_6, &byte_8);
}
// 6: using guessed type char byte_6;
// 8: using guessed type char byte_8;


//----- (000110CA) --------------------------------------------------------
void *__fastcall lodepng_encode24(
        unsigned __int8 **a1,
        unsigned int *a2,
        unsigned __int8 *a3,
        unsigned int a4,
        unsigned int a5)
{
  return lodepng_encode_memory(a1, a2, a3, a4, a5, (char *)&dword_0 + 2, &byte_8);
}
// 0: using guessed type int dword_0;
// 8: using guessed type char byte_8;


//----- (000110E0) --------------------------------------------------------
void *__fastcall lodepng_encode_file(
        const char *a1,
        unsigned __int8 *a2,
        unsigned int a3,
        unsigned int a4,
        void *a5,
        void *a6)
{
  void *v7; // r4
  void *p; // [sp+10h] [bp-Ch] BYREF
  unsigned int v10; // [sp+14h] [bp-8h] BYREF

  v7 = lodepng_encode_memory((unsigned __int8 **)&p, &v10, a2, a3, a4, a5, a6);
  if ( !v7 )
    v7 = (void *)lodepng_save_file((const unsigned __int8 *)p, v10, a1);
  free(p);
  return v7;
}


//----- (0001111C) --------------------------------------------------------
void *__fastcall lodepng_encode32_file(const char *a1, unsigned __int8 *a2, unsigned int a3, unsigned int a4)
{
  return lodepng_encode_file(a1, a2, a3, a4, &byte_6, &byte_8);
}
// 6: using guessed type char byte_6;
// 8: using guessed type char byte_8;


//----- (00011130) --------------------------------------------------------
void *__fastcall lodepng_encode24_file(const char *a1, unsigned __int8 *a2, unsigned int a3, unsigned int a4)
{
  return lodepng_encode_file(a1, a2, a3, a4, (char *)&dword_0 + 2, &byte_8);
}
// 0: using guessed type int dword_0;
// 8: using guessed type char byte_8;


//----- (00011144) --------------------------------------------------------
const char *__fastcall lodepng_error_text(unsigned int a1)
{
  const char *result; // r0

  switch ( a1 )
  {
    case 0u:
      result = "no error, everything went ok";
      break;
    case 1u:
      result = "nothing done yet";
      break;
    case 0xAu:
      result = "end of input memory reached without huffman end code";
      break;
    case 0xBu:
      result = "error in code tree made it jump outside of huffman tree";
      break;
    case 0xDu:
      result = "problem while processing dynamic deflate block";
      break;
    case 0xEu:
      result = "problem while processing dynamic deflate block";
      break;
    case 0xFu:
      result = "problem while processing dynamic deflate block";
      break;
    case 0x10u:
      result = "unexisting code while processing dynamic deflate block";
      break;
    case 0x11u:
      result = "end of out buffer memory reached while inflating";
      break;
    case 0x12u:
      result = "invalid distance code while inflating";
      break;
    case 0x13u:
      result = "end of out buffer memory reached while inflating";
      break;
    case 0x14u:
      result = "invalid deflate block BTYPE encountered while decoding";
      break;
    case 0x15u:
      result = "NLEN is not ones complement of LEN in a deflate block";
      break;
    case 0x16u:
      result = "end of out buffer memory reached while inflating";
      break;
    case 0x17u:
      result = "end of in buffer memory reached while inflating";
      break;
    case 0x18u:
      result = "invalid FCHECK in zlib header";
      break;
    case 0x19u:
      result = "invalid compression method in zlib header";
      break;
    case 0x1Au:
      result = "FDICT encountered in zlib header while it's not used for PNG";
      break;
    case 0x1Bu:
      result = "PNG file is smaller than a PNG header";
      break;
    case 0x1Cu:
      result = "incorrect PNG signature, it's no PNG or corrupted";
      break;
    case 0x1Du:
      result = "first chunk is not the header chunk";
      break;
    case 0x1Eu:
      result = "chunk length too large, chunk broken off at end of file";
      break;
    case 0x1Fu:
      result = "illegal PNG color type or bpp";
      break;
    case 0x20u:
      result = "illegal PNG compression method";
      break;
    case 0x21u:
      result = "illegal PNG filter method";
      break;
    case 0x22u:
      result = "illegal PNG interlace method";
      break;
    case 0x23u:
      result = "chunk length of a chunk is too large or the chunk too small";
      break;
    case 0x24u:
      result = "illegal PNG filter type encountered";
      break;
    case 0x25u:
      result = "illegal bit depth for this color type given";
      break;
    case 0x26u:
      result = "the palette is too big";
      break;
    case 0x27u:
      result = "more palette alpha values given in tRNS chunk than there are colors in the palette";
      break;
    case 0x28u:
      result = "tRNS chunk has wrong size for greyscale image";
      break;
    case 0x29u:
      result = "tRNS chunk has wrong size for RGB image";
      break;
    case 0x2Au:
      result = "tRNS chunk appeared while it was not allowed for this color type";
      break;
    case 0x2Bu:
      result = "bKGD chunk has wrong size for palette image";
      break;
    case 0x2Cu:
      result = "bKGD chunk has wrong size for greyscale image";
      break;
    case 0x2Du:
      result = "bKGD chunk has wrong size for RGB image";
      break;
    case 0x2Eu:
      result = "a value in indexed image is larger than the palette size (bitdepth = 8)";
      break;
    case 0x2Fu:
      result = "a value in indexed image is larger than the palette size (bitdepth < 8)";
      break;
    case 0x30u:
      result = "empty input or file doesn't exist";
      break;
    case 0x31u:
      result = "jumped past memory while generating dynamic huffman tree";
      break;
    case 0x32u:
      result = "jumped past memory while generating dynamic huffman tree";
      break;
    case 0x33u:
      result = "jumped past memory while inflating huffman block";
      break;
    case 0x34u:
      result = "jumped past memory while inflating";
      break;
    case 0x35u:
      result = "size of zlib data too small";
      break;
    case 0x36u:
      result = "repeat symbol in tree while there was no value symbol yet";
      break;
    case 0x37u:
      result = "jumped past tree while generating huffman tree";
      break;
    case 0x38u:
      result = "given output image colortype or bitdepth not supported for color conversion";
      break;
    case 0x39u:
      result = "invalid CRC encountered (checking CRC can be disabled)";
      break;
    case 0x3Au:
      result = "invalid ADLER32 encountered (checking ADLER32 can be disabled)";
      break;
    case 0x3Bu:
      result = "requested color conversion not supported";
      break;
    case 0x3Cu:
      result = "invalid window size given in the settings of the encoder (must be 0-32768)";
      break;
    case 0x3Du:
      result = "invalid BTYPE given in the settings of the encoder (only 0, 1 and 2 are allowed)";
      break;
    case 0x3Eu:
      result = "conversion from color to greyscale not supported";
      break;
    case 0x3Fu:
      result = "length of a chunk too long, max allowed for PNG is 2147483647 bytes per chunk";
      break;
    case 0x40u:
      result = "the length of the END symbol 256 in the Huffman tree is 0";
      break;
    case 0x42u:
      result = "the length of a text chunk keyword given to the encoder is longer than the maximum of 79 bytes";
      break;
    case 0x43u:
      result = "the length of a text chunk keyword given to the encoder is smaller than the minimum of 1 byte";
      break;
    case 0x44u:
      result = "tried to encode a PLTE chunk with a palette that has less than 1 or more than 256 colors";
      break;
    case 0x45u:
      result = "unknown chunk type with 'critical' flag encountered by the decoder";
      break;
    case 0x47u:
      result = "unexisting interlace mode given to encoder (must be 0 or 1)";
      break;
    case 0x48u:
      result = "while decoding, unexisting compression method encountering in zTXt or iTXt chunk (it must be 0)";
      break;
    case 0x49u:
      result = "invalid tIME chunk size";
      break;
    case 0x4Au:
      result = "invalid pHYs chunk size";
      break;
    case 0x4Bu:
      result = "no null termination char found while decoding text chunk";
      break;
    case 0x4Cu:
      result = "iTXt chunk too short to contain required bytes";
      break;
    case 0x4Du:
      result = "integer overflow in buffer size";
      break;
    case 0x4Eu:
      result = "failed to open file for reading";
      break;
    case 0x4Fu:
      result = "failed to open file for writing";
      break;
    case 0x50u:
      result = "tried creating a tree of 0 symbols";
      break;
    case 0x51u:
      result = "lazy matching at pos 0 is impossible";
      break;
    case 0x52u:
      result = "color conversion to palette requested while a color isn't in palette";
      break;
    case 0x53u:
      result = "memory allocation failed";
      break;
    case 0x54u:
      result = "given image too small to contain all pixels to be encoded";
      break;
    case 0x55u:
      result = "internal color conversion bug";
      break;
    case 0x56u:
      result = "impossible offset in lz77 encoding (internal bug)";
      break;
    case 0x57u:
      result = "must provide custom zlib function pointer if LODEPNG_COMPILE_ZLIB is not defined";
      break;
    case 0x58u:
      result = "invalid filter strategy given for LodePNGEncoderSettings.filter_strategy";
      break;
    case 0x59u:
      result = "text chunk keyword too short or long: must have size 1-79";
      break;
    default:
      result = "unknown error code";
      break;
  }
  return result;
}


//----- (00011554) --------------------------------------------------------
// Alternative name is '_ZN7lodepng5StateC1Ev'
lodepng::State *__fastcall lodepng::State::State(lodepng::State *this)
{
  *(_DWORD *)this = &off_17C68;
  lodepng_state_init(this);
  return this;
}
// 17C68: using guessed type _UNKNOWN *off_17C68;


//----- (00011570) --------------------------------------------------------
// Alternative name is '_ZN7lodepng5StateC1ERKS0_'
lodepng::State *__fastcall lodepng::State::State(lodepng::State *this, const lodepng::State *a2)
{
  *(_DWORD *)this = &off_17C68;
  lodepng_state_init(this);
  lodepng_state_copy((void **)this, a2);
  return this;
}
// 17C68: using guessed type _UNKNOWN *off_17C68;


//----- (00011594) --------------------------------------------------------
void **__fastcall lodepng::State::operator=(void **a1, const LodePNGState *a2)
{
  lodepng_state_copy(a1, a2);
  return a1;
}


//----- (000115A0) --------------------------------------------------------
unsigned int __fastcall std::vector<unsigned char>::_M_check_len(_DWORD *a1, unsigned int a2, char *a3)
{
  unsigned int v3; // r3
  unsigned int result; // r0

  v3 = a1[1] - *a1;
  if ( ~v3 < a2 )
    std::__throw_length_error(a3);
  if ( v3 < a2 )
    result = v3 + a2;
  else
    result = 2 * v3;
  if ( result < v3 )
    return -1;
  return result;
}


//----- (000115C8) --------------------------------------------------------
int __fastcall std::__copy_move<true,true,std::random_access_iterator_tag>::__copy_m<unsigned char>(
        _BYTE *src,
        _BYTE *a2,
        void *dest)
{
  size_t v3; // r4

  v3 = a2 - src;
  if ( a2 != src )
    memmove(dest, src, v3);
  return (int)dest + v3;
}


//----- (000116D4) --------------------------------------------------------
void __fastcall std::vector<unsigned char>::_M_range_insert<unsigned char *>(void **a1, char *src, char *a3, char *a4)
{
  unsigned int v7; // r5
  _BYTE *v8; // r8
  size_t v9; // r10
  void *v10; // r0
  char *v11; // r1
  size_t v12; // r2
  char *v13; // r9
  size_t v14; // r2
  _BYTE *v15; // r2
  unsigned int v16; // r0
  unsigned int v17; // r9
  char *v18; // r8
  char *v19; // r0
  char *v20; // r10
  int v21; // r5

  if ( a3 != a4 )
  {
    v7 = a4 - a3;
    v8 = a1[1];
    if ( (_BYTE *)a1[2] - v8 < (unsigned int)(a4 - a3) )
    {
      v16 = std::vector<unsigned char>::_M_check_len(a1, v7, "vector::_M_range_insert");
      v17 = v16;
      if ( v16 )
        v18 = (char *)operator new(v16);
      else
        v18 = 0;
      v19 = (char *)std::__copy_move<true,true,std::random_access_iterator_tag>::__copy_m<unsigned char>(*a1, src, v18);
      v20 = v19;
      if ( v7 )
        memmove(v19, a3, v7);
      v21 = std::__copy_move<true,true,std::random_access_iterator_tag>::__copy_m<unsigned char>(src, a1[1], &v20[v7]);
      if ( *a1 )
        operator delete(*a1);
      *a1 = v18;
      a1[1] = (void *)v21;
      a1[2] = &v18[v17];
    }
    else
    {
      v9 = v8 - src;
      if ( v8 - src <= v7 )
      {
        v13 = &a3[v9];
        v14 = a4 - &a3[v9];
        if ( a4 != &a3[v9] )
          memmove(a1[1], &a3[v9], v14);
        v15 = (char *)a1[1] + v7 - v9;
        a1[1] = v15;
        std::__copy_move<true,true,std::random_access_iterator_tag>::__copy_m<unsigned char>(src, v8, v15);
        v12 = v9;
        a1[1] = (char *)a1[1] + v9;
        if ( v13 != a3 )
        {
          v10 = src;
          v11 = a3;
          goto LABEL_12;
        }
      }
      else
      {
        std::__copy_move<true,true,std::random_access_iterator_tag>::__copy_m<unsigned char>(&v8[-v7], a1[1], a1[1]);
        a1[1] = (char *)a1[1] + v7;
        if ( &v8[-v7] != src )
          memmove(&src[v7], src, &v8[-v7] - src);
        if ( v7 )
        {
          v10 = src;
          v11 = a3;
          v12 = v7;
LABEL_12:
          j_memmove(v10, v11, v12);
        }
      }
    }
  }
}


//----- (00011B50) --------------------------------------------------------
double __fastcall timesince(const timespec *a1, int a2)
{
  const timespec *v4; // [sp+0h] [bp-8h] BYREF
  int v5; // [sp+4h] [bp-4h]

  v4 = a1;
  v5 = a2;
  clock_gettime(4, (struct timespec *)&v4);
  return (double)((int)v4 - *(_DWORD *)a1) + (double)(v5 - *((_DWORD *)a1 + 1)) / 1000000000.0;
}


//----- (00011B98) --------------------------------------------------------
// Alternative name is '_ZN11CurveClientC1Ev'
void __fastcall CurveClient::CurveClient(CurveClient *this)
{
  *(_BYTE *)this = 0;
  *((_BYTE *)this + 80) = 0;
}


//----- (00011E20) --------------------------------------------------------
// Alternative name is '_ZNSt8_Rb_treeISsSt4pairIKSs14themeparameterESt10_Select1stIS3_ESt4lessISsESaIS3_EE13_Rb_tree_implIS7_Lb1EEC1Ev'
_DWORD *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_Rb_tree_impl<std::less<std::string>,true>::_Rb_tree_impl(
        _DWORD *a1)
{
  _DWORD *v1; // r5

  v1 = a1 + 1;
  memset(a1 + 1, 0, 0x10u);
  a1[3] = v1;
  a1[5] = 0;
  a1[4] = v1;
  return a1;
}


//----- (00011E60) --------------------------------------------------------
_DWORD *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::find(
        int a1,
        const std::string *a2)
{
  _DWORD *v2; // r4
  _DWORD *v4; // r5

  v2 = (_DWORD *)(a1 + 4);
  v4 = sub_11E3C(*(_DWORD **)(a1 + 8), (_DWORD *)(a1 + 4), a2);
  if ( v4 == v2 || std::operator<<char>(a2, (const std::string *)(v4 + 4)) )
    return v2;
  else
    return v4;
}


//----- (00011E8A) --------------------------------------------------------
int __fastcall std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_insert_node(
        int a1,
        int a2,
        int a3,
        int a4)
{
  int v7; // r7
  int v8; // r0

  v7 = a1 + 4;
  if ( a2 || a3 == v7 )
    v8 = 1;
  else
    v8 = std::operator<<char>((std::string *)(a4 + 16), (const std::string *)(a3 + 16));
  std::_Rb_tree_insert_and_rebalance(v8, a4, a3, v7);
  ++*(_DWORD *)(a1 + 20);
  return a4;
}
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);


//----- (00011EBE) --------------------------------------------------------
int *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_get_insert_hint_unique_pos(
        int *a1,
        _DWORD *a2,
        _DWORD *a3,
        const std::string *a4)
{
  int v7; // r5
  int v8; // r3
  std::string *v9; // r9
  int v10; // r8

  v7 = (int)a3;
  if ( a3 == a2 + 1 )
  {
    if ( a2[5] )
    {
      v7 = a2[4];
      if ( std::operator<<char>((std::string *)(v7 + 16), a4) )
      {
        v8 = 0;
LABEL_19:
        *a1 = v8;
        goto LABEL_20;
      }
    }
LABEL_21:
    std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_get_insert_unique_pos(
      a1,
      (int)a2,
      a4);
    return a1;
  }
  v9 = (std::string *)(a3 + 4);
  if ( !std::operator<<char>(a4, (const std::string *)(a3 + 4)) )
  {
    if ( !std::operator<<char>(v9, a4) )
    {
      *a1 = v7;
      a1[1] = 0;
      return a1;
    }
    if ( v7 != a2[4] )
    {
      v10 = std::_Rb_tree_increment(v7);
      if ( !std::operator<<char>(a4, (const std::string *)(v10 + 16)) )
        goto LABEL_21;
      v8 = *(_DWORD *)(v7 + 12);
      if ( !v8 )
        goto LABEL_19;
      *a1 = v10;
      goto LABEL_17;
    }
    *a1 = 0;
LABEL_20:
    a1[1] = v7;
    return a1;
  }
  if ( v7 == a2[3] )
    goto LABEL_10;
  v10 = std::_Rb_tree_decrement(v7);
  if ( !std::operator<<char>((std::string *)(v10 + 16), a4) )
    goto LABEL_21;
  if ( *(_DWORD *)(v10 + 12) )
  {
LABEL_10:
    *a1 = v7;
    goto LABEL_20;
  }
  *a1 = 0;
LABEL_17:
  a1[1] = v10;
  return a1;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


//----- (00011F74) --------------------------------------------------------
_DWORD *__fastcall std::map<std::string,themeparameter>::operator[](int a1, const std::string *a2)
{
  _DWORD *v2; // r6
  _DWORD *inserted; // r4
  char *v6; // r0
  void *v7; // r6
  std::string *v8; // r7
  _DWORD *v10; // [sp+0h] [bp-8h] BYREF
  const std::string *v11; // [sp+4h] [bp-4h]

  v10 = (_DWORD *)a1;
  v11 = a2;
  v2 = (_DWORD *)(a1 + 4);
  inserted = sub_11E3C(*(_DWORD **)(a1 + 8), (_DWORD *)(a1 + 4), a2);
  if ( inserted == v2 || std::operator<<char>(a2, (const std::string *)(inserted + 4)) )
  {
    v6 = (char *)operator new(0x38u);
    v7 = v6;
    v8 = (std::string *)(v6 + 16);
    if ( v6 )
    {
      memset(v6, 0, 0x10u);
      std::string::string(v8, a2);
    }
    std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_get_insert_hint_unique_pos(
      (int *)&v10,
      (_DWORD *)a1,
      inserted,
      v8);
    inserted = v10;
    if ( v11 )
    {
      inserted = (_DWORD *)std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_insert_node(
                             a1,
                             (int)v10,
                             (int)v11,
                             (int)v7);
    }
    else
    {
      std::string::~string(v8);
      operator delete(v7);
    }
  }
  return inserted + 6;
}


//----- (00011FF0) --------------------------------------------------------
_DWORD *__fastcall readTheme<std::istringstream>(_DWORD *a1, _DWORD *a2)
{
  int v4; // r0
  int v5; // r0
  int v6; // r0
  int v7; // r0
  double *v8; // r0
  __int64 v9; // r10
  __int64 v10; // r2
  double v11; // d6
  char *v13; // [sp+4h] [bp-24h] BYREF
  double v14; // [sp+8h] [bp-20h] BYREF
  double v15; // [sp+10h] [bp-18h] BYREF
  __int64 v16; // [sp+18h] [bp-10h] BYREF
  __int64 v17; // [sp+20h] [bp-8h] BYREF

  std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_Rb_tree_impl<std::less<std::string>,true>::_Rb_tree_impl(a1);
  while ( std::ios::operator void *((char *)a2 + *(_DWORD *)(*a2 - 12)) )
  {
    v13 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
    v4 = std::operator>><char>(a2, &v13);
    v5 = std::istream::_M_extract<double>(v4, &v14);
    v6 = std::istream::_M_extract<double>(v5, &v15);
    v7 = std::istream::_M_extract<double>(v6, &v16);
    std::istream::operator>>(v7, &v17);
    if ( std::ios::operator void *((char *)a2 + *(_DWORD *)(*a2 - 12)) )
    {
      v8 = (double *)std::map<std::string,themeparameter>::operator[]((int)a1, (const std::string *)&v13);
      v9 = v16;
      v10 = v17;
      v11 = v14;
      v8[1] = v15;
      *v8 = v11;
      *((_QWORD *)v8 + 2) = v9;
      *((_QWORD *)v8 + 3) = v10;
    }
    std::string::~string((std::string *)&v13);
  }
  return a1;
}
// 7C3C: using guessed type int __fastcall std::ios::operator void *(_DWORD);
// 7C48: using guessed type int __fastcall std::operator>><char>(_DWORD, _DWORD);
// 7C54: using guessed type int __fastcall std::istream::_M_extract<double>(_DWORD, _DWORD);
// 7C60: using guessed type int __fastcall std::istream::operator>>(_DWORD, _DWORD);


//----- (0001208C) --------------------------------------------------------
ef2_AAssetManager *__fastcall theme(ef2_AAssetManager *a1, ef2_AAssetManager *a2, int a3)
{
  int v6; // r0
  int v7; // r0
  AAsset *v8; // r7
  const void *Buffer; // r5
  off_t Length; // r0
  _DWORD *v11; // r2
  char *v12; // r1
  int v13; // r2
  int v15; // [sp+0h] [bp-18Ch] BYREF
  int v16; // [sp+4h] [bp-188h] BYREF
  char v17; // [sp+8h] [bp-184h] BYREF
  _DWORD *v18; // [sp+Ch] [bp-180h]
  char *v19; // [sp+10h] [bp-17Ch]
  char *v20; // [sp+14h] [bp-178h]
  int v21; // [sp+18h] [bp-174h]
  _BYTE v22[4]; // [sp+1Ch] [bp-170h] BYREF
  _BYTE v23[176]; // [sp+20h] [bp-16Ch] BYREF
  char *filename[47]; // [sp+D0h] [bp-BCh] BYREF

  std::ostringstream::basic_ostringstream(v22, 16);
  v6 = std::operator<<<std::char_traits<char>>(v22, "lwp.");
  v7 = std::ostream::operator<<(v6, a3);
  std::operator<<<std::char_traits<char>>(v7, ".theme");
  std::stringbuf::str(filename, v23);
  v8 = ef2_AAssetManager_open(a2, filename[0], 3);
  std::string::~string((std::string *)filename);
  if ( v8 )
  {
    Buffer = AAsset_getBuffer(v8);
    Length = AAsset_getLength(v8);
    std::string::string(&v15, Buffer, Length, filename);
    std::istringstream::basic_istringstream(filename, &v15, 8);
    readTheme<std::istringstream>(&v16, filename);
    AAsset_close(v8);
    memset((char *)a1 + 4, 0, 0x10u);
    v11 = v18;
    *((_DWORD *)a1 + 3) = (char *)a1 + 4;
    *((_DWORD *)a1 + 5) = 0;
    *((_DWORD *)a1 + 4) = (char *)a1 + 4;
    if ( v11 )
    {
      v12 = v19;
      *((_DWORD *)a1 + 2) = v11;
      *((_DWORD *)a1 + 3) = v12;
      *((_DWORD *)a1 + 4) = v20;
      v11[1] = (char *)a1 + 4;
      v19 = &v17;
      v20 = &v17;
      v13 = v21;
      v18 = 0;
      v21 = 0;
      *((_DWORD *)a1 + 5) = v13;
    }
    std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_erase(
      (int)&v16,
      v18);
    std::istringstream::~istringstream(filename);
    std::string::~string((std::string *)&v15);
  }
  else if ( a3 == -1 )
  {
    std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_Rb_tree_impl<std::less<std::string>,true>::_Rb_tree_impl(a1);
  }
  else
  {
    theme(a1, (int)a2);
  }
  std::ostringstream::~ostringstream(v22);
  return a1;
}
// 79B4: using guessed type int __fastcall std::string::string(_DWORD, _DWORD, _DWORD, _DWORD);
// 7AEC: using guessed type int __fastcall std::operator<<<std::char_traits<char>>(_DWORD, _DWORD);
// 7C6C: using guessed type int __fastcall std::ostringstream::basic_ostringstream(_DWORD, _DWORD);
// 7C78: using guessed type int __fastcall std::ostream::operator<<(_DWORD, _DWORD);
// 7C84: using guessed type int __fastcall std::stringbuf::str(_DWORD, _DWORD);
// 7C90: using guessed type int __fastcall std::istringstream::basic_istringstream(_DWORD, _DWORD, _DWORD);
// 7C9C: using guessed type int __fastcall std::istringstream::~istringstream(_DWORD);
// 7CA8: using guessed type int __fastcall std::ostringstream::~ostringstream(_DWORD);


//----- (00012200) --------------------------------------------------------
// Alternative name is '_ZN5CurveC2EP13ef2_AAssetManager'
void __fastcall Curve::Curve(Curve *this, ef2_AAssetManager *a2)
{
  CurveClient *v4; // r7
  AAsset *v5; // r4
  const void *Buffer; // r5
  off_t Length; // r0
  unsigned __int8 *v8; // r5
  off_t v9; // r0
  unsigned int v10; // r3
  unsigned int v11; // r0
  unsigned int v12; // r0
  void *v13; // r0
  const void *v14; // r1
  size_t v15; // r2
  unsigned int v16; // [sp+14h] [bp-14h] BYREF
  unsigned int v17; // [sp+18h] [bp-10h] BYREF
  void *v18[3]; // [sp+1Ch] [bp-Ch] BYREF

  std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_Rb_tree_impl<std::less<std::string>,true>::_Rb_tree_impl((_DWORD *)this + 8);
  *((_QWORD *)this + 26) = 0;
  *((_QWORD *)this + 27) = 0;
  *((_QWORD *)this + 28) = 0;
  *((_QWORD *)this + 30) = 0;
  v4 = (CurveClient *)operator new(0x60u);
  CurveClient::CurveClient(v4);
  *((_DWORD *)this + 2) = v4;
  clock_gettime(4, (Curve *)((char *)this + 184));
  *((_QWORD *)this + 38) = 0;
  *((_QWORD *)this + 31) = 0;
  *((_QWORD *)this + 32) = 0;
  *((_QWORD *)this + 29) = 0;
  *((_QWORD *)this + 35) = 0;
  *((_QWORD *)this + 36) = 0;
  *((_QWORD *)this + 33) = 0;
  *((_QWORD *)this + 34) = 0;
  *((_QWORD *)this + 37) = 0;
  *((_DWORD *)this + 51) = 2;
  *((_DWORD *)this + 50) = 2;
  *((_DWORD *)this + 48) = 0;
  *((_DWORD *)this + 49) = 0;
  *((_DWORD *)this + 80) = 0;
  Curve::requestColors(this, a2, -1);
  *((_DWORD *)this + 83) = 1;
  *((_DWORD *)this + 84) = 1;
  *((_DWORD *)this + 92) = 0;
  memset(v18, 0, sizeof(v18));
  v5 = ef2_AAssetManager_open(a2, "noise.png", 3);
  Buffer = AAsset_getBuffer(v5);
  Length = AAsset_getLength(v5);
  _android_log_print(3, "renderlib", "%p, %ld", Buffer, Length);
  v8 = (unsigned __int8 *)AAsset_getBuffer(v5);
  v9 = AAsset_getLength(v5);
  lodepng::decode((int)v18, &v16, &v17, v8, v9, &byte_6, &byte_8);
  v10 = v16;
  v11 = v17;
  *((_DWORD *)this + 90) = v16;
  *((_DWORD *)this + 91) = v11;
  v12 = 4 * v11 * v10;
  *((_DWORD *)this + 89) = v12;
  v13 = (void *)operator new[](v12);
  v14 = v18[0];
  v15 = *((_DWORD *)this + 89);
  *((_DWORD *)this + 44) = v13;
  memcpy(v13, v14, v15);
  *((_DWORD *)this + 45) = 0;
  AAsset_close(v5);
  if ( v18[0] )
    operator delete(v18[0]);
}
// 6: using guessed type char;
// 8: using guessed type char;


//----- (00012334) --------------------------------------------------------
// Alternative name is '_ZNSt13_Rb_tree_nodeISt4pairIKSs14themeparameterEEC2IJRKS3_EEEDpOT_'
// Alternative name is '_ZNSt13_Rb_tree_nodeISt4pairIKSs14themeparameterEEC1IIRKS3_EEEDpOT_'
// Alternative name is '_ZNSt13_Rb_tree_nodeISt4pairIKSs14themeparameterEEC1IJRKS3_EEEDpOT_'
_DWORD *__fastcall std::_Rb_tree_node<std::pair<std::string const,themeparameter>>::_Rb_tree_node<std::pair<std::string const,themeparameter> const&>(
        _DWORD *a1,
        const std::string *a2)
{
  const std::string *v4; // r1
  int v5; // r0
  int v6; // r1
  int v7; // r2
  int v8; // r3
  int v9; // r1
  int v10; // r2
  int v11; // r3

  memset(a1, 0, 0x10u);
  v4 = a2;
  a2 = (const std::string *)((char *)a2 + 8);
  std::string::string((std::string *)(a1 + 4), v4);
  v5 = *(_DWORD *)a2;
  v6 = *((_DWORD *)a2 + 1);
  v7 = *((_DWORD *)a2 + 2);
  v8 = *((_DWORD *)a2 + 3);
  a2 = (const std::string *)((char *)a2 + 16);
  a1[6] = v5;
  a1[7] = v6;
  a1[8] = v7;
  a1[9] = v8;
  v9 = *((_DWORD *)a2 + 1);
  v10 = *((_DWORD *)a2 + 2);
  v11 = *((_DWORD *)a2 + 3);
  a1[10] = *(_DWORD *)a2;
  a1[11] = v9;
  a1[12] = v10;
  a1[13] = v11;
  return a1;
}


//----- (00012362) --------------------------------------------------------
_DWORD *__fastcall std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_copy(
        int a1,
        int *a2,
        int a3)
{
  _DWORD *v6; // r0
  _DWORD *v7; // r4
  int v8; // r1
  int v9; // r2
  int v10; // r3
  int v11; // r1
  int v12; // r2
  int v13; // r3
  int v14; // r3
  int v15; // r1
  int *v16; // r6
  _DWORD *v17; // r7
  _DWORD *v18; // r0
  _DWORD *v19; // r5
  int v20; // r3
  int v21; // r1

  v6 = (_DWORD *)operator new(0x38u);
  v7 = v6;
  if ( v6 )
  {
    memset(v6, 0, 0x10u);
    std::string::string((std::string *)(v7 + 4), (const std::string *)(a2 + 4));
    v8 = a2[7];
    v9 = a2[8];
    v10 = a2[9];
    v7[6] = a2[6];
    v7[7] = v8;
    v7[8] = v9;
    v7[9] = v10;
    v11 = a2[11];
    v12 = a2[12];
    v13 = a2[13];
    v7[10] = a2[10];
    v7[11] = v11;
    v7[12] = v12;
    v7[13] = v13;
  }
  v14 = *a2;
  v7[1] = a3;
  *v7 = v14;
  v7[2] = 0;
  v7[3] = 0;
  v15 = a2[3];
  if ( v15 )
    v7[3] = std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_copy(
              a1,
              v15,
              v7);
  v16 = (int *)a2[2];
  v17 = v7;
  while ( v16 )
  {
    v18 = (_DWORD *)operator new(0x38u);
    v19 = v18;
    if ( v18 )
      std::_Rb_tree_node<std::pair<std::string const,themeparameter>>::_Rb_tree_node<std::pair<std::string const,themeparameter> const&>(
        v18,
        (const std::string *)(v16 + 4));
    v20 = *v16;
    v19[2] = 0;
    v19[3] = 0;
    *v19 = v20;
    v17[2] = v19;
    v19[1] = v17;
    v21 = v16[3];
    if ( v21 )
      v19[3] = std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_copy(
                 a1,
                 v21,
                 v19);
    v16 = (int *)v16[2];
    v17 = v19;
  }
  return v7;
}


//----- (00012402) --------------------------------------------------------
// Alternative name is '_ZN12rendererdataC1ERKS_'
int __fastcall rendererdata::rendererdata(int a1, int a2)
{
  int v2; // r6
  int v5; // r7
  int *v6; // r1
  _DWORD *v7; // r0
  _DWORD *v8; // r3

  v2 = a1 + 20;
  v5 = a1 + 16;
  *(_BYTE *)a1 = *(_BYTE *)a2;
  *(_QWORD *)(a1 + 8) = *(_QWORD *)(a2 + 8);
  memset((void *)(a1 + 20), 0, 0x10u);
  *(_DWORD *)(a1 + 28) = v2;
  *(_DWORD *)(a1 + 36) = 0;
  *(_DWORD *)(a1 + 32) = v2;
  v6 = *(int **)(a2 + 24);
  if ( v6 )
  {
    v7 = std::_Rb_tree<std::string,std::pair<std::string const,themeparameter>,std::_Select1st<std::pair<std::string const,themeparameter>>,std::less<std::string>,std::allocator<std::pair<std::string const,themeparameter>>>::_M_copy(
           v5,
           v6,
           v2);
    v8 = v7;
    *(_DWORD *)(a1 + 24) = v7;
    while ( v8[2] )
      v8 = (_DWORD *)v8[2];
    *(_DWORD *)(a1 + 28) = v8;
    while ( v7[3] )
      v7 = (_DWORD *)v7[3];
    *(_DWORD *)(a1 + 32) = v7;
    *(_DWORD *)(a1 + 36) = *(_DWORD *)(a2 + 36);
  }
  *(_DWORD *)(a1 + 40) = *(_DWORD *)(a2 + 40);
  *(_DWORD *)(a1 + 44) = *(_DWORD *)(a2 + 44);
  *(_DWORD *)(a1 + 48) = *(_DWORD *)(a2 + 48);
  *(_DWORD *)(a1 + 52) = *(_DWORD *)(a2 + 52);
  *(_DWORD *)(a1 + 56) = *(_DWORD *)(a2 + 56);
  *(_DWORD *)(a1 + 60) = *(_DWORD *)(a2 + 60);
  *(_DWORD *)(a1 + 64) = *(_DWORD *)(a2 + 64);
  *(_DWORD *)(a1 + 68) = *(_DWORD *)(a2 + 68);
  *(_DWORD *)(a1 + 72) = *(_DWORD *)(a2 + 72);
  *(_DWORD *)(a1 + 76) = *(_DWORD *)(a2 + 76);
  *(_DWORD *)(a1 + 80) = *(_DWORD *)(a2 + 80);
  *(_DWORD *)(a1 + 84) = *(_DWORD *)(a2 + 84);
  *(_DWORD *)(a1 + 88) = *(_DWORD *)(a2 + 88);
  *(_DWORD *)(a1 + 92) = *(_DWORD *)(a2 + 92);
  *(_DWORD *)(a1 + 96) = *(_DWORD *)(a2 + 96);
  *(_DWORD *)(a1 + 100) = *(_DWORD *)(a2 + 100);
  *(_BYTE *)(a1 + 104) = *(_BYTE *)(a2 + 104);
  *(_BYTE *)(a1 + 105) = *(_BYTE *)(a2 + 105);
  *(_DWORD *)(a1 + 108) = *(_DWORD *)(a2 + 108);
  *(_DWORD *)(a1 + 112) = *(_DWORD *)(a2 + 112);
  *(_DWORD *)(a1 + 116) = *(_DWORD *)(a2 + 116);
  *(_DWORD *)(a1 + 120) = *(_DWORD *)(a2 + 120);
  *(_DWORD *)(a1 + 124) = *(_DWORD *)(a2 + 124);
  *(_DWORD *)(a1 + 128) = *(_DWORD *)(a2 + 128);
  *(_DWORD *)(a1 + 132) = *(_DWORD *)(a2 + 132);
  *(_DWORD *)(a1 + 136) = *(_DWORD *)(a2 + 136);
  *(_DWORD *)(a1 + 140) = *(_DWORD *)(a2 + 140);
  *(_DWORD *)(a1 + 144) = *(_DWORD *)(a2 + 144);
  *(_DWORD *)(a1 + 148) = *(_DWORD *)(a2 + 148);
  *(_DWORD *)(a1 + 152) = *(_DWORD *)(a2 + 152);
  return a1;
}


//----- (0001320C) --------------------------------------------------------
// Alternative name is '__aeabi_ldiv0'
int _aeabi_idiv0()
{
  return raise(8);
}


//----- (00013292) --------------------------------------------------------
int (*__fastcall sub_13292(int a1))()
{
  if ( a1 == 1 )
    return _aeabi_unwind_cpp_pr1;
  if ( a1 == 2 )
    return _aeabi_unwind_cpp_pr2;
  if ( a1 )
    return 0;
  return _aeabi_unwind_cpp_pr0;
}
// 1392C: using guessed type int _aeabi_unwind_cpp_pr0();
// 13930: using guessed type int _aeabi_unwind_cpp_pr1();
// 13934: using guessed type int _aeabi_unwind_cpp_pr2();


//----- (000134C4) --------------------------------------------------------
int __fastcall Unwind_GetCFA(int a1)
{
  return *(_DWORD *)(a1 + 68);
}


//----- (000134C8) --------------------------------------------------------
int __fastcall _gnu_Unwind_RaiseException(int a1, _DWORD *a2)
{
  int *v2; // r5
  int v5; // r0
  int v6; // r1
  int v7; // r2
  int v8; // r3
  int v9; // r0
  int v10; // r1
  int v11; // r2
  int v12; // r3
  int v13; // r0
  int v14; // r1
  int v15; // r2
  int v16; // r3
  int v17; // r1
  int v18; // r2
  int v19; // r3
  int v20; // r4
  _DWORD v22[16]; // [sp+0h] [bp-1E0h] BYREF
  int v23; // [sp+40h] [bp-1A0h]

  v2 = a2 + 1;
  a2[16] = a2[15];
  v5 = a2[1];
  v6 = a2[2];
  v7 = v2[2];
  v8 = v2[3];
  v2 += 4;
  v22[1] = v5;
  v22[2] = v6;
  v22[3] = v7;
  v22[4] = v8;
  v9 = *v2;
  v10 = v2[1];
  v11 = v2[2];
  v12 = v2[3];
  v2 += 4;
  v22[5] = v9;
  v22[6] = v10;
  v22[7] = v11;
  v22[8] = v12;
  v13 = *v2;
  v14 = v2[1];
  v15 = v2[2];
  v16 = v2[3];
  v2 += 4;
  v22[9] = v13;
  v22[10] = v14;
  v22[11] = v15;
  v22[12] = v16;
  v17 = v2[1];
  v18 = v2[2];
  v19 = v2[3];
  v22[13] = *v2;
  v22[14] = v17;
  v22[15] = v18;
  v23 = v19;
  v22[0] = -1;
  while ( !sub_132C4((_DWORD *)a1, v23) )
  {
    v20 = (*(int (__fastcall **)(_DWORD, int, _DWORD *))(a1 + 16))(0, a1, v22);
    if ( v20 != 8 )
    {
      sub_13368(v22);
      if ( v20 == 6 )
        sub_133C8(a1, (int)a2);
      return 9;
    }
  }
  return 9;
}


//----- (0001352A) --------------------------------------------------------
int __fastcall _gnu_Unwind_ForcedUnwind(int a1, int a2, int a3, int a4)
{
  int v4; // r2

  *(_DWORD *)(a1 + 24) = a3;
  v4 = *(_DWORD *)(a4 + 60);
  *(_DWORD *)(a1 + 12) = a2;
  *(_DWORD *)(a4 + 64) = v4;
  return sub_13402(a1, a4, 0);
}


//----- (0001353E) --------------------------------------------------------
void __fastcall __noreturn _gnu_Unwind_Resume(int a1, int a2)
{
  int v3; // r6
  int v5; // r0
  int v6; // r1
  int v7; // r2
  int v8; // r3
  int savedregs; // [sp+0h] [bp+0h]

  v3 = *(_DWORD *)(a1 + 12);
  *(_DWORD *)(a2 + 64) = *(_DWORD *)(a1 + 20);
  if ( v3 )
  {
    sub_13402(a1, a2, 1);
    goto LABEL_7;
  }
  v5 = (*(int (__fastcall **)(int, int, int))(a1 + 16))(2, a1, a2);
  if ( v5 != 7 )
  {
    if ( v5 != 8 )
      goto LABEL_7;
    sub_133C8(a1, a2);
  }
  nullsub_1(0, *(_DWORD *)(a2 + 64));
  restore_core_regs(a2 + 4, v6, v7, v8, savedregs);
LABEL_7:
  abort();
}
// 13578: variable 'v6' is possibly undefined
// 13578: variable 'v7' is possibly undefined
// 13578: variable 'v8' is possibly undefined
// 13578: variable 'savedregs' is possibly undefined
// 133C6: using guessed type int __fastcall nullsub_1(_DWORD, _DWORD);


//----- (00013580) --------------------------------------------------------
int __fastcall _gnu_Unwind_Resume_or_Rethrow(int a1, _DWORD *a2)
{
  if ( !*(_DWORD *)(a1 + 12) )
    return _gnu_Unwind_RaiseException(a1, a2);
  a2[16] = a2[15];
  return sub_13402(a1, (int)a2, 0);
}


//----- (00013592) --------------------------------------------------------
int __fastcall Unwind_DeleteException(int result)
{
  int (__fastcall *v1)(int, int); // r3

  v1 = *(int (__fastcall **)(int, int))(result + 8);
  if ( v1 )
    return v1(1, result);
  return result;
}


//----- (000135A0) --------------------------------------------------------
int __fastcall Unwind_VRS_Get(int a1, int a2, unsigned __int64 a3, _DWORD *a4)
{
  int result; // r0

  switch ( a2 )
  {
    case 0:
      if ( a3 > 0xF )
        goto LABEL_5;
      LODWORD(a3) = a1 + 4 * a3;
      *a4 = *(_DWORD *)(a3 + 4);
      result = HIDWORD(a3);
      break;
    case 1:
    case 3:
    case 4:
      result = 1;
      break;
    default:
LABEL_5:
      result = 2;
      break;
  }
  return result;
}


//----- (000135E4) --------------------------------------------------------
int __fastcall Unwind_VRS_Set(int a1, int a2, unsigned __int64 a3, _DWORD *a4)
{
  int result; // r0

  switch ( a2 )
  {
    case 0:
      if ( a3 > 0xF )
        goto LABEL_5;
      LODWORD(a3) = a1 + 4 * a3;
      *(_DWORD *)(a3 + 4) = *a4;
      result = HIDWORD(a3);
      break;
    case 1:
    case 3:
    case 4:
      result = 1;
      break;
    default:
LABEL_5:
      result = 2;
      break;
  }
  return result;
}


//----- (0001362A) --------------------------------------------------------
int __fastcall _gnu_Unwind_Backtrace(int (__fastcall *a1)(_DWORD *, int), int a2, _DWORD *a3)
{
  int *v3; // r5
  int v6; // r0
  int v7; // r1
  int v8; // r2
  int v9; // r3
  int v10; // r0
  int v11; // r1
  int v12; // r2
  int v13; // r3
  int v14; // r0
  int v15; // r1
  int v16; // r2
  int v17; // r3
  int v18; // r1
  int v19; // r2
  int v20; // r3
  int v21; // r5
  int v22; // r0
  _DWORD v24[22]; // [sp+0h] [bp-238h] BYREF
  _DWORD v25[16]; // [sp+58h] [bp-1E0h] BYREF
  int v26; // [sp+98h] [bp-1A0h]

  v3 = a3 + 1;
  a3[16] = a3[15];
  v6 = a3[1];
  v7 = a3[2];
  v8 = a3[3];
  v9 = v3[3];
  v3 += 4;
  v25[1] = v6;
  v25[2] = v7;
  v25[3] = v8;
  v25[4] = v9;
  v10 = *v3;
  v11 = v3[1];
  v12 = v3[2];
  v13 = v3[3];
  v3 += 4;
  v25[5] = v10;
  v25[6] = v11;
  v25[7] = v12;
  v25[8] = v13;
  v14 = *v3;
  v15 = v3[1];
  v16 = v3[2];
  v17 = v3[3];
  v3 += 4;
  v25[9] = v14;
  v25[10] = v15;
  v25[11] = v16;
  v25[12] = v17;
  v18 = v3[1];
  v19 = v3[2];
  v20 = v3[3];
  v25[13] = *v3;
  v25[14] = v18;
  v25[15] = v19;
  v26 = v20;
  v25[0] = -1;
  do
  {
    if ( sub_132C4(v24, v26) )
      break;
    sub_13610((int)v25, 0xCu, (int)v24);
    if ( a1(v25, a2) )
      break;
    v22 = ((int (__fastcall *)(int, _DWORD *, _DWORD *))v24[4])(8, v24, v25);
    v21 = v22;
    if ( v22 == 5 )
      goto LABEL_8;
  }
  while ( v22 != 9 );
  v21 = 9;
LABEL_8:
  sub_13368(v25);
  return v21;
}


//----- (0001392C) --------------------------------------------------------
int __fastcall _aeabi_unwind_cpp_pr0(char a1, void (__noreturn **a2)(void *), unsigned int *a3)
{
  return sub_136A4(a1, a2, a3, 0);
}


//----- (00013930) --------------------------------------------------------
int __fastcall _aeabi_unwind_cpp_pr1(char a1, void (__noreturn **a2)(void *), unsigned int *a3)
{
  return sub_136A4(a1, a2, a3, 1);
}


//----- (00013934) --------------------------------------------------------
int __fastcall _aeabi_unwind_cpp_pr2(char a1, void (__noreturn **a2)(void *), unsigned int *a3)
{
  return sub_136A4(a1, a2, a3, 2);
}


//----- (00013938) --------------------------------------------------------
int __fastcall Unwind_VRS_Pop(unsigned int *a1, int a2, unsigned __int64 a3)
{
  int v4; // r5
  int v5; // r7
  unsigned int *v6; // r3
  unsigned int v7; // r2
  int result; // r0
  unsigned int v9; // r6
  int v10; // r8
  unsigned int v11; // r7
  unsigned int v12; // r6
  unsigned __int16 v13; // r7
  int v14; // r7
  unsigned int v15; // r3
  int v16; // r2
  unsigned int v17; // r1
  char *i; // r6
  bool v19; // cf
  int v20; // t1
  int *v21; // r2
  int j; // r3
  int v23; // r1
  unsigned int v24; // r3
  unsigned int v25; // r3
  _QWORD *v26; // r0
  unsigned int v27; // r2
  int v28; // r8
  unsigned int v29; // r0
  int v30; // r1
  int v31; // t1
  int v32[34]; // [sp+80h] [bp-88h] BYREF

  v4 = HIDWORD(a3);
  v5 = a3;
  switch ( a2 )
  {
    case 0:
      if ( HIDWORD(a3) )
        return 2;
      v6 = (unsigned int *)a1[14];
      do
      {
        if ( ((1 << v4) & (unsigned __int16)v5) != 0 )
        {
          v7 = *v6++;
          a1[v4 + 1] = v7;
        }
        ++v4;
      }
      while ( v4 != 16 );
      result = v5 & 0x2000;
      if ( (v5 & 0x2000) != 0 )
        return 0;
      a1[14] = (unsigned int)v6;
      return result;
    case 1:
      if ( (HIDWORD(a3) & 0xFFFFFFFB) != 1 )
        return 2;
      v9 = WORD1(a3);
      v10 = (unsigned __int16)a3;
      v11 = (unsigned __int16)a3 + WORD1(a3);
      if ( HIDWORD(a3) == 1 )
      {
        if ( v11 > 0x10 || v9 > 0xF )
          return 2;
      }
      else
      {
        if ( v11 > 0x20 )
          return 2;
        if ( v9 > 0xF )
        {
          if ( (_WORD)a3 )
            return 2;
          goto LABEL_43;
        }
        if ( v11 > 0x10 )
          return 2;
      }
      v25 = *a1;
      if ( (*a1 & 1) != 0 )
      {
        *a1 = v25 & 0xFFFFFFFE;
        v26 = a1 + 18;
        if ( v4 == 5 )
        {
          *a1 = v25 & 0xFFFFFFFC | 2;
          _gnu_Unwind_Save_VFP_D(v26);
        }
        else
        {
          *a1 = v25 & 0xFFFFFFFC;
          _gnu_Unwind_Save_VFP(v26);
        }
      }
      if ( v4 == 1 )
        _gnu_Unwind_Save_VFP(v32);
      else
        _gnu_Unwind_Save_VFP_D(v32);
LABEL_43:
      v27 = a1[14];
      v24 = v27;
      if ( v10 > 0 )
      {
        v28 = 2 * v10;
        v29 = v27 - 4;
        v30 = v28;
        while ( 1 )
        {
          v19 = v30-- != 0;
          if ( !v19 )
            break;
          v31 = *(_DWORD *)(v29 + 4);
          v29 += 4;
          *(int *)((char *)&v32[2 * v9] + v29 - v27) = v31;
        }
        v24 = v27 + 4 * v28;
      }
      if ( v4 == 1 )
        v24 += 4;
      a1[14] = v24;
      if ( v4 == 1 )
      {
        _gnu_Unwind_Restore_VFP();
      }
      else if ( v9 <= 0xF )
      {
        _gnu_Unwind_Restore_VFP_D();
      }
      return 0;
    case 3:
      if ( HIDWORD(a3) != 3 )
        return 2;
      v12 = WORD1(a3);
      v13 = a3;
      if ( (unsigned __int16)a3 + WORD1(a3) > 0x10u )
        return 2;
      if ( (*a1 & 8) != 0 )
      {
        *a1 &= ~8u;
        _gnu_Unwind_Save_WMMXD();
      }
      v14 = 2 * v13;
      _gnu_Unwind_Save_WMMXD();
      v15 = a1[14];
      v16 = v14;
      v17 = v15 - 4;
      for ( i = (char *)&v32[2 * v12] - v15; ; *(_DWORD *)&i[v17] = v20 )
      {
        v19 = v16-- != 0;
        if ( !v19 )
          break;
        v20 = *(_DWORD *)(v17 + 4);
        v17 += 4;
      }
      a1[14] = v15 + 4 * v14;
      _gnu_Unwind_Restore_WMMXD(v32);
      return 0;
    case 4:
      if ( a3 > 0x10 )
        return 2;
      if ( (*a1 & 0x10) != 0 )
      {
        *a1 &= ~0x10u;
        _gnu_Unwind_Save_WMMXC();
      }
      _gnu_Unwind_Save_WMMXC();
      v21 = (int *)a1[14];
      for ( j = 0; j != 4; ++j )
      {
        if ( ((1 << j) & v5) != 0 )
        {
          v23 = *v21++;
          v32[j] = v23;
        }
      }
      a1[14] = (unsigned int)v21;
      _gnu_Unwind_Restore_WMMXC(v32);
      return 0;
    default:
      return 2;
  }
}
// 13A48: conditional instruction was optimized away because r7.4==0
// 13AB6: conditional instruction was optimized away because r7.4==0
// 13AD6: conditional instruction was optimized away because r7.4==0
// 13ADC: conditional instruction was optimized away because r6.4<10u
// 13AE4: conditional instruction was optimized away because r7.4==0
// 13B26: conditional instruction was optimized away because r7.4==0
// 13B4A: conditional instruction was optimized away because r3.4==1


//----- (00013B5C) --------------------------------------------------------
void __fastcall restore_core_regs(int a1, int a2, int a3, int a4, int a5)
{
  *(_DWORD *)(*(_DWORD *)(a1 + 52) - 4) = *(_DWORD *)(a1 + 60);
  __asm { POP             {PC} }
}
// 13B72: unbalanced stack, ignored a potential tail call


//----- (00013B74) --------------------------------------------------------
void _gnu_Unwind_Restore_VFP()
{
  ;
}


//----- (00013B7C) --------------------------------------------------------
_QWORD *__fastcall _gnu_Unwind_Save_VFP(_QWORD *result)
{
  __int64 v1; // d0
  __int64 v2; // d1
  __int64 v3; // d2
  __int64 v4; // d3
  __int64 v5; // d4
  __int64 v6; // d5
  __int64 v7; // d6
  __int64 v8; // d7
  __int64 v9; // d8
  __int64 v10; // d9
  __int64 v11; // d10
  __int64 v12; // d11
  __int64 v13; // d12
  __int64 v14; // d13
  __int64 v15; // d14
  __int64 v16; // d15

  *result = v1;
  result[1] = v2;
  result[2] = v3;
  result[3] = v4;
  result[4] = v5;
  result[5] = v6;
  result[6] = v7;
  result[7] = v8;
  result[8] = v9;
  result[9] = v10;
  result[10] = v11;
  result[11] = v12;
  result[12] = v13;
  result[13] = v14;
  result[14] = v15;
  result[15] = v16;
  return result;
}
// 13B7C: variable 'v1' is possibly undefined
// 13B7C: variable 'v2' is possibly undefined
// 13B7C: variable 'v3' is possibly undefined
// 13B7C: variable 'v4' is possibly undefined
// 13B7C: variable 'v5' is possibly undefined
// 13B7C: variable 'v6' is possibly undefined
// 13B7C: variable 'v7' is possibly undefined
// 13B7C: variable 'v8' is possibly undefined
// 13B7C: variable 'v9' is possibly undefined
// 13B7C: variable 'v10' is possibly undefined
// 13B7C: variable 'v11' is possibly undefined
// 13B7C: variable 'v12' is possibly undefined
// 13B7C: variable 'v13' is possibly undefined
// 13B7C: variable 'v14' is possibly undefined
// 13B7C: variable 'v15' is possibly undefined
// 13B7C: variable 'v16' is possibly undefined


//----- (00013B84) --------------------------------------------------------
void _gnu_Unwind_Restore_VFP_D()
{
  ;
}


//----- (00013B8C) --------------------------------------------------------
_QWORD *__fastcall _gnu_Unwind_Save_VFP_D(_QWORD *result)
{
  __int64 v1; // d0
  __int64 v2; // d1
  __int64 v3; // d2
  __int64 v4; // d3
  __int64 v5; // d4
  __int64 v6; // d5
  __int64 v7; // d6
  __int64 v8; // d7
  __int64 v9; // d8
  __int64 v10; // d9
  __int64 v11; // d10
  __int64 v12; // d11
  __int64 v13; // d12
  __int64 v14; // d13
  __int64 v15; // d14
  __int64 v16; // d15

  *result = v1;
  result[1] = v2;
  result[2] = v3;
  result[3] = v4;
  result[4] = v5;
  result[5] = v6;
  result[6] = v7;
  result[7] = v8;
  result[8] = v9;
  result[9] = v10;
  result[10] = v11;
  result[11] = v12;
  result[12] = v13;
  result[13] = v14;
  result[14] = v15;
  result[15] = v16;
  return result;
}
// 13B8C: variable 'v1' is possibly undefined
// 13B8C: variable 'v2' is possibly undefined
// 13B8C: variable 'v3' is possibly undefined
// 13B8C: variable 'v4' is possibly undefined
// 13B8C: variable 'v5' is possibly undefined
// 13B8C: variable 'v6' is possibly undefined
// 13B8C: variable 'v7' is possibly undefined
// 13B8C: variable 'v8' is possibly undefined
// 13B8C: variable 'v9' is possibly undefined
// 13B8C: variable 'v10' is possibly undefined
// 13B8C: variable 'v11' is possibly undefined
// 13B8C: variable 'v12' is possibly undefined
// 13B8C: variable 'v13' is possibly undefined
// 13B8C: variable 'v14' is possibly undefined
// 13B8C: variable 'v15' is possibly undefined
// 13B8C: variable 'v16' is possibly undefined


//----- (00013B94) --------------------------------------------------------
void _gnu_Unwind_Restore_VFP_D_16_to_31()
{
  ;
}


//----- (00013B9C) --------------------------------------------------------
_QWORD *__fastcall _gnu_Unwind_Save_VFP_D_16_to_31(_QWORD *result)
{
  __int64 v1; // d16
  __int64 v2; // d17
  __int64 v3; // d18
  __int64 v4; // d19
  __int64 v5; // d20
  __int64 v6; // d21
  __int64 v7; // d22
  __int64 v8; // d23
  __int64 v9; // d24
  __int64 v10; // d25
  __int64 v11; // d26
  __int64 v12; // d27
  __int64 v13; // d28
  __int64 v14; // d29
  __int64 v15; // d30
  __int64 v16; // d31

  *result = v1;
  result[1] = v2;
  result[2] = v3;
  result[3] = v4;
  result[4] = v5;
  result[5] = v6;
  result[6] = v7;
  result[7] = v8;
  result[8] = v9;
  result[9] = v10;
  result[10] = v11;
  result[11] = v12;
  result[12] = v13;
  result[13] = v14;
  result[14] = v15;
  result[15] = v16;
  return result;
}
// 13B9C: variable 'v1' is possibly undefined
// 13B9C: variable 'v2' is possibly undefined
// 13B9C: variable 'v3' is possibly undefined
// 13B9C: variable 'v4' is possibly undefined
// 13B9C: variable 'v5' is possibly undefined
// 13B9C: variable 'v6' is possibly undefined
// 13B9C: variable 'v7' is possibly undefined
// 13B9C: variable 'v8' is possibly undefined
// 13B9C: variable 'v9' is possibly undefined
// 13B9C: variable 'v10' is possibly undefined
// 13B9C: variable 'v11' is possibly undefined
// 13B9C: variable 'v12' is possibly undefined
// 13B9C: variable 'v13' is possibly undefined
// 13B9C: variable 'v14' is possibly undefined
// 13B9C: variable 'v15' is possibly undefined
// 13B9C: variable 'v16' is possibly undefined


//----- (00013BA4) --------------------------------------------------------
int *__fastcall _gnu_Unwind_Restore_WMMXD(int *a1)
{
  int *v5; // r0

  _T1 = *a1;
  v5 = a1 + 2;
  __asm { LDCL            p1, c0, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c1, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c2, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c3, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c4, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c5, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c6, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c7, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c8, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c9, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c10, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c11, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c12, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c13, [R0],#8 }
  _T1 = *v5;
  v5 += 2;
  __asm { LDCL            p1, c14, [R0],#8 }
  _T1 = *v5;
  __asm { LDCL            p1, c15, [R0],#8 }
  return v5 + 2;
}


//----- (00013BE8) --------------------------------------------------------
void _gnu_Unwind_Save_WMMXD()
{
  __asm
  {
    STCL            p1, c0, [R0],#8
    STCL            p1, c1, [R0],#8
    STCL            p1, c2, [R0],#8
    STCL            p1, c3, [R0],#8
    STCL            p1, c4, [R0],#8
    STCL            p1, c5, [R0],#8
    STCL            p1, c6, [R0],#8
    STCL            p1, c7, [R0],#8
    STCL            p1, c8, [R0],#8
    STCL            p1, c9, [R0],#8
    STCL            p1, c10, [R0],#8
    STCL            p1, c11, [R0],#8
    STCL            p1, c12, [R0],#8
    STCL            p1, c13, [R0],#8
    STCL            p1, c14, [R0],#8
    STCL            p1, c15, [R0],#8
  }
}


//----- (00013C2C) --------------------------------------------------------
int *__fastcall _gnu_Unwind_Restore_WMMXC(int *a1)
{
  int *v5; // r0

  _T1 = *a1;
  v5 = a1 + 1;
  __asm { LDC             p1, c8, [R0],#4 }
  _T1 = *v5++;
  __asm { LDC             p1, c9, [R0],#4 }
  _T1 = *v5++;
  __asm { LDC             p1, c10, [R0],#4 }
  _T1 = *v5;
  __asm { LDC             p1, c11, [R0],#4 }
  return v5 + 1;
}


//----- (00013C40) --------------------------------------------------------
void _gnu_Unwind_Save_WMMXC()
{
  __asm
  {
    STC             p1, c8, [R0],#4
    STC             p1, c9, [R0],#4
    STC             p1, c10, [R0],#4
    STC             p1, c11, [R0],#4
  }
}


//----- (00013C54) --------------------------------------------------------
int __fastcall __Unwind_RaiseException(int a1, int a2, int a3, int a4)
{
  int v4; // r4
  int v5; // r5
  int v6; // r6
  int v7; // r7
  int v8; // r8
  int v9; // r9
  int v10; // r10
  int v11; // r11
  int v12; // r12
  int (__fastcall *v13)(int); // lr
  int v14; // r0
  _DWORD v16[5]; // [sp+4h] [bp-40h] BYREF
  int v17; // [sp+18h] [bp-2Ch]
  int v18; // [sp+1Ch] [bp-28h]
  int v19; // [sp+20h] [bp-24h]
  int v20; // [sp+24h] [bp-20h]
  int v21; // [sp+28h] [bp-1Ch]
  int v22; // [sp+2Ch] [bp-18h]
  int v23; // [sp+30h] [bp-14h]
  int v24; // [sp+34h] [bp-10h]
  int v25; // [sp+38h] [bp-Ch]
  int v26; // [sp+3Ch] [bp-8h]
  int (__fastcall *v27)(int); // [sp+40h] [bp-4h]

  v26 = v12;
  v27 = v13;
  v16[1] = a1;
  v16[2] = a2;
  v16[3] = a3;
  v16[4] = a4;
  v17 = v4;
  v18 = v5;
  v19 = v6;
  v20 = v7;
  v21 = v8;
  v22 = v9;
  v23 = v10;
  v24 = v11;
  v25 = v12;
  v16[0] = 0;
  v14 = _gnu_Unwind_RaiseException(a1, v16);
  return v27(v14);
}
// 13C58: variable 'v12' is possibly undefined
// 13C58: variable 'v13' is possibly undefined
// 13C5C: variable 'v4' is possibly undefined
// 13C5C: variable 'v5' is possibly undefined
// 13C5C: variable 'v6' is possibly undefined
// 13C5C: variable 'v7' is possibly undefined
// 13C5C: variable 'v8' is possibly undefined
// 13C5C: variable 'v9' is possibly undefined
// 13C5C: variable 'v10' is possibly undefined
// 13C5C: variable 'v11' is possibly undefined


//----- (00013C78) --------------------------------------------------------
void __fastcall __noreturn __Unwind_Resume(int a1, int a2, int a3, int a4)
{
  int v4; // r12
  int v5; // lr
  _DWORD v6[13]; // [sp+4h] [bp-40h] BYREF
  int v7; // [sp+38h] [bp-Ch]
  int v8; // [sp+3Ch] [bp-8h]
  int v9; // [sp+40h] [bp-4h]

  v8 = v4;
  v9 = v5;
  v6[1] = a1;
  v6[2] = a2;
  v6[3] = a3;
  v6[4] = a4;
  v7 = v4;
  v6[0] = 0;
  _gnu_Unwind_Resume(a1, (int)v6);
}
// 13C7C: variable 'v4' is possibly undefined
// 13C7C: variable 'v5' is possibly undefined


//----- (00013C9C) --------------------------------------------------------
void __fastcall __noreturn __Unwind_Resume_or_Rethrow(int a1, int a2, int a3, int a4)
{
  int v4; // r4
  int v5; // r5
  int v6; // r6
  int v7; // r7
  int v8; // r8
  int v9; // r9
  int v10; // r10
  int v11; // r11
  int v12; // r12
  void (__fastcall *v13)(int); // lr
  int v14; // r0
  _DWORD v15[5]; // [sp+4h] [bp-40h] BYREF
  int v16; // [sp+18h] [bp-2Ch]
  int v17; // [sp+1Ch] [bp-28h]
  int v18; // [sp+20h] [bp-24h]
  int v19; // [sp+24h] [bp-20h]
  int v20; // [sp+28h] [bp-1Ch]
  int v21; // [sp+2Ch] [bp-18h]
  int v22; // [sp+30h] [bp-14h]
  int v23; // [sp+34h] [bp-10h]
  int v24; // [sp+38h] [bp-Ch]
  int v25; // [sp+3Ch] [bp-8h]
  void (__fastcall *v26)(int); // [sp+40h] [bp-4h]

  v25 = v12;
  v26 = v13;
  v15[1] = a1;
  v15[2] = a2;
  v15[3] = a3;
  v15[4] = a4;
  v16 = v4;
  v17 = v5;
  v18 = v6;
  v19 = v7;
  v20 = v8;
  v21 = v9;
  v22 = v10;
  v23 = v11;
  v24 = v12;
  v15[0] = 0;
  v14 = _gnu_Unwind_Resume_or_Rethrow(a1, v15);
  v26(v14);
}
// 13CA0: variable 'v12' is possibly undefined
// 13CA0: variable 'v13' is possibly undefined
// 13CA4: variable 'v4' is possibly undefined
// 13CA4: variable 'v5' is possibly undefined
// 13CA4: variable 'v6' is possibly undefined
// 13CA4: variable 'v7' is possibly undefined
// 13CA4: variable 'v8' is possibly undefined
// 13CA4: variable 'v9' is possibly undefined
// 13CA4: variable 'v10' is possibly undefined
// 13CA4: variable 'v11' is possibly undefined


//----- (00013CC0) --------------------------------------------------------
int __fastcall __Unwind_ForcedUnwind(int a1, int a2, int a3, int a4)
{
  int v4; // r4
  int v5; // r5
  int v6; // r6
  int v7; // r7
  int v8; // r8
  int v9; // r9
  int v10; // r10
  int v11; // r11
  int v12; // r12
  int (__fastcall *v13)(int); // lr
  int v14; // r0
  _DWORD v16[5]; // [sp+4h] [bp-40h] BYREF
  int v17; // [sp+18h] [bp-2Ch]
  int v18; // [sp+1Ch] [bp-28h]
  int v19; // [sp+20h] [bp-24h]
  int v20; // [sp+24h] [bp-20h]
  int v21; // [sp+28h] [bp-1Ch]
  int v22; // [sp+2Ch] [bp-18h]
  int v23; // [sp+30h] [bp-14h]
  int v24; // [sp+34h] [bp-10h]
  int v25; // [sp+38h] [bp-Ch]
  int v26; // [sp+3Ch] [bp-8h]
  int (__fastcall *v27)(int); // [sp+40h] [bp-4h]

  v26 = v12;
  v27 = v13;
  v16[1] = a1;
  v16[2] = a2;
  v16[3] = a3;
  v16[4] = a4;
  v17 = v4;
  v18 = v5;
  v19 = v6;
  v20 = v7;
  v21 = v8;
  v22 = v9;
  v23 = v10;
  v24 = v11;
  v25 = v12;
  v16[0] = 0;
  v14 = _gnu_Unwind_ForcedUnwind(a1, a2, a3, (int)v16);
  return v27(v14);
}
// 13CC4: variable 'v12' is possibly undefined
// 13CC4: variable 'v13' is possibly undefined
// 13CC8: variable 'v4' is possibly undefined
// 13CC8: variable 'v5' is possibly undefined
// 13CC8: variable 'v6' is possibly undefined
// 13CC8: variable 'v7' is possibly undefined
// 13CC8: variable 'v8' is possibly undefined
// 13CC8: variable 'v9' is possibly undefined
// 13CC8: variable 'v10' is possibly undefined
// 13CC8: variable 'v11' is possibly undefined


//----- (00013CE4) --------------------------------------------------------
int __fastcall __Unwind_Backtrace(int (__fastcall *a1)(_DWORD *, int), int a2, int a3, int a4)
{
  int v4; // r4
  int v5; // r5
  int v6; // r6
  int v7; // r7
  int v8; // r8
  int v9; // r9
  int v10; // r10
  int v11; // r11
  int v12; // r12
  int (__fastcall *v13)(int); // lr
  int v14; // r0
  _DWORD v16[5]; // [sp+4h] [bp-40h] BYREF
  int v17; // [sp+18h] [bp-2Ch]
  int v18; // [sp+1Ch] [bp-28h]
  int v19; // [sp+20h] [bp-24h]
  int v20; // [sp+24h] [bp-20h]
  int v21; // [sp+28h] [bp-1Ch]
  int v22; // [sp+2Ch] [bp-18h]
  int v23; // [sp+30h] [bp-14h]
  int v24; // [sp+34h] [bp-10h]
  int v25; // [sp+38h] [bp-Ch]
  int v26; // [sp+3Ch] [bp-8h]
  int (__fastcall *v27)(int); // [sp+40h] [bp-4h]

  v26 = v12;
  v27 = v13;
  v16[1] = a1;
  v16[2] = a2;
  v16[3] = a3;
  v16[4] = a4;
  v17 = v4;
  v18 = v5;
  v19 = v6;
  v20 = v7;
  v21 = v8;
  v22 = v9;
  v23 = v10;
  v24 = v11;
  v25 = v12;
  v16[0] = 0;
  v14 = _gnu_Unwind_Backtrace(a1, a2, v16);
  return v27(v14);
}
// 13CE8: variable 'v12' is possibly undefined
// 13CE8: variable 'v13' is possibly undefined
// 13CEC: variable 'v4' is possibly undefined
// 13CEC: variable 'v5' is possibly undefined
// 13CEC: variable 'v6' is possibly undefined
// 13CEC: variable 'v7' is possibly undefined
// 13CEC: variable 'v8' is possibly undefined
// 13CEC: variable 'v9' is possibly undefined
// 13CEC: variable 'v10' is possibly undefined
// 13CEC: variable 'v11' is possibly undefined


//----- (00013D4E) --------------------------------------------------------
int __fastcall _gnu_unwind_execute(unsigned int *a1, int *a2, int a3, int a4)
{
  int v6; // r7
  int v7; // r0
  char v8; // r4
  unsigned __int64 v9; // r2
  unsigned __int8 v10; // r10
  int v11; // r10
  int v12; // r3
  int v13; // r3
  int v14; // r0
  __int16 v16; // r4
  int v17; // r0
  int v18; // r1
  unsigned __int64 v19; // r2
  bool v20; // nf
  unsigned __int64 v21; // r2
  unsigned int *v22; // r0
  int v23; // r1
  int v24; // r0
  char v25; // r4
  char i; // r0
  int v27; // r0
  int v28; // r0
  char v29; // r0
  int v30; // r2
  char v31; // r0
  int v32; // r0
  int v33; // r2
  char v34; // r0
  char v35; // r0
  int v36; // r2
  int v37; // [sp+Ch] [bp-4h] BYREF

  v37 = a4;
  v6 = 0;
  while ( 1 )
  {
    v7 = sub_13D08(a2);
    v8 = v7;
    if ( v7 == 176 )
      break;
    if ( (v7 & 0x80) == 0 )
    {
      HIDWORD(v9) = v7 & 0x80;
      LODWORD(v9) = 13;
      v10 = 4 * v7;
      Unwind_VRS_Get((int)a1, SHIDWORD(v9), v9, &v37);
      v11 = v10 + 4;
      if ( (v8 & 0x40) != 0 )
        v12 = v37 - v11;
      else
        v12 = v37 + v11;
      v37 = v12;
LABEL_20:
      v17 = (int)a1;
      v18 = 0;
      goto LABEL_21;
    }
    v13 = v7 & 0xF0;
    switch ( v13 )
    {
      case 128:
        v14 = sub_13D08(a2) | (v7 << 8);
        if ( v14 == 0x8000 )
          return 9;
        v16 = 16 * v14;
        if ( Unwind_VRS_Pop(a1, 0, (unsigned __int16)(16 * v14)) )
          return 9;
        if ( v16 < 0 )
          v6 = 1;
        break;
      case 144:
        if ( (v7 & 0xD) == 0xD )
          return 9;
        Unwind_VRS_Get((int)a1, 0, v7 & 0xF, &v37);
        goto LABEL_20;
      case 160:
        v20 = (v7 & 8) != 0;
        LODWORD(v21) = (4080 >> (~(_BYTE)v7 & 7)) & 0xFF0;
        v22 = a1;
        if ( v20 )
          LODWORD(v21) = v21 | 0x4000;
        v23 = 0;
        goto LABEL_31;
      case 176:
        if ( v7 == 177 )
        {
          v24 = sub_13D08(a2);
          LODWORD(v21) = v24;
          if ( !v24 )
            return 9;
          v23 = v24 & 0xF0;
          if ( (v24 & 0xF0) != 0 )
            return 9;
          v22 = a1;
          goto LABEL_31;
        }
        if ( v7 != 178 )
        {
          if ( v7 == 179 )
          {
            v29 = sub_13D08(a2);
            v23 = 1;
            LODWORD(v21) = v29 & 0xF0;
            HIDWORD(v21) = (v29 & 0xF) + 1;
            v22 = a1;
            goto LABEL_44;
          }
          if ( (v7 & 0xFC) == 0xB4 )
            return 9;
          v23 = 1;
          v30 = (v7 & 7) + 1;
          v22 = a1;
          LODWORD(v21) = v30 | 0x80000;
LABEL_31:
          HIDWORD(v21) = v23;
          goto LABEL_59;
        }
        v25 = 2;
        Unwind_VRS_Get((int)a1, 0, 0xDu, &v37);
        for ( i = sub_13D08(a2); ; i = sub_13D08(a2) )
        {
          v18 = i & 0x80;
          v27 = i & 0x7F;
          if ( !v18 )
            break;
          v28 = v27 << v25;
          v25 += 7;
          v37 += v28;
        }
        v37 += (v27 << v25) + 516;
        v17 = (int)a1;
LABEL_21:
        LODWORD(v19) = 13;
        HIDWORD(v19) = v18;
        Unwind_VRS_Set(v17, v18, v19, &v37);
        break;
      case 192:
        if ( v7 == 198 )
        {
          v31 = sub_13D08(a2);
          v23 = 3;
          LODWORD(v21) = v31 & 0xF0;
          HIDWORD(v21) = (v31 & 0xF) + 1;
          v22 = a1;
LABEL_44:
          LODWORD(v21) = HIDWORD(v21) | ((_DWORD)v21 << 12);
          goto LABEL_31;
        }
        if ( v7 != 199 )
        {
          if ( (v7 & 0xF8) != 0xC0 )
          {
            if ( v7 == 200 )
            {
              v34 = sub_13D08(a2);
              LODWORD(v21) = (v34 & 0xF0) + 16;
              HIDWORD(v21) = (v34 & 0xF) + 1;
            }
            else
            {
              if ( v7 != 201 )
                return 9;
              v35 = sub_13D08(a2);
              LODWORD(v21) = v35 & 0xF0;
              HIDWORD(v21) = (v35 & 0xF) + 1;
            }
            v22 = a1;
            v23 = 1;
            LODWORD(v21) = HIDWORD(v21) | ((_DWORD)v21 << 12);
LABEL_58:
            HIDWORD(v21) = 5;
            goto LABEL_59;
          }
          v23 = 3;
          v33 = (v7 & 0xF) + 1;
          v22 = a1;
          LODWORD(v21) = v33 | 0xA0000;
          goto LABEL_31;
        }
        v32 = sub_13D08(a2);
        LODWORD(v21) = v32;
        if ( !v32 )
          return 9;
        HIDWORD(v21) = v32 & 0xF0;
        if ( (v32 & 0xF0) != 0 )
          return 9;
        v22 = a1;
        v23 = 4;
LABEL_59:
        if ( Unwind_VRS_Pop(v22, v23, v21) )
          return 9;
        break;
      default:
        if ( (v7 & 0xF8) != 0xD0 )
          return 9;
        v23 = 1;
        v36 = (v7 & 7) + 1;
        v22 = a1;
        LODWORD(v21) = v36 | 0x80000;
        goto LABEL_58;
    }
  }
  if ( !v6 )
  {
    Unwind_VRS_Get((int)a1, 0, 0xEu, &v37);
    Unwind_VRS_Set((int)a1, 0, 0xFu, &v37);
  }
  return 0;
}


//----- (00013FAC) --------------------------------------------------------
int __fastcall _gnu_unwind_frame(int a1, unsigned int *a2, int a3, int a4)
{
  int v4; // r3
  int v5; // r3
  unsigned int *v7; // [sp+4h] [bp-Ch] BYREF
  int v8; // [sp+8h] [bp-8h]
  int v9; // [sp+Ch] [bp-4h]

  v7 = a2;
  v8 = a3;
  v9 = a4;
  v4 = *(_DWORD *)(a1 + 76);
  v7 = (unsigned int *)(*(_DWORD *)(v4 + 4) << 8);
  v8 = v4 + 8;
  LOBYTE(v9) = 3;
  v5 = *(unsigned __int8 *)(v4 + 7);
  BYTE1(v9) = v5;
  return _gnu_unwind_execute(a2, (int *)&v7, 3, v5);
}


//----- (00013FD6) --------------------------------------------------------
int Unwind_GetRegionStart()
{
  return *(_DWORD *)(sub_13D4C() + 72);
}
// 13D4C: using guessed type int sub_13D4C(void);


//----- (00013FE0) --------------------------------------------------------
int Unwind_GetLanguageSpecificData()
{
  int v0; // r0

  v0 = sub_13D4C();
  return *(_DWORD *)(v0 + 76) + 4 * *(unsigned __int8 *)(*(_DWORD *)(v0 + 76) + 7) + 8;
}
// 13D4C: using guessed type int sub_13D4C(void);


//----- (00013FF2) --------------------------------------------------------
void __noreturn Unwind_GetDataRelBase()
{
  abort();
}


//----- (00013FF8) --------------------------------------------------------
void __noreturn Unwind_GetTextRelBase()
{
  abort();
}


//----- (00014000) --------------------------------------------------------
// attributes: thunk
int j___aeabi_atexit()
{
  return _aeabi_atexit();
}
// 796C: using guessed type int _aeabi_atexit(void);


//----- (00014010) --------------------------------------------------------
// attributes: thunk
void j_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
  glDrawArrays(mode, first, count);
}


//----- (00014020) --------------------------------------------------------
// attributes: thunk
void j_glBindTexture(GLenum target, GLuint texture)
{
  glBindTexture(target, texture);
}


//----- (00014030) --------------------------------------------------------
// attributes: thunk
void __fastcall j_glTexParameteri(GLenum target, GLenum pname, GLint param)
{
  glTexParameteri(target, pname, param);
}


//----- (00014040) --------------------------------------------------------
// attributes: thunk
int j_glBindFramebuffer()
{
  return glBindFramebuffer();
}
// 7B10: using guessed type int glBindFramebuffer(void);


//----- (00014050) --------------------------------------------------------
// attributes: thunk
void j_free(void *p)
{
  free(p);
}


//----- (00014060) --------------------------------------------------------
// attributes: thunk
void *j_memmove(void *a1, const void *a2, size_t a3)
{
  return memmove(a1, a2, a3);
}

// nfuncs=613 queued=336 decompiled=336 lumina nreq=0 worse=0 better=0
// ALL OK, 336 function(s) have been successfully decompiled

