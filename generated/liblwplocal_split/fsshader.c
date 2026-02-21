// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: fsshader  Functions: 1

//----- (000095AC) --------------------------------------------------------
void __fastcall fsshader::run(fsshader *this)
{
  program::update(*((program **)this + 2));
  varray::update(*((_DWORD *)this + 1));
  j_glDrawArrays(5u, 0, 4);
}


