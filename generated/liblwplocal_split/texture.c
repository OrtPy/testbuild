// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: texture  Functions: 4

//----- (0000B3AC) --------------------------------------------------------
void __fastcall texture::bind(GLuint *this, int a2)
{
  if ( a2 >= 0 )
    glActiveTexture(a2 + 33984);
  j_glBindTexture(0xDE1u, *this);
}


//----- (0000B3CC) --------------------------------------------------------
void __fastcall texture::set(
        GLuint *this,
        GLint a2,
        GLenum a3,
        GLenum a4,
        GLsizei a5,
        GLsizei height,
        void *pixels,
        bool a8)
{
  texture::bind(this, -1);
  *(this + 4) = a2;
  *(this + 5) = a3;
  *(this + 3) = a4;
  *(this + 1) = a5;
  *(this + 2) = height;
  glTexImage2D(0xDE1u, 0, a2, a5, height, 0, a3, a4, pixels);
  if ( pixels )
  {
    glTexParameteri(0xDE1u, 0x2800u, 9728);
    j_glTexParameteri(0xDE1u, 0x2801u, 9728);
  }
}


//----- (0000B448) --------------------------------------------------------
void __fastcall texture::set(GLuint *a1, _DWORD *a2)
{
  int v4; // r0
  int v5; // r0
  int v6; // r0
  void *v7[4]; // [sp+14h] [bp-10h] BYREF

  memset(v7, 0, 12);
  if ( lodepng::decode((int)v7, a1 + 1, a1 + 2, a2, &byte_6, &byte_8) )
  {
    v4 = std::operator<<<std::char_traits<char>>(&std::cerr, "Could not decode ");
    v5 = std::operator<<<char>(v4, a2);
    v6 = std::operator<<<std::char_traits<char>>(v5, ", file missing or corrupt!");
    std::endl<char,std::char_traits<char>>(v6);
    exit(1);
  }
  texture::set(a1, 6408, 0x1908u, 0x1401u, a1[1], a1[2], v7[0], 1);
  if ( v7[0] )
    operator delete(v7[0]);
}
// 6: using guessed type char byte_6;
// 8: using guessed type char byte_8;
// 7AEC: using guessed type int __fastcall std::operator<<<std::char_traits<char>>(_DWORD, _DWORD);
// 7AF8: using guessed type int __fastcall std::operator<<<char>(_DWORD, _DWORD);
// 7B04: using guessed type int __fastcall std::endl<char,std::char_traits<char>>(_DWORD);


//----- (0000B4CC) --------------------------------------------------------
GLuint *__fastcall texture::load(const std::string *a1, int a2)
{
  GLuint *v3; // r5
  int v5; // [sp+4h] [bp-4h] BYREF

  v5 = a2;
  v3 = (GLuint *)operator new(0x18u);
  texture::texture(v3);
  std::string::string((std::string *)&v5, a1);
  texture::set(v3, &v5);
  std::string::~string((std::string *)&v5);
  return v3;
}


