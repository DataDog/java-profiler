package com.datadoghq.profiler;

public class ContextAttribute {
    final int provenance;
    final int offset;
    final int encoding;
    private final CharSequence name;

    public ContextAttribute(int provenance, int offset, int encoding, CharSequence name) {
        this.provenance = provenance;
        this.offset = offset;
        this.encoding = encoding;
        this.name = name;
    }

    public CharSequence getName() {
        return name;
    }
}
