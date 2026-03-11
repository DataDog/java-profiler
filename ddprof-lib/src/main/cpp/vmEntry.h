/*
 * Copyright The async-profiler authors
 * Copyright 2021, 2025 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _VMENTRY_H
#define _VMENTRY_H

#include <jvmti.h>
#include "arch.h"

#include "arch.h"
#include "codeCache.h"
#include "frame.h"

#ifdef __clang__
#define DLLEXPORT __attribute__((visibility("default")))
#else
#define DLLEXPORT __attribute__((visibility("default"), externally_visible))
#endif

// Denotes ASGCT_CallFrame where method_id has special meaning (not jmethodID)
enum ASGCT_CallFrameType {
  BCI_CPU = 0,                  // cpu time
  BCI_WALL = -10,               // wall time
  BCI_NATIVE_FRAME = -11,       // native function name (char*)
  BCI_ALLOC = -12,              // name of the allocated class
  BCI_ALLOC_OUTSIDE_TLAB = -13, // name of the class allocated outside TLAB
  BCI_LIVENESS = -14,           // name of the allocated class
  BCI_LOCK = -15,               // class name of the locked object
  BCI_PARK = -16,               // class name of the park() blocker
  BCI_THREAD_ID = -17,          // method_id designates a thread
  BCI_ERROR = -18,              // method_id is an error string
  BCI_NATIVE_FRAME_REMOTE = -19, // method_id points to RemoteFrameInfo for remote symbolication
};

// See hotspot/src/share/vm/prims/forte.cpp
enum ASGCT_Failure {
  ticks_no_Java_frame = 0,
  ticks_no_class_load = -1,
  ticks_GC_active = -2,
  ticks_unknown_not_Java = -3,
  ticks_not_walkable_not_Java = -4,
  ticks_unknown_Java = -5,
  ticks_not_walkable_Java = -6,
  ticks_unknown_state = -7,
  ticks_thread_exit = -8,
  ticks_deopt = -9,
  ticks_safepoint = -10,
  ticks_skipped = -11,
  ASGCT_FAILURE_TYPES = 12
};

/**
 * Information for native frames requiring remote symbolication.
 * Used when bci == BCI_NATIVE_FRAME_REMOTE.
 */
typedef struct RemoteFrameInfo {
    const char* build_id;      // GNU build-id for library identification (null-terminated hex string)
    uintptr_t pc_offset;       // PC offset within the library/module
    short lib_index;           // Index into CodeCache library table for fast lookup

#ifdef __cplusplus
    // Constructor for C++ convenience
    RemoteFrameInfo(const char* bid, uintptr_t offset, short lib_idx)
        : build_id(bid), pc_offset(offset), lib_index(lib_idx) {}
#endif
} RemoteFrameInfo;

typedef struct {
    jint bci;
    LP64_ONLY(jint padding;)
    union {
        jmethodID method_id;
        unsigned long packed_remote_frame; // packed RemoteFrameInfo data
        const char* native_function_name;
    };
} ASGCT_CallFrame;

typedef struct {
  JNIEnv *env;
  jint num_frames;
  ASGCT_CallFrame *frames;
} ASGCT_CallTrace;

typedef void (*AsyncGetCallTrace)(ASGCT_CallTrace *, jint, void *);

typedef struct {
  void *unused[38];
  jstring(JNICALL *ExecuteDiagnosticCommand)(JNIEnv *, jstring);
} VMManagement;

typedef VMManagement *(*JVM_GetManagement)(jint);

typedef struct {
  void *unused1[86];
  jvmtiError(JNICALL *RedefineClasses)(jvmtiEnv *, jint,
                                       const jvmtiClassDefinition *);
  void *unused2[64];
  jvmtiError(JNICALL *RetransformClasses)(jvmtiEnv *, jint, const jclass *);
} JVMTIFunctions;

typedef struct {
  int major;
  int update;
} JavaFullVersion;

class JavaVersionAccess {
 public:
   static JavaFullVersion get_java_version(char* prop_value);
   static int get_hotspot_version(char* prop_value);
};

class VM {
private:
  static JavaVM *_vm;
  static jvmtiEnv *_jvmti;

  static int _java_version;
  static int _java_update_version;
  static int _hotspot_version;
  static bool _openj9;
  static bool _hotspot;
  static bool _zing;
  static bool _can_sample_objects;
  static bool _can_intercept_binding;
  static bool _is_adaptive_gc_boundary_flag_set;

  static jvmtiError(JNICALL *_orig_RedefineClasses)(
      jvmtiEnv *, jint, const jvmtiClassDefinition *);
  static jvmtiError(JNICALL *_orig_RetransformClasses)(jvmtiEnv *, jint,
                                                       const jclass *classes);

  static void ready(jvmtiEnv *jvmti, JNIEnv *jni);
  static void applyPatch(char *func, const char *patch, const char *end_patch);
  static void *getLibraryHandle(const char *name);
  static void loadMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass);
  static void loadAllMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni);

  static bool initShared(JavaVM *vm);

  static CodeCache* openJvmLibrary();

public:
  static void *_libjvm;
  static void *_libjava;
  static AsyncGetCallTrace _asyncGetCallTrace;
  static JVM_GetManagement _getManagement;

  static bool initLibrary(JavaVM *vm);
  static bool initProfilerBridge(JavaVM *vm, bool attach);

  static jvmtiEnv *jvmti() { return _jvmti; }

  static bool loaded() { return _jvmti != nullptr; }

  static JNIEnv *jni() {
    JNIEnv *jni;
    return _vm->GetEnv((void **)&jni, JNI_VERSION_1_6) == 0 ? jni : NULL;
  }

  static JNIEnv *attachThread(const char *name) {
    JNIEnv *jni;
    JavaVMAttachArgs args = {JNI_VERSION_1_6, (char *)name, NULL};
    return _vm->AttachCurrentThreadAsDaemon((void **)&jni, &args) == 0 ? jni
                                                                       : NULL;
  }

  static void detachThread() { _vm->DetachCurrentThread(); }

  static VMManagement *management() {
    return _getManagement != NULL ? _getManagement(0x20030000) : NULL;
  }

  static int java_version() { return _java_version; }

  static int hotspot_version() { return isHotspot() ? _hotspot_version : -1; }

  static int java_update_version() { return _java_update_version; }

  static bool isOpenJ9() { return _openj9; }
  static bool isHotspot() { return _hotspot; }

  static bool canSampleObjects() { return _can_sample_objects; }

  static bool isZing() { return _zing; }

  static bool isUseAdaptiveGCBoundarySet() {
    return _is_adaptive_gc_boundary_flag_set;
  }

  static void JNICALL VMInit(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread);
  static void JNICALL VMDeath(jvmtiEnv *jvmti, JNIEnv *jni);

  static void JNICALL ClassLoad(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                jclass klass) {
    // Needed only for AsyncGetCallTrace support
  }

  static void JNICALL ClassPrepare(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                   jclass klass) {
    loadMethodIDs(jvmti, jni, klass);
  }

  static jvmtiError JNICALL
  RedefineClassesHook(jvmtiEnv *jvmti, jint class_count,
                      const jvmtiClassDefinition *class_definitions);
  static jvmtiError JNICALL RetransformClassesHook(jvmtiEnv *jvmti,
                                                   jint class_count,
                                                   const jclass *classes);
};

#endif // _VMENTRY_H
