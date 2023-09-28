#ifndef JAVA_PROFILER_JNIHELPER_H
#define JAVA_PROFILER_JNIHELPER_H

#include <jni.h>

static void jniExceptionCheck(JNIEnv* jni, bool describe = false) {
    if(jni->ExceptionCheck()) {
        if (describe) {
            jni->ExceptionDescribe();
        }
        jni->ExceptionClear();
    }
}

#endif
