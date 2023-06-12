#ifndef JAVA_PROFILER_LIBRARY_THREAD_STATE_H
#define JAVA_PROFILER_LIBRARY_THREAD_STATE_H

#include "jvmti.h"

enum class ThreadState : int {
    UNKNOWN = 0,
    NEW = 1,                          // The thread has been initialized but yet started
    RUNNABLE = 2,                     // Has been started and is runnable, but not necessarily running
    MONITOR_WAIT = 3,                 // Waiting on a contended monitor lock
    CONDVAR_WAIT = 4,                 // Waiting on a condition variable
    OBJECT_WAIT = 5,                  // Waiting on an Object.wait() call
    BREAKPOINTED = 6,                 // Suspended at breakpoint
    SLEEPING = 7,                     // Thread.sleep()
    TERMINATED = 8,                   // All done, but not reclaimed yet
};

#endif //JAVA_PROFILER_LIBRARY_THREAD_STATE_H
