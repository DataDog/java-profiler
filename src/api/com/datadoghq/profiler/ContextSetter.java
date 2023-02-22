package com.datadoghq.profiler;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class ContextSetter {

    private static final int TAGS_STORAGE_LIMIT = 10;
    private final List<ConcurrentHashMap<String, Integer>> encodings;

    private final AtomicInteger dictionaryCode = new AtomicInteger();
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

    @Deprecated()
    public boolean setContextValue(int offset, String value) {
        if (offset >= 0) {
            int encoding = encodings.get(offset)
                    .computeIfAbsent(value, newKey -> {
                        int ordinal = dictionaryCode.incrementAndGet();
                        profiler.registerConstant(newKey, ordinal);
                        return ordinal;
                    });
            if (encoding >= 0) {
                profiler.setContextValue(offset, encoding);
                return true;
            }
        }
        return false;
    }

    public void registerContextValue(CharSequence key, int encoding) {
        assert dictionaryCode.get() == 0 : "detected deprecated method being used alongside external constant registration";
        profiler.registerConstant(key.toString(), encoding);
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
