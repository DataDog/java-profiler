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

#include "signalInflight.h"
#include "log.h"

#include <errno.h>
#include <sched.h>
#include <time.h>

alignas(64) int SignalInflight::_counter = 0;

// 200 ms: long enough for any legitimate signal handler to finish,
// short enough to avoid a perceptible hang if a handler is somehow stuck.
static const long DRAIN_TIMEOUT_NS = 200000000L;

bool SignalInflight::drain() {
  if (__atomic_load_n(&_counter, __ATOMIC_ACQUIRE) == 0) {
    return true; // fast path: nothing in flight
  }

  struct timespec deadline;
  if (clock_gettime(CLOCK_MONOTONIC, &deadline) != 0) {
    Log::error("SignalInflight::drain: clock_gettime(CLOCK_MONOTONIC) failed (errno=%d). "
               "Skipping JFR teardown to prevent use-after-free.", errno);
    return false;
  }
  deadline.tv_nsec += DRAIN_TIMEOUT_NS;
  if (deadline.tv_nsec >= 1000000000L) {
    deadline.tv_sec += 1;
    deadline.tv_nsec -= 1000000000L;
  }

  while (__atomic_load_n(&_counter, __ATOMIC_ACQUIRE) > 0) {
    struct timespec now;
    if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) {
      Log::error("SignalInflight::drain: clock_gettime(CLOCK_MONOTONIC) failed (errno=%d). "
                 "Skipping JFR teardown to prevent use-after-free.", errno);
      return false;
    }
    if (now.tv_sec > deadline.tv_sec ||
        (now.tv_sec == deadline.tv_sec && now.tv_nsec >= deadline.tv_nsec)) {
      int remaining = __atomic_load_n(&_counter, __ATOMIC_ACQUIRE);
      Log::error("SignalInflight::drain: timed out after %ldms waiting for "
                 "%d in-flight signal handler(s). Skipping JFR teardown to "
                 "prevent use-after-free. This indicates a stuck signal handler.",
                 DRAIN_TIMEOUT_NS / 1000000L, remaining);
      return false;
    }
    sched_yield();
  }
  return true;
}
