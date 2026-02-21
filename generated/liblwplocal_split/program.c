// Auto-split from: /mnt/data/ef2_cified_v2/ref/native/liblwplocal.so.c
// Group: program  Functions: 6

//----- (00008500) --------------------------------------------------------
int __fastcall program::getattrib(const std::string *a1)
{
  _DWORD *v1; // r4
  _DWORD *i; // r5
  _DWORD *v4; // r3
  _DWORD *v5; // r0
  const std::string *v7; // [sp+Ch] [bp-8h] BYREF

  v1 = &unk_18848;
  for ( i = (_DWORD *)dword_1884C; i; i = v4 )
  {
    if ( std::operator<<char>((std::string *)(i + 4), a1) )
    {
      v4 = (_DWORD *)i[3];
      i = v1;
    }
    else
    {
      v4 = (_DWORD *)i[2];
    }
    v1 = i;
  }
  if ( v1 == (_DWORD *)&unk_18848 || std::operator<<char>(a1, (const std::string *)(v1 + 4)) )
  {
    v7 = a1;
    v1 = std::_Rb_tree<std::string,std::pair<std::string const,attribute *>,std::_Select1st<std::pair<std::string const,attribute *>>,std::less<std::string>,std::allocator<std::pair<std::string const,attribute *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string const&>,std::tuple<>>(
           &program::attribs,
           v1,
           (int)&unk_149EC,
           &v7);
  }
  if ( !v1[5] )
  {
    v5 = (_DWORD *)operator new(0x1Cu);
    *v5 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
    v1[5] = v5;
  }
  return v1[5];
}
// 18844: using guessed type _DWORD program::attribs;
// 1884C: using guessed type int dword_1884C;


//----- (0000888C) --------------------------------------------------------
int __fastcall program::bind(program *this)
{
  int result; // r0

  result = *(_DWORD *)this;
  if ( program::bound != result )
    result = glUseProgram();
  program::bound = *(_DWORD *)this;
  return result;
}
// 77E0: using guessed type int glUseProgram(void);
// 18004: using guessed type int program::bound;


//----- (000088B0) --------------------------------------------------------
int __fastcall program::update(program *this)
{
  int result; // r0
  char *v3; // r6
  int i; // r5
  int v5; // r4
  int v6; // r3
  GLuint *v7; // r0
  int v8; // r3
  int v9; // r1

  result = program::bind(this);
  v3 = (char *)this + 8;
  for ( i = *((_DWORD *)v3 + 2); (char *)i != v3; i = result )
  {
    v5 = *(_DWORD *)(i + 16);
    v6 = *(_DWORD *)(v5 + 8);
    v7 = *(GLuint **)(v6 + 16);
    if ( v7 )
      texture::bind(v7, **(_DWORD **)(v6 + 12));
    if ( *(_BYTE *)v5 )
    {
      v8 = *(_DWORD *)(v5 + 8);
      *(_BYTE *)v5 = 0;
      v9 = *(_DWORD *)(v8 + 4);
      if ( v9 == 35667 )
      {
        glUniform2iv(*(_DWORD *)(v5 + 4), 1, *(_DWORD *)(v8 + 12));
        goto LABEL_31;
      }
      if ( v9 > 35667 )
      {
        if ( v9 == 35674 )
        {
          glUniformMatrix2fv(*(_DWORD *)(v5 + 4), 1);
          goto LABEL_31;
        }
        if ( v9 > 35674 )
        {
          if ( v9 == 35675 )
          {
            glUniformMatrix3fv(*(_DWORD *)(v5 + 4), 1);
            goto LABEL_31;
          }
          if ( v9 == 35676 )
          {
            glUniformMatrix4fv(*(_DWORD *)(v5 + 4), 1);
            goto LABEL_31;
          }
        }
        else
        {
          if ( v9 == 35668 )
          {
            glUniform3iv(*(_DWORD *)(v5 + 4), 1, *(_DWORD *)(v8 + 12));
            goto LABEL_31;
          }
          if ( v9 == 35669 )
          {
            glUniform4iv(*(_DWORD *)(v5 + 4), 1, *(_DWORD *)(v8 + 12));
            goto LABEL_31;
          }
        }
        goto LABEL_30;
      }
      if ( v9 == 35664 )
      {
        glUniform2fv(*(_DWORD *)(v5 + 4), 1, *(_DWORD *)(v8 + 12));
        goto LABEL_31;
      }
      if ( v9 <= 35664 )
      {
        if ( v9 == 5124 )
        {
          glUniform1iv(*(_DWORD *)(v5 + 4), 1, *(_DWORD *)(v8 + 12));
          goto LABEL_31;
        }
        if ( v9 == 5126 )
        {
          glUniform1fv(*(_DWORD *)(v5 + 4), 1, *(_DWORD *)(v8 + 12));
          goto LABEL_31;
        }
LABEL_30:
        glUniform1i(*(_DWORD *)(v5 + 4), **(_DWORD **)(v8 + 12));
        goto LABEL_31;
      }
      if ( v9 == 35665 )
        glUniform3fv(*(_DWORD *)(v5 + 4), 1, *(_DWORD *)(v8 + 12));
      else
        glUniform4fv(*(_DWORD *)(v5 + 4), 1, *(_DWORD *)(v8 + 12));
    }
LABEL_31:
    result = std::_Rb_tree_increment(i);
  }
  return result;
}
// 8924: conditional instruction was optimized away because r1.4==8B52
// 7750: using guessed type int __fastcall std::_Rb_tree_increment(_DWORD);
// 77EC: using guessed type int __fastcall glUniform1fv(_DWORD, _DWORD, _DWORD);
// 77F8: using guessed type int __fastcall glUniform4fv(_DWORD, _DWORD, _DWORD);
// 7804: using guessed type int __fastcall glUniform4iv(_DWORD, _DWORD, _DWORD);
// 7810: using guessed type int __fastcall glUniformMatrix4fv(_DWORD, _DWORD);
// 781C: using guessed type int __fastcall glUniform2fv(_DWORD, _DWORD, _DWORD);
// 7828: using guessed type int __fastcall glUniform3fv(_DWORD, _DWORD, _DWORD);
// 7834: using guessed type int __fastcall glUniform1iv(_DWORD, _DWORD, _DWORD);
// 7840: using guessed type int __fastcall glUniform2iv(_DWORD, _DWORD, _DWORD);
// 784C: using guessed type int __fastcall glUniform3iv(_DWORD, _DWORD, _DWORD);
// 7858: using guessed type int __fastcall glUniformMatrix2fv(_DWORD, _DWORD);
// 7864: using guessed type int __fastcall glUniformMatrix3fv(_DWORD, _DWORD);
// 7870: using guessed type int __fastcall glUniform1i(_DWORD, _DWORD);


//----- (00008AEC) --------------------------------------------------------
int __fastcall program::shader(int a1, int *a2, int a3)
{
  int Shader; // r0
  int *v6; // r3
  int v8; // [sp+0h] [bp-14h] BYREF
  int v9; // [sp+4h] [bp-10h] BYREF
  int v10; // [sp+8h] [bp-Ch] BYREF
  int v11; // [sp+Ch] [bp-8h] BYREF

  Shader = glCreateShader();
  v9 = 0;
  v10 = *a2;
  v8 = Shader;
  v11 = *(_DWORD *)(v10 - 12);
  glShaderSource(Shader, 1, &v10, &v11);
  glCompileShader(v8);
  glGetShaderiv(v8, 35713, &v9);
  if ( v9 != 1 )
  {
    glGetShaderInfoLog(v8, 2048, &v9, &unk_18028);
    exit(1);
  }
  v6 = *(int **)(a3 + 4);
  if ( v6 == *(int **)(a3 + 8) )
  {
    std::vector<unsigned int>::_M_emplace_back_aux<unsigned int const&>(a3, &v8);
  }
  else
  {
    if ( v6 )
      *v6 = v8;
    *(_DWORD *)(a3 + 4) += 4;
  }
  return a3;
}
// 787C: using guessed type int glCreateShader(void);
// 7888: using guessed type int __fastcall glShaderSource(_DWORD, _DWORD, _DWORD, _DWORD);
// 7894: using guessed type int __fastcall glCompileShader(_DWORD);
// 78A0: using guessed type int __fastcall glGetShaderiv(_DWORD, _DWORD, _DWORD);
// 78AC: using guessed type int __fastcall glGetShaderInfoLog(_DWORD, _DWORD, _DWORD, _DWORD);


//----- (00008F6C) --------------------------------------------------------
program *__fastcall program::createProgram(int **a1)
{
  unsigned int Program; // r0
  int *v3; // r4
  int *v4; // r6
  int v5; // t1
  int v6; // r7
  _DWORD *v7; // r6
  _DWORD *k; // r4
  _BOOL4 v9; // r6
  int v10; // r2
  const std::string *v11; // r3
  _DWORD *v12; // r0
  unsigned int v13; // r6
  int v14; // r10
  int v15; // r0
  char *v16; // r3
  int v17; // r1
  char *v18; // r11
  int i; // r3
  std::string *v20; // r2
  int v21; // r2
  const std::string *v22; // r3
  _DWORD *v23; // r5
  int v24; // r2
  const std::string *v25; // r3
  std::string *v26; // r0
  int v27; // lr
  unsigned int v28; // r2
  int v29; // r1
  int v30; // r2
  int v31; // r1
  int v32; // r2
  int v33; // r1
  int v34; // r2
  int v35; // r1
  int v36; // r2
  int v37; // r3
  _DWORD *v38; // r3
  int v39; // r2
  const std::string *v40; // r3
  _DWORD *v41; // r6
  unsigned int v42; // r2
  int v43; // r6
  unsigned int v44; // r0
  int v45; // r0
  int v46; // r6
  int v47; // r6
  int v48; // r2
  const std::string *v49; // r3
  int v50; // r2
  const std::string *v51; // r3
  _DWORD *v52; // r0
  int v54; // r2
  const std::string *v55; // r3
  int v56; // [sp+10h] [bp-124h]
  _DWORD *v57; // [sp+10h] [bp-124h]
  _DWORD *v58; // [sp+10h] [bp-124h]
  std::string *v59; // [sp+14h] [bp-120h]
  std::string *v60; // [sp+14h] [bp-120h]
  int j; // [sp+18h] [bp-11Ch]
  program *v62; // [sp+1Ch] [bp-118h]
  unsigned int v63; // [sp+38h] [bp-FCh] BYREF
  int v64; // [sp+3Ch] [bp-F8h] BYREF
  int v65; // [sp+40h] [bp-F4h] BYREF
  int v66; // [sp+44h] [bp-F0h] BYREF
  int v67; // [sp+48h] [bp-ECh] BYREF
  int v68; // [sp+4Ch] [bp-E8h] BYREF
  unsigned int v69; // [sp+50h] [bp-E4h] BYREF
  int v70; // [sp+54h] [bp-E0h] BYREF
  unsigned int v71; // [sp+58h] [bp-DCh] BYREF
  _BYTE v72[8]; // [sp+5Ch] [bp-D8h] BYREF
  _BYTE v73[100]; // [sp+64h] [bp-D0h] BYREF
  _BYTE v74[108]; // [sp+C8h] [bp-6Ch] BYREF

  Program = glCreateProgram();
  v3 = *a1;
  v4 = a1[1];
  v63 = Program;
  while ( v3 != v4 )
  {
    v5 = *v3++;
    glAttachShader(v63, v5);
    glDeleteShader(v5);
  }
  v6 = 0;
  v64 = 0;
  glLinkProgram(v63);
  glGetProgramiv(v63, 35714, &v64);
  if ( v64 != 1 )
  {
    glGetProgramInfoLog(v63, 2048, &v64, &unk_18028);
LABEL_15:
    exit(1);
  }
  v62 = (program *)operator new(0x1Cu);
  program::program(v62, &v63);
  program::bind(v62);
  v65 = 0;
  glGetProgramiv(v63, 35721, &v65);
  while ( v6 < v65 )
  {
    v66 = 0;
    v70 = 0;
    v71 = 0;
    glGetActiveAttrib(v63, v6, 99, &v66, &v70, &v71, v73);
    v74[v66 - 100] = 0;
    std::string::string(v72, v73, &v69);
    v18 = (char *)&unk_18848;
    for ( i = dword_1884C; i; i = v17 )
    {
      v56 = i;
      v15 = std::operator<<char>((std::string *)(i + 16), (const std::string *)v72);
      v16 = (char *)v56;
      if ( v15 )
      {
        v17 = *(_DWORD *)(v56 + 12);
        v16 = v18;
      }
      else
      {
        v17 = *(_DWORD *)(v56 + 8);
      }
      v18 = v16;
    }
    if ( v18 == (char *)&unk_18848 )
    {
      v20 = (std::string *)v18;
    }
    else if ( std::operator<<char>((std::string *)v72, (const std::string *)(v18 + 16)) )
    {
      v20 = (std::string *)&unk_18848;
    }
    else
    {
      v20 = (std::string *)v18;
    }
    v59 = v20;
    std::string::~string((std::string *)v72);
    if ( v59 != (std::string *)&unk_18848 )
      goto LABEL_25;
    std::string::string(v72, v73, &v69);
    v57 = std::map<std::string,attribute *>::operator[](&program::attribs, (const std::string *)v72, v24, v25);
    std::string::~string((std::string *)v72);
    v26 = (std::string *)operator new(0x1Cu);
    *(_DWORD *)v26 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
    *v57 = v26;
    v60 = v26;
    std::string::string(v72, v73, &v69);
    std::string::swap(v60, (std::string *)v72);
    std::string::~string((std::string *)v72);
    v27 = program::attribindex;
    *(_DWORD *)(*v57 + 12) = program::attribindex;
    *(_BYTE *)(*v57 + 4) = 0;
    v28 = v71;
    *(_DWORD *)(*v57 + 16) = v71;
    if ( v28 > 0x8B55 )
    {
      switch ( v28 )
      {
        case 0x8B5Bu:
          program::attribindex = v27 + 3;
LABEL_63:
          v34 = *v57;
          v35 = 5126;
          goto LABEL_69;
        case 0x8B5Cu:
          program::attribindex = v27 + 4;
LABEL_64:
          v30 = *v57;
          v31 = 5126;
          goto LABEL_70;
        case 0x8B5Au:
          program::attribindex = v27 + 2;
LABEL_62:
          v32 = *v57;
          v33 = 5126;
          goto LABEL_67;
      }
    }
    else
    {
      if ( v28 >= 0x8B53 || v28 == 5126 )
      {
LABEL_45:
        program::attribindex = v27 + 1;
        goto LABEL_46;
      }
      if ( v28 > 0x1406 )
      {
        if ( v28 >= 0x8B50 )
          goto LABEL_45;
      }
      else if ( v28 == 5124 )
      {
        goto LABEL_45;
      }
    }
LABEL_46:
    if ( v28 == 35667 )
    {
      v32 = *v57;
      v33 = 5124;
LABEL_67:
      *(_DWORD *)(v32 + 20) = v33;
      v36 = 2;
      v37 = *v57;
      goto LABEL_71;
    }
    if ( v28 > 0x8B53 )
    {
      if ( v28 <= 0x8B5A )
      {
        if ( v28 != 35668 )
        {
          if ( v28 != 35669 )
            goto LABEL_25;
          v30 = *v57;
          v31 = 5124;
LABEL_70:
          *(_DWORD *)(v30 + 20) = v31;
          v36 = 4;
          v37 = *v57;
          goto LABEL_71;
        }
        v34 = *v57;
        v35 = 5124;
LABEL_69:
        *(_DWORD *)(v34 + 20) = v35;
        v36 = 3;
        v37 = *v57;
        goto LABEL_71;
      }
      v29 = 35675;
      goto LABEL_59;
    }
    if ( v28 == 35664 )
      goto LABEL_62;
    if ( v28 > 0x8B50 )
    {
      v29 = 35665;
LABEL_59:
      if ( v28 == v29 )
        goto LABEL_63;
      if ( v28 == v29 + 1 )
        goto LABEL_64;
      goto LABEL_25;
    }
    if ( v28 == 5124 || v28 == 5126 )
    {
      *(_DWORD *)(*v57 + 20) = v28;
      v36 = 1;
      v37 = *v57;
LABEL_71:
      *(_DWORD *)(v37 + 24) = v36;
    }
LABEL_25:
    std::string::string(v72, v73, &v69);
    v23 = std::map<std::string,attribute *>::operator[](&program::attribs, (const std::string *)v72, v21, v22);
    std::string::~string((std::string *)v72);
    if ( *(_DWORD *)(*v23 + 16) != v71 )
      goto LABEL_15;
    ++v6;
    glBindAttribLocation(v63, *(_DWORD *)(*v23 + 12), *(_DWORD *)*v23);
  }
  glLinkProgram(v63);
  glGetProgramiv(v63, 35718, &v65);
  for ( j = 0; j < v65; ++j )
  {
    v67 = 0;
    v68 = 0;
    v69 = 0;
    glGetActiveUniform(v63, j, 99, &v67, &v68, &v69, v74);
    v74[v67] = 0;
    std::string::string(&v71, v74, &v66);
    v7 = &unk_18830;
    for ( k = (_DWORD *)dword_18834; k; k = v38 )
    {
      if ( std::operator<<char>((std::string *)(k + 4), (const std::string *)&v71) )
      {
        v38 = (_DWORD *)k[3];
        k = v7;
      }
      else
      {
        v38 = (_DWORD *)k[2];
      }
      v7 = k;
    }
    if ( v7 == (_DWORD *)&unk_18830 || std::operator<<char>((std::string *)&v71, (const std::string *)(v7 + 4)) )
    {
      v9 = 1;
    }
    else
    {
      std::string::string(v72, v74, &v70);
      v9 = *(_DWORD *)(*std::map<std::string,uniform *>::operator[](
                          &program::uniforms,
                          (const std::string *)v72,
                          v54,
                          v55)
                     + 4) == 0;
      std::string::~string((std::string *)v72);
    }
    std::string::~string((std::string *)&v71);
    if ( v9 )
    {
      std::string::string(v72, v74, &v71);
      v58 = std::map<std::string,uniform *>::operator[](&program::uniforms, (const std::string *)v72, v39, v40);
      std::string::~string((std::string *)v72);
      v41 = (_DWORD *)operator new(0x2Cu);
      *v41 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
      v41[1] = 0;
      v41[2] = 0;
      v41[3] = 0;
      v41[4] = 0;
      memset(v41 + 6, 0, 0x10u);
      v41[10] = 0;
      v41[8] = v41 + 6;
      v41[9] = v41 + 6;
      *v58 = v41;
      std::string::string(v72, v74, &v71);
      std::string::swap((std::string *)v41, (std::string *)v72);
      std::string::~string((std::string *)v72);
      v42 = v69;
      *(_DWORD *)(*v58 + 4) = v69;
      v43 = *v58;
      if ( v42 == 35669 )
        goto LABEL_103;
      if ( v42 <= 0x8B55 )
      {
        if ( v42 == 35665 )
          goto LABEL_98;
        if ( v42 <= 0x8B51 )
        {
          if ( v42 == 35664 )
          {
LABEL_96:
            v44 = 8;
            *(_DWORD *)(v43 + 8) = 2;
            goto LABEL_97;
          }
          goto LABEL_105;
        }
        if ( v42 == 35667 )
          goto LABEL_96;
        if ( v42 > 0x8B53 )
        {
LABEL_98:
          v44 = 12;
          *(_DWORD *)(v43 + 8) = 3;
          goto LABEL_97;
        }
        goto LABEL_103;
      }
      if ( v42 == 35673 )
      {
        v44 = 4;
      }
      else
      {
        if ( v42 > 0x8B59 )
        {
          if ( v42 == 35675 )
          {
            v44 = 36;
            *(_DWORD *)(v43 + 8) = 9;
            goto LABEL_97;
          }
          if ( v42 >= 0x8B5B )
          {
            if ( v42 == 35676 )
            {
              *(_DWORD *)(v43 + 8) = 16;
              v44 = 64;
LABEL_97:
              *(_DWORD *)(v43 + 12) = operator new[](v44);
              goto LABEL_106;
            }
LABEL_105:
            v44 = 4;
            *(_DWORD *)(v43 + 8) = 1;
            goto LABEL_97;
          }
LABEL_103:
          v44 = 16;
          *(_DWORD *)(v43 + 8) = 4;
          goto LABEL_97;
        }
        if ( v42 == 35671 )
        {
          v44 = 2;
        }
        else if ( v42 > 0x8B57 )
        {
          v44 = 3;
        }
        else
        {
          v44 = 1;
        }
      }
      *(_DWORD *)(v43 + 8) = v44;
      goto LABEL_97;
    }
    std::string::string(v72, v74, &v71);
    v12 = std::map<std::string,uniform *>::operator[](&program::uniforms, (const std::string *)v72, v10, v11);
    v13 = v69;
    v14 = *(_DWORD *)(*v12 + 4);
    std::string::~string((std::string *)v72);
    if ( v14 != v13 )
      goto LABEL_15;
LABEL_106:
    v45 = operator new(0xCu);
    *(_DWORD *)(v45 + 4) = 0;
    *(_DWORD *)(v45 + 8) = 0;
    v70 = v45;
    *(_BYTE *)v45 = 1;
    v46 = v70;
    *(_DWORD *)(v46 + 4) = glGetUniformLocation(v63, v74);
    v47 = v70;
    std::string::string(v72, v74, &v71);
    *(_DWORD *)(v47 + 8) = *std::map<std::string,uniform *>::operator[](
                              &program::uniforms,
                              (const std::string *)v72,
                              v48,
                              v49);
    std::string::~string((std::string *)v72);
    std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::_M_insert_unique<uniformconfig * const&>(
      (int)v72,
      (_DWORD *)v62 + 1,
      &v70);
    std::string::string(&v71, v74, &v66);
    v52 = std::map<std::string,uniform *>::operator[](&program::uniforms, (const std::string *)&v71, v50, v51);
    std::_Rb_tree<uniformconfig *,uniformconfig *,std::_Identity<uniformconfig *>,std::less<uniformconfig *>,std::allocator<uniformconfig *>>::_M_insert_unique<uniformconfig * const&>(
      (int)v72,
      (_DWORD *)(*v52 + 20),
      &v70);
    std::string::~string((std::string *)&v71);
  }
  return v62;
}
// 92A6: conditional instruction was optimized away because r2.4 is in (8B54..8B59|>=8B5Du)
// 90AC: variable 'v10' is possibly undefined
// 90AC: variable 'v11' is possibly undefined
// 9124: variable 'v21' is possibly undefined
// 9124: variable 'v22' is possibly undefined
// 91B0: variable 'v24' is possibly undefined
// 91B0: variable 'v25' is possibly undefined
// 9352: variable 'v39' is possibly undefined
// 9352: variable 'v40' is possibly undefined
// 949C: variable 'v48' is possibly undefined
// 949C: variable 'v49' is possibly undefined
// 94C4: variable 'v50' is possibly undefined
// 94C4: variable 'v51' is possibly undefined
// 9500: variable 'v54' is possibly undefined
// 9500: variable 'v55' is possibly undefined
// 78C4: using guessed type int glCreateProgram(void);
// 78D0: using guessed type int __fastcall glAttachShader(_DWORD, _DWORD);
// 78DC: using guessed type int __fastcall glDeleteShader(_DWORD);
// 78E8: using guessed type int __fastcall glLinkProgram(_DWORD);
// 78F4: using guessed type int __fastcall glGetProgramiv(_DWORD, _DWORD, _DWORD);
// 7900: using guessed type int __fastcall glGetProgramInfoLog(_DWORD, _DWORD, _DWORD, _DWORD);
// 790C: using guessed type int __fastcall glGetActiveUniform(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 7918: using guessed type int __fastcall std::string::string(_DWORD, _DWORD, _DWORD);
// 7924: using guessed type int __fastcall glBindAttribLocation(_DWORD, _DWORD, _DWORD);
// 7930: using guessed type int __fastcall glGetActiveAttrib(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 7954: using guessed type int __fastcall glGetUniformLocation(_DWORD, _DWORD);
// 18828: using guessed type int program::attribindex;
// 1882C: using guessed type _DWORD program::uniforms;
// 18834: using guessed type int dword_18834;
// 18844: using guessed type _DWORD program::attribs;
// 1884C: using guessed type int dword_1884C;


//----- (0000A078) --------------------------------------------------------
int __fastcall program::getuniform(const std::string *a1)
{
  _DWORD *v1; // r5
  _DWORD *i; // r4
  _DWORD *v4; // r3
  _DWORD *v5; // r0
  _DWORD *v6; // r7
  _DWORD *v7; // r4
  const std::string *v9; // [sp+Ch] [bp-8h] BYREF

  v1 = &unk_18830;
  for ( i = (_DWORD *)dword_18834; i; i = v4 )
  {
    if ( std::operator<<char>((std::string *)(i + 4), a1) )
    {
      v4 = (_DWORD *)i[3];
      i = v1;
    }
    else
    {
      v4 = (_DWORD *)i[2];
    }
    v1 = i;
  }
  if ( v1 == (_DWORD *)&unk_18830 || std::operator<<char>(a1, (const std::string *)(v1 + 4)) )
  {
    v9 = a1;
    v1 = std::_Rb_tree<std::string,std::pair<std::string const,uniform *>,std::_Select1st<std::pair<std::string const,uniform *>>,std::less<std::string>,std::allocator<std::pair<std::string const,uniform *>>>::_M_emplace_hint_unique<std::piecewise_construct_t const&,std::tuple<std::string const&>,std::tuple<>>(
           &program::uniforms,
           v1,
           (int)&unk_15B63,
           &v9);
  }
  if ( !v1[5] )
  {
    v5 = (_DWORD *)operator new(0x2Cu);
    v6 = v5 + 6;
    v7 = v5;
    *v5 = (char *)&std::string::_Rep::_S_empty_rep_storage + 12;
    v5[1] = 0;
    v5[2] = 0;
    v5[3] = 0;
    v5[4] = 0;
    memset(v5 + 6, 0, 0x10u);
    v7[10] = 0;
    v7[8] = v6;
    v7[9] = v6;
    v1[5] = v7;
  }
  return v1[5];
}
// 1882C: using guessed type _DWORD program::uniforms;
// 18834: using guessed type int dword_18834;


