/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__

#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <jni.h>

// A native thread that names itself with raw bytes and burns CPU until stopped, so a profiler
// that reads its name from /proc at dump time records it.
typedef struct {
    pthread_t thread;
    char name[16];  // the kernel's limit, including the terminator
    volatile int running;
} NamedSpinner;

static void spin_until_stopped(volatile int *running) {
    volatile unsigned long x = 0;
    while (__atomic_load_n(running, __ATOMIC_ACQUIRE)) {
        x++;
    }
}

static void *named_spinner_main(void *arg) {
    NamedSpinner *spinner = (NamedSpinner *)arg;
    pthread_setname_np(pthread_self(), spinner->name);
    spin_until_stopped(&spinner->running);
    return NULL;
}

JNIEXPORT jlong JNICALL Java_com_datadoghq_profiler_nativethread_NamedNativeThread_start0(
    JNIEnv *env, jclass clz, jbyteArray name) {
    NamedSpinner *spinner = calloc(1, sizeof(NamedSpinner));
    if (spinner == NULL) {
        return 0;
    }
    jsize length = (*env)->GetArrayLength(env, name);
    if (length > (jsize)sizeof(spinner->name) - 1) {
        length = (jsize)sizeof(spinner->name) - 1;
    }
    (*env)->GetByteArrayRegion(env, name, 0, length, (jbyte *)spinner->name);
    __atomic_store_n(&spinner->running, 1, __ATOMIC_RELEASE);
    if (pthread_create(&spinner->thread, NULL, named_spinner_main, spinner) != 0) {
        free(spinner);
        return 0;
    }
    return (jlong)(intptr_t)spinner;
}

JNIEXPORT void JNICALL Java_com_datadoghq_profiler_nativethread_NamedNativeThread_stop0(
    JNIEnv *env, jclass clz, jlong handle) {
    NamedSpinner *spinner = (NamedSpinner *)(intptr_t)handle;
    __atomic_store_n(&spinner->running, 0, __ATOMIC_RELEASE);
    pthread_join(spinner->thread, NULL);
    free(spinner);
}

#endif
