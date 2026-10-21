/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/**
 * Describes the native library build the tests run against, as passed by the test task in the
 * {@code ddprof_test.config} system property (the build configuration name, e.g. {@code release},
 * {@code debug}, {@code asan}, {@code coverage}).
 */
public final class NativeBuildConfig {
    private NativeBuildConfig() {}

    /** The build configuration name, or {@code null} when the property is not set. */
    public static String name() {
        return System.getProperty("ddprof_test.config");
    }

    /**
     * Whether the library is an unoptimized {@code -O0 -DDEBUG} build without a sanitizer:
     * {@code debug}, or {@code coverage} (the debug build with gcov instrumentation added).
     * Debug-only code paths (e.g. {@code datadog.UnwindFailure} recording) are compiled in, and
     * unwinding is several times slower than in the release build.
     */
    public static boolean isDebug() {
        String config = name();
        return "debug".equals(config) || "coverage".equals(config);
    }
}
