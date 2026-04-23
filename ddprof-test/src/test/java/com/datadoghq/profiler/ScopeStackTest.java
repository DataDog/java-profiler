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

    private static final int COMBINED_SIZE = ThreadContext.SNAPSHOT_SIZE;
    private static final int RECORD_SIZE = ThreadContext.OTEL_MAX_RECORD_SIZE;
    // Offsets mirror OtelThreadContextRecord in otel_context.h and the sidecar layout
    // built by initializeContextTLS0 in javaApi.cpp. These are spec-fixed; guarded by
    // static_asserts in native code.
    private static final int TRACE_ID_OFFSET = 0;
    private static final int SPAN_ID_OFFSET = 16;
    private static final int VALID_OFFSET = 24;
    private static final int ATTRS_DATA_SIZE_OFFSET = 26;
    private static final int ATTRS_DATA_OFFSET = 28;
    private static final int LRS_SIDECAR_OFFSET = 40; // 10 * sizeof(u32)

    private static ThreadContext newContext() {
        // Combined buffer aliases record + sidecar via slices sharing the same backing array.
        ByteBuffer combined = ByteBuffer.allocate(COMBINED_SIZE).order(ByteOrder.nativeOrder());
        combined.position(0).limit(RECORD_SIZE);
        ByteBuffer record = combined.slice().order(ByteOrder.nativeOrder());
        combined.position(RECORD_SIZE).limit(COMBINED_SIZE);
        ByteBuffer sidecar = combined.slice().order(ByteOrder.nativeOrder());
        combined.position(0).limit(COMBINED_SIZE);
        long[] metadata = {
            VALID_OFFSET, TRACE_ID_OFFSET, SPAN_ID_OFFSET,
            ATTRS_DATA_SIZE_OFFSET, ATTRS_DATA_OFFSET, LRS_SIDECAR_OFFSET
        };
        return new ThreadContext(record, sidecar, combined, metadata);
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
}
