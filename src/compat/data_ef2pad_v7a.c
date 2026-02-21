// SPDX-License-Identifier: MIT
// Inject the remaining 0x24 bytes for the reference .data payload.
//
// Reference .data is 0x28 bytes. In our build, the first 4 bytes are provided
// by __dso_handle (0x00000000). This file injects the remaining 9 words (0x24).

#include <stdint.h>

__attribute__((used, section(".data.ef2pad")))
uint32_t ef2_data_pad_words[9] = {
    0xffffffffu,
    0x00000000u,
    0x00000000u,
    0x00000000u,
    0x3f800000u,
    0x3f800000u,
    0x00000000u,
    0x3f800000u,
    0x3f800000u,
};
