#include "ef2/program.h"
#include "ef2/platform.h"
#include "ef2/common.h"

#include <stdlib.h>
#include <string.h>

#ifndef ANDROID_LOG_ERROR
#define ANDROID_LOG_ERROR 6
#define ANDROID_LOG_WARN  5
#define ANDROID_LOG_INFO  4
#define ANDROID_LOG_DEBUG 3
#endif

static char* ef2__dupstr(const char* s)
{
  if (!s) return NULL;
  size_t n = strlen(s);
  char* d = (char*)malloc(n + 1);
  if (!d) return NULL;
  memcpy(d, s, n);
  d[n] = '\0';
  return d;
}

static void ef2__uniform_free(ef2_UniformEntry* u)
{
  if (!u) return;
  free(u->name);
  u->name = NULL;
}

static ef2_UniformEntry* ef2__program_find_uniform(ef2_Program* p, const char* name)
{
  if (!p || !name) return NULL;
  {
    size_t i;
    for (i = 0; i < p->uniform_count; i++) {
      if (p->uniforms[i].name && strcmp(p->uniforms[i].name, name) == 0)
        return &p->uniforms[i];
    }
  }
  return NULL;
}

static ef2_UniformEntry* ef2__program_add_uniform(ef2_Program* p, const char* name, int kind, int count)
{
  if (!p || !name) return NULL;
  if (p->uniform_count == p->uniform_cap) {
    size_t ncap = p->uniform_cap ? p->uniform_cap * 2 : 16;
    ef2_UniformEntry* nu = (ef2_UniformEntry*)realloc(p->uniforms, ncap * sizeof(*nu));
    if (!nu) return NULL;
    // zero new region
    if (ncap > p->uniform_cap) {
      memset(nu + p->uniform_cap, 0, (ncap - p->uniform_cap) * sizeof(*nu));
    }
    p->uniforms = nu;
    p->uniform_cap = ncap;
  }
  ef2_UniformEntry* u = &p->uniforms[p->uniform_count++];
  memset(u, 0, sizeof(*u));
  u->name = ef2__dupstr(name);
  u->kind = kind;
  u->count = count;
  u->loc = -2; // unknown
  return u;
}

static ef2_UniformEntry* ef2__program_get_uniform(ef2_Program* p, const char* name, int kind, int count)
{
  ef2_UniformEntry* u = ef2__program_find_uniform(p, name);
  if (u) {
    // If kind/count changed across calls, keep the latest request (matches decomp behavior).
    u->kind = kind;
    u->count = count;
    return u;
  }
  return ef2__program_add_uniform(p, name, kind, count);
}

#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
#include <stdio.h>

static void ef2__gl_log_shader(GLuint shader, const char* stage, const char* tag)
{
  GLint len = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  if (len <= 1) return;

  char* buf = (char*)malloc((size_t)len + 1);
  if (!buf) return;
  memset(buf, 0, (size_t)len + 1);

  GLsizei out_len = 0;
  glGetShaderInfoLog(shader, len, &out_len, buf);

  ef2_log_print(ANDROID_LOG_ERROR, "ef2", "[%s] %s shader infoLog:\n%s", tag ? tag : "program", stage ? stage : "?", buf);
  free(buf);
}

static void ef2__gl_log_program(GLuint prog, const char* tag)
{
  GLint len = 0;
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
  if (len <= 1) return;

  char* buf = (char*)malloc((size_t)len + 1);
  if (!buf) return;
  memset(buf, 0, (size_t)len + 1);

  GLsizei out_len = 0;
  glGetProgramInfoLog(prog, len, &out_len, buf);

  ef2_log_print(ANDROID_LOG_ERROR, "ef2", "[%s] program infoLog:\n%s", tag ? tag : "program", buf);
  free(buf);
}

static GLuint ef2__gl_compile_shader(GLenum type, const char* src, const char* tag, const char* stage)
{
  if (!src) return 0;

  GLuint sh = glCreateShader(type);
  if (!sh) {
    ef2_log_print(ANDROID_LOG_ERROR, "ef2", "[%s] glCreateShader failed (%s)", tag ? tag : "program", stage ? stage : "?");
    return 0;
  }

  const GLchar* p = (const GLchar*)src;
  glShaderSource(sh, 1, &p, NULL);
  glCompileShader(sh);

  GLint ok = 0;
  glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    ef2_log_print(ANDROID_LOG_ERROR, "ef2", "[%s] %s shader compile FAILED", tag ? tag : "program", stage ? stage : "?");
    ef2__gl_log_shader(sh, stage, tag);
    glDeleteShader(sh);
    return 0;
  }

  // Even on success, log warnings if any.
  ef2__gl_log_shader(sh, stage, tag);
  return sh;
}

static GLuint ef2__gl_link_program(GLuint vs, GLuint fs, const char* tag)
{
  GLuint prog = glCreateProgram();
  if (!prog) {
    ef2_log_print(ANDROID_LOG_ERROR, "ef2", "[%s] glCreateProgram failed", tag ? tag : "program");
    return 0;
  }

  glAttachShader(prog, vs);
  glAttachShader(prog, fs);
  // Bind common attributes to fixed locations (match original: no glGetAttribLocation).

  glBindAttribLocation(prog, 0, "linedata");

  glLinkProgram(prog);
  GLint ok = 0;
  glGetProgramiv(prog, GL_LINK_STATUS, &ok);
  if (!ok) {
    ef2_log_print(ANDROID_LOG_ERROR, "ef2", "[%s] program link FAILED", tag ? tag : "program");
    ef2__gl_log_program(prog, tag);
    glDeleteProgram(prog);
    return 0;
  }

  // Log warnings if any.
  ef2__gl_log_program(prog, tag);
  return prog;
}
#endif

void ef2_Program_init(ef2_Program* p)
{
  if (!p) return;
  memset(p, 0, sizeof(*p));
  p->id = 0;
  p->vs_id = 0;
  p->fs_id = 0;
  p->vert_src = NULL;
  p->frag_src = NULL;
  p->uniforms = NULL;
  p->uniform_count = 0;
  p->uniform_cap = 0;
}

void ef2_Program_deinit(ef2_Program* p)
{
  if (!p) return;

#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
  if (p->id) {
    // Best-effort cleanup. If called without a valid context, GL may simply ignore.
    glDeleteProgram(p->id);
    p->id = 0;
  }
  if (p->vs_id) { glDeleteShader(p->vs_id); p->vs_id = 0; }
  if (p->fs_id) { glDeleteShader(p->fs_id); p->fs_id = 0; }
#else
  p->id = 0;
#endif

  free(p->vert_src); p->vert_src = NULL;
  free(p->frag_src); p->frag_src = NULL;

  {
    size_t i;
    for (i = 0; i < p->uniform_count; i++) {
      ef2__uniform_free(&p->uniforms[i]);
    }
  }
  free(p->uniforms);
  p->uniforms = NULL;
  p->uniform_count = 0;
  p->uniform_cap = 0;
}

int ef2_Program_setSource(ef2_Program* p, const char* vert_src, const char* frag_src)
{
  if (!p) return 0;

  // Keep a copy of sources for debugging (and for stub/host mode).
  free(p->vert_src); p->vert_src = ef2__dupstr(vert_src ? vert_src : "");
  free(p->frag_src); p->frag_src = ef2__dupstr(frag_src ? frag_src : "");

#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
  // Recreate the real program each time.
  if (p->id) { glDeleteProgram(p->id); p->id = 0; }
  if (p->vs_id) { glDeleteShader(p->vs_id); p->vs_id = 0; }
  if (p->fs_id) { glDeleteShader(p->fs_id); p->fs_id = 0; }

  // Compile + link
  GLuint vs = ef2__gl_compile_shader(GL_VERTEX_SHADER, vert_src, "renderer", "vertex");
  GLuint fs = ef2__gl_compile_shader(GL_FRAGMENT_SHADER, frag_src, "renderer", "fragment");
  if (!vs || !fs) {
    if (vs) glDeleteShader(vs);
    if (fs) glDeleteShader(fs);
    return 0;
  }

  GLuint prog = ef2__gl_link_program(vs, fs, "renderer");
  if (!prog) {
    glDeleteShader(vs);
    glDeleteShader(fs);
    return 0;
  }

  // We can detach shaders after linking; keep ids for optional cleanup anyway.

  p->id = prog;
  p->vs_id = vs;
  p->fs_id = fs;

  // Reset cached locations; they depend on linked program.
  {
    size_t i;
    for (i = 0; i < p->uniform_count; i++) {
      p->uniforms[i].loc = -2;
    }
  }

  ef2_log_print(ANDROID_LOG_INFO, "ef2", "[renderer] program linked id=%u", (unsigned)p->id);
  return 1;
#else
  // Stub/host: allocate a stable synthetic id using GL buffer ids.
  if (!p->id) {
    GLuint tmp = 0;
    glGenBuffers(1, &tmp);
    p->id = tmp;
  }
  return 1;
#endif
}

int ef2_Program_setUniform1f(ef2_Program* p, const char* name, float a)
{
  ef2_UniformEntry* u = ef2__program_get_uniform(p, name, 0, 1);
  if (!u) return 0;
  u->v.f[0] = a;
  return 1;
}
int ef2_Program_setUniform2f(ef2_Program* p, const char* name, float a, float b)
{
  ef2_UniformEntry* u = ef2__program_get_uniform(p, name, 0, 2);
  if (!u) return 0;
  u->v.f[0] = a; u->v.f[1] = b;
  return 1;
}
int ef2_Program_setUniform3f(ef2_Program* p, const char* name, float a, float b, float c)
{
  ef2_UniformEntry* u = ef2__program_get_uniform(p, name, 0, 3);
  if (!u) return 0;
  u->v.f[0] = a; u->v.f[1] = b; u->v.f[2] = c;
  return 1;
}
int ef2_Program_setUniform4f(ef2_Program* p, const char* name, float a, float b, float c, float d)
{
  ef2_UniformEntry* u = ef2__program_get_uniform(p, name, 0, 4);
  if (!u) return 0;
  u->v.f[0] = a; u->v.f[1] = b; u->v.f[2] = c; u->v.f[3] = d;
  return 1;
}
int ef2_Program_setUniform1i(ef2_Program* p, const char* name, int v)
{
  ef2_UniformEntry* u = ef2__program_get_uniform(p, name, 1, 1);
  if (!u) return 0;
  u->v.i = v;
  return 1;
}

int ef2_Program_getAttribLocation(ef2_Program* p, const char* name)
{
  // Match original behavior: attributes are bound to fixed locations during link
  // (see glBindAttribLocation in ef2__gl_link_program).
  if (!p || !name) return -1;
  if (strcmp(name, "linedata") == 0) return 0;
  return -1;
}

int ef2_Program_getUniformLocation(ef2_Program* p, const char* name)
{
#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
  if (!p || !name || !p->id) return -1;
  return (int)glGetUniformLocation(p->id, (const GLchar*)name);
#else
  (void)p; (void)name;
  return -1;
#endif
}

void ef2_Program_applyUniforms(ef2_Program* p)
{
#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
  if (!p || !p->id) return;

  glUseProgram(p->id);

  {
    size_t i;
    for (i = 0; i < p->uniform_count; i++) {
      ef2_UniformEntry* u = &p->uniforms[i];
      if (!u->name) continue;

    if (u->loc == -2) {
      u->loc = (int)glGetUniformLocation(p->id, (const GLchar*)u->name);
    }
    if (u->loc < 0) continue;

    if (u->kind == 1) {
      glUniform1iv((GLint)u->loc, 1, &u->v.i);
      continue;
    }

    switch (u->count) {
      case 1: glUniform1fv((GLint)u->loc, 1, &u->v.f[0]); break;
      case 2: glUniform2fv((GLint)u->loc, 1, &u->v.f[0]); break;
      case 3: glUniform3fv((GLint)u->loc, 1, &u->v.f[0]); break;
      case 4: glUniform4fv((GLint)u->loc, 1, &u->v.f[0]); break;
      default: break;
    }
    }
  }
#else
  (void)p;
#endif
}

void ef2_Program_use(ef2_Program* p)
{
#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
  if (!p || !p->id) return;
  glUseProgram(p->id);
#else
  (void)p;
#endif
}

int ef2_Program_enableAttrib(ef2_Program* p, const char* name,
                            GLint size, GLenum type, GLboolean normalized,
                            GLsizei stride, const void* offset)
{
#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
  if (!p || !p->id || !name) return 0;
  GLint loc = ef2_Program_getAttribLocation(p, name);
  if (loc < 0) return 0;
  glEnableVertexAttribArray((GLuint)loc);
  glVertexAttribPointer((GLuint)loc, size, type, normalized, stride, offset);
  return 1;
#else
  (void)p; (void)name; (void)size; (void)type; (void)normalized; (void)stride; (void)offset;
  return 0;
#endif
}


void ef2_Program_dumpUniforms(const ef2_Program* p, const char* tag)
{
  if (!p) return;
  const char* t = tag ? tag : "program";
  ef2_log_print(ANDROID_LOG_INFO, "ef2", "[%s] uniforms=%zu", t, p->uniform_count);

  {
    size_t i;
    for (i = 0; i < p->uniform_count; i++) {
      const ef2_UniformEntry* u = &p->uniforms[i];
      if (!u->name) continue;
      if (u->kind == 1) {
        ef2_log_print(ANDROID_LOG_INFO, "ef2", "  %s = %d (i)", u->name, u->v.i);
      } else {
        if (u->count == 1) ef2_log_print(ANDROID_LOG_INFO, "ef2", "  %s = %f", u->name, u->v.f[0]);
        else if (u->count == 2) ef2_log_print(ANDROID_LOG_INFO, "ef2", "  %s = (%f,%f)", u->name, u->v.f[0], u->v.f[1]);
        else if (u->count == 3) ef2_log_print(ANDROID_LOG_INFO, "ef2", "  %s = (%f,%f,%f)", u->name, u->v.f[0], u->v.f[1], u->v.f[2]);
        else if (u->count == 4) ef2_log_print(ANDROID_LOG_INFO, "ef2", "  %s = (%f,%f,%f,%f)", u->name, u->v.f[0], u->v.f[1], u->v.f[2], u->v.f[3]);
        else ef2_log_print(ANDROID_LOG_INFO, "ef2", "  %s = (float x%d)", u->name, u->count);
      }
    }
  }
}
