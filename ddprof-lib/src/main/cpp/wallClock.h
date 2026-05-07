/*
 * Copyright The async-profiler authors
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WALLCLOCK_H
#define _WALLCLOCK_H

#include <cassert>
#include "engine.h"
#include "os.h"
#include "profiler.h"
#include "reservoirSampler.h"
#include "thread.h"
#include "threadFilter.h"
#include "threadState.h"
#include "tsc.h"
#include "wallClockCounters.h"

class BaseWallClock : public Engine {
  private:
    static std::atomic<bool> _enabled;
    std::atomic<bool> _running;
  protected:
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

    template <typename ThreadType, typename CollectThreadsFunc, typename SampleThreadsFunc, typename CleanThreadFunc>
    void timerLoopCommon(CollectThreadsFunc collectThreads, SampleThreadsFunc sampleThreads, CleanThreadFunc cleanThreads, int reservoirSize, u64 interval) {
      if (!_enabled.load(std::memory_order_acquire)) {
        return;
      }

      // Dither the sampling interval to introduce some randomness and prevent step-locking
      const double stddev = ((double)_interval) / 10.0;  // 10% standard deviation
      // Set up random engine and normal distribution
      std::random_device rd;
      std::mt19937 generator(rd());
      std::normal_distribution<double> distribution(interval, stddev);

      std::vector<ThreadType> threads;
      threads.reserve(reservoirSize);
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

      ReservoirSampler<ThreadType> reservoir(reservoirSize);

      while (_running.load(std::memory_order_relaxed)) {
        collectThreads(threads);

        int num_failures = 0;
        int threads_already_exited = 0;
        int permission_denied = 0;
        u32 num_skipped_precheck_os = 0;
        u32 num_successful_samples = 0;
        std::vector<ThreadType> sample = reservoir.sample(threads);
        for (ThreadType thread : sample) {
          if (sampleThreads(thread, num_failures, threads_already_exited, permission_denied,
                            num_skipped_precheck_os)) {
            num_successful_samples++;
          }
        }

        epoch.updateNumSamplableThreads(threads.size());
        epoch.updateNumFailedSamples(num_failures);
        epoch.updateNumSuccessfulSamples(num_successful_samples);
        epoch.updateNumSkippedPrecheckOs(num_skipped_precheck_os);
        WallClockCounterSnapshot counter_snapshot = WallClockCounters::drain();
        epoch.updateNumSkippedParkedSpanless(counter_snapshot.skipped_parked_spanless);
        epoch.updateNumSkippedParkedActiveSpan(counter_snapshot.skipped_parked_active_span);
        epoch.updateNumTaskBlockEmitted(counter_snapshot.task_block_emitted);
        epoch.updateNumTaskBlockSkippedSpanZero(counter_snapshot.task_block_skipped_span_zero);
        epoch.updateNumTaskBlockSkippedTooShort(counter_snapshot.task_block_skipped_too_short);
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
        OS::sleep(std::min(std::max((long int)1, static_cast<long int>(distribution(generator))), ((_interval * 2) - 1)));
      }
    }

public:
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

  inline void enableEvents(bool enabled) {
        _enabled.store(enabled, std::memory_order_release);
    }

    Error start(Arguments& args);
    void stop();
};

class WallClockASGCT : public BaseWallClock {
  private:
    bool _collapsing;
    bool _precheck;

    static bool inSyscall(void* ucontext);

    static void sharedSignalHandler(int signo, siginfo_t* siginfo, void* ucontext);
    void signalHandler(int signo, siginfo_t* siginfo, void* ucontext, u64 last_sample);

    void initialize(Arguments& args) override;
    void timerLoop() override;

  public:
    WallClockASGCT() : BaseWallClock(), _collapsing(false), _precheck(true) {}
    const char* name() override {
        return "WallClock (ASGCT)";
    }
};

#endif // _WALLCLOCK_H
