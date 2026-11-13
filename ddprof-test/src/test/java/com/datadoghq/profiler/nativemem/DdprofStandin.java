/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

/**
 * Test double for the ddprof hook-owner image, living inside
 * {@code libddproftest}: the library exports the ddprof marker names (with
 * call counters) and the JNI entry points save, rewrite and restore the
 * profiler's own allocation GOT slots to stand-in forwarding hooks, the way
 * the real ddprof would. Production code never calls this class; only Linux
 * child-JVM tests do. The native entry points are Linux-only: the library
 * builds everywhere, but {@code install()}/{@code restore()} link only on
 * Linux and must not be called elsewhere.
 */
final class DdprofStandin {
    static {
        System.loadLibrary("ddproftest");
    }

    // Rewrites the profiler's own allocation GOT slots to stand-in
    // forwarding hooks. Returns 0 on success, -1 when the profiler image or
    // its relocations could not be inspected.
    static native int install();

    // Restores the saved allocation GOT slot values. Returns 0 on success.
    static native int restore();

    // Times the two marker functions were called. The admission check must
    // never call a marker, so tests assert these stay 0 across it.
    static native long startMarkerCalls();

    static native long stopMarkerCalls();

    private DdprofStandin() {}
}
