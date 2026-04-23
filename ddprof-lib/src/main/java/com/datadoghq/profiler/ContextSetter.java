package com.datadoghq.profiler;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class ContextSetter {

    private static final int TAGS_STORAGE_LIMIT = 10;
    private final List<String> attributes;
    private final JavaProfiler profiler;

    public ContextSetter(JavaProfiler profiler, List<String> attributes) {
        this.profiler = profiler;
        Set<String> unique = new HashSet<>(attributes);
        this.attributes = new ArrayList<>(unique.size());
        for (int i = 0; i < Math.min(attributes.size(), TAGS_STORAGE_LIMIT); i++) {
            String attribute = attributes.get(i);
            if (unique.remove(attribute)) {
                this.attributes.add(attribute);
            }
        }
    }

    public int[] snapshotTags() {
        int[] snapshot = new int[attributes.size()];
        snapshotTags(snapshot);
        return snapshot;
    }

    public void snapshotTags(int[] snapshot) {
        if (snapshot.length <= attributes.size()) {
            profiler.copyTags(snapshot);
        }
    }

    public int offsetOf(String attribute) {
        return attributes.indexOf(attribute);
    }

    public boolean setContextValue(String attribute, String value) {
        return setContextValue(offsetOf(attribute), value);
    }

    public boolean setContextValue(int offset, String value) {
        if (offset >= 0) {
            return profiler.setContextAttribute(offset, value);
        }
        return false;
    }

    /**
     * Returns the string value currently set at the given attribute offset on this thread,
     * or {@code null} if no value is set or the offset is negative.
     *
     * <p>Reads from thread-local storage — caller and setter must be the same thread.
     */
    public String readContextValue(int offset) {
        if (offset >= 0) {
            return profiler.readContextAttribute(offset);
        }
        return null;
    }

    /**
     * Reads the current value of the named context attribute.
     * Resolves the attribute name to its registered offset via {@link #offsetOf(String)},
     * then delegates to {@link #readContextValue(int)}. Returns {@code null} if the
     * attribute was not set or the name is not registered.
     *
     * <p>Reads from thread-local storage — caller and setter must be the same thread.
     *
     * @param attribute the attribute name
     * @return the current value, or null if absent or unregistered
     */
    public String readContextValue(String attribute) {
        return readContextValue(offsetOf(attribute));
    }

    public boolean clearContextValue(String attribute) {
        return clearContextValue(offsetOf(attribute));
    }

    public boolean clearContextValue(int offset) {
        if (offset >= 0) {
            profiler.clearContextAttribute(offset);
            return true;
        }
        return false;
    }
}
