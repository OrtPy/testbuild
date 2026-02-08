#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Returns 1 on success, 0 on failure.
// The returned names list must be freed by free_string_list().
int list_exported_function_names(const char *path, const char *filter, char ***out_names, int *out_count);
void free_string_list(char **names, int count);

#ifdef __cplusplus
}
#endif
