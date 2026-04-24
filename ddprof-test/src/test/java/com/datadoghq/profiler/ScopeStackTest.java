package com.datadoghq.profiler;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Pure-Java unit test for {@link ScopeStack}. Uses heap-backed {@link ByteBuffer}s so
 * no native library is required. Exercises depth accounting, underflow, and round-trip
 * preservation of trace/span IDs across fast-path and chunked-path depths.
 */
public class ScopeStackTest {

    // Offsets mirror OtelThreadContextRecord in otel_context.h and the sidecar layout
    // built by initializeContextTLS0 in javaApi.cpp. These are spec-fixed; guarded by
    // static_asserts in native code. All are absolute within the unified buffer.
    private static final int TRACE_ID_OFFSET = 0;
    private static final int SPAN_ID_OFFSET = 16;
    private static final int VALID_OFFSET = 24;
    private static final int ATTRS_DATA_SIZE_OFFSET = 26;
    private static final int ATTRS_DATA_OFFSET = 28;
    private static final int LRS_OFFSET = 640 + 40; // after 640-byte record + 10 * sizeof(u32)

    private static ThreadContext newContext() {
        ByteBuffer buf = ByteBuffer.allocate(ThreadContext.SNAPSHOT_SIZE).order(ByteOrder.nativeOrder());
        long[] metadata = {
            VALID_OFFSET, TRACE_ID_OFFSET, SPAN_ID_OFFSET,
            ATTRS_DATA_SIZE_OFFSET, ATTRS_DATA_OFFSET, LRS_OFFSET
        };
        return new ThreadContext(buf, metadata);
    }

    private static void assumeLittleEndian() {
        Assumptions.assumeTrue(
            ByteOrder.nativeOrder() == ByteOrder.LITTLE_ENDIAN,
            "ThreadContext only supports little-endian platforms");
    }

    @Test
    public void depthBalance() {
        assumeLittleEndian();
        ThreadContext ctx = newContext();
        ScopeStack stack = new ScopeStack();
        assertEquals(0, stack.depth());
        stack.enter(ctx);
        assertEquals(1, stack.depth());
        stack.enter(ctx);
        assertEquals(2, stack.depth());
        stack.exit(ctx);
        assertEquals(1, stack.depth());
        stack.exit(ctx);
        assertEquals(0, stack.depth());
    }

    @Test
    public void exitUnderflowThrows() {
        assumeLittleEndian();
        ThreadContext ctx = newContext();
        ScopeStack stack = new ScopeStack();
        assertThrows(IllegalStateException.class, () -> stack.exit(ctx));
    }

    @Test
    public void fastPathRoundTrip() {
        assumeLittleEndian();
        ThreadContext ctx = newContext();
        ScopeStack stack = new ScopeStack();

        ctx.put(/*lrs*/ 100L, /*span*/ 200L, /*trHi*/ 0L, /*trLo*/ 300L);
        assertEquals(200L, ctx.getSpanId());
        assertEquals(100L, ctx.getRootSpanId());

        stack.enter(ctx);
        ctx.put(500L, 600L, 0L, 700L);
        assertEquals(600L, ctx.getSpanId());
        assertEquals(500L, ctx.getRootSpanId());

        stack.exit(ctx);
        assertEquals(200L, ctx.getSpanId(), "span must be restored");
        assertEquals(100L, ctx.getRootSpanId(), "root span must be restored");
    }

    @Test
    public void chunkedPathRoundTrip() {
        // Push past FAST_DEPTH (6) to exercise the lazy-chunk path and Arrays.copyOf growth.
        assumeLittleEndian();
        ThreadContext ctx = newContext();
        ScopeStack stack = new ScopeStack();

        final int depth = 20; // FAST_DEPTH + one full 12-slot chunk + 2 into the next
        for (int i = 0; i < depth; i++) {
            ctx.put(1000L + i, 2000L + i, 0L, 3000L + i);
            stack.enter(ctx);
        }
        assertEquals(depth, stack.depth());

        // Scramble state so restore has something to correct.
        ctx.put(99L, 99L, 0L, 99L);

        for (int i = depth - 1; i >= 0; i--) {
            stack.exit(ctx);
            assertEquals(2000L + i, ctx.getSpanId(), "span mismatch at depth " + i);
            assertEquals(1000L + i, ctx.getRootSpanId(), "root mismatch at depth " + i);
        }
        assertEquals(0, stack.depth());
    }

    @Test
    public void reusesStackAfterFullUnwind() {
        // After the stack returns to depth 0, re-entering must not leak state from the prior run.
        assumeLittleEndian();
        ThreadContext ctx = newContext();
        ScopeStack stack = new ScopeStack();

        ctx.put(1L, 2L, 0L, 3L);
        stack.enter(ctx);
        ctx.put(10L, 20L, 0L, 30L);
        stack.exit(ctx);
        assertEquals(2L, ctx.getSpanId());

        ctx.put(4L, 5L, 0L, 6L);
        stack.enter(ctx);
        ctx.put(40L, 50L, 0L, 60L);
        stack.exit(ctx);
        assertEquals(5L, ctx.getSpanId());
    }

    @Test
    public void snapshotOverClearedContextDoesNotRepublish() {
        // Regression: snapshot() used to unconditionally re-attach, flipping valid back to 1
        // after a zero-put clear. The clear path leaves attrs_data_size / attrs_data stale and
        // relies on valid=0 to keep external readers from seeing the stale bytes. Here we verify
        // the valid byte directly since setContextAttribute is a native path unavailable to
        // pure-Java tests.
        assumeLittleEndian();
        ByteBuffer buf = ByteBuffer.allocate(ThreadContext.SNAPSHOT_SIZE).order(ByteOrder.nativeOrder());
        long[] metadata = {
            VALID_OFFSET, TRACE_ID_OFFSET, SPAN_ID_OFFSET,
            ATTRS_DATA_SIZE_OFFSET, ATTRS_DATA_OFFSET, LRS_OFFSET
        };
        ThreadContext ctx = new ThreadContext(buf, metadata);
        ScopeStack stack = new ScopeStack();

        ctx.put(1L, 2L, 0L, 3L);
        assertEquals(1, buf.get(VALID_OFFSET), "record must be published after non-zero put");

        // Zero-put clear: leaves valid=0 (the all-zero early-return in setContextDirect).
        ctx.put(0L, 0L, 0L, 0L);
        assertEquals(0, buf.get(VALID_OFFSET), "record must be invalid after zero-put clear");

        stack.enter(ctx);
        assertEquals(0, buf.get(VALID_OFFSET),
            "snapshot must preserve valid=0 — not republish a cleared record");

        stack.exit(ctx);
        assertEquals(0, buf.get(VALID_OFFSET),
            "restore must replay valid=0 — not republish a cleared record");
    }
}
