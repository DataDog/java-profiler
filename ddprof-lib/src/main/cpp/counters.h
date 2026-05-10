/*
 * Copyright 2023 Datadog, Inc
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
#ifndef JAVA_PROFILER_LIBRARY_COUNTERS_H
#define JAVA_PROFILER_LIBRARY_COUNTERS_H

#include "arch.h"
#include <cstring>
#include <vector>

#define DD_COUNTER_TABLE(X)                                                    \
  X(DICTIONARY_BYTES, "dictionary_bytes")                                      \
  X(DICTIONARY_CLASSES_BYTES, "dictionary_classes_bytes")                      \
  X(DICTIONARY_ENDPOINTS_BYTES, "dictionary_endpoints_bytes")                  \
  X(DICTIONARY_CONTEXT_BYTES, "dictionary_context_bytes")                      \
  X(DICTIONARY_PAGES, "dictionary_pages")                                      \
  X(DICTIONARY_CLASSES_PAGES, "dictionary_classes_pages")                      \
  X(DICTIONARY_ENDPOINTS_PAGES, "dictionary_endpoints_pages")                  \
  X(DICTIONARY_CONTEXT_PAGES, "dictionary_context_pages")                      \
  X(DICTIONARY_KEYS, "dictionary_keys")                                        \
  X(DICTIONARY_CLASSES_KEYS, "dictionary_classes_keys")                        \
  X(DICTIONARY_ENDPOINTS_KEYS, "dictionary_endpoints_keys")                    \
  X(DICTIONARY_CONTEXT_KEYS, "dictionary_context_keys")                        \
  X(DICTIONARY_KEYS_BYTES, "dictionary_keys_bytes")                            \
  X(DICTIONARY_CLASSES_KEYS_BYTES, "dictionary_classes_keys_bytes")            \
  X(DICTIONARY_ENDPOINTS_KEYS_BYTES, "dictionary_endpoints_keys_bytes")        \
  X(DICTIONARY_CONTEXT_KEYS_BYTES, "dictionary_context_keys_bytes")            \
  X(CONTEXT_STORAGE_BYTES, "context_storage_bytes")                            \
  X(CONTEXT_STORAGE_PAGES, "context_storage_pages")                            \
  X(CONTEXT_BOUNDS_MISS_INITS, "context_bounds_miss_inits")                    \
  X(CONTEXT_BOUNDS_MISS_GETS, "context_bounds_miss_gets")                      \
  X(CONTEXT_NULL_PAGE_GETS, "context_null_page_gets")                          \
  X(CONTEXT_ALLOC_FAILS, "context_alloc_fails")                                \
  X(CALLTRACE_STORAGE_BYTES, "calltrace_storage_bytes")                        \
  X(CALLTRACE_STORAGE_TRACES, "calltrace_storage_traces")                      \
  X(LINEAR_ALLOCATOR_BYTES, "linear_allocator_bytes")                          \
  X(LINEAR_ALLOCATOR_CHUNKS, "linear_allocator_chunks")                        \
  X(THREAD_IDS_COUNT, "thread_ids_count")                                      \
  X(THREAD_NAMES_COUNT, "thread_names_count")                                  \
  X(THREAD_FILTER_PAGES, "thread_filter_pages")                                \
  X(THREAD_FILTER_BYTES, "thread_filter_bytes")                                \
  X(JMETHODID_SKIPPED, "jmethodid_skipped_count")                              \
  X(CODECACHE_NATIVE_SIZE_BYTES, "codecache_native_size_bytes")                \
  X(CODECACHE_NATIVE_COUNT, "native_codecache_count")                          \
  X(CODECACHE_RUNTIME_STUBS_SIZE_BYTES, "codecache_runtime_stubs_size_bytes")  \
  X(AGCT_NOT_REGISTERED_IN_TLS, "agct_not_registered_in_tls")                  \
  X(AGCT_NOT_JAVA, "agct_not_java")                                            \
  X(AGCT_NATIVE_NO_JAVA_CONTEXT, "agct_native_no_java_context")                \
  X(AGCT_BLOCKED_IN_VM, "agct_blocked_in_vm")                                  \
  X(SKIPPED_WALLCLOCK_UNWINDS, "skipped_wallclock_unwinds")                    \
  X(UNWINDING_TIME_ASYNC, "unwinding_ticks_async")                             \
  X(UNWINDING_TIME_JVMTI, "unwinding_ticks_jvmti")                             \
  X(CALLTRACE_STORAGE_DROPPED, "calltrace_storage_dropped_traces")             \
  X(LINE_NUMBER_TABLES, "line_number_tables")                                  \
  X(REMOTE_SYMBOLICATION_FRAMES, "remote_symbolication_frames")                \
  X(REMOTE_SYMBOLICATION_LIBS_WITH_BUILD_ID, "remote_symbolication_libs_with_build_id") \
  X(REMOTE_SYMBOLICATION_BUILD_ID_CACHE_HITS, "remote_symbolication_build_id_cache_hits") \
  X(THREAD_ENTRY_MARK_DETECTIONS, "thread_entry_mark_detections")              \
  X(WALKVM_THREAD_INACCESSIBLE, "walkvm_thread_inaccessible")                  \
  X(WALKVM_ANCHOR_NULL, "walkvm_anchor_null")                                  \
  X(WALKVM_CACHED_NOT_JAVA, "walkvm_cached_not_java")                          \
  X(WALKVM_NO_VMTHREAD, "walkvm_no_vmthread")                                  \
  X(WALKVM_VMTHREAD_OK, "walkvm_vmthread_ok")                                  \
  X(WALKVM_ANCHOR_USED_INLINE, "walkvm_anchor_used_inline")                    \
  X(WALKVM_ANCHOR_FALLBACK, "walkvm_anchor_fallback")                          \
  X(WALKVM_CODEH_NO_VM, "walkvm_codeh_no_vm")                                  \
  X(WALKVM_DEPTH_ZERO, "walkvm_depth_zero")                                    \
  X(WALKVM_HIT_CODEHEAP, "walkvm_hit_codeheap")                                \
  X(WALKVM_ANCHOR_FALLBACK_FAIL, "walkvm_anchor_fallback_fail")                \
  X(WALKVM_ANCHOR_CONSUMED, "walkvm_anchor_consumed")                          \
  X(WALKVM_BREAK_INTERPRETED, "walkvm_break_interpreted")                      \
  X(WALKVM_BREAK_COMPILED, "walkvm_break_compiled")                            \
  X(WALKVM_JAVA_FRAME_OK, "walkvm_java_frame_ok")                            \
  X(WALKVM_ANCHOR_INLINE_NO_ANCHOR, "walkvm_anchor_inline_no_anchor")        \
  X(WALKVM_ANCHOR_INLINE_NO_SP, "walkvm_anchor_inline_no_sp")                \
  X(WALKVM_ANCHOR_INLINE_BAD_SP, "walkvm_anchor_inline_bad_sp")              \
  X(WALKVM_SAVED_ANCHOR_USED, "walkvm_saved_anchor_used")                    \
  X(WALKVM_STUB_GENERIC_UNWIND, "walkvm_stub_generic_unwind")                \
  X(WALKVM_STUB_FRAMESIZE_FALLBACK, "walkvm_stub_framesize_fallback")        \
  X(WALKVM_FP_CHAIN_ATTEMPT, "walkvm_fp_chain_attempt")                      \
  X(WALKVM_FP_CHAIN_REACHED_CODEHEAP, "walkvm_fp_chain_reached_codeheap")    \
  X(WALKVM_ANCHOR_NOT_IN_JAVA,  "walkvm_anchor_not_in_java")                   \
  X(WALKVM_CONT_BARRIER_HIT,    "walkvm_cont_barrier_hit")                     \
  X(WALKVM_ENTER_SPECIAL_HIT,   "walkvm_enter_special_hit")                    \
  X(WALKVM_CONT_SPECULATIVE_HIT,"walkvm_cont_speculative_hit")                 \
  X(WALKVM_CONT_ENTRY_NULL,     "walkvm_cont_entry_null")                      \
  X(NATIVE_LIBS_DROPPED, "native_libs_dropped")                                \
  X(SIGACTION_PATCHED_LIBS, "sigaction_patched_libs")                          \
  X(SIGACTION_INTERCEPTED, "sigaction_intercepted")                             \
  X(CTIMER_SIGNAL_OWN, "ctimer_signal_own")                                     \
  X(CTIMER_SIGNAL_FOREIGN, "ctimer_signal_foreign")                             \
  X(WALLCLOCK_SIGNAL_OWN, "wallclock_signal_own")                               \
  X(WALLCLOCK_SIGNAL_FOREIGN, "wallclock_signal_foreign")
#define X_ENUM(a, b) a,
typedef enum CounterId : int {
  DD_COUNTER_TABLE(X_ENUM) DD_NUM_COUNTERS
} CounterId;
#undef X_ENUM

class Counters {
private:
  static const u32 ALIGNMENT = 16;
  volatile long long *_counters;
  static long long *init();
  Counters() : _counters() {
#ifdef COUNTERS
    _counters = Counters::init();
#endif // COUNTERS
  }

public:
  static Counters &instance() {
    static Counters instance;
    return instance;
  }

  Counters(Counters const &) = delete;
  void operator=(Counters const &) = delete;

  static constexpr int address(int index) { return index * ALIGNMENT; }

  static constexpr int size() {
    return address(DD_NUM_COUNTERS * sizeof(long long));
  }

  static long long *getCounters() {
#ifdef COUNTERS
    return const_cast<long long *>(Counters::instance()._counters);
#else
    return nullptr;
#endif // COUNTERS
  }

  static long long getCounter(CounterId counter, int offset = 0) {
#ifdef COUNTERS
    return Counters::instance()
        ._counters[address(static_cast<int>(counter) + offset)];
#else
    return 0;
#endif // COUNTERS
  }

  static void set(CounterId counter, long long value, int offset = 0) {
#ifdef COUNTERS
    storeRelease(Counters::instance()
                     ._counters[address(static_cast<int>(counter) + offset)],
                 value);
#endif // COUNTERS
  }

  static void increment(CounterId counter, long long delta = 1,
                        int offset = 0) {
#ifdef COUNTERS
    atomicIncRelaxed(Counters::instance()
                         ._counters[address(static_cast<int>(counter) + offset)],
                     delta);
#endif // COUNTERS
  }

  static void decrement(CounterId counter, long long delta = 1,
                        int offset = 0) {
#ifdef COUNTERS
    increment(counter, -delta, offset);
#endif // COUNTERS
  }

  static std::vector<const char *> describeCounters() {
#ifdef COUNTERS
#define X_NAME(a, b) b,
    return {DD_COUNTER_TABLE(X_NAME)};
#undef X_NAME
#else
    return {};
#endif // COUNTERS
  }

  static void reset() {
#ifdef COUNTERS
    memset((void *)Counters::instance()._counters, 0, size());
#endif // COUNTERS
  }
};

#endif // JAVA_PROFILER_LIBRARY_COUNTERS_H
