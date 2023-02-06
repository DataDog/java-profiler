package com.datadoghq.profiler;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.UUID;

import org.junit.jupiter.api.AfterEach;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import org.junit.jupiter.api.BeforeEach;
import org.openjdk.jmc.common.IMCStackTrace;
import static org.openjdk.jmc.common.item.Attribute.attr;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.UnitLookup;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

public abstract class AbstractProfilerTest {

  private static final boolean ALLOW_NATIVE_CSTACKS = true;

  private boolean stopped = true;

  public static final IAttribute<String> TYPE =
          attr("objectClass", "objectClass", "Object Class", PLAIN_TEXT);
  public static final IAttribute<IQuantity> SIZE =
          attr("allocationSize", "allocationSize", "Allocation Size", NUMBER);

  public static final IAttribute<IQuantity> LOCAL_ROOT_SPAN_ID = attr("localRootSpanId", "localRootSpanId",
          "localRootSpanId", NUMBER);
  public static final IAttribute<IQuantity> SPAN_ID = attr("spanId", "spanId",
          "spanId", NUMBER);

  public static final IAttribute<IQuantity> WEIGHT = attr("weight", "weight",
          "weight", NUMBER);

  public static final IAttribute<String> THREAD_STATE =
          attr("state", "state", "Thread State", PLAIN_TEXT);

  public static final IAttribute<String> TAG_1 = attr("tag1", "", "", PLAIN_TEXT);
  public static final IAttribute<String> TAG_2 = attr("tag2", "", "", PLAIN_TEXT);
  public static final IAttribute<String> TAG_3 = attr("tag3", "", "", PLAIN_TEXT);

  public static final IAttribute<IMCStackTrace> STACK_TRACE = attr("stackTrace", "stackTrace", "", UnitLookup.STACKTRACE);

  protected JavaProfiler profiler;
  private Path jfrDump;

  @BeforeEach
  public void setupProfiler() throws Exception {
    jfrDump = Files.createTempFile(Paths.get("/tmp"), getClass().getName() + UUID.randomUUID(), ".jfr");
    profiler = JavaProfiler.getInstance();
    profiler.execute("start," + getAmendedProfilerCommand() + ",jfr,file=" + jfrDump.toAbsolutePath());
    stopped = false;
    before();
  }

  @AfterEach
  public void cleanup() throws Exception {
    after();
    stopProfiler();
    Files.deleteIfExists(jfrDump);
  }

  protected void before() throws Exception {
  }

  protected void after() throws Exception {
  }

  protected void runTests(Runnable... runnables) throws InterruptedException {
    Thread[] threads = new Thread[runnables.length];
    for (int i = 0; i < runnables.length; i++) {
      threads[i] = new Thread(runnables[i]);
    }
    for (Thread thread : threads) {
      thread.start();
    }
    for (Thread thread : threads) {
      thread.join();
    }
    stopProfiler();
  }


  protected void stopProfiler() {
    if (!stopped) {
      profiler.stop();
      stopped = true;
    }
  }

  protected void registerCurrentThreadForWallClockProfiling() {
    profiler.addThread();
  }

  private String getAmendedProfilerCommand() {
    String profilerCommand = getProfilerCommand();
    return (ALLOW_NATIVE_CSTACKS || profilerCommand.contains("cstack=")
            ? profilerCommand
            : profilerCommand + ",cstack=no")
            // FIXME - test framework doesn't seem to be forking each test, so need to sync
            //  these across test cases for now
            + ",attributes=tag1;tag2;tag3";
  }

  protected abstract String getProfilerCommand();

  protected void verifyEventsPresent(String... expectedEventTypes) {
    try {
      IItemCollection events = JfrLoaderToolkit.loadEvents(Files.newInputStream(jfrDump));
      assertTrue(events.hasItems());
      for (String expectedEventType : expectedEventTypes) {
        assertTrue(events.apply(ItemFilters.type(expectedEventType)).hasItems(),
                expectedEventType + " was empty for " + getAmendedProfilerCommand());
      }
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t.getMessage());
    }
  }

  protected IItemCollection verifyEvents(String eventType) {
    try {
      IItemCollection events = JfrLoaderToolkit.loadEvents(Files.newInputStream(jfrDump));
      assertTrue(events.hasItems());
      IItemCollection collection = events.apply(ItemFilters.type(eventType));
        assertTrue(collection.hasItems(),
            eventType + " was empty for " + getAmendedProfilerCommand());
        return collection;
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t.getMessage());
      return null;
    }
  }

  protected void verifyStackTraces(String eventType, String... patterns) {
    Set<String> unmatched = new HashSet<>(Arrays.asList(patterns));
    outer: for (IItemIterable sample : verifyEvents(eventType)) {
      IMemberAccessor<String, IItem> stackTraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(sample.getType());
      for (IItem item : sample) {
        String stackTrace = stackTraceAccessor.getMember(item);
        unmatched.removeIf(stackTrace::contains);
        if (unmatched.isEmpty()) {
          break outer;
        }
      }
    }
    assertTrue(unmatched.isEmpty(), "couldn't find datadog.ExecutionSample with " + unmatched);
  }
}
