/*
 * Copyright 2018 Andrei Pangin
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

#ifndef _WALLCLOCK_H
#define _WALLCLOCK_H

#include "engine.h"
#include "os.h"
#include "profiler.h"
#include "reservoirSampler.h"
#include "threadFilter.h"
#include "threadState.h"
#include "tsc.h"
#include "vmStructs_dd.h"

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
      thread_filter->remove(self);

      u64 startTime = TSC::ticks();
      WallClockEpochEvent epoch(startTime);

      while (_running.load(std::memory_order_relaxed)) {
        collectThreads(threads);

        if (threads.empty()) {
          continue;
        }
        ReservoirSampler<ThreadType> reservoir(reservoirSize);
        int num_failures = 0;
        int threads_already_exited = 0;
        int permission_denied = 0;
        std::vector<ThreadType> sample = reservoir.sample(threads);
        for (const ThreadType &thread : sample) {
          if (!sampleThreads(thread, num_failures, threads_already_exited, permission_denied)) {
            continue;
          }
        }

        // Statistics
        epoch.updateNumSamplableThreads(threads.size());
        
        // No explicit cleanup needed - ThreadHandle destructors handle it automatically
        threads.clear();

        epoch.updateNumFailedSamples(num_failures);
        epoch.updateNumSuccessfulSamples(sample.size() - num_failures);
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

        // Get a random sleep duration
        // clamp the random interval to <1,2N-1>
        // the probability of clamping is extremely small, close to zero
        OS::sleep(std::min(std::max((long int)1, static_cast<long int>(distribution(generator))), ((_interval * 2) - 1)));
      }
    }

    // Overload for RAII types that automatically handle cleanup
    template <typename ThreadType, typename CollectThreadsFunc, typename SampleThreadsFunc>
    void timerLoopCommon(CollectThreadsFunc collectThreads, SampleThreadsFunc sampleThreads, int reservoirSize, u64 interval) {
      // Delegate to the main version with a no-op cleanup function
      timerLoopCommon<ThreadType>(collectThreads, sampleThreads, [](ThreadType&){}, reservoirSize, interval);
    }

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

    static bool inSyscall(void* ucontext);

    static void sharedSignalHandler(int signo, siginfo_t* siginfo, void* ucontext);
    void signalHandler(int signo, siginfo_t* siginfo, void* ucontext, u64 last_sample);

    void initialize(Arguments& args) override;
    void timerLoop() override;

  public:
    WallClockASGCT() : BaseWallClock(), _collapsing(false) {}
    const char* name() override {
        return "WallClock (ASGCT)";
    }
};

class WallClockJVMTI : public BaseWallClock {
  private:
    // RAII wrapper for JNI local thread references
    class ThreadHandle {
    private:
      jthread _thread;
      bool _owned;
      
    public:
      // Constructor takes ownership of the reference
      explicit ThreadHandle(jthread thread) : _thread(thread), _owned(true) {}
      
      // Copy constructor - create new local reference
      ThreadHandle(const ThreadHandle& other) : _thread(nullptr), _owned(false) {
        if (other._owned && other._thread) {
          JNIEnv* env = VM::jni();
          if (env) {
            _thread = (jthread)env->NewLocalRef(other._thread);
            _owned = (_thread != nullptr);
          }
        }
      }
      
      // Copy assignment - create new local reference
      ThreadHandle& operator=(const ThreadHandle& other) {
        if (this != &other) {
          cleanup();
          _thread = nullptr;
          _owned = false;
          
          if (other._owned && other._thread) {
            JNIEnv* env = VM::jni();
            if (env) {
              _thread = (jthread)env->NewLocalRef(other._thread);
              _owned = (_thread != nullptr);
            }
          }
        }
        return *this;
      }
      
      // Move constructor - transfer ownership
      ThreadHandle(ThreadHandle&& other) noexcept 
        : _thread(other._thread), _owned(other._owned) {
        other._thread = nullptr;
        other._owned = false;
      }
      
      // Move assignment - transfer ownership
      ThreadHandle& operator=(ThreadHandle&& other) noexcept {
        if (this != &other) {
          cleanup();
          _thread = other._thread;
          _owned = other._owned;
          other._thread = nullptr;
          other._owned = false;
        }
        return *this;
      }
      
      // Destructor - cleanup if owned
      ~ThreadHandle() {
        cleanup();
      }
      
      // Release ownership (caller takes responsibility)
      jthread release() {
        _owned = false;
        return _thread;
      }
      
      // Get the jthread (still owned by this handle)
      jthread get() const {
        return _thread;
      }
      
      // Get the jthread (still owned by this handle)
      operator jthread() const {
        return _thread;
      }
      
    private:
      void cleanup() {
        if (_owned && _thread) {
          JNIEnv* env = VM::jni();
          if (env) {
            env->DeleteLocalRef(_thread);
          }
        }
      }
    };

    void timerLoop() override;
  public:
    struct ThreadEntry {
        ddprof::VMThread* native;
        ThreadHandle java;
        int tid;
        
        // Constructor that takes a ThreadHandle by move
        ThreadEntry(ddprof::VMThread* n, ThreadHandle&& handle, int t) 
          : native(n), java(std::move(handle)), tid(t) {}
    };
    
    WallClockJVMTI() : BaseWallClock() {}
    const char* name() override {
    return "WallClock (JVMTI)";
  }
};

#endif // _WALLCLOCK_H
