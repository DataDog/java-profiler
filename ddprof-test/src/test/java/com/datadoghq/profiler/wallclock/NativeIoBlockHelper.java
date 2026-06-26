package com.datadoghq.profiler.wallclock;

final class NativeIoBlockHelper {
    static {
        System.loadLibrary("ddproftest");
    }

    static native long blockingAccept4(int delayMillis);

    static native long blockingPpoll(int delayMillis);

    static native long blockingPselect(int delayMillis);

    static native long blockingEpollWait(int delayMillis);

    static native long blockingEpollPwait(int delayMillis);

    private NativeIoBlockHelper() {}
}
