package com.datadoghq.profiler;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class ContextSetter {

    private static final int TAGS_STORAGE_LIMIT = 10;
    private final List<String> attributes;
    private final JavaProfiler profiler;

    private final ConcurrentHashMap<String, Integer> jniCache = new ConcurrentHashMap<>();

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

    public int encode(String key) {
        if (key != null) {
            Integer encoding = jniCache.get(key);
            if (encoding != null) {
                return encoding;
            } else if (jniCache.size() <= 1 << 16) {
                int e = profiler.registerConstant(key);
                if (e > 0 && jniCache.putIfAbsent(key, e) == null) {
                    return e;
                }
            }
        }
        return 0;
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
            int encoding = encode(value);
            if (encoding >= 0) {
                setContextValue(offset, encoding);
                return true;
            }
        }
        return false;
    }

    public boolean setContextValue(int offset, int encoding) {
        if (offset >= 0 && encoding >= 0) {
            profiler.setContextValue(offset, encoding);
            return true;
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
