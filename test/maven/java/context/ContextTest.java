package context;

import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.JfrAttributes;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.ThreadLocalRandom;

import one.profiler.AsyncProfiler;
import utils.Utils;

import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class ContextTest {

  public static final IAttribute<IQuantity> LOCAL_ROOT_SPAN_ID = attr("localRootSpanId", "localRootSpanId",
      "localRootSpanId", NUMBER);
  public static final IAttribute<IQuantity> SPAN_ID = attr("spanId", "spanId",
      "spanId", NUMBER);
  public static final IAttribute<IQuantity> PARALLELISM = attr("parallelism", "parallelism",
      "parallelism", NUMBER);

    @Test
    public void testReadContext() throws Exception {
        Path jfrDump = Files.createTempFile("context-test", ".jfr");
        AsyncProfiler ap = AsyncProfiler.getInstance(Utils.getAsyncProfilerLib());
        int tid = ap.getNativeThreadId();
        ap.addThread(tid);
        ap.setContext(tid, 42, 84);
        ap.setPoolParallelism(tid, 89);
        ap.execute("start,cpu=1ms,wall=~1ms,jfr,thread,file=" + jfrDump.toAbsolutePath());
        // sleep to get some wall samples
        Thread.sleep(10);
        // do some work to get some cpu samples
        long value = 0;
        for (int i = 0; i < 10_000_000; i++) {
           value ^= ThreadLocalRandom.current().nextLong();
        }
        System.err.println(value);
        Thread.sleep(10);
        ap.clearPoolParallelism(tid);
        ap.stop();
        IItemCollection events = JfrLoaderToolkit.loadEvents(jfrDump.toFile());
        IItemCollection cpuSamples = events.apply(ItemFilters.type("datadog.ExecutionSample"));
        assertTrue(cpuSamples.hasItems());
        for (IItemIterable cpuSample : cpuSamples) {
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(cpuSample.getType());
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(cpuSample.getType());
            IMemberAccessor<IMCThread, IItem> threadAccessor = JfrAttributes.EVENT_THREAD.getAccessor(cpuSample.getType());
            for (IItem sample : cpuSample) {
                if (threadAccessor.getMember(sample).getThreadName().equals(Thread.currentThread().getName())) {
                    long rootSpanId = rootSpanIdAccessor.getMember(sample).longValue();
                    assertEquals(84, rootSpanId);
                    long spanId = spanIdAccessor.getMember(sample).longValue();
                    assertEquals(42, spanId);
                }
            }
        }
        IItemCollection wallSamples = events.apply(ItemFilters.type("datadog.MethodSample"));
        assertTrue(wallSamples.hasItems());
        for (IItemIterable wallSample : wallSamples) {
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(wallSample.getType());
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(wallSample.getType());
            IMemberAccessor<IQuantity, IItem> parallelismAccessor = PARALLELISM.getAccessor(wallSample.getType());
            IMemberAccessor<IMCThread, IItem> threadAccessor = JfrAttributes.EVENT_THREAD.getAccessor(wallSample.getType());
            for (IItem sample : wallSample) {
                if (threadAccessor.getMember(sample).getThreadName().equals(Thread.currentThread().getName())) {
                    long rootSpanId = rootSpanIdAccessor.getMember(sample).longValue();
                    assertEquals(84, rootSpanId);
                    long spanId = spanIdAccessor.getMember(sample).longValue();
                    assertEquals(42, spanId);
                    int parallelism = (int) parallelismAccessor.getMember(sample).longValue();
                    assertEquals(89, parallelism);
                }
            }
        }
    }

}
