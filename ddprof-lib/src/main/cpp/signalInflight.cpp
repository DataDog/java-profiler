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
#include "thread.h"

#include <errno.h>
#include <sched.h>
#include <time.h>

alignas(64) int SignalInflight::_fallback_counter = 0;

// 200 ms: long enough for any legitimate signal handler to finish,
// short enough to avoid a perceptible hang if a handler is somehow stuck.
static const long DRAIN_TIMEOUT_NS = 200000000L;

void SignalInflight::enter() {
  ProfiledThread *pt = ProfiledThread::currentSignalSafe();
  if (pt != nullptr) {
    // Fast path: increment the owning thread's counter. No cross-core write
    // traffic because only this thread ever writes here.
    pt->enterJfrInflight();
  } else {
    // Fallback for threads without a ProfiledThread (early init, native
    // threads that fire a signal before initCurrentThread runs).
    __atomic_fetch_add(&_fallback_counter, 1, __ATOMIC_ACQUIRE);
  }
}

void SignalInflight::exit() {
  ProfiledThread *pt = ProfiledThread::currentSignalSafe();
  if (pt != nullptr) {
    pt->exitJfrInflight();
  } else {
    __atomic_fetch_sub(&_fallback_counter, 1, __ATOMIC_RELEASE);
  }
}

// Sum callback used by drain(); ctx points to an int accumulator.
static void addInflight(ProfiledThread *pt, void *ctx) {
  *static_cast<int *>(ctx) += pt->jfrInflight();
}

static int totalInflight() {
  int total = __atomic_load_n(&SignalInflight::_fallback_counter, __ATOMIC_ACQUIRE);
  ProfiledThread::forEachRegistered(addInflight, &total);
  return total;
}

bool SignalInflight::hasInflight() {
  return totalInflight() > 0;
}

bool SignalInflight::drain() {
  if (totalInflight() == 0) {
    return true; // fast path
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

  while (true) {
    int total = totalInflight();
    if (total == 0) {
      return true;
    }
    struct timespec now;
    if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) {
      Log::error("SignalInflight::drain: clock_gettime(CLOCK_MONOTONIC) failed (errno=%d). "
                 "Skipping JFR teardown to prevent use-after-free.", errno);
      return false;
    }
    if (now.tv_sec > deadline.tv_sec ||
        (now.tv_sec == deadline.tv_sec && now.tv_nsec >= deadline.tv_nsec)) {
      Log::error("SignalInflight::drain: timed out after %ldms waiting for "
                 "%d in-flight signal handler(s). Skipping JFR teardown to "
                 "prevent use-after-free. This indicates a stuck signal handler.",
                 DRAIN_TIMEOUT_NS / 1000000L, total);
      return false;
    }
    sched_yield();
  }
}
