#include <jni.h>
#include "com_datadoghq_loader_DynamicLibraryLoader.h"
#include <iostream>
#include <dlfcn.h>

JNIEXPORT jboolean JNICALL Java_com_datadoghq_loader_DynamicLibraryLoader_loadLibrary(JNIEnv* env, jobject unused, jstring library, jstring name) {
    int (*function)(int i);
    const char* libraryName = env->GetStringUTFChars(library, 0);
    void* handle = dlopen(libraryName, RTLD_LAZY);
    if (NULL == handle) {
        std::cout << "could not load " << libraryName << std::endl;
        return false;
    } else {
        const char *functionName = env->GetStringUTFChars(name, 0);
        function = (int(*)(int)) dlsym(handle, functionName);
        int next = (*function)(1);
        std::cout << "loaded " << libraryName << " and computed: " << next << std::endl;
        return true;
    }
}

