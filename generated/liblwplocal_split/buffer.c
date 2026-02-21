// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: buffer  Functions: 4

//----- (000080AA) --------------------------------------------------------
int __fastcall buffer::addconfig(_DWORD *a1, unsigned int a2)
{
  _DWORD *v2; // r7
  _DWORD *v3; // r2
  _DWORD *v6; // r4
  int v7; // r3
  _DWORD *v8; // r1
  int result; // r0
  _BOOL4 v10; // r8
  _DWORD *v11; // r0
  _DWORD *v12; // r9

  v2 = a1 + 1;
  v3 = (_DWORD *)a1[2];
  v6 = a1 + 1;
  v7 = 1;
  while ( v3 )
  {
    v6 = v3;
    if ( a2 >= v3[4] )
    {
      v8 = (_DWORD *)v3[3];
      v7 = 0;
    }
    else
    {
      v8 = (_DWORD *)v3[2];
      v7 = 1;
    }
    v3 = v8;
  }
  if ( !v7 )
  {
    result = (int)v6;
LABEL_11:
    if ( *(_DWORD *)(result + 16) >= a2 )
      return result;
    goto LABEL_12;
  }
  if ( v6 != (_DWORD *)a1[3] )
  {
    result = std::_Rb_tree_decrement(v6);
    goto LABEL_11;
  }
LABEL_12:
  v10 = v6 == v2 || a2 < v6[4];
  v11 = (_DWORD *)operator new(0x14u);
  v12 = v11;
  if ( v11 )
  {
    memset(v11, 0, 0x10u);
    v12[4] = a2;
  }
  result = std::_Rb_tree_insert_and_rebalance(v10, v12, v6, v2);
  ++a1[5];
  return result;
}
// 7708: using guessed type int __fastcall std::_Rb_tree_decrement(_DWORD);
// 7720: using guessed type int __fastcall std::_Rb_tree_insert_and_rebalance(_DWORD, _DWORD, _DWORD, _DWORD);


//----- (00008212) --------------------------------------------------------
void __fastcall buffer::touch(buffer *this)
{
  int v1; // r4
  char *v2; // r7
  unsigned int v4; // r3
  unsigned int *v5; // r9
  unsigned int *v6; // r10
  char *v7; // r6
  unsigned int v8; // r12
  unsigned int v9; // t1
  char *i; // r4
  unsigned int v11; // r3
  char *v12; // r3
  char *v13; // r0
  char *v14; // r3
  char *v15; // r2
  char *v16; // r2
  int v17; // r11
  void *v18; // r0
  unsigned int v19; // [sp+0h] [bp-14h] BYREF
  void *v20; // [sp+4h] [bp-10h] BYREF
  unsigned int *v21; // [sp+8h] [bp-Ch]
  unsigned int *v22; // [sp+Ch] [bp-8h]

  v1 = *((_DWORD *)this + 3);
  v2 = (char *)this + 4;
  v20 = 0;
  v21 = 0;
  v22 = 0;
  while ( (char *)v1 != v2 )
  {
    v4 = *(_DWORD *)(v1 + 16);
    v19 = v4;
    if ( *(buffer **)v4 == this )
    {
      *(_BYTE *)(v4 + 12) = 1;
    }
    else if ( v21 == v22 )
    {
      std::vector<bufferconfig *>::_M_emplace_back_aux<bufferconfig * const&>((int)&v20, &v19);
    }
    else
    {
      if ( v21 )
        *v21 = v4;
      ++v21;
    }
    v1 = std::_Rb_tree_increment(v1);
  }
  v5 = v21;
  v6 = (unsigned int *)v20;
  while ( v6 != v5 )
  {
    v7 = v2;
    v9 = *v6++;
    v8 = v9;
    for ( i = (char *)*((_DWORD *)this + 2); ; i = v12 )
    {
      if ( !i )
      {
        i = v7;
        goto LABEL_32;
      }
      v11 = *((_DWORD *)i + 4);
      if ( v11 < v8 )
      {
        v12 = (char *)*((_DWORD *)i + 3);
        i = v7;
        goto LABEL_30;
      }
      if ( v8 >= v11 )
        break;
      v12 = (char *)*((_DWORD *)i + 2);
LABEL_30:
      v7 = i;
    }
    v13 = (char *)*((_DWORD *)i + 2);
    v14 = (char *)*((_DWORD *)i + 3);
    while ( v13 )
    {
      if ( *((_DWORD *)v13 + 4) >= v8 )
      {
        v15 = (char *)*((_DWORD *)v13 + 2);
      }
      else
      {
        v15 = (char *)*((_DWORD *)v13 + 3);
        v13 = i;
      }
      i = v13;
      v13 = v15;
    }
    while ( v14 )
    {
      if ( v8 < *((_DWORD *)v14 + 4) )
      {
        v16 = (char *)*((_DWORD *)v14 + 2);
      }
      else
      {
        v16 = (char *)*((_DWORD *)v14 + 3);
        v14 = v7;
      }
      v7 = v14;
      v14 = v16;
    }
LABEL_32:
    if ( i == *((char **)this + 3) && v7 == v2 )
    {
      std::_Rb_tree<bufferconfig *,bufferconfig *,std::_Identity<bufferconfig *>,std::less<bufferconfig *>,std::allocator<bufferconfig *>>::_M_erase(
        (int)this,
        *((_DWORD **)this + 2));
      *((_DWORD *)this + 3) = v2;
      *((_DWORD *)this + 2) = 0;
      *((_DWORD *)this + 4) = v2;
      *((_DWORD *)this + 5) = 0;
    }
    else
    {
      while ( i != v7 )
      {
        v17 = std::_Rb_tree_increment(i);
        v18 = (void *)std::_Rb_tree_rebalance_for_erase(i, v2);
        i = (char *)v17;
        operator delete(v18);
        --*((_DWORD *)this + 5);
      }
    }
  }
  if ( v20 )
    operator delete(v20);
}
// 7750: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);
// 775C: using guessed type int __fastcall std::_Rb_tree_rebalance_for_erase(_DWORD, _DWORD);


//----- (00008318) --------------------------------------------------------
void __fastcall buffer::set(buffer *this, unsigned int a2, void *a3, unsigned int a4)
{
  glBindBuffer(*((_DWORD *)this + 6), *((_DWORD *)this + 7));
  glBufferData(*((_DWORD *)this + 6), a2, a3, a4);
  buffer::touch(this);
}
// 7768: using guessed type int __fastcall glBindBuffer(_DWORD, _DWORD);
// 7774: using guessed type int __fastcall glBufferData(_DWORD, _DWORD, _DWORD, _DWORD);


//----- (00008340) --------------------------------------------------------
void __fastcall buffer::subset(buffer *this, unsigned int a2, unsigned int a3, void *a4)
{
  glBindBuffer(*((_DWORD *)this + 6), *((_DWORD *)this + 7));
  glBufferSubData(*((_DWORD *)this + 6), a2, a3, a4);
  buffer::touch(this);
}
// 7768: using guessed type int __fastcall glBindBuffer(_DWORD, _DWORD);
// 7780: using guessed type int __fastcall glBufferSubData(_DWORD, _DWORD, _DWORD, _DWORD);


