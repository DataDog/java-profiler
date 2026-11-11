/*
 * Copyright The async-profiler authors
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WALLCLOCK_H
#define _WALLCLOCK_H

#include <algorithm>
#include <cassert>
#include "engine.h"
#include "nativeMem.h"
#include "os.h"
#include "profiler.h"
#include "reservoirSampler.h"
#include "threadLocalData.inline.h"
#include "threadFilter.h"
#include "threadState.h"
#include "tsc.h"
#include "wallClockCandidateSelector.h"
#include "wallClockCounters.h"
#include "wallClockTimer.h"
#include "xorshift.h"

class BaseWallClock : public Engine {
  private:
    static std::atomic<bool> _enabled;
    std::atomic<bool> _running;
    // Timer-owned fixed-size ledger, published only when the timer exits and
    // read after pthread_join(). No signal-handler or per-tick logging.
    struct TimerPhases {
      u64 iterations = 0, empty = 0, single = 0, large = 0;
      u64 selected = 0, sent = 0, failed = 0;
      u64 first_eligible = 0, last_eligible = 0, first_send = 0, last_send = 0;
      u64 collect_ns = 0, select_ns = 0, send_ns = 0, finish_ns = 0;
      u64 requested_sleep_ns = 0, actual_sleep_ns = 0;
    };
    TimerPhases _timer_phases;
    bool _timer_diagnostics = false;
  protected:
    // Backfill rejected candidates without letting a population of already-
    // suppressed blockers restore O(N) registry lookups on every wall tick.
    static constexpr size_t PRECHECK_VISIT_BUDGET_MULTIPLIER = 4;
    long _interval;
    // Maximum number of threads sampled in one iteration. This limit serves as a
    // throttle when generating profiling signals. Otherwise applications with too
    // many threads may suffer from a big profiling overhead. Also, keeping this
    // limit low enough helps to avoid contention on a spin lock inside
    // Profiler::recordSample().
    int _reservoir_size;
    pthread_t _thread;
    virtual void timerLoop() = 0;
    virtual void initialize(Arguments& args) {};

    static void *threadEntry(void *wall_clock) {
      ((BaseWallClock *)wall_clock)->timerLoop();
      return NULL;
    }

    bool isEnabled() const;
    static bool inSyscall(void* ucontext);

    // Shared by WallClockASGCT::timerLoop() and WallClockJvmti::timerLoop(): both
    // engines resolve a registry slot, check precheck suppression, and send the
    // sampling signal identically; only collectThreads() differs between them.
    WallClockCandidateOutcome sampleThreadCommon(
        ThreadEntry entry, int& num_failures, int& threads_already_exited,
        int& permission_denied, int& registry_lookups, bool lookup_registry_slot,
        bool precheck, ThreadFilter* thread_filter,
        ThreadFilter::RecordingEpoch recording_epoch);
    // Timer-thread precheck: true when an explicit lifecycle hook still owns an
    // already-sampled blocked run for this thread, so no signal is needed.
    static bool suppressAlreadySampled(const ThreadEntry& entry);

    template <typename ThreadType, typename CollectThreadsFunc, typename SampleThreadsFunc, typename CleanThreadFunc>
    void timerLoopCommon(CollectThreadsFunc collectThreads, SampleThreadsFunc sampleThreads,
                         CleanThreadFunc cleanThreads, int reservoirSize, u64 interval,
                         bool precheck = false, bool lazyBackfill = false) {
      if (!_enabled.load(std::memory_order_acquire)) {
        return;
      }

      // Dither the sampling interval to introduce some randomness and prevent step-locking
      const double stddev = ((double)_interval) / 10.0;  // 10% standard deviation
      // One generator for the life of the loop; the start tick varies the
      // stream between recordings without needing an entropy source.
      u64 rng = xorshift::seed((u64)(uintptr_t)this, TSC::ticks());

      u64 candidate_generator = 0;
      if (lazyBackfill) {
        candidate_generator =
            xorshift::seed((u64)(uintptr_t)&candidate_generator, TSC::ticks());
      }

      std::vector<ThreadType> threads;
      threads.reserve(reservoirSize);
      size_t accounted_capacity = threads.capacity();
      NativeMem::record(NM_WALLCLOCK,
                        static_cast<long long>(accounted_capacity * sizeof(ThreadType)));
      int self = OS::threadId();
      ThreadFilter* thread_filter = Profiler::instance()->threadFilter();
      
      // We don't want to profile ourselves in wall time.
      // current may be null if this thread is still initializing its ProfiledThread
      // (wall-clock thread startup races with JVMTI ThreadStart). Safe to skip removal.
      ProfiledThread* current = ProfiledThread::current();
      if (current != nullptr) {
        int slot_id = current->filterSlotId();
        if (slot_id != -1) {
          thread_filter->remove(slot_id);
        }
      }

      u64 startTime = TSC::ticks();
      WallClockEpochEvent epoch(startTime);

      ReservoirSampler<ThreadType> reservoir(reservoirSize, TSC::ticks());
      TimerPhases phases;
      WallClockTimer timer(OS::nanotime());

      while (_running.load(std::memory_order_relaxed)) {
        u64 phase_start = _timer_diagnostics ? OS::nanotime() : 0;
        collectThreads(threads);
        size_t capacity = threads.capacity();
        if (capacity != accounted_capacity) {
          NativeMem::record(NM_WALLCLOCK,
                            (static_cast<long long>(capacity) -
                             static_cast<long long>(accounted_capacity)) *
                            static_cast<long long>(sizeof(ThreadType)));
          accounted_capacity = capacity;
        }
        // The epoch's samplePoolSize counts every candidate, including threads
        // the precheck suppresses below, so it means the same in both precheck
        // modes: lazy backfill only discovers suppression while visiting.
        const u32 num_samplable_threads = static_cast<u32>(threads.size());
        if (precheck && !lazyBackfill) {
          // Drop suppressed threads before reservoir sampling so they do not
          // consume reservoir slots.
          threads.erase(std::remove_if(threads.begin(), threads.end(),
                                       suppressAlreadySampled),
                        threads.end());
        }

        if (_timer_diagnostics) {
          u64 now = OS::nanotime();
          phases.collect_ns += now - phase_start;
          phase_start = now;
          phases.iterations++;
          phases.empty += threads.empty();
          phases.single += threads.size() == 1;
          phases.large += threads.size() > static_cast<size_t>(reservoirSize);
          if (!threads.empty()) {
            if (phases.first_eligible == 0) phases.first_eligible = TSC::ticks();
            phases.last_eligible = TSC::ticks();
          }
        }
        int num_failures = 0;
        int threads_already_exited = 0;
        int permission_denied = 0;
        int registry_lookups = 0;
        u32 num_successful_samples = 0;
        u64 send_ns_before = phases.send_ns;
        if (lazyBackfill) {
          WallClockCandidateStats stats = selectWallClockCandidates(
              threads,
              static_cast<size_t>(reservoirSize),
              static_cast<size_t>(reservoirSize) *
                  PRECHECK_VISIT_BUDGET_MULTIPLIER,
              candidate_generator,
              [&](ThreadType thread) {
                u64 send_start = _timer_diagnostics ? OS::nanotime() : 0;
                WallClockCandidateOutcome outcome = sampleThreads(
                    thread, num_failures, threads_already_exited,
                    permission_denied, registry_lookups, true);
                if (_timer_diagnostics) {
                  phases.selected++;
                  phases.send_ns += OS::nanotime() - send_start;
                }
                if (outcome == WallClockCandidateOutcome::SIGNAL_SENT) {
                  num_successful_samples++;
                }
                return outcome;
              });
          if (stats.precheck_rejected > 0) {
            Counters::increment(WC_PRECHECK_CANDIDATES_REJECTED,
                                stats.precheck_rejected);
          }
          if (stats.visit_limit_reached) {
            Counters::increment(WC_PRECHECK_LOOKUP_BUDGET_EXHAUSTED);
          }
        } else {
          const std::vector<ThreadType>& sample = reservoir.sample(threads);
          if (_timer_diagnostics) {
            u64 now = OS::nanotime();
            phases.select_ns += now - phase_start;
            phase_start = now;
            phases.selected += sample.size();
          }
          for (ThreadType thread : sample) {
            WallClockCandidateOutcome outcome = sampleThreads(
                thread, num_failures, threads_already_exited,
                permission_denied, registry_lookups, false);
            if (outcome == WallClockCandidateOutcome::SIGNAL_SENT) {
              num_successful_samples++;
            }
          }
        }
        if (_timer_diagnostics) {
          u64 now = OS::nanotime();
          u64 elapsed = now - phase_start;
          if (lazyBackfill) phases.select_ns += elapsed - (phases.send_ns - send_ns_before);
          else phases.send_ns += elapsed;
          phase_start = now;
          phases.sent += num_successful_samples;
          phases.failed += num_failures;
          if (num_successful_samples != 0) {
            if (phases.first_send == 0) phases.first_send = TSC::ticks();
            phases.last_send = TSC::ticks();
          }
        }
        if (registry_lookups > 0) {
          Counters::increment(WC_PRECHECK_REGISTRY_LOOKUPS, registry_lookups);
        }

        epoch.updateNumSamplableThreads(num_samplable_threads);
        epoch.updateNumFailedSamples(num_failures);
        epoch.updateNumSuccessfulSamples(num_successful_samples);
        epoch.addNumSuppressedSampledRun(WallClockCounters::drainSuppressedSampledRun());
        epoch.updateNumExitedThreads(threads_already_exited);
        epoch.updateNumPermissionDenied(permission_denied);
        u64 endTime = TSC::ticks();
        u64 duration = TSC::ticks_to_millis(endTime - startTime);
        if (epoch.hasChanged() || duration >= 1000) {
          epoch.endEpoch(duration);
          Profiler::instance()->recordWallClockEpoch(self, &epoch);
          epoch.newEpoch(endTime);
          startTime = endTime;
        } else {
          epoch.clean();
        }

        threads.clear();
        cleanThreads();

        // Get a random sleep duration
        // clamp the random interval to <1,2N-1>
        // the probability of clamping is extremely small, close to zero
        u64 period_ns = std::min(std::max((long int)1,
                                    static_cast<long int>(xorshift::nextNormal(rng, (double)interval, stddev))),
                               ((_interval * 2) - 1));
        u64 sleep_ns = timer.nextSleep(OS::nanotime(), period_ns);
        if (_timer_diagnostics) {
          u64 now = OS::nanotime();
          phases.finish_ns += now - phase_start;
          phases.requested_sleep_ns += sleep_ns;
          phase_start = now;
        }
        OS::sleepWhile(sleep_ns, _running);
        if (_timer_diagnostics) phases.actual_sleep_ns += OS::nanotime() - phase_start;
      }
      _timer_phases = phases;

      // Retract only this timer's backing allocation. The tracker and any other
      // timers account for their own storage in the same category.
      NativeMem::record(NM_WALLCLOCK,
                        -static_cast<long long>(accounted_capacity * sizeof(ThreadType)));
    }

public:
#ifdef UNIT_TEST
    // The timer publishes this snapshot at exit; callers must stop/join first.
    const auto& timerPhasesForTest() const { return _timer_phases; }
#endif

  BaseWallClock() :
        _running(false),
        _interval(LONG_MAX),
        _reservoir_size(0),
        _thread(0) {}
    virtual ~BaseWallClock() = default;

    const char* units() {
        return "ns";
    }

  virtual const char* name() = 0;

  long interval() const { return _interval; }
  static bool eventsEnabled() { return _enabled.load(std::memory_order_acquire); }

  inline void enableEvents(bool enabled) {
        _enabled.store(enabled, std::memory_order_release);
    }

    Error start(Arguments& args);
    void stop();

#ifdef UNIT_TEST
    using ThreadStateReaderForTest = OSThreadState (*)();
    static ThreadStateReaderForTest exchangeThreadStateReaderForTest(ThreadStateReaderForTest reader);
    using UnownedContextProbeHook = void (*)(void*);
    static void setUnownedContextProbeHookForTest(UnownedContextProbeHook hook, void* arg);
    WallSampleRequest prepareWallSampleRequestForTest(ProfiledThread* current, bool& suppressed);
#endif
#if defined(UNIT_TEST) || defined(DEBUG)
    static void setForceStartFailureForTest(bool force) {
        _force_start_failure_for_test.store(force, std::memory_order_release);
    }
    static bool isForceStartFailureForTest() {
        return _force_start_failure_for_test.load(std::memory_order_acquire);
    }
  private:
    static std::atomic<bool> _force_start_failure_for_test;
  public:
#endif
};

class WallClockASGCT : public BaseWallClock {
  private:
    bool _collapsing;
    bool _precheck;

    static void sharedSignalHandler(int signo, siginfo_t* siginfo, void* ucontext);
    void signalHandler(int signo, siginfo_t* siginfo, void* ucontext, u64 last_sample, ProfiledThread* current);

    void initialize(Arguments& args) override;
    void timerLoop() override;

  public:
    WallClockASGCT() : BaseWallClock(), _collapsing(false), _precheck(false) {}
    const char* name() override {
        return "WallClock (ASGCT)";
    }
    bool supportsUnfilteredThreadRegistryTracking() const override { return true; }
};

// Wall-clock engine that uses BaseWallClock's pthread reservoir sampling loop
// to signal target threads, but in its signal handler delegates the stack walk
// to HotSpot's JFR RequestStackTrace JVMTI extension. Requires
// VM::canRequestStackTrace().
class WallClockJvmti : public BaseWallClock {
  private:
    bool _precheck;

    static void sharedSignalHandler(int signo, siginfo_t* siginfo, void* ucontext);
    void signalHandler(int signo, siginfo_t* siginfo, void* ucontext, u64 last_sample, ProfiledThread* current);

    void initialize(Arguments& args) override;
    void timerLoop() override;

  public:
    WallClockJvmti() : BaseWallClock(), _precheck(false) {}
    const char* name() override {
        return "WallClock (JVMTI)";
    }
    bool supportsUnfilteredThreadRegistryTracking() const override { return true; }
};

#endif // _WALLCLOCK_H
