/*
 * Copyright 2026, Datadog, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Compile-time fault-injection layer for the profiler's memory-access sites.
//
// The macros below wrap a pointer or value expression at a real dereference
// site (VMStructs::at, walkVM, walkFP, walkDwarf).  When __FAULT_INJECTION__ is
// defined, each wrapped expression, with the tier's probability, is replaced by
// a deliberately bad address (so the load faults and the profiler's recovery
// path — SafeAccess safefetch or walkVM's setjmp/longjmp — is exercised) or a
// random int/long value.  When the flag is NOT defined, every macro is a strict
// identity: it expands to exactly the parenthesized original expression, with
// unchanged type and value category and zero runtime cost.
//
//   pc = SafeAccess::load(INJECT_FAULT_ADDRESS_LIKELY((void**)fp));
//   VMMethod* m = ((VMMethod**)INJECT_FAULT_ADDRESS_UNLIKELY(fp))[off];
//
// The three tiers name their firing frequency: RARE 0.01%, UNLIKELY 0.1%,
// LIKELY 1%.  See faultInjection.cpp for the poison-address and PRNG details.

#ifndef _FAULT_INJECTION_H
#define _FAULT_INJECTION_H

#ifdef __FAULT_INJECTION__

#include "arch.h"  // u64
#include <cstdint>

namespace faultinj {

// Firing probability expressed as an xorshift64 threshold (round(p * 2^64)), so
// the hot-path check is a single integer compare (rng < threshold) with no
// floating point in the signal handler.
constexpr u64 PROB_RARE     = 1844674407370955ULL;    // 1e-4  (0.01%)
constexpr u64 PROB_UNLIKELY = 18446744073709552ULL;   // 1e-3  (0.1%)
constexpr u64 PROB_LIKELY   = 184467440737095520ULL;  // 1e-2  (1%)

// Called once at profiler startup (off the signal path) to mmap the PROT_NONE
// guard region used by poisonAddress().  Safe to call before any injection.
void init();

// Draws one per-thread (or global-fallback) PRNG value.  Async-signal-safe.
u64 nextRandom();

// Returns true with probability threshold/2^64.  The function name perturbs the
// draw so distinct call sites get statistically independent decisions.
bool shouldFire(u64 threshold, const char* fn);

// A word-aligned address intended to fault on access. When init() has reserved the
// mmap'd PROT_NONE guard region, this returns an address inside it (deterministic
// SIGSEGV). If init() failed, it falls back to a best-effort garbage address.

// Returns ptr unchanged, or a poison address (cast to T) when the tier fires.
// Templated so the wrapped expression's static type (void**, const char*,
// uintptr_t, ...) is preserved exactly.
template <typename T>
inline T injectAddress(T ptr, u64 threshold, const char* fn) {
  if (__builtin_expect(shouldFire(threshold, fn), 0)) {
    // C-style cast intentionally: converts the numeric poison address to any
    // pointer type or to uintptr_t. This code only ever compiles under the flag.
    return (T)poisonAddress();
  }
  return ptr;
}

// Returns v unchanged, or a pseudo-random value when the tier fires.
int32_t injectInt(int32_t v, u64 threshold, const char* fn);
int64_t injectLong(int64_t v, u64 threshold, const char* fn);

}  // namespace faultinj

#define INJECT_FAULT_ADDRESS_RARE(ptr) \
    ::faultinj::injectAddress((ptr), ::faultinj::PROB_RARE, __func__)
#define INJECT_FAULT_ADDRESS_UNLIKELY(ptr) \
    ::faultinj::injectAddress((ptr), ::faultinj::PROB_UNLIKELY, __func__)
#define INJECT_FAULT_ADDRESS_LIKELY(ptr) \
    ::faultinj::injectAddress((ptr), ::faultinj::PROB_LIKELY, __func__)

#define INJECT_FAULT_INT_RARE(v) \
    ::faultinj::injectInt((v), ::faultinj::PROB_RARE, __func__)
#define INJECT_FAULT_INT_UNLIKELY(v) \
    ::faultinj::injectInt((v), ::faultinj::PROB_UNLIKELY, __func__)
#define INJECT_FAULT_INT_LIKELY(v) \
    ::faultinj::injectInt((v), ::faultinj::PROB_LIKELY, __func__)

#define INJECT_FAULT_LONG_RARE(v) \
    ::faultinj::injectLong((v), ::faultinj::PROB_RARE, __func__)
#define INJECT_FAULT_LONG_UNLIKELY(v) \
    ::faultinj::injectLong((v), ::faultinj::PROB_UNLIKELY, __func__)
#define INJECT_FAULT_LONG_LIKELY(v) \
    ::faultinj::injectLong((v), ::faultinj::PROB_LIKELY, __func__)

#else  // __FAULT_INJECTION__ not defined — strict identity, zero cost.

#define INJECT_FAULT_ADDRESS_RARE(ptr)     (ptr)
#define INJECT_FAULT_ADDRESS_UNLIKELY(ptr) (ptr)
#define INJECT_FAULT_ADDRESS_LIKELY(ptr)   (ptr)

#define INJECT_FAULT_INT_RARE(v)     (v)
#define INJECT_FAULT_INT_UNLIKELY(v) (v)
#define INJECT_FAULT_INT_LIKELY(v)   (v)

#define INJECT_FAULT_LONG_RARE(v)     (v)
#define INJECT_FAULT_LONG_UNLIKELY(v) (v)
#define INJECT_FAULT_LONG_LIKELY(v)   (v)

#endif  // __FAULT_INJECTION__

#endif  // _FAULT_INJECTION_H
