#ifndef THREADSTATETRACKER_H
#define THREADSTATETRACKER_H

#include <jvmti.h>
#include <string>
#include "vmStructs.h"

typedef jint (JNICALL *RegisterNativesFunction)(JNIEnv*, jclass, const JNINativeMethod*, jint);
// see jvm.cpp for intercepted function definitions
// void JVM_SleepNanos(JNIEnv* env, jclass threadClass, jlong nanos)
typedef void (JNICALL *ThreadSleepFunction)(JNIEnv*, jobject, jlong);

// hooks functions to set thread state in context storage
class ThreadStateTracker {
private:
    static bool _initialized;
    static jclass _ThreadClass;
    static std::string* _sleepFunctionName;
    static RegisterNativesFunction _orig_RegisterNatives;
    static jint JNICALL RegisterNativesHook(JNIEnv* env, jclass cls, const JNINativeMethod* methods, jint nMethods);

    static ThreadSleepFunction _orig_Thread_sleep;
    static void JNICALL ThreadSleepHook(JNIEnv* env, jobject instance, jlong millis);

    static void bindThreadSleep(ThreadSleepFunction entry);
public:
    static void initialize();
    static void close();
};

#endif //THREADSTATETRACKER_H
