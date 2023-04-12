package com.datadoghq.profiler;

public class MoreAssertions {

    public static final int DICTIONARY_PAGE_SIZE = (128 * (3 * 8 + 8) + 4);

    public static void assertBoundedBy(long value, long maximum, String error) {
        if (value >= maximum) {
            throw new AssertionError(error + ". Too large: " + value + " > " + maximum);
        }
    }
}
