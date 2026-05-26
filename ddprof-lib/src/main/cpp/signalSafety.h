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

#ifndef _SIGNAL_SAFETY_H
#define _SIGNAL_SAFETY_H

#include "guards.h"   // isInSignalContext, SIGNAL_HANDLER_GUARD, ...
#include "thread.h"   // ProfiledThread::currentSignalSafe

// Detect ASAN using compiler-provided macros so the ASAN_ENABLED guard below
// works in every TU that includes this header, independent of include order.
#ifdef __has_feature
#  if __has_feature(address_sanitizer)
#    ifndef ASAN_ENABLED
#      define ASAN_ENABLED 1
#    endif
#  endif
#endif
#ifdef __SANITIZE_ADDRESS__
#  ifndef ASAN_ENABLED
#    define ASAN_ENABLED 1
#  endif
#endif

// Detect TSAN.  clang exposes TSan via __has_feature(thread_sanitizer);
// gcc defines __SANITIZE_THREAD__.  Use both so callers don't have to know
// which compiler is in use.
#ifdef __has_feature
#  if __has_feature(thread_sanitizer)
#    ifndef TSAN_ENABLED
#      define TSAN_ENABLED 1
#    endif
#  endif
#endif
#ifdef __SANITIZE_THREAD__
#  ifndef TSAN_ENABLED
#    define TSAN_ENABLED 1
#  endif
#endif

// Debug-only AS-safety assertion.  Aborts with a file:line diagnostic when
// invoked from inside a signal handler in debug / ASAN builds; compiles to a
// no-op in release builds (NDEBUG).
//
// The depth counter itself lives in ProfiledThread::_signal_depth (see
// guards.h for the rationale).  The check is skipped when ProfiledThread
// is null — uninstrumented threads (VM Thread, JIT, GC) have no thread
// context, so the assertion has no way to know whether they're really in
// a signal frame.  Treating "unknown" as a violation would produce false
// positives every time AS-unsafe code legitimately ran on such a thread.
//
// write(2) is POSIX async-signal-safe.  abort() generates a core dump and
// triggers ASAN's stack-trace symbolization, making it far more debuggable
// than _exit(1).  The macro is only active in debug/ASAN builds where we
// intentionally trade AS-safety of the abort path for diagnosability.
#define _SIGNAL_SAFETY_STR(x) #x
#define _SIGNAL_SAFETY_TOSTR(x) _SIGNAL_SAFETY_STR(x)

#if !defined(NDEBUG) || defined(ASAN_ENABLED)
#include <unistd.h>  // write, STDERR_FILENO, open, close
#include <stdlib.h>  // abort
#include <fcntl.h>   // O_WRONLY, O_CREAT, O_APPEND

// Path for the diagnostic file — picked up as a CI artifact on failure.
#define _SIGNAL_SAFETY_DIAG_FILE "/tmp/signal-safety-violation.txt"

#define DEBUG_ASSERT_NOT_IN_SIGNAL()                                                        \
    do {                                                                                     \
        ProfiledThread *_pt_for_assert = ProfiledThread::currentSignalSafe();                \
        /* Skip when no thread context — see comment above. */                              \
        if (_pt_for_assert != nullptr && _pt_for_assert->signalDepth() != 0) {              \
            static const char _msg[] =                                                       \
                "[java-profiler] AS-safety violation at "                                    \
                __FILE__ ":" _SIGNAL_SAFETY_TOSTR(__LINE__)                                  \
                ": async-signal-unsafe call made from signal handler context\n";             \
            (void)write(STDERR_FILENO, _msg, sizeof(_msg) - 1);                             \
            /* Also write to a file so CI can capture it regardless of output routing. */   \
            int _diag_fd = open(_SIGNAL_SAFETY_DIAG_FILE,                                   \
                                O_WRONLY | O_CREAT | O_APPEND, 0644);                       \
            if (_diag_fd >= 0) {                                                             \
                (void)write(_diag_fd, _msg, sizeof(_msg) - 1);                              \
                close(_diag_fd);                                                             \
            }                                                                                \
            abort();                                                                         \
        }                                                                                    \
    } while (0)
#else
#define DEBUG_ASSERT_NOT_IN_SIGNAL() ((void)0)
#endif

#endif  // _SIGNAL_SAFETY_H
