/*
 * Copyright 2016 Andrei Pangin
 * Copyright 2021, 2023 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _VMENTRY_H
#define _VMENTRY_H

#include <jvmti.h>

#include "frame.h"


#ifdef __clang__
#  define DLLEXPORT __attribute__((visibility("default")))
#else
#  define DLLEXPORT __attribute__((visibility("default"),externally_visible))
#endif


// Denotes ASGCT_CallFrame where method_id has special meaning (not jmethodID)
enum ASGCT_CallFrameType {
    BCI_CPU                 =   0,  // cpu time
    BCI_WALL                = -10,  // wall time
    BCI_NATIVE_FRAME        = -11,  // native function name (char*)
    BCI_ALLOC               = -12,  // name of the allocated class
    BCI_ALLOC_OUTSIDE_TLAB  = -13,  // name of the class allocated outside TLAB
    BCI_LIVENESS             = -14,  // name of the allocated class
    BCI_LOCK                = -15,  // class name of the locked object
    BCI_PARK                = -16,  // class name of the park() blocker
    BCI_THREAD_ID           = -17,  // method_id designates a thread
    BCI_ERROR               = -18,  // method_id is an error string
};

// See hotspot/src/share/vm/prims/forte.cpp
enum ASGCT_Failure {
    ticks_no_Java_frame         =  0,
    ticks_no_class_load         = -1,
    ticks_GC_active             = -2,
    ticks_unknown_not_Java      = -3,
    ticks_not_walkable_not_Java = -4,
    ticks_unknown_Java          = -5,
    ticks_not_walkable_Java     = -6,
    ticks_unknown_state         = -7,
    ticks_thread_exit           = -8,
    ticks_deopt                 = -9,
    ticks_safepoint             = -10,
    ticks_skipped               = -11,
    ASGCT_FAILURE_TYPES         = 12
};

typedef struct {
    jint bci;
    jmethodID method_id;
} ASGCT_CallFrame;

typedef struct {
    JNIEnv* env;
    jint num_frames;
    ASGCT_CallFrame* frames;
} ASGCT_CallTrace;

typedef void (*AsyncGetCallTrace)(ASGCT_CallTrace*, jint, void*);

typedef struct {
    void* unused[38];
    jstring (JNICALL *ExecuteDiagnosticCommand)(JNIEnv*, jstring);
} VMManagement;

typedef VMManagement* (*JVM_GetManagement)(jint);

typedef struct {
    void* unused1[86];
    jvmtiError (JNICALL *RedefineClasses)(jvmtiEnv*, jint, const jvmtiClassDefinition*);
    void* unused2[64];
    jvmtiError (JNICALL *RetransformClasses)(jvmtiEnv*, jint, const jclass*);
} JVMTIFunctions;


class VM {
  private:
    static JavaVM* _vm;
    static jvmtiEnv* _jvmti;

    static int _java_version;
    static int _java_update_version;
    static bool _openj9;
    static bool _hotspot;
    static bool _zing;
    static bool _can_sample_objects;
    static bool _can_intercept_binding;
    static bool _is_adaptive_gc_boundary_flag_set;


    static jvmtiError (JNICALL *_orig_RedefineClasses)(jvmtiEnv*, jint, const jvmtiClassDefinition*);
    static jvmtiError (JNICALL *_orig_RetransformClasses)(jvmtiEnv*, jint, const jclass* classes);

    static void ready(jvmtiEnv* jvmti, JNIEnv* jni);
    static void applyPatch(char* func, const char* patch, const char* end_patch);
    static void* getLibraryHandle(const char* name);
    static void loadMethodIDs(jvmtiEnv* jvmti, JNIEnv* jni, jclass klass);
    static void loadAllMethodIDs(jvmtiEnv* jvmti, JNIEnv* jni);

  public:
    static void* _libjvm;
    static void* _libjava;
    static AsyncGetCallTrace _asyncGetCallTrace;
    static JVM_GetManagement _getManagement;

    static bool init(JavaVM* vm, bool attach);

    static void restartProfiler();

    static jvmtiEnv* jvmti() {
        return _jvmti;
    }

    static JNIEnv* jni() {
        JNIEnv* jni;
        return _vm->GetEnv((void**)&jni, JNI_VERSION_1_6) == 0 ? jni : NULL;
    }

    static JNIEnv* attachThread(const char* name) {
        JNIEnv* jni;
        JavaVMAttachArgs args = {JNI_VERSION_1_6, (char*)name, NULL};
        return _vm->AttachCurrentThreadAsDaemon((void**)&jni, &args) == 0 ? jni : NULL;
    }

    static void detachThread() {
        _vm->DetachCurrentThread();
    }

    static VMManagement* management() {
        return _getManagement != NULL ? _getManagement(0x20030000) : NULL;
    }

    static int java_version() {
        return _java_version;
    }

    static int hotspot_version() {
        return isHotspot() ? _java_version : -1;
    }

    static int java_update_version() {
        return _java_update_version;
    }

    static bool isOpenJ9() {
        return _openj9;
    }
    static bool isHotspot() {
        return _hotspot;
    }

    static bool canSampleObjects() {
        return _can_sample_objects;
    }

    static bool isZing() {
        return _zing;
    }

    static bool isUseAdaptiveGCBoundarySet() {
        return _is_adaptive_gc_boundary_flag_set;
    }

    static void JNICALL VMInit(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread);
    static void JNICALL VMDeath(jvmtiEnv* jvmti, JNIEnv* jni);

    static void JNICALL ClassLoad(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread, jclass klass) {
        // Needed only for AsyncGetCallTrace support
    }

    static void JNICALL ClassPrepare(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread, jclass klass) {
        loadMethodIDs(jvmti, jni, klass);
    }

    static jvmtiError JNICALL RedefineClassesHook(jvmtiEnv* jvmti, jint class_count, const jvmtiClassDefinition* class_definitions);
    static jvmtiError JNICALL RetransformClassesHook(jvmtiEnv* jvmti, jint class_count, const jclass* classes);
};

#endif // _VMENTRY_H
