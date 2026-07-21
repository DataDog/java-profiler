/*
 * Copyright 2026 Datadog, Inc
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
#ifndef _NATIVEMEM_H
#define _NATIVEMEM_H

#include "arch.h"
#include <cassert>

// Physical native-memory categories used by the profiler's own allocations.
// Every tracked backing allocation belongs to exactly one category, so the
// per-category live byte gauges partition the total: sum(category) == total,
// with no double counting.
//
// The "reserved vs used vs wasted" breakdowns exposed by the existing counters
// (CALLTRACE_STORAGE_BYTES is the used slice of the CALLTRACE arena;
// DICTIONARY_ARENA_WASTE_BYTES is the wasted slice of the DICTIONARY arena) are
// a separate, nested dimension. They are intentionally NOT summed in here.
#define DD_NATIVE_MEM_CATEGORY_TABLE(X)                                        \
  X(CALLTRACE, "calltrace")                                                    \
  X(DICTIONARY, "dictionary")                                                  \
  X(THREAD_FILTER, "thread_filter")                                            \
  X(NATIVE_SYMBOLS, "native_symbols")                                          \
  X(LINE_TABLES, "line_tables")                                                \
  X(PERF, "perf")                                                              \
  X(THREAD_LOCAL, "thread_local")                                              \
  X(JFR_BUFFERS, "jfr_buffers")                                                \
  X(MISC, "misc")

#define X_NM_ENUM(a, b) NM_##a,
typedef enum NativeMemCategory : int {
  DD_NATIVE_MEM_CATEGORY_TABLE(X_NM_ENUM) NM_NUM_CATEGORIES
} NativeMemCategory;
#undef X_NM_ENUM

// Tracks the profiler's live native memory per category, plus a moving-window
// average and running peak. Live accounting is always-on and independent of the
// COUNTERS build flag: record() is a relaxed atomic add, plus (for allocations)
// a conditional lock-free high-water update of the per-category peak.
//
// Most call sites are off the signal path (they allocate via malloc/new, which
// are not async-signal-safe anyway). The exception is the CALLTRACE arena: it
// allocates from within the sampling signal handler (via OS::safeAlloc's raw
// mmap syscall), so record() must stay async-signal-safe there -- which
// lock-free relaxed atomics are.
//
// The moving average and peak are refreshed by sample(), which is expected to
// be called from a single thread (the JFR chunk-finish path).
class NativeMem {
private:
  // Number of sample() ticks retained in the moving-average window.
  static const int WINDOW = 64;

  static volatile long long _live[NM_NUM_CATEGORIES];
  // Precise per-category high-water mark, maintained at allocation time by
  // record() so peaks that rise and fall between sample() ticks are still seen.
  static volatile long long _max[NM_NUM_CATEGORIES];

  // sample()-owned state; touched only from the single-threaded sampling path.
  static long long _window[NM_NUM_CATEGORIES][WINDOW];
  static long long _total_window[WINDOW];
  static int _window_pos;
  static int _window_count;
  static long long _avg[NM_NUM_CATEGORIES];
  static long long _total_avg;
  static long long _total_max_observed;

public:
  // Account for a backing allocation (delta > 0) or free (delta < 0).
  static void record(NativeMemCategory category, long long delta) {
    long long prev = atomicIncRelaxed(_live[category], delta);
    long long updated = prev + delta;
    // Invariant: a category's live bytes never go negative — every decrement is
    // matched by a prior same-sized increment. A negative result means an
    // unbalanced or oversized free (an accounting bug). Stripped under NDEBUG,
    // so this costs nothing in release and never runs in a real signal handler
    // there; it catches pairing bugs in debug/gtest builds instead.
    assert(updated >= 0);
    if (delta > 0) {
      // Only allocations can raise the peak. In the common case (no new peak)
      // this is a single relaxed load plus a compare; the CAS fires only when a
      // genuinely higher peak is set, which is rare since _max is monotonic.
      long long m = load(_max[category]);
      while (updated > m &&
             !__atomic_compare_exchange_n(&_max[category], &m, updated, false,
                                          __ATOMIC_RELAXED, __ATOMIC_RELAXED)) {
        // On failure m is reloaded with the current value; loop and retry.
      }
    }
  }

  // Set a category's live value directly, for gauge-style subsystems whose size
  // is recomputed as an absolute (rather than tracked via alloc/free deltas).
  // Also advances the peak. Not for use from a signal handler.
  static void setLive(NativeMemCategory category, long long value) {
    store(_live[category], value);
    long long m = load(_max[category]);
    while (value > m &&
           !__atomic_compare_exchange_n(&_max[category], &m, value, false,
                                        __ATOMIC_RELAXED, __ATOMIC_RELAXED)) {
    }
  }

  static long long live(NativeMemCategory category) {
    return load(_live[category]);
  }
  static long long liveTotal();

  // Fold the current live gauges into the moving-average window and the observed
  // total peak. Call once per sampling tick from a single thread.
  static void sample();

  static long long avg(NativeMemCategory category) { return _avg[category]; }
  static long long max(NativeMemCategory category) { return load(_max[category]); }
  static long long avgTotal() { return _total_avg; }
  // Upper bound on the total peak: the sum of the precise per-category peaks.
  // Exact only if the category peaks coincided; otherwise an overestimate.
  static long long maxTotal();
  // Lower bound on the total peak: the largest instantaneous total seen at a
  // sampling tick. Misses peaks that rise and fall entirely between ticks.
  static long long maxTotalObserved() { return _total_max_observed; }

  // Clear all live gauges and window/peak state. Not thread-safe against
  // concurrent record()/sample(); intended for process init and tests.
  static void reset();

  static const char *categoryName(NativeMemCategory category);
};

#endif // _NATIVEMEM_H
