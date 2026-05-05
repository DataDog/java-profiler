/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <jni.h>
#include <stdlib.h>

/* Drive malloc through libddproftest.so's PLT, which is patched by MallocTracer.
 * ByteBuffer.allocateDirect() routes through libjvm.so which may use -Bsymbolic-functions,
 * binding malloc internally and bypassing GOT patching entirely. */
JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_nativemem_NativeAllocHelper_nativeMalloc(
    JNIEnv *env, jclass clazz, jlong size, jint count) {
    for (jint i = 0; i < count; i++) {
        void *p = malloc((size_t)size);
        if (p != NULL) {
            free(p);
        }
    }
}
