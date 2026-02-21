#pragma once

// Minimal placeholder for ef2/event.h
//
// The current C-port build does not require event APIs yet, but some compat
// translation units include this header to match the original include layout.
// Keep this header intentionally minimal to avoid changing codegen.

#ifdef __cplusplus
extern "C" {
#endif

// Forward-declare a small opaque event type for future use.
typedef struct ef2_event ef2_event;

#ifdef __cplusplus
}
#endif
