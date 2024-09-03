package com.datadoghq.profiler.wallclock;

public class JvmtiBasedContextWallClockTest extends ContextWallClockTest {

    @Override
    protected String getProfilerCommand() {
        return super.getProfilerCommand() + ";wallsampler=jvmti";
    }
}