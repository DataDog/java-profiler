package com.datadoghq.profiler.context;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.util.concurrent.ArrayBlockingQueue;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;

/**
 * Verifies the "encode-once, push-many" int-int fast path:
 *
 * <ol>
 *   <li>{@link JavaProfiler#registerConstant(String)} registers the value in the native
 *       {@code _context_value_map} Dictionary and returns its stable encoding id.</li>
 *   <li>{@link JavaProfiler#setContextValue(int, int)} on any thread (typically a worker
 *       activating a continuation) writes the encoding to the per-thread sidecar slot
 *       without a second registerConstant0() JNI hit.</li>
 *   <li>JFR sample events resolve the sidecar encoding via the {@code T_ATTRIBUTE_VALUE}
 *       constant pool, so context columns ({@code tag1}, {@code tag2}, {@code tag3}) carry
 *       the original strings end-to-end.</li>
 * </ol>
 *
 * <p>The int-int path is sidecar-only — it does not update OTEP {@code attrs_data}.
 * External OTEP-reading profilers must use {@link JavaProfiler#setContextAttribute(int, String)}
 * if they need {@code attrs_data} parity. The DD JFR signal-handler reader (which feeds
 * the {@code _dd.trace.operation} / {@code _dd.trace.resource} columns in JMC) is fully
 * supported by this path because it resolves sidecar ids via the JFR constant pool.
 *
 * <p>Pre-fix regression that this test guards against: the encoder reflectively probed for
 * {@code ContextSetter.encode(String)} and {@code JavaProfiler.registerConstant(String)}
 * and silently returned 0 because neither existed. The int-int sidecar push also reflected
 * on {@code JavaProfiler.setContextValue(int,int)} which did not exist. Spans cached
 * {@code encodedOperationName = 0} at construction and every activation pushed 0 into the
 * sidecar, so {@code _dd.trace.operation} on Method CPU / Allocation / QueueTime events
 * was empty across the whole profile and {@code _context_value_map} stayed empty
 * (verifiable via the {@code dictionary_context_*} Profiler Internal Counter values).
 */
public class EncodedAttributeFastPathTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }

    /**
     * API sanity: registerConstant returns non-zero ids for non-empty strings, is idempotent,
     * and setContextValue(int,int) accepts those ids without error.
     */
    @Test
    public void testRegisterAndPushApi() {
        int enc1 = profiler.registerConstant("route-fast-path");
        int enc2 = profiler.registerConstant("postgres");
        int enc3 = profiler.registerConstant("worker-pool");

        // Encoding 0 is the empty/no-value sentinel; real values must be > 0.
        assertNotEquals(0, enc1, "registerConstant must return a non-zero id for a non-empty string");
        assertNotEquals(0, enc2);
        assertNotEquals(0, enc3);
        assertNotEquals(enc1, enc2, "distinct strings must get distinct encoding ids");
        assertNotEquals(enc2, enc3);

        // Idempotency: repeated registration of the same string returns the same id.
        assertEquals(enc1, profiler.registerConstant("route-fast-path"));
        assertEquals(enc2, profiler.registerConstant("postgres"));

        // The int-int push lands in the per-thread sidecar slot.
        assertTrue(profiler.setContextValue(0, enc1));
        assertTrue(profiler.setContextValue(1, enc2));
        assertTrue(profiler.setContextValue(2, enc3));
        // encoding == 0 is the sidecar zero/clear sentinel and must also succeed.
        assertTrue(profiler.setContextValue(1, 0));

        // Out-of-range key indices are rejected.
        assertEquals(false, profiler.setContextValue(-1, enc1));
        assertEquals(false, profiler.setContextValue(99, enc1));
    }

    /**
     * End-to-end JFR round-trip: register encodings on the submitter, push them on the
     * worker via the int-int path, emit a QueueTime event, then verify the JFR event's
     * {@code tag1/tag2/tag3} columns resolve back to the original strings via the
     * {@code T_ATTRIBUTE_VALUE} constant pool. This is the exact path that was broken
     * pre-fix for {@code _dd.trace.operation} / {@code _dd.trace.resource} on production
     * profiles, and the assertion below is the user-visible behavior in JMC.
     */
    @Test
    public void testIntIntPathRoundTripsThroughQueueTimeJfr() throws Exception {
        IAttribute<IQuantity> submittingSpanIdAttr = attr("submittingSpanId", "", "", NUMBER);

        // Submitter: register the strings (populates _context_value_map).
        int encRoute = profiler.registerConstant("route-int-int-roundtrip");
        int encDb = profiler.registerConstant("mysql");
        int encPool = profiler.registerConstant("custom-thread-pool");
        assertNotEquals(0, encRoute);
        assertNotEquals(0, encDb);
        assertNotEquals(0, encPool);

        Thread origin = Thread.currentThread();
        origin.setName("origin-int-int-roundtrip");
        long start = profiler.getCurrentTicks();

        Runnable worker = () -> {
            profiler.setContext(7, 42);
            // Use the int-int fast path — no string passed across thread boundaries.
            assertTrue(profiler.setContextValue(0, encRoute));
            assertTrue(profiler.setContextValue(1, encDb));
            assertTrue(profiler.setContextValue(2, encPool));
            long now = profiler.getCurrentTicks();
            profiler.recordQueueTime(
                    start,
                    now,
                    EncodedAttributeFastPathTest.class,
                    EncodedAttributeFastPathTest.class,
                    ArrayBlockingQueue.class,
                    1,
                    origin,
                    99L,
                    88L);
            profiler.clearContext();
        };
        Thread thread = new Thread(worker, "destination-int-int-roundtrip");
        Thread.sleep(10);
        thread.start();
        thread.join();
        stopProfiler();

        IItemCollection events = verifyEvents("datadog.QueueTime");
        boolean found = false;
        for (IItemIterable it : events) {
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> submittingAccessor = submittingSpanIdAttr.getAccessor(it.getType());
            IMemberAccessor<String, IItem> tag1Accessor = TAG_1.getAccessor(it.getType());
            IMemberAccessor<String, IItem> tag2Accessor = TAG_2.getAccessor(it.getType());
            IMemberAccessor<String, IItem> tag3Accessor = TAG_3.getAccessor(it.getType());
            assertNotNull(tag1Accessor);
            assertNotNull(tag2Accessor);
            assertNotNull(tag3Accessor);
            for (IItem item : it) {
                if (spanIdAccessor.getMember(item).longValue() == 88) {
                    found = true;
                    assertEquals(42, rootSpanIdAccessor.getMember(item).longValue());
                    assertEquals(99, submittingAccessor.getMember(item).longValue());
                    // The critical assertion: tag values must resolve through the JFR
                    // constant pool, proving the int-int path correctly populated both
                    // the per-thread sidecar AND the _context_value_map Dictionary.
                    assertEquals("route-int-int-roundtrip", tag1Accessor.getMember(item),
                            "tag1 must resolve via the constant pool to the registered string");
                    assertEquals("mysql", tag2Accessor.getMember(item));
                    assertEquals("custom-thread-pool", tag3Accessor.getMember(item));
                }
            }
        }
        assertTrue(found, "Expected QueueTime with overridden spanId=88 from int-int worker push");
    }
}
