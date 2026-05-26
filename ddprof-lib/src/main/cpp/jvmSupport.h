/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _JVMSUPPORT_H
#define _JVMSUPPORT_H

#include "hotspot/hotspotSupport.h"
#include "stackFrame.h"
#include "stackWalker.h"
#include "vmEntry.h"

// Stack recovery techniques used to workaround AsyncGetCallTrace flaws.
// Can be disabled with 'safemode' option.
enum StackRecovery {
  UNKNOWN_JAVA = (1 << 0),
  POP_STUB = (1 << 1),
  POP_METHOD = (1 << 2),
  LAST_JAVA_PC = (1 << 4),
  GC_TRACES = (1 << 5),
  PROBE_SP = 0x100,
};

class JVMSupport {
    friend class HotspotSupport;

    static int asyncGetCallTrace(ASGCT_CallFrame *frames, int max_depth, void* ucontext);

    // J9 and Zing shared implementation
    static bool loadMethodIDsImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass);

public:
    static int walkJavaStack(StackWalkRequest& request);
    static inline bool canUnwind(const StackFrame& frame, const void*& pc);
    static inline bool isJitCode(const void* pc);

    static void loadAllMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni);
    static bool loadMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass);

    // Resolve method pointer to jmethodID
    static jmethodID resolve(const void* method) {
      if (VM::isHotspot()) {
          return HotspotSupport::resolve(method);
      } else {
          assert(false && "Should not reach here");
          return nullptr;
      }
    }

    // JVMTI callback
    static void JNICALL ClassPrepare(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                   jclass klass);
    static void JNICALL ClassLoad(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                jclass klass);
};

#endif // _JVMSUPPORT_H
