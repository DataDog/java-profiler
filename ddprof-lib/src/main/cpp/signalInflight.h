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

#ifndef _SIGNAL_INFLIGHT_H
#define _SIGNAL_INFLIGHT_H

// Global tally of signal handlers currently executing past their _enabled
// check and capable of writing JFR. Profiler::stop() waits (drain()) for the
// counter to reach zero before calling _jfr.stop(), closing the TOCTOU
// window between a handler's _enabled check and its JFR buffer access.
//
// All CPU and wall-clock signal handlers that can write JFR should construct
// an InflightGuard at handler entry so they participate in the drain.
//
// The counter is on its own cache line (alignas(64)) so that handler-side
// writes do not invalidate the cache line backing each engine's _enabled
// flag, which is read on every signal.
class SignalInflight {
public:
    // ACQUIRE on increment / RELEASE on decrement: drain() observes all
    // handler-side writes before observing the counter at zero.
    static void enter() {
        __atomic_fetch_add(&_counter, 1, __ATOMIC_ACQUIRE);
    }
    static void exit() {
        __atomic_fetch_sub(&_counter, 1, __ATOMIC_RELEASE);
    }
    static bool hasInflight() {
        return __atomic_load_n(&_counter, __ATOMIC_ACQUIRE) > 0;
    }

    // Spin until the counter reaches zero or DRAIN_TIMEOUT_NS elapses.
    // Returns true on clean drain, false on timeout. Callers MUST NOT proceed
    // with JFR teardown when this returns false.
    static bool drain();

private:
    alignas(64) static int _counter;
};

// RAII guard for signal-handler in-flight tracking. Construct as the first
// statement (after SIGNAL_HANDLER_GUARD) of any signal handler that can
// write JFR; the counter is incremented on construction and decremented on
// destruction, balancing automatically across every return path.
class InflightGuard {
public:
    InflightGuard()  { SignalInflight::enter(); }
    ~InflightGuard() { SignalInflight::exit(); }

    InflightGuard(const InflightGuard&)            = delete;
    InflightGuard& operator=(const InflightGuard&) = delete;
    InflightGuard(InflightGuard&&)                 = delete;
    InflightGuard& operator=(InflightGuard&&)      = delete;
};

#endif // _SIGNAL_INFLIGHT_H
