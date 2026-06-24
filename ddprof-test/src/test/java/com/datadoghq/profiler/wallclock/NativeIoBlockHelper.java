package com.datadoghq.profiler.wallclock;

final class NativeIoBlockHelper {
    static {
        System.loadLibrary("ddproftest");
    }

    static native void blockingAccept4(int delayMillis);

    static native void blockingPpoll(int delayMillis);

    static native void blockingPselect(int delayMillis);

    static native void blockingEpollWait(int delayMillis);

    static native void blockingEpollPwait(int delayMillis);

    private NativeIoBlockHelper() {}
}
