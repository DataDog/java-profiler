package com.datadoghq.profiler;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.openjdk.jmc.common.IMCFrame;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.*;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.UnitLookup;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.UUID;

import one.profiler.JavaProfiler;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;

public abstract class AbstractProfilerTest {

  private static final boolean ALLOW_NATIVE_CSTACKS = true;

  private boolean stopped = true;

  public static final IAttribute<String> TYPE =
          Attribute.attr("objectClass", "objectClass", "Object Class", UnitLookup.PLAIN_TEXT);
  public static final IAttribute<IQuantity> SIZE =
          Attribute.attr("allocationSize", "allocationSize", "Allocation Size", UnitLookup.NUMBER);

  public static final IAttribute<IQuantity> LOCAL_ROOT_SPAN_ID = attr("localRootSpanId", "localRootSpanId",
          "localRootSpanId", NUMBER);
  public static final IAttribute<IQuantity> SPAN_ID = attr("spanId", "spanId",
          "spanId", NUMBER);
  public static final IAttribute<IQuantity> PARALLELISM = attr("parallelism", "parallelism",
          "parallelism", NUMBER);

  public static final IAttribute<IQuantity> WEIGHT = attr("weight", "weight",
          "weight", NUMBER);

  public static final IAttribute<IMCStackTrace> STACK_TRACE = attr("stackTrace", "stackTrace", "", UnitLookup.STACKTRACE);

  protected JavaProfiler profiler;
  private Path jfrDump;

  @BeforeEach
  public void setupProfiler() throws IOException {
    before();
    jfrDump = Files.createTempFile(getClass().getName() + UUID.randomUUID(), ".jfr");
    profiler = JavaProfiler.getInstance(getJavaProfilerLib());
    profiler.execute("start," + getAmendedProfilerCommand() + ",jfr,file=" + jfrDump.toAbsolutePath());
    stopped = false;
  }

  @AfterEach
  public void cleanup() throws IOException {
    stopProfiler();
    Files.deleteIfExists(jfrDump);
    after();
  }

  protected void before() {
  }

  protected void after() throws IOException {
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
    profiler.addThread(profiler.getNativeThreadId());
  }

  private String getAmendedProfilerCommand() {
    String profilerCommand = getProfilerCommand();
    return ALLOW_NATIVE_CSTACKS || profilerCommand.contains("cstack=")
            ? profilerCommand
            : profilerCommand + ",cstack=no";
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


  public static String getJavaProfilerLib() {
    try {
      File root = new File(AbstractProfilerTest.class
          .getResource("AbstractProfilerTest.class").toURI()).getParentFile();
      while (!root.getName().startsWith("java-profiler")) {
        root = root.getParentFile();
      }
      return root.toPath().resolve("build/libjavaProfiler.so").toAbsolutePath().toString();
    } catch (Throwable t) {
      throw new RuntimeException("Could not find javaProfiler lib", t);
    }
  }
}
