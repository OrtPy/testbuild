#pragma once
#include "ef2/common.h"
#include "ef2/gles.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ef2_UniformEntry {
  char* name;      // heap-owned
  int   kind;      // 0=float, 1=int
  int   count;     // number of float components (1/2/3/4)
  int   loc;       // cached glGetUniformLocation (or -1 if not found). For host/stub, stays -1.
  union {
    float f[4];
    int   i;
  } v;
} ef2_UniformEntry;

typedef struct ef2_Program {
  // Real GLES: this is the GL program object id.
  // Stub/host: a synthetic id.
  GLuint id;

  // Optional shader object ids (real GLES only). Zero when unused.
  GLuint vs_id;
  GLuint fs_id;

  // Stored sources (also used for debugging and for stub/host mode).
  char* vert_src;
  char* frag_src;

  // Host-side uniform store (keeps the project testable without a GLES context).
  ef2_UniformEntry* uniforms;
  size_t uniform_count;
  size_t uniform_cap;
} ef2_Program;

void ef2_Program_init(ef2_Program* p);
void ef2_Program_deinit(ef2_Program* p);

// Create/replace program from source.
// - Stub/host: stores strings + alloc id.
// - Android + EF2_USE_REAL_GLES: compiles/links a real GLES2 program and keeps sources too.
int  ef2_Program_setSource(ef2_Program* p, const char* vert_src, const char* frag_src);

// ---- Uniform handling ------------------------------------------------------
// These helpers mimic the original program::getuniform + uniform::set flow.
// They always cache values. When used with a real program, call ef2_Program_applyUniforms()
// after glUseProgram(p->id) to actually send them to GL.

// Set scalar or vector uniforms by name.
int  ef2_Program_setUniform1f(ef2_Program* p, const char* name, float a);
int  ef2_Program_setUniform2f(ef2_Program* p, const char* name, float a, float b);
int  ef2_Program_setUniform3f(ef2_Program* p, const char* name, float a, float b, float c);
int  ef2_Program_setUniform4f(ef2_Program* p, const char* name, float a, float b, float c, float d);
int  ef2_Program_setUniform1i(ef2_Program* p, const char* name, int v);

// Real GLES helpers (safe no-ops on stub/host).
int  ef2_Program_getAttribLocation(ef2_Program* p, const char* name);
int  ef2_Program_getUniformLocation(ef2_Program* p, const char* name);
void ef2_Program_applyUniforms(ef2_Program* p);

// Helpers used by renderer draw path (match original C++ flow).
void ef2_Program_use(ef2_Program* p);
int ef2_Program_enableAttrib(ef2_Program* p, const char* name,
                           GLint size, GLenum type, GLboolean normalized,
                           GLsizei stride, const void* offset);

// Debug: dump current uniform values.
void ef2_Program_dumpUniforms(const ef2_Program* p, const char* tag);

#ifdef __cplusplus
}
#endif
