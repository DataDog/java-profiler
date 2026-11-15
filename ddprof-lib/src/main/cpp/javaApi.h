/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _JAVA_API_H
#define _JAVA_API_H

#include <jvmti.h>

// Shared declarations for the blocking hooks exercised directly by native tests.
// Keep the implementation and callers on the same JNI ABI.
extern "C" {
JNIEXPORT jlong JNICALL Java_com_datadoghq_profiler_JavaProfiler_blockEnter0(
    JNIEnv*, jclass, jboolean, jint);
JNIEXPORT void JNICALL Java_com_datadoghq_profiler_JavaProfiler_blockExit0(
    JNIEnv*, jclass, jboolean, jlong, jlong, jlong);
JNIEXPORT jboolean JNICALL Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(
    JNIEnv*, jclass, jthread, jboolean);
JNIEXPORT void JNICALL Java_com_datadoghq_profiler_JavaProfiler_parkExit0(
    JNIEnv*, jclass, jthread, jboolean, jlong, jlong);
JNIEXPORT jlong JNICALL Java_com_datadoghq_profiler_JavaProfiler_beginTaskBlock0(
    JNIEnv*, jclass, jthread);
JNIEXPORT jboolean JNICALL Java_com_datadoghq_profiler_JavaProfiler_endTaskBlock0(
    JNIEnv*, jclass, jthread, jlong, jlong, jlong);
}

#endif // _JAVA_API_H
