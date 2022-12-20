package com.datadoghq.profiler;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.Attribute;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.UnitLookup;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.UUID;

import one.profiler.JavaProfiler;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;

public abstract class AbstractProfilerTest {

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
    profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + jfrDump.toAbsolutePath());
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

  protected void after() {
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

  protected abstract String getProfilerCommand();

  protected void verifyEventsPresent(String... expectedEventTypes) {
    try {
      IItemCollection events = JfrLoaderToolkit.loadEvents(Files.newInputStream(jfrDump));
      assertTrue(events.hasItems());
      for (String expectedEventType : expectedEventTypes) {
        assertTrue(events.apply(ItemFilters.type(expectedEventType)).hasItems(),
            expectedEventType + " was empty for " + getProfilerCommand());
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
            eventType + " was empty for " + getProfilerCommand());
        return collection;
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t.getMessage());
      return null;
    }
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
