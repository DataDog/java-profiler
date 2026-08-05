/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;

/**
 * Wraps a resolved {@code jdk.types.StackTrace} value: {@code {frames: [...], truncated: boolean}}.
 */
public final class JfrStackTrace {
    private final List<JfrFrame> frames;
    private final boolean truncated;

    private static final JfrStackTrace EMPTY = new JfrStackTrace(Collections.emptyList(), false);

    private JfrStackTrace(List<JfrFrame> frames, boolean truncated) {
        this.frames = frames;
        this.truncated = truncated;
    }

    @SuppressWarnings("unchecked")
    static JfrStackTrace of(Object rawStackTrace) {
        if (!(rawStackTrace instanceof Map)) {
            return EMPTY;
        }
        Map<String, Object> map = (Map<String, Object>) rawStackTrace;
        Object framesVal = map.get("frames");
        List<JfrFrame> frames;
        if (framesVal instanceof Object[]) {
            Object[] arr = (Object[]) framesVal;
            frames = new ArrayList<>(arr.length);
            for (Object frame : arr) {
                if (frame instanceof Map) {
                    frames.add(new JfrFrame((Map<String, Object>) frame));
                }
            }
        } else {
            frames = Collections.emptyList();
        }
        Object truncatedVal = map.get("truncated");
        boolean truncated = Boolean.TRUE.equals(truncatedVal);
        return new JfrStackTrace(frames, truncated);
    }

    public List<JfrFrame> frames() {
        return frames;
    }

    public boolean isEmpty() {
        return frames.isEmpty();
    }

    public boolean isTruncated() {
        return truncated;
    }
}
