// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: varray  Functions: 2

//----- (00008584) --------------------------------------------------------
int __fastcall varray::update(int this)
{
  int v1; // r8
  int i; // r4
  _DWORD *v3; // r6
  int v4; // [sp+Ch] [bp+0h] BYREF
  _BYTE v5[4]; // [sp+10h] [bp+4h] BYREF
  int v6; // [sp+14h] [bp+8h]

  v1 = this + 8;
  for ( i = *(_DWORD *)(this + 16); i != v1; i = this )
  {
    std::string::string((std::string *)v5, (const std::string *)(i + 16));
    v6 = *(_DWORD *)(i + 20);
    glBindBuffer(*(_DWORD *)(*(_DWORD *)v6 + 24), *(_DWORD *)(*(_DWORD *)v6 + 28));
    if ( std::string::compare((std::string *)v5, "_index") )
    {
      std::string::string((std::string *)&v4, (const std::string *)v5);
      v3 = (_DWORD *)program::getattrib((const std::string *)&v4);
      glVertexAttribPointer(v3[3], v3[6], v3[5], 0, *(_DWORD *)(v6 + 4), *(_DWORD *)(v6 + 8));
      glEnableVertexAttribArray(v3[3]);
      std::string::~string((std::string *)&v4);
    }
    *(_BYTE *)(v6 + 12) = 0;
    std::string::~string((std::string *)v5);
    this = std::_Rb_tree_increment(i);
  }
  return this;
}
// 7768: using guessed type int __fastcall glBindBuffer(_DWORD, _DWORD);
// 77A4: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);
// 77C8: using guessed type int __fastcall glVertexAttribPointer(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 77D4: using guessed type int __fastcall glEnableVertexAttribArray(_DWORD);


//----- (00008804) --------------------------------------------------------
int __fastcall varray::getconfig(_DWORD *a1, const std::string *a2)
{
  _DWORD *v2; // r7
  _DWORD *v3; // r8
  _DWORD *v4; // r4
  _DWORD *v6; // r6
  _DWORD *v7; // r3
  int v8; // r2
  const std::string *v9; // r3
  int v10; // r0
  int v11; // r2

  v2 = a1 + 1;
  v3 = a1 + 2;
  v4 = (_DWORD *)a1[3];
  v6 = a1 + 2;
  while ( v4 )
  {
    if ( std::operator<<char>((std::string *)(v4 + 4), a2) )
    {
      v7 = (_DWORD *)v4[3];
      v4 = v6;
    }
    else
    {
      v7 = (_DWORD *)v4[2];
    }
    v6 = v4;
    v4 = v7;
  }
  if ( v6 == v3 || std::operator<<char>(a2, (const std::string *)(v6 + 4)) )
  {
    v10 = operator new(0x10u);
    *(_DWORD *)v10 = 0;
    *(_BYTE *)(v10 + 12) = 1;
    *std::map<std::string,bufferconfig *>::operator[](v2, a2, v11, (const std::string *)((char *)&dword_0 + 1)) = v10;
  }
  return *std::map<std::string,bufferconfig *>::operator[](v2, a2, v8, v9);
}
// 8854: variable 'v11' is possibly undefined
// 885E: variable 'v8' is possibly undefined
// 885E: variable 'v9' is possibly undefined
// 0: using guessed type int dword_0;


