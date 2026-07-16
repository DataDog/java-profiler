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

#include "faultInjection.h"

// The whole translation unit is empty unless fault injection is enabled, so a
// normal build links a no-op object file.
#ifdef __FAULT_INJECTION__

#include "counters.h"          // Counters::increment (FAULTS_INJECTED)
#include "os.h"                // OS::page_size
#include "threadLocalData.h"   // ProfiledThread::currentSignalSafe / nextFiRandom
#include <atomic>
#include <sys/mman.h>

namespace faultinj {

// Knuth multiplicative constant (== common.h KNUTH_MULTIPLICATIVE_CONSTANT),
// used to hash the function name and to advance the global fallback PRNG.
static constexpr u64 KNUTH = 0x9e3779b97f4a7c15ULL;

// Word-alignment mask for produced addresses.
static constexpr uintptr_t ALIGN_MASK = ~(uintptr_t)(sizeof(void*) - 1);

// Guard region: mmapped once at init() with PROT_NONE so any access faults.
// Written only by init() (off the signal path); read-only afterwards.
static std::atomic<uintptr_t> g_guard_base{0};
static std::atomic<uintptr_t> g_guard_span{0};
static std::atomic<bool>      g_guard_ok{false};

// Fallback PRNG for threads with no ProfiledThread context.  Relaxed atomics
// keep it lock-free and async-signal-safe; a lost update on a race is harmless.
static std::atomic<u64> g_fallback_rng{KNUTH};

void init() {
  // Avoid repeated mmaps (tests call init() in each fixture SetUp()).
  if (g_guard_ok.load(std::memory_order_acquire)) {
    return;
  }

  // A handful of pages is plenty of distinct fault addresses; keep it small.
  size_t span = 16 * OS::page_size;
  void* p = mmap(nullptr, span, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (p == MAP_FAILED) {
    return;
  }

  g_guard_base.store((uintptr_t)p, std::memory_order_relaxed);
  g_guard_span.store(span, std::memory_order_relaxed);
  g_guard_ok.store(true, std::memory_order_release);
}

u64 nextRandom() {
  ProfiledThread* t = ProfiledThread::currentSignalSafe();  // never allocates
  if (t != nullptr) {
    return t->nextFiRandom();
  }
  // Fallback: relaxed atomic xorshift64.  Not perfectly serialised, but the
  // stream only needs to be roughly uniform for injection decisions.
  u64 x = g_fallback_rng.load(std::memory_order_relaxed);
  if (x == 0) x = 1;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  g_fallback_rng.store(x, std::memory_order_relaxed);
  return x;
}

bool shouldFire(u64 threshold, const char* fn) {
  // XOR with a per-function hash is a bijection on 64 bits, so it perturbs the
  // stream per call site while keeping the fire probability exactly
  // threshold/2^64.
  u64 r = nextRandom() ^ ((u64)(uintptr_t)fn * KNUTH);
  if (__builtin_expect(r < threshold, 0)) {
    // Every address/int/long injection routes through here, so this is the one
    // place that counts an actually-injected fault.
    Counters::increment(FAULTS_INJECTED);
    return true;
  }
  return false;
}

uintptr_t poisonAddress() {
  u64 r = nextRandom();
  if (g_guard_ok && (r & 1u)) {
    // Guaranteed-unmapped guard page — deterministic SIGSEGV.
    return (g_guard_base + (uintptr_t)(r % g_guard_span)) & ALIGN_MASK;
  }
  // Random non-canonical address (high bit set keeps it well above any mapped
  // low page) — may raise SIGSEGV or SIGBUS.
  return ((uintptr_t)r | (uintptr_t)0x8000000000000000ULL) & ALIGN_MASK;
}

int32_t injectInt(int32_t v, u64 threshold, const char* fn) {
  if (__builtin_expect(shouldFire(threshold, fn), 0)) {
    return (int32_t)nextRandom();
  }
  return v;
}

int64_t injectLong(int64_t v, u64 threshold, const char* fn) {
  if (__builtin_expect(shouldFire(threshold, fn), 0)) {
    return (int64_t)nextRandom();
  }
  return v;
}

}  // namespace faultinj

#endif  // __FAULT_INJECTION__
