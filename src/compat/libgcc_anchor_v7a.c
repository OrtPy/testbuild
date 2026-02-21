#include <stdint.h>

// Force-pull common libgcc / AEABI helpers into the shared object so that
// exported symbols (listed in exports_armeabi_v7a.map) actually exist.
//
// IMPORTANT: This must *not* create new PLT imports. These should resolve from
// libgcc objects that get linked into the DSO.

#ifdef __cplusplus
extern "C" {
#endif

// Division / modulo helpers
uint32_t __aeabi_uidiv(uint32_t, uint32_t);
int32_t  __aeabi_idiv(int32_t, int32_t);
uint64_t __aeabi_uidivmod(uint32_t, uint32_t);
int64_t  __aeabi_idivmod(int32_t, int32_t);
uint64_t __aeabi_uldivmod(uint64_t, uint64_t);
int64_t  __aeabi_ldivmod(int64_t, int64_t);

// Integer/FP conversions
int32_t  __aeabi_d2iz(double);
int32_t  __aeabi_f2iz(float);
double   __aeabi_i2d(int32_t);
float    __aeabi_i2f(int32_t);
float    __aeabi_d2f(double);
double   __aeabi_f2d(float);

double   __aeabi_dadd(double,double);
double   __aeabi_dsub(double,double);
double   __aeabi_dmul(double,double);
double   __aeabi_ddiv(double,double);

long long __aeabi_lmul(long long, long long);

// Unwind entrypoints often present in reference.
void __aeabi_unwind_cpp_pr0(void);
void __aeabi_unwind_cpp_pr1(void);
void __aeabi_unwind_cpp_pr2(void);

static inline void ef2_barrier_u32(uint32_t v) { __asm__ __volatile__("" : : "r"(v) : "memory"); }
static inline void ef2_barrier_u64(uint64_t v) { __asm__ __volatile__("" : : "r"(v) : "memory"); }
static inline void ef2_barrier_f(float v) { __asm__ __volatile__("" : : "r"(v) : "memory"); }
static inline void ef2_barrier_d(double v) { __asm__ __volatile__("" : : "r"(v) : "memory"); }

__attribute__((used, visibility("default"))) void ef2_libgcc_anchor_v7a(void) {
  volatile uint32_t a = 123, b = 7;
  volatile uint64_t A = 123456789ULL, B = 97ULL;

  // The following calls are only to force inclusion.
  ef2_barrier_u32(__aeabi_uidiv(a, b));
  ef2_barrier_u32((uint32_t)__aeabi_idiv((int32_t)a, (int32_t)b));
  ef2_barrier_u64(__aeabi_uidivmod(a, b));
  ef2_barrier_u64((uint64_t)__aeabi_idivmod((int32_t)a, (int32_t)b));
  ef2_barrier_u64(__aeabi_uldivmod(A, B));
  ef2_barrier_u64((uint64_t)__aeabi_ldivmod((int64_t)A, (int64_t)B));

  ef2_barrier_d(__aeabi_i2d((int32_t)a));
  ef2_barrier_f(__aeabi_i2f((int32_t)a));
  ef2_barrier_u32((uint32_t)__aeabi_d2iz(3.14));
  ef2_barrier_u32((uint32_t)__aeabi_f2iz(2.0f));
  ef2_barrier_f(__aeabi_d2f(1.5));
  ef2_barrier_d(__aeabi_f2d(1.0f));

  ef2_barrier_d(__aeabi_dadd(1.0, 2.0));
  ef2_barrier_d(__aeabi_dsub(3.0, 1.0));
  ef2_barrier_d(__aeabi_dmul(2.0, 4.0));
  ef2_barrier_d(__aeabi_ddiv(9.0, 3.0));

  (void)__aeabi_lmul(2, 3);

  // Unwind entrypoints
  __aeabi_unwind_cpp_pr0();
  __aeabi_unwind_cpp_pr1();
  __aeabi_unwind_cpp_pr2();
}

#ifdef __cplusplus
}
#endif
