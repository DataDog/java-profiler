package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.Platform;

public class JvmtiBasedWallClockThreadFilterTest extends WallClockThreadFilterTest {
    @Override
    protected boolean isPlatformSupported() {
        // Liveness tracking requires Java 11+ and specific JVM types
        return Platform.isJ9();
    }

    @Override
    protected String getProfilerCommand() {
        return super.getProfilerCommand() + ";wallsampler=jvmti";
    }
}