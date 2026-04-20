#ifndef JAVA_PROFILER_JNIHELPER_H
#define JAVA_PROFILER_JNIHELPER_H

#include <jni.h>

inline bool jniExceptionCheck(JNIEnv *jni, bool describe = false) {
  if (jni->ExceptionCheck()) {
    if (describe) {
      jni->ExceptionDescribe();
    }
    jni->ExceptionClear();
    return true;
  }
  return false;
}

#endif
