// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: bufferconfig  Functions: 1

//----- (00008130) --------------------------------------------------------
int __fastcall bufferconfig::set(unsigned int a1, _DWORD *a2, int a3, int a4)
{
  int result; // r0

  result = buffer::addconfig(a2, a1);
  *(_DWORD *)a1 = a2;
  *(_BYTE *)(a1 + 12) = 1;
  *(_DWORD *)(a1 + 4) = a3;
  *(_DWORD *)(a1 + 8) = a4;
  return result;
}


