/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.params.provider.ValueSource;

import java.security.MessageDigest;
import java.util.Arrays;
import java.util.zip.Adler32;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Exercises AArch64 runtime-stub unwinding through the precomputed unwind info
 * derived from JVMTI DynamicCodeGenerated ranges (see
 * hotspot/stubUnwindInfo.h). Runs CPU profiling with cstack=vm over workloads
 * that sit in generated stubs -- megamorphic itable/vtable dispatch, arraycopy,
 * and hash/checksum intrinsics -- and verifies that samples landing in those
 * stubs unwind into the calling Java frames instead of failing or truncating.
 */
public class StubUnwindCpuTest extends CStackAwareAbstractProfilerTest {
    public StubUnwindCpuTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        // Wall-clock at 100us gives dense sampling of the registered thread on
        // every platform (CPU itimer sampling is too coarse on macOS); with
        // cstack=vm/vmx every sample is unwound through HotspotSupport::walkVM,
        // which is the path the precomputed stub info serves.
        return isAsan() ? "wall=1ms" : "wall=100us";
    }

    interface Calculator {
        int calculate();
    }

    static class Calculator1 implements Calculator {
        @Override
        public int calculate() {
            return ThreadLocalRandomHolder.random();
        }
    }

    static class Calculator2 implements Calculator {
        @Override
        public int calculate() {
            return ThreadLocalRandomHolder.random();
        }
    }

    static class Calculator3 implements Calculator {
        @Override
        public int calculate() {
            return ThreadLocalRandomHolder.random();
        }
    }

    // Indirection keeps ThreadLocalRandom out of the megamorphic loop's profile
    private static final class ThreadLocalRandomHolder {
        static int random() {
            return java.util.concurrent.ThreadLocalRandom.current().nextInt();
        }
    }

    private static long arraycopyWork(byte[] src, byte[] dst, long acc) {
        for (int i = 0; i < 1000; i++) {
            System.arraycopy(src, 0, dst, 0, src.length);
            acc += dst[0];
        }
        return acc;
    }

    private static long hashWork(MessageDigest md, byte[] data, long acc) {
        for (int i = 0; i < 200; i++) {
            md.update(data);
            acc += md.digest()[0];
        }
        return acc;
    }

    private static long adlerWork(byte[] data, long acc) {
        Adler32 adler = new Adler32();
        for (int i = 0; i < 500; i++) {
            adler.update(data);
            acc += adler.getValue();
            adler.reset();
        }
        return acc;
    }

    private int megamorphicWork(int iterations, Calculator... calculators) {
        int result = 0;
        for (int i = 0; i < iterations; i++) {
            for (Calculator calculator : calculators) {
                result += calculator.calculate();
            }
        }
        return result;
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void testStubUnwinding(@CStack String cstack) throws Exception {
        // HotSpot runtime stubs are the test subject; J9 and Zing do not
        // generate them (and have no '.itable stub()' frames to sample).
        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isZing());
        registerCurrentThreadForWallClockProfiling();
        byte[] data = new byte[4096];
        Arrays.fill(data, (byte) 0x5a);
        byte[] dst = new byte[data.length];
        MessageDigest sha256 = MessageDigest.getInstance("SHA-256");
        MessageDigest md5 = MessageDigest.getInstance("MD5");
        Calculator[] calculators = {new Calculator1(), new Calculator2(), new Calculator3()};

        long acc = 0;
        for (int round = 0; round < 40; round++) {
            acc += megamorphicWork(10_000, calculators);
            acc += arraycopyWork(data, dst, acc);
            acc += hashWork(sha256, data, acc);
            acc += hashWork(md5, data, acc);
            acc += adlerWork(data, acc);
        }
        System.err.println(acc);
        stopProfiler();

        StubScan scan = reduceEvents("datadog.MethodSample", StubScan::new, (s, sample) -> {
            String stackTrace = sample.getStackTraceString();
            if (stackTrace.contains("break_unwind_stub_failed")
                    || stackTrace.contains("break_invalid_framesize")
                    || stackTrace.contains("break_misaligned_sp")) {
                // Only these break frames indicate failed stub unwinding;
                // break_interpreted/break_compiled/etc. are normal walk
                // terminations unrelated to stubs.
                s.sawBreakFrame = true;
                for (String line : stackTrace.split("\n")) {
                    if (line.contains("break_")) {
                        s.breakFrame = line.trim();
                        break;
                    }
                }
            }
            if (stackTrace.contains("StubUnwindCpuTest.megamorphicWork")) {
                s.sawWorkloadFrame = true;
            }
            if (stackTrace.contains(".itable stub()")) {
                s.sawItableStub = true;
                if (stackTrace.contains("StubUnwindCpuTest.megamorphicWork")) {
                    // a Java frame was recovered above the stub frame: the
                    // stub unwound successfully
                    s.sawItableUnwound = true;
                }
            }
            if (stackTrace.contains("sha256_implCompress")
                    || stackTrace.contains("md5_implCompress")
                    || stackTrace.contains("updateBytesAdler32")
                    || stackTrace.contains("base64_encodeBlock")
                    || stackTrace.contains("copy_")) {
                s.sawIntrinsicStub = true;
                if (stackTrace.contains("StubUnwindCpuTest.")) {
                    s.sawIntrinsicUnwound = true;
                }
            }
        });

        // Walked Java frames from the workload prove samples were captured
        // and unwound at all.
        assertTrue(scan.sawWorkloadFrame, "no samples from the workload were captured; scan=" + scan);
        // A failed stub unwind produces an error frame instead of silently
        // corrupting the trace. On aarch64 the precomputed metadata must
        // eliminate error frames for these stubs; other architectures are
        // inert and may still emit break_unwind_stub_failed (observed on
        // Linux x86_64 / JDK 26 baseline) -- report but do not fail.
        if (Platform.isAarch64()) {
            assertTrue(!scan.sawBreakFrame, "unwinding produced an error frame: " + scan);
        } else if (scan.sawBreakFrame) {
            System.err.println("NOTE: legacy stub unwinding error frame (pre-existing): " + scan.breakFrame);
        }

        // itable/vtable stubs: the megamorphic loop must show the stub frame
        // with the calling Java frame above it. Graal compiles megamorphic
        // invokeinterface without the shared itable stub, so no stub frames
        // appear in the profile.
        if (!Platform.isGraal()) {
            assertTrue(scan.sawItableStub, "no itable stub frames seen; scan=" + scan);
            assertTrue(scan.sawItableUnwound, "itable stub did not unwind to a Java frame; scan=" + scan);
        }

        // Intrinsic stubs (hash/checksum/arraycopy): the frame must be
        // visible and unwind to a Java frame where the metadata covers it;
        // gated like the break-frame check since stub sampling is sparse
        // elsewhere.
        if (Platform.isAarch64()) {
            assertTrue(scan.sawIntrinsicStub, "no intrinsic stub frames seen; scan=" + scan);
            assertTrue(scan.sawIntrinsicUnwound,
                    "intrinsic stub did not unwind to a Java frame; scan=" + scan);
        }

        // Precomputed stub unwind info must be in use for unwinding (counters
        // are process-wide, so these are corroboration rather than isolation).
        // classified/unclassified are attach-time statistics: they increment
        // while GenerateEvents replays stub creation during profiler start,
        // and Profiler::start()'s Counters::reset() wipes them afterwards, so
        // only post-start classification survives into the recording. The
        // meaningful in-recording signal is hit vs fallback.
        long hit = getRecordedCounterValue("walkvm_stub_info_hit");
        long fallback = getRecordedCounterValue("walkvm_stub_info_fallback");
        System.err.println("stub info: classified=" + getRecordedCounterValue("walkvm_stub_info_classified")
                + " unclassified=" + getRecordedCounterValue("walkvm_stub_info_unclassified")
                + " hit=" + hit + " fallback=" + fallback);
        if (Platform.isAarch64()) {
            assertTrue(hit > 0,
                    "no unwinds used precomputed stub info");
            assertTrue(fallback < hit,
                    "legacy fallback dominates over precomputed info");
        }
    }

    private static final class StubScan {
        boolean sawBreakFrame;
        String breakFrame;
        boolean sawWorkloadFrame;
        boolean sawItableStub;
        boolean sawItableUnwound;
        boolean sawIntrinsicStub;
        boolean sawIntrinsicUnwound;

        @Override
        public String toString() {
            return "StubScan{sawBreakFrame=" + sawBreakFrame + ", breakFrame=" + breakFrame
                    + ", sawWorkloadFrame=" + sawWorkloadFrame
                    + ", sawItableStub=" + sawItableStub + ", sawItableUnwound=" + sawItableUnwound
                    + ", sawIntrinsicStub=" + sawIntrinsicStub + ", sawIntrinsicUnwound=" + sawIntrinsicUnwound + "}";
        }
    }
}
