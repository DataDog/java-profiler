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

#endif // JAVA_PROFILER_LIBRARY_THREAD_STATE_H
