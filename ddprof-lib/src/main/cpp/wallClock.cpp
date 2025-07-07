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

#include "wallClock.h"
#include "stackFrame.h"
#include "context.h"
#include "debugSupport.h"
#include "libraries.h"
#include "log.h"
#include "profiler.h"
#include "stackFrame.h"
#include "thread.h"
#include "vmStructs_dd.h"
#include <math.h>
#include <random>
#include <algorithm> // For std::sort and std::binary_search

std::atomic<bool> BaseWallClock::_enabled{false};

bool WallClockASGCT::inSyscall(void *ucontext) {
  StackFrame frame(ucontext);
  uintptr_t pc = frame.pc();

  // Consider a thread sleeping, if it has been interrupted in the middle of
  // syscall execution, either when PC points to the syscall instruction, or if
  // syscall has just returned with EINTR
  if (StackFrame::isSyscall((instruction_t *)pc)) {
    return true;
  }

  // Make sure the previous instruction address is readable
  uintptr_t prev_pc = pc - SYSCALL_SIZE;
  if ((pc & 0xfff) >= SYSCALL_SIZE ||
      Libraries::instance()->findLibraryByAddress((instruction_t *)prev_pc) !=
          NULL) {
    if (StackFrame::isSyscall((instruction_t *)prev_pc) &&
        frame.checkInterruptedSyscall()) {
      return true;
    }
  }

  return false;
}

void WallClockASGCT::sharedSignalHandler(int signo, siginfo_t *siginfo,
                                    void *ucontext) {
  WallClockASGCT *engine = reinterpret_cast<WallClockASGCT *>(Profiler::instance()->wallEngine());
  if (signo == SIGVTALRM) {
    engine->signalHandler(signo, siginfo, ucontext, engine->_interval);
  }
}

void WallClockASGCT::signalHandler(int signo, siginfo_t *siginfo, void *ucontext,
                              u64 last_sample) {
  ProfiledThread *current = ProfiledThread::current();
  int tid = current != NULL ? current->tid() : OS::threadId();
  Shims::instance().setSighandlerTid(tid);
  u32 call_trace_id = 0;
  if (current != NULL && _collapsing) {
    StackFrame frame(ucontext);
    Context &context = Contexts::get(tid);
    call_trace_id = current->lookupWallclockCallTraceId(
        (u64)frame.pc(), Profiler::instance()->recordingEpoch(),
        context.spanId);
    if (call_trace_id != 0) {
      Counters::increment(SKIPPED_WALLCLOCK_UNWINDS);
    }
  }

  ExecutionEvent event;
  ddprof::VMThread *vm_thread = ddprof::VMThread::current();
  bool is_java_thread = vm_thread && VM::jni();
  int raw_thread_state = vm_thread && is_java_thread ? vm_thread->state() : 0;
  bool is_initialized = raw_thread_state >= 4 && raw_thread_state < 12;
  OSThreadState state = OSThreadState::UNKNOWN;
  ExecutionMode mode = ExecutionMode::UNKNOWN;
  if (vm_thread && is_initialized) {
    OSThreadState os_state = vm_thread->osThreadState();
    if (os_state != OSThreadState::UNKNOWN) {
      state = os_state;
    }
    mode = is_java_thread ? convertJvmExecutionState(raw_thread_state)
                          : ExecutionMode::JVM;
  }
  if (state == OSThreadState::UNKNOWN) {
    if (inSyscall(ucontext)) {
      state = OSThreadState::SYSCALL;
      mode = ExecutionMode::SYSCALL;
    } else {
      state = OSThreadState::RUNNABLE;
    }
  }
  event._thread_state = state;
  event._execution_mode = mode;
  event._weight = 1;
  Profiler::instance()->recordSample(ucontext, last_sample, tid, BCI_WALL,
                                     call_trace_id, &event);
  Shims::instance().setSighandlerTid(-1);
}

Error BaseWallClock::start(Arguments &args) {
  int interval = args._event != NULL ? args._interval : args._wall;
  if (interval < 0) {
    return Error("interval must be positive");
  }
  _interval = interval ? interval : DEFAULT_WALL_INTERVAL;

    _reservoir_size =
            args._wall_threads_per_tick ?
            args._wall_threads_per_tick
                                                : DEFAULT_WALL_THREADS_PER_TICK;

  initialize(args);

  _running = true;

  if (pthread_create(&_thread, NULL, threadEntry, this) != 0) {
    return Error("Unable to create timer thread");
  }

  return Error::OK;
}

void BaseWallClock::stop() {
  _running.store(false);
  // the thread join ensures we wait for the thread to finish before returning
  // (and possibly removing the object)
  pthread_kill(_thread, WAKEUP_SIGNAL);
  int res = pthread_join(_thread, NULL);
  if (res != 0) {
    Log::warn("Unable to join WallClock thread on stop %d", res);
  }
}

bool BaseWallClock::isEnabled() const {
  return _enabled.load(std::memory_order_acquire);
}

void WallClockASGCT::initialize(Arguments& args) {
  _collapsing = args._wall_collapsing;
  OS::installSignalHandler(SIGVTALRM, sharedSignalHandler);
}

/* This method is extremely racy!
 * Thread references, that are returned from JVMTI::GetAllThreads(), only guarantee thread objects
 * are not collected by GCs, they don't prevent threads from exiting.
 * We have to be extremely careful when accessing thread's data, so it may not be valid.
 */
void WallClockJVMTI::timerLoop() {
    // Check for enablement before attaching/dettaching the current thread
  if (!isEnabled()) {
    return;
  }

  jvmtiEnv* jvmti = VM::jvmti();
  if (jvmti == nullptr) {
    return;
  }

  // Notice:
  // We want to cache threads that are captured by collectThread(), so that we can
  // clean them up in cleanThreadRefs().
  // The approach is not ideal, but it is cleaner than cleaning individual thread
  // during filtering phases.
  jint threads_count = 0;
  jthread* threads_ptr = nullptr;

  // Attach to JVM as the first step
  VM::attachThread("Datadog Profiler Wallclock Sampler");
  auto collectThreads = [&](std::vector<ThreadEntry>& threads) {
      jvmtiEnv* jvmti = VM::jvmti();
      if (jvmti == nullptr) {
          return;
      }

      if (jvmti->GetAllThreads(&threads_count, &threads_ptr) != JVMTI_ERROR_NONE ||
        threads_count == 0) {
        return;
      }

      JNIEnv* jni = VM::jni();

      ThreadFilter* threadFilter = Profiler::instance()->threadFilter();
      bool do_filter = threadFilter->enabled();
      int self = OS::threadId();

        // If filtering is enabled, collect the filtered TIDs first
        std::vector<int> filtered_tids;
        if (do_filter) {
            Profiler::instance()->threadFilter()->collect(filtered_tids);
            // Sort the TIDs for efficient lookup
            std::sort(filtered_tids.begin(), filtered_tids.end());
        }

        for (int i = 0; i < threads_count; i++) {
          jthread thread = threads_ptr[i];
          if (thread != nullptr) {
            ddprof::VMThread* nThread = static_cast<ddprof::VMThread*>(VMThread::fromJavaThread(jni, thread));
            if (nThread == nullptr) {
              continue;
            }
            int tid = nThread->osThreadId();
            if (tid != self && (!do_filter ||
                 // Use binary search to efficiently find if tid is in filtered_tids
                 std::binary_search(filtered_tids.begin(), filtered_tids.end(), tid))) {
              threads.push_back({nThread, thread});
            }
          }
        }
      }
    };

  auto sampleThreads = [&](ThreadEntry& thread_entry, int& num_failures, int& threads_already_exited, int& permission_denied) {
    static jint max_stack_depth = (jint)Profiler::instance()->max_stack_depth();

    ExecutionEvent event;
    ddprof::VMThread* vm_thread = thread_entry.native;
    int raw_thread_state = vm_thread->state();
    bool is_initialized = raw_thread_state >= ddprof::JVMJavaThreadState::_thread_in_native &&
                          raw_thread_state < ddprof::JVMJavaThreadState::_thread_max_state;
    OSThreadState state = OSThreadState::UNKNOWN;
    ExecutionMode mode = ExecutionMode::UNKNOWN;
    if (vm_thread == nullptr || !is_initialized) {
        return false;
    }
    OSThreadState os_state = vm_thread->osThreadState();
    if (state == OSThreadState::TERMINATED) {
      return false;
    } else if (state == OSThreadState::UNKNOWN) {
      state = OSThreadState::RUNNABLE;
    } else {
      state = os_state;
    }
    mode = convertJvmExecutionState(raw_thread_state);

    event._thread_state = state;
    event._execution_mode = mode;
    event._weight =  1;

    Profiler::instance()->recordJVMTISample(1, thread_entry.tid, thread_entry.java, BCI_WALL, &event, false);
    return true;
  };

  auto cleanThreadRefs = [&]() {
      JNIEnv* jni = VM::jni();
      for (jint index = 0; index < threads_count; index++) {
        jni->DeleteLocalRef(threads_ptr[index]);
      }
      jvmti->Deallocate((unsigned char*)threads_ptr);
      threads_ptr = nullptr;
      threads_count = 0;
  };

  timerLoopCommon<ThreadEntry>(collectThreads, sampleThreads, cleanThreadRefs, _reservoir_size, _interval);


  // Don't forget to detach the thread
  VM::detachThread();
}

void WallClockASGCT::timerLoop() {
    // todo: re-allocating the vector every time is not efficient
    auto collectThreads = [&](std::vector<int>& tids) {
      // Get thread IDs from the filter if it's enabled
      // Otherwise list all threads in the system
      if (Profiler::instance()->threadFilter()->enabled()) {
        Profiler::instance()->threadFilter()->collect(tids);
      } else {
        ThreadList *thread_list = OS::listThreads();
        int tid = thread_list->next();
        while (tid != -1) {
          // Don't include the current thread
          if (tid != OS::threadId()) {
            tids.push_back(tid);
          }
          tid = thread_list->next();
        }
        delete thread_list;
      }
    };

    auto sampleThreads = [&](int tid, int& num_failures, int& threads_already_exited, int& permission_denied) {
      if (!OS::sendSignalToThread(tid, SIGVTALRM)) {
        num_failures++;
        if (errno != 0) {
          if (errno == ESRCH) {
              threads_already_exited++;
          } else if (errno == EPERM) {
              permission_denied++;
          } else {
              Log::debug("unexpected error %s", strerror(errno));
          }
        }
        return false;
      }
      return true;
    };

    auto doNothing = []() {
    };

    timerLoopCommon<int>(collectThreads, sampleThreads, doNothing, _reservoir_size, _interval);
}
