/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

/** JNI workloads that block in Linux APIs not exposed directly by the Java standard library. */
final class NativeIoBlockHelper {
    static {
        System.loadLibrary("ddproftest");
    }

    /** Blocks in {@code accept4} and returns the expected native blocker encoding. */
    static native long blockingAccept4(int delayMillis);

    /** Blocks in {@code ppoll} and returns the expected native blocker encoding. */
    static native long blockingPpoll(int delayMillis);

    /** Blocks in {@code pselect} and returns the expected native blocker encoding. */
    static native long blockingPselect(int delayMillis);

    /** Blocks in {@code epoll_wait} and returns the expected native blocker encoding. */
    static native long blockingEpollWait(int delayMillis);

    /** Blocks in {@code epoll_pwait} and returns the expected native blocker encoding. */
    static native long blockingEpollPwait(int delayMillis);

    private NativeIoBlockHelper() {}
}
