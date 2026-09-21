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

// Compile-time per-sampler performance measurement.
//
// SAMPLER_PERF_PROBE(SP_CPU) declares an RAII object at a sampler's entry
// point.  Its constructor takes a TSC timestamp; its destructor adds the
// elapsed ticks to sampler_ticks.<name> and bumps sampler_count.<name>.  At
// Profiler::stop(), SamplerPerf::report() prints total elapsed time, sample
// count and average per sampler.
//
//   void CTimer::signalHandler(int signo, siginfo_t* si, void* uc) {
//     ErrnoPreserver errno_preserver;
//     ... foreign-signal rejection ...
//     SAMPLER_PERF_PROBE(SP_CPU);
//     ...
//   }
//
// When __SAMPLER_PERF__ is NOT defined the macro expands to ((void)0), the
// SamplerPerfProbe class does not exist, and the counter slots are absent from
// DD_COUNTER_TABLE entirely -- no enum slot, no storage, no runtime cost.
// SamplerId and DD_SAMPLER_LIST stay defined in both modes so probe call sites
// compile unchanged either way.
//
// The RAII form is not stylistic here: every instrumented handler has several
// early returns (CriticalSection reject, disabled engine, init-window tick), so
// a manual start/stop pair would have to be repeated at each exit and would
// silently miss any newly added one.
//
// HOW TO READ THE NUMBERS -- five caveats, all of them easy to get wrong:
//
//  1. sampler_ticks.* is ELAPSED WALL TIME, not CPU time.  It includes time the
//     sampled thread spent descheduled, page-faulting, or waiting on the
//     Profiler::_locks[] stripe.  That is the right metric for the latency the
//     sampler adds to the sampled thread, but it is not the sampler's CPU cost
//     and it inflates under load.
//
//  2. sampler_ticks.cpu ALREADY CONTAINS unwinding_ticks_async.  Both time the
//     same stack unwinder (Profiler::recordSample).  Never sum them; the
//     unwinding counter is a strict subset and is the first thing to compare
//     against when a cpu average looks too large.
//
//  3. sampler_ticks.alloc ALREADY CONTAINS sampler_ticks.liveness, because
//     LivenessTracker::track() is called from ObjectSampler::recordAllocation().
//     Liveness is a nested breakdown of alloc, not a sibling of it.
//
//  4. Cross-sampler nesting is possible and slightly double-counts.
//     SIGNAL_HANDLER_GUARD_OR_DROP() drops only when there is no ProfiledThread
//     (guards.h); it does not reject nested signals.  A wallclock signal landing
//     inside a CPU handler is therefore counted in both totals.  The distortion
//     is bounded and small -- the nested handler bails almost immediately at its
//     CriticalSection -- but it is not zero.  Detecting it would need a
//     ProfiledThread field, since no thread_local is permitted on these paths.
//
//  5. The count INCLUDES samples that bailed out (reentrancy reject, disabled
//     engine, init window), which dilutes the average downward.  Foreign signals
//     are excluded by construction: each probe is declared after its handler's
//     signal-origin check, so a stray SIGPROF from something like Go's
//     process-wide setitimer -- and the foreign handler that
//     OS::forwardForeignSignal() runs -- is never timed as our work.  Use the
//     SAMPLES_DROPPED_* / WC_SIGNAL_* counters to quantify the bail-outs.
//
//  6. report() can undercount the very last sample of a run.  The probe is
//     declared before InflightGuard (see caveat 5), so at handler exit
//     InflightGuard's destructor -- which Profiler::stop()'s
//     SignalInflight::drain() waits on -- runs before the probe's, which is
//     the one that bumps sampler_ticks.*/sampler_count.*.  A handler that is
//     still unwinding when drain() observes zero can have its counters land
//     after report() already read them.  In practice the teardown work
//     between drain() and report() (profiler.cpp) dwarfs the few
//     instructions between those two destructors, so this is a real but
//     vanishingly unlikely race, and its only effect is a diagnostic
//     printout under-reporting by at most one sample.
//
// See doc/reference/SamplerPerfCounters.md.

#ifndef _SAMPLER_PERF_H
#define _SAMPLER_PERF_H

#include "arch.h"
#include "counters.h"
#include "tsc.h"

// The samplers measured by the probe, one logical slot per sampler family.
//
// Only one CPU engine and one wallclock engine is ever live in a run
// (Profiler::selectCpuEngine / selectWallEngine), so all CPU variants
// (PerfEvents, CTimer, CTimerJvmti, ITimer, ITimerJvmti) share SP_CPU and all
// wallclock variants (WallClockASGCT, WallClockJvmti, J9WallClock) share
// SP_WALL.  Per-variant slots would only ever have one of them non-zero.
//
// Order is load-bearing: it must match DD_COUNTER_TABLE_SAMPLER_PERF in
// counters.h, which the static_asserts below verify.
#define DD_SAMPLER_LIST(X)                                                     \
  X(CPU, "cpu")                                                                \
  X(WALL, "wallclock")                                                         \
  X(ALLOC, "alloc")                                                            \
  X(LIVENESS, "liveness")                                                      \
  X(NATIVEMEM, "nativemem")                                                    \
  X(NATIVESOCKET, "nativesocket")

#define X_SAMPLER_ENUM(id, name) SP_##id,
typedef enum SamplerId : int {
  DD_SAMPLER_LIST(X_SAMPLER_ENUM) SP_NUM_SAMPLERS
} SamplerId;
#undef X_SAMPLER_ENUM

class SamplerPerf {
public:
  // Prints the per-sampler table to stdout. Samplers with a zero sample count
  // are skipped so only engines that actually ran are listed. A no-op when
  // __SAMPLER_PERF__ is not defined, so the call site needs no #ifdef.
  static void report();

  // Converts TSC ticks to nanoseconds without overflowing.
  //
  // The naive ticks * NANOTIME_FREQ / frequency() overflows u64 well inside a
  // normal recording: at 3 GHz, one hour is ~1.08e13 ticks and ticks * 1e9 is
  // ~1.08e22, far past 1.8e19 -- it silently reports 2.88 seconds instead of
  // 3600. Splitting into whole seconds plus remainder keeps every intermediate
  // in range, since (ticks % freq) * 1e9 < freq * 1e9 and freq is at most a few
  // GHz.
  //
  // TSC::frequency() returns NANOTIME_FREQ when the TSC is unavailable and
  // TSC::ticks() is already handing back OS::nanotime() nanoseconds, so this one
  // expression is correct in both modes.
  static u64 ticksToNanos(u64 ticks) {
    u64 freq = TSC::frequency();
    if (freq == 0) {
      return 0;
    }
    return (ticks / freq) * NANOTIME_FREQ +
           ((ticks % freq) * NANOTIME_FREQ) / freq;
  }

  // Display name for a sampler, e.g. "cpu". Defined in both modes.
  static const char *name(SamplerId id);
};

#ifdef __SAMPLER_PERF__

// Pin each sampler's two counter slots to the base-plus-offset layout the probe
// relies on. Generated from DD_SAMPLER_LIST so the two lists cannot drift:
// reordering DD_COUNTER_TABLE_SAMPLER_PERF, or inserting an unrelated counter
// between its entries, fails the build here instead of silently attributing
// ticks to the wrong sampler.
#define X_SAMPLER_ASSERT(id, name)                                             \
  static_assert(SAMPLER_TICKS_##id == SAMPLER_TICKS_CPU + 2 * SP_##id,         \
                "sampler_ticks." name " is not at its expected offset; keep "  \
                "DD_COUNTER_TABLE_SAMPLER_PERF in DD_SAMPLER_LIST order");     \
  static_assert(SAMPLER_COUNT_##id == SAMPLER_TICKS_CPU + 2 * SP_##id + 1,     \
                "sampler_count." name " is not at its expected offset; keep "  \
                "DD_COUNTER_TABLE_SAMPLER_PERF in DD_SAMPLER_LIST order");
DD_SAMPLER_LIST(X_SAMPLER_ASSERT)
#undef X_SAMPLER_ASSERT

// Accumulates elapsed ticks and one sample count for a sampler over its scope.
//
// Async-signal-safe: all state is on the stack (no thread_local -- a
// thread_local here would risk the lazy DTV-slot malloc that deadlocked against
// the JVMCI compiler on Graal aarch64, see guards.h), and the destructor does
// nothing but read the TSC and issue two relaxed atomic adds, which land on
// separate cache lines because Counters pads every slot to 128 bytes.
//
// Declare it AFTER any ErrnoPreserver in the enclosing handler: ErrnoPreserver
// must stay the first-declared local so it destructs last, and TSC::ticks() can
// reach clock_gettime() on the OS::nanotime() fallback path, which may set
// errno.
class SamplerPerfProbe {
private:
  u64 _start;
  SamplerId _id;

public:
  explicit SamplerPerfProbe(SamplerId id) : _start(TSC::ticks()), _id(id) {}

  ~SamplerPerfProbe() {
    Counters::increment(SAMPLER_TICKS_CPU, (long long)(TSC::ticks() - _start),
                        2 * (int)_id);
    Counters::increment(SAMPLER_TICKS_CPU, 1, 2 * (int)_id + 1);
  }

  SamplerPerfProbe(const SamplerPerfProbe &) = delete;
  SamplerPerfProbe &operator=(const SamplerPerfProbe &) = delete;
};

#define SAMPLER_PERF_PROBE(id) ::SamplerPerfProbe _sampler_perf_probe(id)

#else // __SAMPLER_PERF__ not defined -- zero cost.

// ((void)0) rather than nothing, so `SAMPLER_PERF_PROBE(SP_CPU);` stays a
// well-formed expression statement in every context (e.g. as the sole body of
// an unbraced if/else) instead of collapsing to a stray semicolon.
#define SAMPLER_PERF_PROBE(id) ((void)0)

#endif // __SAMPLER_PERF__

#endif // _SAMPLER_PERF_H
