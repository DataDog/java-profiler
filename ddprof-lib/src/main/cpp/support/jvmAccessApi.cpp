/*
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "common.h"
#include "hotspot/vmStructs.h"

#include <jni.h>
#include <string.h>

#ifndef DLLEXPORT
#  define DLLEXPORT __attribute__((visibility("default")))
#endif

// RAII wrapper for JNI string conversion.
class JniString {
private:
    JNIEnv *_env;
    const char *_c_string;
    jstring _java_string;
    int _length;

public:
    JniString(JNIEnv *env, jstring java_string) {
        _env = env;
        _c_string = _env->GetStringUTFChars(java_string, NULL);
        _length = _env->GetStringUTFLength(java_string);
        _java_string = java_string;
    }
    JniString(JniString &jniString) = delete;
    ~JniString() { _env->ReleaseStringUTFChars(_java_string, _c_string); }
    const char *c_str() const { return _c_string; }
    int length() const { return _length; }
};

extern "C" DLLEXPORT jstring JNICALL
Java_com_datadoghq_profiler_JVMAccess_findStringJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
    JniString flag_str(env, flagName);
    VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::String, VMFlag::Type::Stringlist});
    if (f) {
        char** value = static_cast<char**>(f->addr());
        if (value != NULL && *value != NULL) {
            return env->NewStringUTF(*value);
        }
    }
    return NULL;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JVMAccess_setStringJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName,
                                                         jstring flagValue) {
    JniString flag_str(env, flagName);
    JniString value_str(env, flagValue);
    VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::String, VMFlag::Type::Stringlist});
    if (f) {
        char** value = static_cast<char**>(f->addr());
        if (value != NULL) {
            *value = strdup(value_str.c_str());
        }
    }
}

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JVMAccess_findBooleanJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
    JniString flag_str(env, flagName);
    VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::Bool});
    if (f) {
        char* value = static_cast<char*>(f->addr());
        if (value != NULL) {
            return ((*value) & 0xff) == 1;
        }
    }
    return false;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JVMAccess_setBooleanJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName,
                                                         jboolean flagValue) {
    JniString flag_str(env, flagName);
    VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::Bool});
    if (f) {
        char* value = static_cast<char*>(f->addr());
        if (value != NULL) {
            *value = flagValue ? 1 : 0;
        }
    }
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JVMAccess_findIntJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
    JniString flag_str(env, flagName);
    VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::Int, VMFlag::Type::Uint, VMFlag::Type::Intx, VMFlag::Type::Uintx, VMFlag::Type::Uint64_t, VMFlag::Type::Size_t});
    if (f) {
        long* value = static_cast<long*>(f->addr());
        if (value != NULL) {
            return *value;
        }
    }
    return 0;
}

extern "C" DLLEXPORT jdouble JNICALL
Java_com_datadoghq_profiler_JVMAccess_findFloatJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
    JniString flag_str(env, flagName);
    VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::Double});
    if (f) {
        double* value = static_cast<double*>(f->addr());
        if (value != NULL) {
            return *value;
        }
    }
    return 0.0;
}

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JVMAccess_healthCheck0(JNIEnv *env,
                                                         jobject unused) {
    TEST_LOG("JVMAccess::healthCheck0");
    return true;
}
