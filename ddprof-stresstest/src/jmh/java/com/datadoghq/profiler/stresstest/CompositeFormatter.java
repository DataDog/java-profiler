package com.datadoghq.profiler.stresstest;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class CompositeFormatter implements Formatter {
    private final Set<Formatter> formatters = new HashSet<>();

    public static Formatter of(Formatter formatter, Formatter ... formatters) {
        return new CompositeFormatter(formatter, formatters);
    }

    private CompositeFormatter(Formatter formatter, Formatter ... formatters) {
        this.formatters.add(formatter);
        this.formatters.addAll(Arrays.asList(formatters));
    }

    @Override
    public void format() {
        formatters.forEach(Formatter::format);
    }
}
