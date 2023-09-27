#ifndef JAVA_PROFILER_JNIHELPER_H
#define JAVA_PROFILER_JNIHELPER_H

#include <jni.h>

static void jniExceptionCheck(JNIEnv* jni) {
    if(jni->ExceptionCheck()) {
        jni->ExceptionClear();
    }
}

#endif
