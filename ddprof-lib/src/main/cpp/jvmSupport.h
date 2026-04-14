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


class JVMSupport {
    static int asyncGetCallTrace(ASGCT_CallFrame *frames, int max_depth, void* ucontext);
public:
    static int walkJavaStack(StackWalkRequest& request);
    static inline bool canUnwind(const void*& pc);
    static inline bool isJitCode(const void* pc);
};

#endif // _JVMSUPPORT_H
