/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

final class NativeAllocHelper {
    static {
        System.loadLibrary("ddproftest");
    }

    static native void nativeMalloc(long size, int count);

    private NativeAllocHelper() {}
}
