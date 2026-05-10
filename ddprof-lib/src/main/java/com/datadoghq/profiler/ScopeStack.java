/*
 * Copyright 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
package com.datadoghq.profiler;

import java.util.Arrays;

/**
 * Per-thread stack of {@link ThreadContext} snapshots for nested scopes.
 *
 * <p>Provides bulk save/restore of the full OTEP record + sidecar state via one memcpy per
 * transition. Not thread-safe: a single stack instance must be accessed only from its
 * owning thread.
 *
 * <p>Storage is tiered to keep shallow nesting allocation-free:
 * <ul>
 *   <li>Depths 0 .. {@value #FAST_DEPTH}-1: one contiguous byte[] allocated eagerly.</li>
 *   <li>Depths {@value #FAST_DEPTH} and beyond: lazily allocated {@value #CHUNK_DEPTH}-slot
 *       chunks, each a single byte[]. Chunks are allocated once per depth band and reused.</li>
 * </ul>
 */
public final class ScopeStack {
    private static final int FAST_DEPTH = 6;
    private static final int CHUNK_DEPTH = 12;
    private static final int SLOT_SIZE = ThreadContext.SNAPSHOT_SIZE;

    private final byte[] fast = new byte[FAST_DEPTH * SLOT_SIZE];
    // chunks[i] covers depths [FAST_DEPTH + i*CHUNK_DEPTH .. FAST_DEPTH + (i+1)*CHUNK_DEPTH).
    private byte[][] chunks;
    private int depth;

    public void enter(ThreadContext ctx) {
        int d = depth;
        ctx.snapshot(bufferFor(d), offsetFor(d));
        depth = d + 1;
    }

    public void exit(ThreadContext ctx) {
        int d = depth - 1;
        if (d < 0) {
            throw new IllegalStateException("ScopeStack underflow");
        }
        ctx.restore(bufferFor(d), offsetFor(d));
        depth = d;
    }

    /** Current nesting depth (number of outstanding {@link #enter} calls). */
    public int depth() {
        return depth;
    }

    private byte[] bufferFor(int d) {
        if (d < FAST_DEPTH) {
            return fast;
        }
        // chunkFor is idempotent: if this depth was previously populated (via a matching enter),
        // it returns the existing chunk without allocating.
        return chunkFor((d - FAST_DEPTH) / CHUNK_DEPTH);
    }

    private static int offsetFor(int d) {
        int slot = d < FAST_DEPTH ? d : (d - FAST_DEPTH) % CHUNK_DEPTH;
        return slot * SLOT_SIZE;
    }

    private byte[] chunkFor(int idx) {
        byte[][] cs = chunks;
        if (cs == null) {
            cs = new byte[4][];
            chunks = cs;
        } else if (idx >= cs.length) {
            int newLen = cs.length;
            while (newLen <= idx) {
                newLen <<= 1;
            }
            cs = Arrays.copyOf(cs, newLen);
            chunks = cs;
        }
        byte[] c = cs[idx];
        if (c == null) {
            c = new byte[CHUNK_DEPTH * SLOT_SIZE];
            cs[idx] = c;
        }
        return c;
    }
}
