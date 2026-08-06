/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.util.Map;
import java.util.Objects;

/**
 * One parsed JFR event: a type name plus its fully-resolved field map (no jafar
 * {@code ComplexType}/{@code ArrayType} wrappers remain — {@link JfrEvents} resolves them eagerly
 * at load time via {@code Values.resolvedDeep()}, so every nested value here is a plain
 * {@code Map}/{@code Object[]}/boxed-primitive/{@code String}).
 *
 * <p>Numeric fields annotated {@code @Timestamp(TICKS)}/{@code @Timespan(TICKS)} (the standard JDK
 * convention, used for e.g. {@code startTime}/{@code duration}) are already normalized to epoch/duration
 * nanoseconds by jafar's parser before this class ever sees them — see
 * {@code io.jafar.parser.impl.TemporalNormalizer}. Fields with an explicit non-TICKS unit
 * (e.g. this profiler's own {@code cpuInterval}/{@code wallInterval}, annotated
 * {@code @Timespan("MILLISECONDS")}) are left as the raw value in that already-correct unit.
 */
public final class JfrEvent {
    private final String typeName;
    private final Map<String, Object> value;

    JfrEvent(String typeName, Map<String, Object> value) {
        this.typeName = typeName;
        this.value = value;
    }

    public String typeName() {
        return typeName;
    }

    /** Escape hatch: the raw, fully-resolved field map for this event. */
    public Map<String, Object> raw() {
        return value;
    }

    /** The raw field value at {@code field}, or {@code null} if absent. */
    public Object get(String field) {
        return value.get(field);
    }

    public boolean has(String field) {
        return value.containsKey(field);
    }

    public String getString(String field) {
        Object v = value.get(field);
        return v != null ? v.toString() : null;
    }

    /**
     * The name of a constant-pool-referenced enum-like type (e.g. this profiler's
     * {@code jdk.types.ThreadState}/{@code datadog.types.ExecutionMode} fields {@code state}/
     * {@code mode}). {@link JfrEvents#load} already collapses these single-field wrapper types to
     * their scalar value, so this is just {@link #getString(String)} under a name that documents
     * intent at enum-like call sites.
     */
    public String getEnumName(String field) {
        return getString(field);
    }

    /** Boxed so callers can distinguish "field absent" (null) from a real 0. */
    public Long getLong(String field) {
        Object v = value.get(field);
        return v instanceof Number ? ((Number) v).longValue() : null;
    }

    public long getLong(String field, long defaultValue) {
        Long v = getLong(field);
        return v != null ? v : defaultValue;
    }

    public Double getDouble(String field) {
        Object v = value.get(field);
        return v instanceof Number ? ((Number) v).doubleValue() : null;
    }

    public double getDouble(String field, double defaultValue) {
        Double v = getDouble(field);
        return v != null ? v : defaultValue;
    }

    public Boolean getBoolean(String field) {
        Object v = value.get(field);
        return v instanceof Boolean ? (Boolean) v : null;
    }

    /**
     * Converts a nanosecond field (e.g. a {@code @Timestamp(TICKS)}-normalized {@code startTime},
     * or a {@code @Timespan(TICKS)}-normalized {@code duration}) to epoch/duration milliseconds.
     * Returns {@code null} if the field is absent.
     */
    public Long getNanosAsMillis(String field) {
        Long nanos = getLong(field);
        return nanos != null ? nanos / 1_000_000L : null;
    }

    /** The stack trace at {@code field} (default: {@code "stackTrace"}), never {@code null} (empty if absent). */
    public JfrStackTrace getStackTrace() {
        return getStackTrace("stackTrace");
    }

    public JfrStackTrace getStackTrace(String field) {
        return JfrStackTrace.of(value.get(field));
    }

    /**
     * The stack trace at {@code field} (default: {@code "stackTrace"}) formatted as one
     * newline-joined string, one {@code className.methodName()} call-site per frame — for
     * substring pattern matching against expected frames, matching how tests used JMC's
     * {@code JdkAttributes.STACK_TRACE_STRING} synthetic attribute.
     *
     * <p>{@code Lookup::fillNativeMethodInfo} (flightRecorder.cpp) gives every native/stub frame
     * (e.g. {@code vtable stub}/{@code itable stub}) an explicit empty-string class, never a
     * missing one — so the dot is printed whenever a class field is present at all, even if its
     * name is empty, producing e.g. {@code .vtable stub()} to match what tests substring-match
     * against. Only a truly absent class (no {@code type} field/map, {@link JfrFrame#className()}
     * returns {@code null}) skips the dot. The trailing {@code ()} is likewise always appended,
     * even though the raw JFR method name never includes it (confirmed via jafar MCP inspection
     * of a real recording: the vtable-stub frame's name is literally {@code "vtable stub"}).
     */
    public String getStackTraceString() {
        return getStackTraceString("stackTrace");
    }

    public String getStackTraceString(String field) {
        // Mirrors IMemberAccessor.getMember()'s null-on-absent contract: some events
        // (e.g. lightweight-mode CPU samples) have no stackTrace field at all, which
        // callers distinguish from "present but empty" via a null check.
        if (!has(field)) {
            return null;
        }
        StringBuilder sb = new StringBuilder();
        for (JfrFrame frame : getStackTrace(field).frames()) {
            String className = frame.className();
            String methodName = frame.methodName();
            if (className != null) {
                sb.append(className).append('.');
            }
            sb.append(methodName != null ? methodName : "").append("()\n");
        }
        return sb.toString();
    }

    /**
     * The name of a JFR thread-reference field (e.g. {@code "eventThread"}), preferring
     * {@code osName} (what this profiler's own attribution and most JDK events key on) and
     * falling back to {@code javaName}. Returns {@code null} if the field/thread is absent.
     */
    @SuppressWarnings("unchecked")
    public String getThreadName(String field) {
        Object t = value.get(field);
        if (!(t instanceof Map)) {
            return null;
        }
        Map<String, Object> thread = (Map<String, Object>) t;
        Object osName = thread.get("osName");
        if (osName != null && !osName.toString().isEmpty()) {
            return osName.toString();
        }
        Object javaName = thread.get("javaName");
        return javaName != null ? javaName.toString() : null;
    }

    /**
     * The Java thread id of a JFR thread-reference field, or {@code null} if the field/thread
     * is absent.
     */
    @SuppressWarnings("unchecked")
    public Long getThreadJavaId(String field) {
        Object t = value.get(field);
        if (!(t instanceof Map)) {
            return null;
        }
        Object id = ((Map<String, Object>) t).get("javaThreadId");
        return id instanceof Number ? ((Number) id).longValue() : null;
    }

    /**
     * The full name (e.g. {@code java.lang.String}) of a JFR class-reference field
     * (e.g. {@code "objectClass"}, {@code "task"}), or {@code null} if the field/class is absent.
     */
    @SuppressWarnings("unchecked")
    public String getClassName(String field) {
        Object c = value.get(field);
        if (!(c instanceof Map)) {
            return null;
        }
        Object name = ((Map<String, Object>) c).get("name");
        String s;
        if (name instanceof Map) {
            Object v = ((Map<String, Object>) name).get("string");
            s = v != null ? v.toString() : null;
        } else {
            s = name != null ? name.toString() : null;
        }
        return s != null ? s.replace('/', '.') : null;
    }

    @Override
    public String toString() {
        return "JfrEvent{" + typeName + ", " + value + '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof JfrEvent)) return false;
        JfrEvent other = (JfrEvent) o;
        return typeName.equals(other.typeName) && value.equals(other.value);
    }

    @Override
    public int hashCode() {
        return Objects.hash(typeName, value);
    }
}
