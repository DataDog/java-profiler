package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.Platform;

public class JvmtiBasedWallClockThreadFilterTest extends WallClockThreadFilterTest {
    @Override
    protected boolean isPlatformSupported() {
        return Platform.isJ9();
    }

    @Override
    protected String getProfilerCommand() {
        return super.getProfilerCommand() + ";wallsampler=jvmti";
    }
}