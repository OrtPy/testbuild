// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: framebuffer  Functions: 3

//----- (0000B4FC) --------------------------------------------------------
int __fastcall framebuffer::exit(framebuffer *this)
{
  dword_18884 -= 4;
  return j_glBindFramebuffer();
}
// 18880: using guessed type int framebuffer::fbstack;
// 18884: using guessed type int dword_18884;


//----- (0000B54C) --------------------------------------------------------
int __fastcall framebuffer::set(framebuffer *this, unsigned int a2, texture *a3)
{
  glBindFramebuffer(36160, *(_DWORD *)this);
  glFramebufferTexture2D(36160, a2 + 36064, 3553, *(_DWORD *)a3, 0);
  return j_glBindFramebuffer();
}
// 7B10: using guessed type int __fastcall glBindFramebuffer(_DWORD, _DWORD);
// 7B28: using guessed type int __fastcall glFramebufferTexture2D(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 18880: using guessed type int framebuffer::fbstack;
// 18884: using guessed type int dword_18884;


//----- (0000B614) --------------------------------------------------------
void __fastcall framebuffer::enter(framebuffer *this, framebuffer *a2, int a3)
{
  _DWORD v3[2]; // [sp+4h] [bp-8h] BYREF

  v3[1] = a3;
  v3[0] = this;
  glBindFramebuffer(36160, *(_DWORD *)this);
  if ( dword_18884 == dword_18888 )
  {
    std::vector<framebuffer *>::_M_emplace_back_aux<framebuffer * const&>((int)&framebuffer::fbstack, v3);
  }
  else
  {
    if ( dword_18884 )
      *(_DWORD *)dword_18884 = v3[0];
    dword_18884 += 4;
  }
}
// 7B10: using guessed type int __fastcall glBindFramebuffer(_DWORD, _DWORD);
// 18880: using guessed type int framebuffer::fbstack;
// 18884: using guessed type int dword_18884;
// 18888: using guessed type int dword_18888;


