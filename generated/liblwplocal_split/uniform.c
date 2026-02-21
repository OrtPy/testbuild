// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: uniform  Functions: 1

//----- (00009DC0) --------------------------------------------------------
void __fastcall uniform::touched(uniform *this)
{
  int v1; // r5
  char *v2; // r6
  unsigned int v4; // r3
  uniform *v5; // r2
  unsigned int *v6; // r5
  _DWORD *v7; // r4
  unsigned int *v8; // r6
  unsigned int v9; // t1
  unsigned int v10; // [sp+4h] [bp-18h] BYREF
  unsigned int v11; // [sp+8h] [bp-14h] BYREF
  void *v12; // [sp+Ch] [bp-10h] BYREF
  unsigned int *v13; // [sp+10h] [bp-Ch]
  unsigned int *v14; // [sp+14h] [bp-8h]

  v1 = *((_DWORD *)this + 8);
  v2 = (char *)this + 24;
  v12 = 0;
  v13 = 0;
  v14 = 0;
  while ( (char *)v1 != v2 )
  {
    v4 = *(_DWORD *)(v1 + 16);
    v5 = *(uniform **)(v4 + 8);
    v10 = v4;
    if ( v5 == this )
    {
      *(_BYTE *)v4 = 1;
    }
    else if ( v13 == v14 )
    {
      std::vector<uniformconfig *>::_M_emplace_back_aux<uniformconfig * const&>((int)&v12, &v10);
    }
    else
    {
      if ( v13 )
        *v13 = v4;
      ++v13;
    }
    v1 = std::_Rb_tree_increment(v1);
  }
  v6 = (unsigned int *)v12;
  v7 = (_DWORD *)((char *)this + 20);
  v8 = v13;
  while ( v6 != v8 )
  {
    v9 = *v6++;
    v11 = v9;
    std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::erase(
      v7,
      &v11);
  }
  if ( v12 )
    operator delete(v12);
}
// 7750: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);


