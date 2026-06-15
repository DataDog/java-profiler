package com.datadoghq.profiler;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class ContextSetter {

    // Must equal ThreadContext.MAX_CUSTOM_SLOTS — both cap the same physical slot range.
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
        if (snapshot.length >= attributes.size()) {
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
     * Re-applies attribute values from precomputed constant IDs and UTF-8 bytes, indexed by slot
     * (as produced by {@link #snapshotTags(int[])}). Restores both the DD sidecar encoding and the
     * OTEP attrs_data value for every slot whose constantId is {@code > 0}, in a single atomic
     * publish — no String allocation, hashing, or cache lookup. Intended for re-applying
     * application-managed context after a {@code setContext} span activation wipes the slots.
     */
    public boolean setContextValuesByIdAndBytes(int[] constantIds, byte[][] utf8) {
        return profiler.setContextAttributesByIdAndBytes(constantIds, utf8);
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
