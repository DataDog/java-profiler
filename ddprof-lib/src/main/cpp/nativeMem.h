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
  X(CONTEXT, "context")                                                        \
  X(THREAD_FILTER, "thread_filter")                                            \
  X(CODECACHE, "codecache")                                                    \
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
// COUNTERS build flag: record() is a single relaxed atomic add, which is
// async-signal-safe and therefore usable from signal handlers.
//
// The moving average and peak are refreshed by sample(), which is expected to
// be called from a single thread (the JFR chunk-finish path).
class NativeMem {
private:
  // Number of sample() ticks retained in the moving-average window.
  static const int WINDOW = 64;

  static volatile long long _live[NM_NUM_CATEGORIES];

  // sample()-owned state; not touched from allocation sites.
  static long long _window[NM_NUM_CATEGORIES][WINDOW];
  static long long _total_window[WINDOW];
  static int _window_pos;
  static int _window_count;
  static long long _avg[NM_NUM_CATEGORIES];
  static long long _max[NM_NUM_CATEGORIES];
  static long long _total_avg;
  static long long _total_max;

public:
  // Account for a backing allocation (delta > 0) or free (delta < 0).
  static void record(NativeMemCategory category, long long delta) {
    atomicIncRelaxed(_live[category], delta);
  }

  static long long live(NativeMemCategory category) {
    return load(_live[category]);
  }
  static long long liveTotal();

  // Fold the current live gauges into the moving-average window and the running
  // peak. Call once per sampling tick from a single thread.
  static void sample();

  static long long avg(NativeMemCategory category) { return _avg[category]; }
  static long long max(NativeMemCategory category) { return _max[category]; }
  static long long avgTotal() { return _total_avg; }
  static long long maxTotal() { return _total_max; }

  // Clear all live gauges and window/peak state. Not thread-safe against
  // concurrent record()/sample(); intended for process init and tests.
  static void reset();

  static const char *categoryName(NativeMemCategory category);
};

#endif // _NATIVEMEM_H
