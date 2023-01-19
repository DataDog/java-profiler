package com.datadoghq.profiler;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class ContextSetter {

    private static final int TAGS_STORAGE_LIMIT = 10;
    private final List<ConcurrentHashMap<String, Integer>> encodings;
    private final List<String> attributes;
    private final JavaProfiler profiler;

    public ContextSetter(JavaProfiler profiler, List<String> attributes) {
        this.profiler = profiler;
        Set<String> unique = new HashSet<>(attributes);
        this.encodings = new ArrayList<>(unique.size());
        this.attributes = new ArrayList<>(unique.size());
        int i = 0;
        for (String attribute : attributes) {
            if (!unique.remove(attribute)) {
                continue;
            }
            // TODO ask JNI for this info instead to stop it from diverging
            if (i < TAGS_STORAGE_LIMIT) {
                this.attributes.add(attribute);
                encodings.add(new ConcurrentHashMap<>());
                i++;
            }
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
            int encoding = encodings.get(offset)
                    .computeIfAbsent(value, profiler::registerContextValue);
            if (encoding >= 0) {
                profiler.setContextValue(offset, encoding);
                return true;
            }
        }
        return false;
    }

    public boolean clearContextValue(String attribute) {
        return clearContextValue(offsetOf(attribute));
    }

    public boolean clearContextValue(int offset) {
        if (offset >= 0) {
            profiler.setContextValue(offset, 0);
            return true;
        }
        return false;
    }
}
