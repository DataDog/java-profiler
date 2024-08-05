package com.datadoghq.profiler.wallclock;

public class JvmtiBasedWallclockThreadFilterTest extends WallclockThreadFilterTest {

    @Override
    protected String getProfilerCommand() {
        return super.getProfilerCommand() + ";wallsampler=jvmti";
    }
}
