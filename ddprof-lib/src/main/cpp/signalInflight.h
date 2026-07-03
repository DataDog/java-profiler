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
//
// Known limitation — longjmp out of a signal handler frame:
// If a signal handler frame is unwound by a longjmp that bypasses the
// InflightGuard destructor, the counter leaks by +1 permanently. In this
// codebase that can only happen via J9's SIGSEGV null-pointer-check
// handler: our segvHandler chains to J9 for unclaimed faults, and J9 may
// siglongjmp to a setjmp installed in normal Java code (J9 null-check
// recovery), unwinding past every frame above it including any active
// InflightGuard. SignalHandlerScope has the same limitation for its own
// depth counter (see guards.h) and the codebase accepts it.
//
// In practice this is extremely unlikely to fire from a profiler signal
// handler: J9 only siglongjmps when the fault matches an annotated
// null-check site in Java bytecode, and our stack walker faults occur
// inside our own C++ code that J9 has no reason to claim. If it ever did
// fire, the failure mode is graceful: every subsequent Profiler::stop()
// hits drain()'s timeout, returns Error, and refuses to tear down JFR.
// The JVM keeps running; the profiler is wedged until process exit.
// No crash, no use-after-free — the timeout path that this counter exists
// to gate is exactly the safety net for this case.
class SignalInflight {
public:
    // Increment / decrement the inflight tally. Prefers per-thread storage on
    // the current ProfiledThread when one is available; falls back to the
    // global counter otherwise (early-init threads, native threads with no PT).
    static void enter();
    static void exit();

    // True iff any thread (per-thread or global-fallback) has a positive count.
    static bool hasInflight();

    // Spin until every counter reaches zero or DRAIN_TIMEOUT_NS elapses.
    // Returns true on clean drain, false on timeout. Callers MUST NOT proceed
    // with JFR teardown when this returns false.
    static bool drain();

    // Global fallback counter (still cache-line-aligned to keep it off engine
    // _enabled lines). Not private so InflightGuard's inline path can access
    // it if needed; the recommended entry point remains enter()/exit().
    alignas(64) static int _fallback_counter;
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
