/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#define _GNU_SOURCE
#include <jni.h>

#if defined(__linux__)
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

static void wait_control_failure(JNIEnv *env, const char *message) {
    jclass error = (*env)->FindClass(env, "java/lang/IllegalStateException");
    if (error != NULL) {
        (*env)->ThrowNew(env, error, message);
        (*env)->DeleteLocalRef(env, error);
    }
}

JNIEXPORT jlong JNICALL
Java_com_datadoghq_profiler_NativeWaitTestSupport_signalMask(JNIEnv *env, jclass cls) {
    sigset_t mask;
    if (pthread_sigmask(SIG_SETMASK, NULL, &mask) != 0) {
        wait_control_failure(env, "cannot read worker signal mask");
        return 0;
    }
    uint64_t bits = 0;
    for (int signal = 1; signal < NSIG; signal++) {
        if (sigismember(&mask, signal) == 1) bits |= UINT64_C(1) << (signal - 1);
    }
    return (jlong)bits;
}

JNIEXPORT jlong JNICALL
Java_com_datadoghq_profiler_NativeWaitTestSupport_profilingSignalMask(JNIEnv *env, jclass cls) {
    return (jlong)((UINT64_C(1) << (SIGPROF - 1)) | (UINT64_C(1) << (SIGVTALRM - 1)));
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_NativeWaitTestSupport_withProfilingSignalsBlocked0(
        JNIEnv *env, jclass cls, jobject callback) {
    jclass type = (*env)->GetObjectClass(env, callback);
    if (type == NULL) return;
    jmethodID run = (*env)->GetMethodID(env, type, "run", "()V");
    (*env)->DeleteLocalRef(env, type);
    if (run == NULL) return;
    sigset_t blocked, saved;
    sigemptyset(&blocked);
    sigaddset(&blocked, SIGPROF);
    sigaddset(&blocked, SIGVTALRM);
    if (pthread_sigmask(SIG_BLOCK, &blocked, &saved) != 0) {
        wait_control_failure(env, "cannot block profiling signals");
        return;
    }
    /* C cannot use an RAII guard; the single callback return, including a pending
     * Java exception, passes through this same-thread restoration. */
    (*env)->CallVoidMethod(env, callback, run);
    if (pthread_sigmask(SIG_SETMASK, &saved, NULL) != 0) {
        (*env)->FatalError(env, "cannot restore worker signal mask");
    }
}

static volatile sig_atomic_t wait_signal_delivered;

static void interrupt_wait(int signal) {
    __atomic_store_n(&wait_signal_delivered, 1, __ATOMIC_RELEASE);
}

static uint64_t monotonic_nanos(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint64_t)now.tv_sec * UINT64_C(1000000000) + now.tv_nsec;
}

JNIEXPORT void JNICALL
Java_com_datadoghq_profiler_NativeWaitTestSupport_interruptWait(JNIEnv *env, jclass cls, jint tid) {
    if (tid <= 0) {
        wait_control_failure(env, "expected a positive worker tid");
        return;
    }
    struct sigaction saved, action = {0};
    if (sigaction(SIGWINCH, NULL, &saved) != 0 ||
        (saved.sa_handler != SIG_DFL && saved.sa_handler != SIG_IGN)) {
        wait_control_failure(env, "SIGWINCH is not available for the isolated wait control");
        return;
    }
    action.sa_handler = interrupt_wait;
    sigemptyset(&action.sa_mask);
    __atomic_store_n(&wait_signal_delivered, 0, __ATOMIC_RELEASE);
    if (sigaction(SIGWINCH, &action, NULL) != 0) {
        wait_control_failure(env, "cannot install wait interruption handler");
        return;
    }
    /* The isolated child's sole controller owns this process-wide handler.
     * C centralizes restoration so send failure and delivery timeout also release it. */
    int sent = syscall(SYS_tgkill, getpid(), tid, SIGWINCH) == 0;
    uint64_t deadline = monotonic_nanos() + UINT64_C(5000000000);
    while (sent && !__atomic_load_n(&wait_signal_delivered, __ATOMIC_ACQUIRE) &&
           monotonic_nanos() < deadline) {
        struct timespec pause = {0, 1000000};
        nanosleep(&pause, NULL);
    }
    int delivered = __atomic_load_n(&wait_signal_delivered, __ATOMIC_ACQUIRE);
    if (sigaction(SIGWINCH, &saved, NULL) != 0) {
        (*env)->FatalError(env, "cannot restore wait interruption handler");
    }
    if (!sent || !delivered) wait_control_failure(env, "targeted wait interruption was not delivered");
}
#endif
