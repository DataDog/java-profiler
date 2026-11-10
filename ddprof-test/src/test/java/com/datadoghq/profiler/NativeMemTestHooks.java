/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.util.LinkedHashMap;
import java.util.Map;

/** Test bridge for the package-scoped native-memory seams of {@link JavaProfiler}. */
public final class NativeMemTestHooks {
    private NativeMemTestHooks() {}

    /** Live native memory in bytes per NativeMem category name, as of the moment of the call. */
    public static Map<String, Long> liveBytesByCategory() {
        String[] names = JavaProfiler.describeNativeMemCategories0();
        long[] values = JavaProfiler.getNativeMemLive0();
        if (names.length != values.length) {
            throw new IllegalStateException("NativeMem reports " + names.length
                    + " category names but " + values.length + " live values");
        }
        Map<String, Long> live = new LinkedHashMap<>();
        for (int i = 0; i < names.length; i++) {
            live.put(names[i], values[i]);
        }
        return live;
    }
}
