#ifndef JAVA_PROFILER_LIBRARY_THREAD_STATE_INLINE_H
#define JAVA_PROFILER_LIBRARY_THREAD_STATE_INLINE_H


#include "threadState.h"
#include "vmStructs.h"
#include "thread.h"
#include <stdio.h>

inline ExecutionMode getThreadExecutionMode() {
  VMThread* vm_thread = VMThread::current();
  // Not a JVM thread - native thread, e.g. thread launched by JNI code
  if (vm_thread == nullptr) {
    return ExecutionMode::NATIVE;
  }

  
  ProfiledThread *prof_thread = ProfiledThread::currentSignalSafe();
  bool is_java_thread = prof_thread != nullptr && prof_thread->isJavaThread();

  // A Java thread that JVM tells us via jvmti `ThreadStart()` callback.
  if (is_java_thread) {
    int raw_thread_state = vm_thread->state();

    // Java threads: [4, 12) = [_thread_in_native, _thread_max_state)
    // JVM internal threads: 0 or outside this range
    is_java_thread = raw_thread_state >= 4 && raw_thread_state < 12;

    return is_java_thread ? convertJvmExecutionState(raw_thread_state)
                        : ExecutionMode::JVM;
  } else {
    // It is a JVM internal thread, may or may not be a Java thread, 
    // e.g. Compiler thread or GC thread, etc
    return ExecutionMode::JVM;
  }
}

#endif // JAVA_PROFILER_LIBRARY_THREAD_STATE_INLINE_H