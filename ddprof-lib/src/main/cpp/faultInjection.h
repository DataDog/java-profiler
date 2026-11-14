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
// path — SafeAccess safefetch or walkVM's sigsetjmp/siglongjmp — is exercised) or a
// random int/long value.  When the flag is NOT defined, every macro is a strict
// identity: it expands to exactly the parenthesized original expression, with
// unchanged type and value category and zero runtime cost.
//
//   pc = SafeAccess::load(INJECT_FAULT_ADDRESS_LIKELY((void**)fp));
//   VMMethod* m = ((VMMethod**)INJECT_FAULT_ADDRESS_UNLIKELY(fp))[off];
//
// INJECT_FAULT_BOOL_* wraps the *result* of a call that already ran for
// real, forcing it to report `false` so a caller's failure-handling path
// (not its memory-safety recovery path) gets exercised, e.g.:
//
//   return INJECT_FAULT_BOOL_LIKELY(dlopen(name, flags) != nullptr);
//
// INJECT_CRASH_* goes at the same kind of site as INJECT_FAULT_ADDRESS_*, but it
// is a statement rather than an expression wrapper: it takes no argument and
// yields no value.  Instead of substituting a poison address for the caller to
// dereference -- which a downstream recovery path (SafeAccess safefetch, a
// sigsetjmp/siglongjmp window) may absorb without a signal ever being raised --
// it raises the SIGSEGV itself, right at the call site.  Use it to exercise the
// sigsetjmp/siglongjmp window enclosing the call site, or the top-level crash
// handler where there is no such window:
//
//   INJECT_CRASH_LIKELY();
//
// The four tiers name their firing frequency: RARE 0.01%, UNLIKELY 0.1%,
// LIKELY 1%, HIGH 10%.  See faultInjection.cpp for the poison-address and PRNG
// details.

#ifndef _FAULT_INJECTION_H
#define _FAULT_INJECTION_H

#include <cassert>

#if defined(__FAULT_INJECTION__) || defined(DEBUG) 
// Deliberately dereferences nullptr to raise a real SIGSEGV right now,
// unconditionally (no probability gate, no shouldFire() draw). For exercising
// crash-handler / recovery paths on demand (e.g. from a test), never from a
// production code path.
[[noreturn]] void crashNow();
#endif 

#ifdef __FAULT_INJECTION__

#include "arch.h"  // u64
#include <cstdint>

#define NO_INJECTION_ASSERT(a)
namespace faultinj {

// Firing probability expressed as an xorshift64 threshold (round(p * 2^64)), so
// the hot-path check is a single integer compare (rng < threshold) with no
// floating point in the signal handler.
constexpr u64 PROB_RARE     = 1844674407370955ULL;    // 1e-4  (0.01%)
constexpr u64 PROB_UNLIKELY = 18446744073709552ULL;   // 1e-3  (0.1%)
constexpr u64 PROB_LIKELY   = 184467440737095520ULL;  // 1e-2  (1%)
constexpr u64 PROB_HIGH     = 1844674407370955162ULL; // 1e-1  (10%)

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
uintptr_t poisonAddress();

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

// Like injectAddress(), but instead of substituting a poison pointer into the
// expression (leaving recovery to whatever the caller does with it downstream
// -- SafeAccess safefetch, walkVM's sigsetjmp/siglongjmp), this crashes right
// here, right now, when the tier fires. Whatever encloses the call site is what
// gets exercised: the nearest sigsetjmp/siglongjmp window if there is one, the
// top-level crash handler otherwise.
//
// Unlike injectAddress() this wraps no expression -- it takes no pointer and
// returns nothing, so it is a statement, not a drop-in for an
// INJECT_FAULT_ADDRESS_* site. It does nothing when the tier does not fire.
inline void injectCrash(u64 threshold, const char* fn) {
    if (__builtin_expect(shouldFire(threshold, fn), 0)) {
        crashNow();
    }
}

// Returns orig unchanged, or `faulty` when the tier fires. Unlike
// injectAddress() (which fakes an input about to be dereferenced), this fakes
// the *outcome* of a call that already ran for real — e.g. making a
// successful dlopen() appear to have failed, to exercise a caller's error
// path without needing the library to actually be absent.
template <typename T>
inline T injectValue(T orig, T faulty, u64 threshold, const char* fn) {
  if (__builtin_expect(shouldFire(threshold, fn), 0)) {
    return faulty;
  }
  return orig;
}
}  // namespace faultinj

#define INJECT_FAULT_ADDRESS_RARE(ptr) \
    ::faultinj::injectAddress((ptr), ::faultinj::PROB_RARE, __func__)
#define INJECT_FAULT_ADDRESS_UNLIKELY(ptr) \
    ::faultinj::injectAddress((ptr), ::faultinj::PROB_UNLIKELY, __func__)
#define INJECT_FAULT_ADDRESS_LIKELY(ptr) \
    ::faultinj::injectAddress((ptr), ::faultinj::PROB_LIKELY, __func__)
#define INJECT_FAULT_ADDRESS_HIGH(ptr) \
    ::faultinj::injectAddress((ptr), ::faultinj::PROB_HIGH, __func__)

#define INJECT_FAULT_BOOL_RARE(v) \
    ::faultinj::injectValue((v), false, ::faultinj::PROB_RARE, __func__)
#define INJECT_FAULT_BOOL_UNLIKELY(v) \
    ::faultinj::injectValue((v), false, ::faultinj::PROB_UNLIKELY, __func__)
#define INJECT_FAULT_BOOL_LIKELY(v) \
    ::faultinj::injectValue((v), false, ::faultinj::PROB_LIKELY, __func__)
#define INJECT_FAULT_BOOL_HIGH(v) \
    ::faultinj::injectValue((v), false, ::faultinj::PROB_HIGH, __func__)

#define INJECT_CRASH_RARE() \
    ::faultinj::injectCrash(::faultinj::PROB_RARE, __func__)
#define INJECT_CRASH_UNLIKELY() \
    ::faultinj::injectCrash(::faultinj::PROB_UNLIKELY, __func__)
#define INJECT_CRASH_LIKELY() \
    ::faultinj::injectCrash(::faultinj::PROB_LIKELY, __func__)
#define INJECT_CRASH_HIGH() \
    ::faultinj::injectCrash(::faultinj::PROB_HIGH, __func__)

#else  // __FAULT_INJECTION__ not defined — strict identity, zero cost.

#define INJECT_FAULT_ADDRESS_RARE(ptr)     (ptr)
#define INJECT_FAULT_ADDRESS_UNLIKELY(ptr) (ptr)
#define INJECT_FAULT_ADDRESS_LIKELY(ptr)   (ptr)
#define INJECT_FAULT_ADDRESS_HIGH(ptr)     (ptr)

#define INJECT_FAULT_BOOL_RARE(v)     (v)
#define INJECT_FAULT_BOOL_UNLIKELY(v) (v)
#define INJECT_FAULT_BOOL_LIKELY(v)   (v)
#define INJECT_FAULT_BOOL_HIGH(v)     (v)

// ((void)0) rather than nothing, so `INJECT_CRASH_LIKELY();` stays a
// well-formed expression statement in every context (e.g. as the sole body of
// an unbraced if/else) instead of collapsing to a stray semicolon.
#define INJECT_CRASH_RARE()     ((void)0)
#define INJECT_CRASH_UNLIKELY() ((void)0)
#define INJECT_CRASH_LIKELY()   ((void)0)
#define INJECT_CRASH_HIGH()     ((void)0)

#define NO_INJECTION_ASSERT(a) (assert(a))

#endif  // __FAULT_INJECTION__

#endif  // _FAULT_INJECTION_H
