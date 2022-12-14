#ifndef JAVA_PROFILER_COM_DATADOGHQ_LOADER_DYNAMICLIBRARYLOADER_H
#define JAVA_PROFILER_COM_DATADOGHQ_LOADER_DYNAMICLIBRARYLOADER_H

#include <jni.h>

extern "C" {
    JNIEXPORT jboolean JNICALL Java_com_datadoghq_loader_DynamicLibraryLoader_loadLibrary(JNIEnv *, jobject, jstring, jstring);
}

#endif //JAVA_PROFILER_COM_DATADOGHQ_LOADER_DYNAMICLIBRARYLOADER_H
