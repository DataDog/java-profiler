package com.datadoghq.profiler;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class ContextSetter {

    private static final MethodHandle IMMUTABLE_COPY = findCopyOf();
    private final List<ConcurrentHashMap<String, Integer>> encodings;
    private final Map<String, ContextAttribute> registration;
    private final JavaProfiler profiler;

    public ContextSetter(JavaProfiler profiler, List<String> attributes) {
        this.profiler = profiler;
        Set<String> unique = new HashSet<>(attributes);
        encodings = new ArrayList<>(unique.size());
        Map<String, ContextAttribute> registration = new HashMap<>();
        for (String attribute : attributes) {
            if (!unique.remove(attribute)) {
                continue;
            }
            ContextAttribute contextAttribute = profiler.registerContextAttribute(attribute);
            if (contextAttribute != null) {
                registration.put(attribute, contextAttribute);
                encodings.add(new ConcurrentHashMap<>());
            }
        }
        this.registration = tryMakeImmutable(registration);
    }

    public boolean setContextValue(String attribute, String value) {
        ContextAttribute contextAttribute = registration.get(attribute);
        if (contextAttribute != null) {
            int encoding = encodings.get(contextAttribute.offset)
                    .computeIfAbsent(value, profiler::registerContextValue);
            if (encoding >= 0) {
                profiler.setContextValue(contextAttribute, encoding);
                return true;
            }
        }
        return false;
    }

    @SuppressWarnings("unchecked")
    private static Map<String, ContextAttribute> tryMakeImmutable(Map<String, ContextAttribute> map) {
        try {
            return IMMUTABLE_COPY == null ? map : (Map<String, ContextAttribute>) IMMUTABLE_COPY.invokeExact(map);
        } catch (Throwable ignore) {
            return map;
        }
    }

    private static MethodHandle findCopyOf() {
        try {
            return MethodHandles.lookup().findStatic(Map.class, "copyOf",
                    MethodType.methodType(Map.class, Map.class));
        } catch (NoSuchMethodException | IllegalAccessException ignore) {
        }
        return null;
    }
}
