/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _JVMSUPPORT_H
#define _JVMSUPPORT_H

#include "stackFrame.h"
#include "stackWalker.h"

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

class HotspotSupport;

class JVMSupport {
    enum JMethodIDLoadStats {
        No_loaded,          // Has not yet executed any profiling command, no jmethodIDs are loaded
        Partial_loaded,     // Partially loaded, see HotspotSupport::shouldPreloadJmethodIDs()
        Fully_loaded        // All jmethodIDs are loaded
    };

    friend class HotspotSupport;

    static volatile JMethodIDLoadStats jmethodID_load_state;

    static int asyncGetCallTrace(ASGCT_CallFrame *frames, int max_depth, void* ucontext);
    // J9 and Zing shared implementation, load jmethodIDs of the method unconditionally.
    static bool loadMethodIDsImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass);

    static JMethodIDLoadStats getLoadState();
    static void setLoadState(JMethodIDLoadStats state);
public:
    // Initializing JVM support
    static void initExecution(Arguments& args, jvmtiEnv* jvmti, JNIEnv* jni);

    static int walkJavaStack(StackWalkRequest& request);
    static inline bool canUnwind(const StackFrame& frame, const void*& pc);
    static inline bool isJitCode(const void* pc);

    static void loadAllMethodIDsIfNeeded(jvmtiEnv *jvmti, JNIEnv *jni);
    static bool loadMethodIDsIfNeeded(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass);

    // Resolve method pointer to jmethodID
    static inline jmethodID resolve(const void* method);

    // If a class is hidden class
    static inline bool isHidden(jint modifiers);
};

#endif // _JVMSUPPORT_H
