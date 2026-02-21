// Pad .init_array entries to match original layout (size only).
// These constructors do minimal volatile work so the compiler cannot drop them.

static volatile int ef2_ctor_pad_sink;

__attribute__((constructor(200), used)) static void ef2_pad_ctor_200(void) { ef2_ctor_pad_sink++; }
__attribute__((constructor(201), used)) static void ef2_pad_ctor_201(void) { ef2_ctor_pad_sink++; }
__attribute__((constructor(202), used)) static void ef2_pad_ctor_202(void) { ef2_ctor_pad_sink++; }
__attribute__((constructor(203), used)) static void ef2_pad_ctor_203(void) { ef2_ctor_pad_sink++; }
__attribute__((constructor(204), used)) static void ef2_pad_ctor_204(void) { ef2_ctor_pad_sink++; }
__attribute__((constructor(205), used)) static void ef2_pad_ctor_205(void) { ef2_ctor_pad_sink++; }
