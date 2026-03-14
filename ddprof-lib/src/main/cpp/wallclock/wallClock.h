/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WALLCLOCK_H
#define _WALLCLOCK_H

#include "engine.h"
#include "os.h"
#include "profiler.h"
#include "reservoirSampler.h"
#include "thread.h"
#include "threadFilter.h"
#include "threadState.h"
#include "tsc.h"
#include "vmStructs.h"

class BaseWallClock : public Engine {
  public:
    enum class Mode : int {
        JVMTI,
        ASGCT
    };

  protected:

    static std::atomic<bool> _enabled;
    std::atomic<bool> _running;
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
    void timerLoopCommon(CollectThreadsFunc collectThreads, SampleThreadsFunc sampleThreads, CleanThreadFunc cleanThreads, int reservoirSize, u64 interval);
public:
  BaseWallClock() :
        _interval(LONG_MAX),
        _reservoir_size(0),
        _running(false),
        _thread(0) {}
    virtual ~BaseWallClock() = default;

    const char* units() {
        return "ns";
    }

  virtual const char* name() const = 0;
  virtual Mode mode() const = 0;

  long interval() const { return _interval; }

  inline void enableEvents(bool enabled) {
        _enabled.store(enabled, std::memory_order_release);
    }

    Error start(Arguments& args);
    void stop();
};


#endif // _WALLCLOCK_H
