/*
 * Copyright 2025, 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _PROFILERVMSTRUCTSEXT_H
#define _PROFILERVMSTRUCTSEXT_H

#include <jni.h>
#include <jvmti.h>
#include <stdint.h>
#include "jvmHeap.h"

class HeapUsage {
  private:
    static bool is_jmx_attempted;
    static bool is_jmx_supported;

  public:
    size_t _initSize = -1;
    size_t _used = -1;
    size_t _committed = -1;
    size_t _maxSize = -1;
    size_t _used_at_last_gc = -1;

    static void initJMXUsage(JNIEnv* env);
    static bool isJMXSupported();
    static bool isLastGCUsageSupported();
    static bool needsNativeBindingInterception();
    static jlong getMaxHeap(JNIEnv* env);
    static HeapUsage get();
    static HeapUsage get(bool allow_jmx);
};

class ProfilerVMStructsExt {
  public:
    static void init();
    static void initCriticalJNINatives();
    static void patchSafeFetch();
    static bool isSafeToWalk(uintptr_t pc);
    static void JNICALL NativeMethodBind(jvmtiEnv* jvmti, JNIEnv* jni,
                                         jthread thread, jmethodID method,
                                         void* address, void** new_address_ptr);

  private:
    typedef HeapUsage (*HeapUsageFunc)(const void*);
    typedef void* (*MemoryUsageFunc)(void*, void*, bool);
    typedef GCHeapSummary (*GCHeapSummaryFunc)(void*);

    static HeapUsageFunc _heap_usage_func;
    static MemoryUsageFunc _memory_usage_func;
    static GCHeapSummaryFunc _gc_heap_summary_func;

    static const void* findHeapUsageFunc();
    static void checkNativeBinding(jvmtiEnv* jvmti, JNIEnv* jni,
                                   jmethodID method, void* address);

    friend class HeapUsage;
};

#endif // _PROFILERVMSTRUCTSEXT_H
