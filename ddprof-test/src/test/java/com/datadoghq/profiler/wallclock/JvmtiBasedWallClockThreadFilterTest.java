package com.datadoghq.profiler.wallclock;

public class JvmtiBasedWallClockThreadFilterTest extends WallClockThreadFilterTest {

    @Override
    protected String getProfilerCommand() {
        return super.getProfilerCommand() + ";wallsampler=jvmti";
    }
}