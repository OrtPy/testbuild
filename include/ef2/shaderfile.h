#pragma once
#include "ef2/platform.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Read an asset as NUL-terminated text. Returns 1 on success, 0 on failure.
// On success, out_text is heap-owned and must be freed by the caller.
int ef2_asset_read_text(ef2_AAssetManager* mgr, const char* filename, char** out_text, size_t* out_len);

// Build a shader file by concatenating (if present), in order:
//  - header.<name>.base
//  - inputs.base
//  - <package>.<name>.header
//  - <package>.<name>
//  - footer.<name>.base
// Returns heap-owned NUL-terminated string (never NULL; empty string on failure).
char* ef2_renderer_buildShaderFile(ef2_AAssetManager* mgr, const char* package, const char* name);

#ifdef __cplusplus
}
#endif
