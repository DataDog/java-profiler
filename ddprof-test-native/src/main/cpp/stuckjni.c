/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <jni.h>
#include <stdio.h>
#include <unistd.h>

// Test-only nonreturn injection. Only an independently owned JVM may invoke it.
JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_wallclock_TimedNativeWorkerTest_00024Child_waitForever(
    JNIEnv* env, jclass klass) {
    (void)env;
    (void)klass;
    puts("JNI_WORKER_ENTERED");
    fflush(stdout);
    for (;;) {
        pause();
    }
}
