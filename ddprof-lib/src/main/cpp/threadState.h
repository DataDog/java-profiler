#ifndef JAVA_PROFILER_LIBRARY_THREAD_STATE_H
#define JAVA_PROFILER_LIBRARY_THREAD_STATE_H

#include "jvmti.h"

enum JavaThreadState : int {
    JAVA_THREAD_NEW = 0,
    JAVA_THREAD_TERMINATED = 1,
    JAVA_THREAD_RUNNABLE = 2,
    JAVA_THREAD_BLOCKED = 3,
    JAVA_THREAD_WAITING = 4,
    JAVA_THREAD_TIMED_WAITING = 5
};

static JavaThreadState convertThreadState(int jvmtiThreadState) {
    if ((JVMTI_THREAD_STATE_WAITING | JVMTI_THREAD_STATE_WAITING_WITH_TIMEOUT) & jvmtiThreadState) {
        return JAVA_THREAD_TIMED_WAITING;
    } else if ((JVMTI_THREAD_STATE_WAITING | JVMTI_THREAD_STATE_WAITING_INDEFINITELY) & jvmtiThreadState) {
        return JAVA_THREAD_WAITING;
    } else if ((JVMTI_THREAD_STATE_BLOCKED_ON_MONITOR_ENTER) & jvmtiThreadState) {
        return JAVA_THREAD_BLOCKED;
    } else if ((JVMTI_THREAD_STATE_RUNNABLE) & jvmtiThreadState) {
        return JAVA_THREAD_RUNNABLE;
    } else if (JVMTI_THREAD_STATE_TERMINATED & jvmtiThreadState) {
        return JAVA_THREAD_TERMINATED;
    }
    return JAVA_THREAD_NEW;
}

#endif //JAVA_PROFILER_LIBRARY_THREAD_STATE_H
