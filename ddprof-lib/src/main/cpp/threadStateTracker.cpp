#include "thread.h"
#include "threadStateTracker.h"
#include "threadState.h"

bool ThreadStateTracker::_initialized = false;
std::string* ThreadStateTracker::_sleepFunctionName = nullptr;
jclass ThreadStateTracker::_ThreadClass = nullptr;
ThreadSleepFunction ThreadStateTracker::_orig_Thread_sleep = nullptr;
RegisterNativesFunction ThreadStateTracker::_orig_RegisterNatives = nullptr;

jint JNICALL ThreadStateTracker::RegisterNativesHook(JNIEnv* env, jclass cls, const JNINativeMethod* methods, jint nMethods) {
    if (env->IsSameObject(cls, _ThreadClass)) {
        for (jint i = 0; i < nMethods; i++) {
            // sleep(long) is native in older JDKs, for a while there was sleep0(long), now there is sleepNanos0(long)
            if (strncmp(methods[i].name, "sleep", 5) == 0 && strcmp(methods[i].signature, "(J)V") == 0) {
                _sleepFunctionName = new std::string(methods[i].name);
                _orig_Thread_sleep = (ThreadSleepFunction)methods[i].fnPtr;
                break;
            }
        }
        return 0;
    }
    return _orig_RegisterNatives(env, cls, methods, nMethods);
}

void JNICALL ThreadStateTracker::ThreadSleepHook(JNIEnv* env, jobject instance, jlong timespan) {
    ProfiledThread* current = ProfiledThread::current();
    ThreadState previousState = ThreadState::UNKNOWN;
    if (current != nullptr) {
        previousState = current->get_thread_state();
        current->set_thread_state(ThreadState::SLEEPING);
    }
    _orig_Thread_sleep(env, instance, timespan);
    if (current != nullptr) {
        current->set_thread_state(previousState);
    }
}

void ThreadStateTracker::initialize() {
    jvmtiEnv* jvmti = VM::jvmti();
    JNIEnv* env = VM::jni();

    jclass thread = env->FindClass("java/lang/Thread");
    if (thread == NULL) {
        env->ExceptionClear();
        return;
    }

    _ThreadClass = (jclass)env->NewGlobalRef(thread);
    // code adapted from async-profiler's lock tracer
    jmethodID register_natives = env->GetStaticMethodID(_ThreadClass, "registerNatives", "()V");
    jniNativeInterface* jni_functions;
    if (register_natives != NULL && jvmti->GetJNIFunctionTable(&jni_functions) == 0) {
        _orig_RegisterNatives = jni_functions->RegisterNatives;
        jni_functions->RegisterNatives = RegisterNativesHook;
        jvmti->SetJNIFunctionTable(jni_functions);

        // Trace Unsafe.registerNatives() to find the original address of Unsafe.park() native
        env->CallStaticVoidMethod(_ThreadClass, register_natives);

        jni_functions->RegisterNatives = _orig_RegisterNatives;
        jvmti->SetJNIFunctionTable(jni_functions);
    }

    if (_orig_Thread_sleep != NULL) {
        bindThreadSleep(ThreadSleepHook);
    }

    env->ExceptionClear();
    _initialized = true;
}

void ThreadStateTracker::bindThreadSleep(ThreadSleepFunction function) {
    if (_sleepFunctionName != nullptr) {
        JNIEnv * env = VM::jni();
        const JNINativeMethod sleep = {(char *) _sleepFunctionName->c_str(), (char *) "(J)V", (void *) function};
        if (env->RegisterNatives(_ThreadClass, &sleep, 1) != 0) {
            env->ExceptionClear();
        }
    }
}
