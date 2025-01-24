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
#include "vmStructs.h"
#include <math.h>
#include <random>
#include <cstdlib>

class JVMTIThreads {
 private:
  jvmtiEnv* _jvmti;           // Pointer to JVMTI environment
  JNIEnv* _jni;               // Pointer to JNI environment
  jthread* _threads_ptr;      // Array of thread references
  jint _threads_count;        // Number of threads

 public:
  // Constructor that takes a jvmtiEnv and retrieves all threads
  JVMTIThreads(jvmtiEnv* jvmti, JNIEnv* jni) : _jvmti(jvmti), _jni(jni), _threads_ptr(nullptr), _threads_count(0) {
    if (_jvmti && _jvmti->GetAllThreads(&_threads_count, &_threads_ptr) != JVMTI_ERROR_NONE) {
      _threads_count = 0;
      _threads_ptr = nullptr;
    }
  }

  // Destructor to clean up resources
  ~JVMTIThreads() {
    if (_threads_ptr) {
      // Delete local references of threads
      for (jint i = 0; i < _threads_count; ++i) {
        if (_threads_ptr[i]) {
          _jni->DeleteLocalRef(_threads_ptr[i]);
        }
      }

      // Deallocate memory for threads_ptr
      _jvmti->Deallocate(reinterpret_cast<unsigned char*>(_threads_ptr));
    }
  }

  // Disable copy constructor and assignment operator
  JVMTIThreads(const JVMTIThreads&) = delete;
  JVMTIThreads& operator=(const JVMTIThreads&) = delete;

  // Allow move constructor and assignment operator
  JVMTIThreads(JVMTIThreads&& other) noexcept
    : _jvmti(other._jvmti), _jni(other._jni), _threads_ptr(other._threads_ptr), _threads_count(other._threads_count) {
    other._jvmti = nullptr;
    other._threads_ptr = nullptr;
    other._threads_count = 0;
  }

  JVMTIThreads& operator=(JVMTIThreads&& other) noexcept {
    if (this != &other) {
      // Clean up current resources
      this->~JVMTIThreads();

      // Transfer ownership
      _jvmti = other._jvmti;
      _jni = other._jni;
      _threads_ptr = other._threads_ptr;
      _threads_count = other._threads_count;

      other._jvmti = nullptr;
      other._jni = nullptr;
      other._threads_ptr = nullptr;
      other._threads_count = 0;
    }
    return *this;
  }

  // Getters for thread count and thread pointer
  jint count() const {
      return _threads_count;
  }

  // Operator[] to access individual threads
  jthread operator[](jint index) const noexcept {
    if (index < 0 || index >= _threads_count) {
      return nullptr;
    }
    return _threads_ptr[index];
  }
};

template<typename T>
class MoveToLocal {
 private:
   JNIEnv* _jni;  // JNI environment
   T _ref;        // Local JNI reference
 public:
  MoveToLocal(JNIEnv* jni, T global_ref, bool is_weak) : _jni(jni) {
    if (jni != nullptr) {
      _ref = jni->NewLocalRef(global_ref);
      if (is_weak) {
        _jni->DeleteWeakGlobalRef(global_ref);
      } else {
        _jni->DeleteGlobalRef(global_ref);
      }
    }
  }

  ~MoveToLocal() {
    if (_jni != nullptr) {
      if (_ref) {
        _jni->DeleteLocalRef(_ref);
      }
    }
  }

  // Disable copy constructor and assignment operator
  MoveToLocal(const MoveToLocal&) = delete;
  MoveToLocal& operator=(const MoveToLocal&) = delete;

  // Allow move constructor and assignment operator
  MoveToLocal(MoveToLocal&& other) noexcept
    : _jni(other._jni), _ref(other._ref) {
    other._jni = nullptr;
    other._ref = nullptr;
  }

  MoveToLocal& operator=(MoveToLocal&& other) noexcept {
    if (this != &other) {
      // Clean up current resources
      this->~MoveToLocal();

      // Transfer ownership
      _jni = other._jni;
      _ref = other._ref;

      other._jni = nullptr;
      other._ref = nullptr;
    }
    return *this;
  }

  T local() {
    return _ref;
  }
};

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
  VMThread *vm_thread = VMThread::current();
  bool is_java_thread = vm_thread && VM::jni();
  int raw_thread_state = vm_thread && is_java_thread ? vm_thread->state() : 0;
  bool is_initialized = raw_thread_state >= 4 && raw_thread_state < 12;
  ThreadState state = ThreadState::UNKNOWN;
  ExecutionMode mode = ExecutionMode::UNKNOWN;
  if (vm_thread && is_initialized) {
    ThreadState os_state = vm_thread->osThreadState();
    if (os_state != ThreadState::UNKNOWN) {
      state = os_state;
    }
    mode = is_java_thread ? convertJvmExecutionState(raw_thread_state)
                          : ExecutionMode::JVM;
  }
  if (state == ThreadState::UNKNOWN) {
    if (inSyscall(ucontext)) {
      state = ThreadState::SYSCALL;
      mode = ExecutionMode::SYSCALL;
    } else {
      state = ThreadState::RUNNABLE;
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

void WallClockJVMTI::timerLoop() {
  // Check for enablement before attaching/dettaching the current thread
  if (!isEnabled()) {
    return;
  }
  // Attach to JVM as the first step
  VM::attachThread("Datadog Profiler Wallclock Sampler");
  auto collectThreads = [&](std::vector<ThreadEntry>& threads) {
    jvmtiEnv* jvmti = VM::jvmti();
    if (jvmti == nullptr) {
        return;
    }
    JNIEnv* jni = VM::jni();

    // When we collect thread list via JVMTI the threads will be effectively local references
    // These local references would be automatically cleaned up once we get back from the native call to Java
    // But here we are in an endless loop, never leaving the native call and as such all those local references
    //  would just keep on piling up
    // Therefore, we have this neat RAII JMVTIThreads type which will take care of releasing the local references
    //  once we are out of scope here
    JVMTIThreads thread_array(jvmti, jni);
    bool do_filter = Profiler::instance()->threadFilter()->enabled();
    int self = OS::threadId();
    for (int i = 0; i < thread_array.count(); i++) {
      jthread thread = thread_array[i];
      if (thread != nullptr) {
        VMThread* nThread = VMThread::fromJavaThread(jni, thread);
        if (nThread == nullptr) {
          continue;
        }
        jint thread_state;
        if (jvmti->GetThreadState(thread, &thread_state) == JVMTI_ERROR_NONE &&
            (thread_state & JVMTI_THREAD_STATE_TERMINATED) == 0) {
            // It might not always be possible to resolve native thread from a java thread
            //   eg. when we are trying that very early in the thread startup
            // In that case we would return -1 as the native tid and just skip that thread
            int tid = VMThread::nativeThreadId(jni, thread);
            if (tid != -1 && tid != self && (!do_filter || Profiler::instance()->threadFilter()->accept(tid))) {
              // if NewWeakGlobalRef fails it will return 'nullptr' and we will skip it when the thread list is processed
              threads.push_back({nThread, jni->NewWeakGlobalRef(thread)});
            }
        }
      }
    }
  };

  auto sampleThreads = [&](ThreadEntry& thread_entry, int& num_failures, int& threads_already_exited, int& permission_denied) {
    static jint max_stack_depth = (jint)Profiler::instance()->max_stack_depth();
    static jvmtiFrameInfo* frame_buffer = new jvmtiFrameInfo[max_stack_depth];
    static jvmtiEnv* jvmti = VM::jvmti();
    static JNIEnv* jni = VM::jni();

    int num_frames = 0;
    if (thread_entry.java_ref == nullptr) {
      num_failures++;
      return false;
    }

    MoveToLocal<jthread> mtl(jni, thread_entry.java_ref, true);
    jthread thread = mtl.local();
    if (thread == nullptr) {
        num_failures++;
        return false;
    }

    jint thread_state;
    jvmtiError state_err = jvmti->GetThreadState(thread, &thread_state);
    if (state_err != JVMTI_ERROR_NONE || (thread_state & JVMTI_THREAD_STATE_TERMINATED) != 0) {
        num_failures++;
        return false;
    }
    jvmtiError err = jvmti->GetStackTrace(thread, 0, max_stack_depth, frame_buffer, &num_frames);

    if (err != JVMTI_ERROR_NONE) {
      num_failures++;
      if (err == JVMTI_ERROR_THREAD_NOT_ALIVE) {
        threads_already_exited++;
      }
      return false;
    }
    if (num_frames == 0) {
      // some JVMTI attached threads are Java-like but have no stack; we can just ignore them
      return true;
    }
    ExecutionEvent event;
    VMThread* vm_thread = thread_entry.native;
    int raw_thread_state = vm_thread->state();
    bool is_initialized = raw_thread_state >= JVMJavaThreadState::_thread_in_native &&
                          raw_thread_state < JVMJavaThreadState::_thread_max_state;
    ThreadState state = ThreadState::UNKNOWN;
    ExecutionMode mode = ExecutionMode::UNKNOWN;
    if (vm_thread && is_initialized) {
      ThreadState os_state = vm_thread->osThreadState();
      if (os_state != ThreadState::UNKNOWN) {
        state = os_state;
      }
      mode = convertJvmExecutionState(raw_thread_state);
    }
    if (state == ThreadState::UNKNOWN) {
      state = ThreadState::RUNNABLE;
    }
    event._thread_state = state;
    event._execution_mode = mode;
    event._weight =  1;

    Profiler::instance()->recordExternalSample(1, thread_entry.native->osThreadId(), frame_buffer, num_frames, false, BCI_WALL, &event);
    return true;
  };

  timerLoopCommon<ThreadEntry>(collectThreads, sampleThreads, _reservoir_size, _interval);
  // Don't forget to detach the thread
  VM::detachThread();
}

void WallClockASGCT::timerLoop() {
    auto collectThreads = [&](std::vector<int>& tids) {
      if (Profiler::instance()->threadFilter()->enabled()) {
        Profiler::instance()->threadFilter()->collect(tids);
      } else {
        ThreadList *thread_list = OS::listThreads();
        int tid = thread_list->next();
        while (tid != -1) {
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
    timerLoopCommon<int>(collectThreads, sampleThreads, _reservoir_size, _interval);
}
