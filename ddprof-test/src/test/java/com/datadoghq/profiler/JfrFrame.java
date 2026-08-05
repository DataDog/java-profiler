/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.util.Map;

/**
 * One frame of a {@link JfrStackTrace}, wrapping a resolved {@code jdk.types.StackFrame} map:
 * {@code {method: {type: {name: {string: ...}}, name: {string: ...}}, lineNumber, bytecodeIndex, type}}.
 */
public final class JfrFrame {
    private final Map<String, Object> value;

    JfrFrame(Map<String, Object> value) {
        this.value = value;
    }

    @SuppressWarnings("unchecked")
    private static String symbolString(Object symbolOrMap) {
        if (symbolOrMap instanceof Map) {
            Object s = ((Map<String, Object>) symbolOrMap).get("string");
            return s != null ? s.toString() : null;
        }
        return symbolOrMap != null ? symbolOrMap.toString() : null;
    }

    @SuppressWarnings("unchecked")
    private Map<String, Object> method() {
        Object m = value.get("method");
        return m instanceof Map ? (Map<String, Object>) m : null;
    }

    /** The frame's method name, or {@code null} if unavailable. */
    public String methodName() {
        Map<String, Object> method = method();
        return method != null ? symbolString(method.get("name")) : null;
    }

    /** The method's descriptor (JVM signature string), or {@code null} if unavailable. */
    public String methodDescriptor() {
        Map<String, Object> method = method();
        return method != null ? symbolString(method.get("descriptor")) : null;
    }

    /** The full name (e.g. {@code java.lang.String}) of the method's declaring type, or {@code null}. */
    @SuppressWarnings("unchecked")
    public String className() {
        Map<String, Object> method = method();
        if (method == null) {
            return null;
        }
        Object type = method.get("type");
        if (!(type instanceof Map)) {
            return null;
        }
        return symbolString(((Map<String, Object>) type).get("name"));
    }
}
