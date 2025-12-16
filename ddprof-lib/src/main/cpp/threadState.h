#ifndef JAVA_PROFILER_LIBRARY_THREAD_STATE_H
#define JAVA_PROFILER_LIBRARY_THREAD_STATE_H

#include "jvmti.h"

enum class OSThreadState : int {
  UNKNOWN = 0,
  NEW = 1,      // The thread has been initialized but yet started
  RUNNABLE = 2, // Has been started and is runnable, but not necessarily running
  MONITOR_WAIT = 3, // Waiting on a contended monitor lock
  CONDVAR_WAIT = 4, // Waiting on a condition variable
  OBJECT_WAIT = 5,  // Waiting on an Object.wait() call
  BREAKPOINTED = 6, // Suspended at breakpoint
  SLEEPING = 7,     // Thread.sleep()
  TERMINATED = 8,   // All done, but not reclaimed yet
  SYSCALL = 9 // does not originate in the JVM, used when the current frame is
              // known to be a syscall
};

enum class ExecutionMode : int {
  UNKNOWN = 0,
  JAVA = 1,
  JVM = 2,
  NATIVE = 3,
  SAFEPOINT = 4,
  SYSCALL = 5
};

static ExecutionMode convertJvmExecutionState(int state) {
  switch (state) {
  case 4:
  case 5:
    return ExecutionMode::NATIVE;
  case 6:
  case 7:
    return ExecutionMode::JVM;
  case 8:
  case 9:
    return ExecutionMode::JAVA;
  case 10:
  case 11:
    return ExecutionMode::SAFEPOINT;
  default:
    return ExecutionMode::UNKNOWN;
  }
}

/**
 * Determines the execution mode from a VMThread's state.
 *
 * This function distinguishes Java threads from JVM internal threads based on their state.
 * Java threads have states in [_thread_in_native, _thread_max_state) range [4, 12).
 * JVM internal threads (GC, Compiler) have state 0 or outside this range.
 *
 * CRITICAL: This function is safe to call from signal handlers. It does NOT call VM::jni()
 * which would trigger __tls_get_addr for thread-local JNIEnv lookup. If the signal interrupts
 * during TLS initialization (e.g., ForkJoinWorkerThread startup), VM::jni() would cause
 * re-entrant TLS allocation and heap corruption.
 *
 * Thread states are defined in OpenJDK:
 * https://github.com/openjdk/jdk/blob/master/src/hotspot/share/utilities/globalDefinitions.hpp
 * Search for "enum JavaThreadState"
 *
 * @param vm_thread The VMThread pointer (can be null)
 * @return ExecutionMode::UNKNOWN if vm_thread is null,
 *         ExecutionMode::JVM for JVM internal threads,
 *         or the appropriate execution mode for Java threads
 */
template<typename VMThreadType>
static inline ExecutionMode getThreadExecutionMode(VMThreadType* vm_thread) {
  if (vm_thread == nullptr) {
    return ExecutionMode::UNKNOWN;
  }

  int raw_thread_state = vm_thread->state();

  // Java threads: [4, 12) = [_thread_in_native, _thread_max_state)
  // JVM internal threads: 0 or outside this range
  bool is_java_thread = raw_thread_state >= 4 && raw_thread_state < 12;

  return is_java_thread ? convertJvmExecutionState(raw_thread_state)
                        : ExecutionMode::JVM;
}

#endif // JAVA_PROFILER_LIBRARY_THREAD_STATE_H
