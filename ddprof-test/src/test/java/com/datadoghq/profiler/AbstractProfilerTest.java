package com.datadoghq.profiler;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Duration;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.UUID;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.Attribute;

import static org.junit.jupiter.api.Assertions.*;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.*;

import org.openjdk.jmc.common.IMCType;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.IItemFilter;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.common.item.IType;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.QuantityConversionException;
import org.openjdk.jmc.common.unit.UnitLookup;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

public abstract class AbstractProfilerTest {

  private static final boolean ALLOW_NATIVE_CSTACKS = true;

  private boolean stopped = true;

  public static final IQuantity ZERO_BYTES = BYTE.quantity(0);
  public static final IAttribute<IQuantity> SIZE = attr("size", "size", "", BYTE.getContentType());
  public static final IAttribute<IQuantity> WEIGHT = attr("weight", "weight", "weight", NUMBER);
  
  public static final IAttribute<IQuantity> SCALED_SIZE = new Attribute<IQuantity>("scaledSize", "scaled size", "", BYTE.getContentType()) {
      @Override
      public <U> IMemberAccessor<IQuantity, U> customAccessor(IType<U> type) {
          IMemberAccessor<IQuantity, U> sizeAccessor = SIZE.getAccessor(type);
          IMemberAccessor<IQuantity, U> weightAccessor = WEIGHT.getAccessor(type);
          if (sizeAccessor == null || weightAccessor == null) {
            return i -> ZERO_BYTES;
          }
          return i -> sizeAccessor.getMember(i).multiply(weightAccessor.getMember(i).doubleValue());
      }
  };

  public static final IAttribute<IQuantity> LOCAL_ROOT_SPAN_ID = attr("localRootSpanId", "localRootSpanId",
          "localRootSpanId", NUMBER);
  public static final IAttribute<IQuantity> SPAN_ID = attr("spanId", "spanId",
          "spanId", NUMBER);



  public static final IAttribute<String> THREAD_STATE =
          attr("state", "state", "Thread State", PLAIN_TEXT);

  public static final IAttribute<String> THREAD_EXECUTION_MODE =
          attr("mode", "mode", "Execution Mode", PLAIN_TEXT);

  public static final IAttribute<String> TAG_1 = attr("tag1", "", "", PLAIN_TEXT);
  public static final IAttribute<String> TAG_2 = attr("tag2", "", "", PLAIN_TEXT);
  public static final IAttribute<String> TAG_3 = attr("tag3", "", "", PLAIN_TEXT);

  public static final IAttribute<IMCStackTrace> STACK_TRACE = attr("stackTrace", "stackTrace", "", UnitLookup.STACKTRACE);

  public static final IAttribute<IQuantity> CPU_INTERVAL = attr("cpuInterval", "cpuInterval", "", TIMESPAN);

  public static final IAttribute<IQuantity> WALL_INTERVAL = attr("wallInterval", "wallInterval", "", TIMESPAN);

  public static final IAttribute<String> NAME = attr("name", "", "", PLAIN_TEXT);

  public static final IAttribute<IQuantity> COUNT = attr("count", "", "", NUMBER);

  protected JavaProfiler profiler;
  private Path jfrDump;

  private Duration cpuInterval;
  private Duration wallInterval;

  private static Duration parseInterval(String command, String part) {
    String prefix = part + "=";
    int start = command.indexOf(prefix);
    if (start >= 0) {
      start += prefix.length();
      int end = command.indexOf(",", start);
      if (end < 0) {
        end = command.length();
      }
      String interval = command.substring(start, end);
      int unitFirstChar = 0;
      int durationFirstChar = interval.charAt(0) == '~' ? 1 : 0;
      for (int i = 0; i < interval.length(); i++) {
        if (Character.isAlphabetic(interval.charAt(i))) {
          unitFirstChar = i;
          break;
        }
      }
      long duration = Long.parseLong(interval.substring(durationFirstChar, unitFirstChar));
      String unit = interval.substring(unitFirstChar).toLowerCase();
      switch (unit) {
        case "s":
          return Duration.ofSeconds(duration);
        case "ms":
          return Duration.ofMillis(duration);
        // backend assumes we report duration in millis,
        // so we can't express these more accurately than 0
        case "us":
        case "ns":
        default:
      }
    }
    return Duration.ofMillis(0);
  }

  @BeforeEach
  public void setupProfiler() throws Exception {
    jfrDump = Files.createTempFile(Paths.get("/tmp"), getClass().getName() + UUID.randomUUID(), ".jfr");
    profiler = JavaProfiler.getInstance();
    String command = "start," + getAmendedProfilerCommand() + ",jfr,file=" + jfrDump.toAbsolutePath();
    // FIXME cpu interval argument not respected and is sometimes hardcoded to 10ms if cpu is active at all
    boolean isSafeJ9Engine = (Platform.isJ9() && Platform.isJavaVersionAtLeast(11));
    cpuInterval = isSafeJ9Engine
            // respected for the safe J9 engine
            ? command.contains("cpu") ? parseInterval(command, "cpu") : Duration.ZERO
            // hardcoded for itimer and perfevents
            : command.contains("cpu") ? Duration.ofMillis(10) : Duration.ZERO;
    wallInterval = parseInterval(command, "wall");
    System.out.println("===> command: " + command);
    profiler.execute(command);
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

  private void checkConfig() {
    try {
      IItemCollection profilerConfig = verifyEvents("datadog.DatadogProfilerConfig");
      for (IItemIterable items : profilerConfig) {
        IMemberAccessor<IQuantity, IItem> cpuIntervalAccessor = CPU_INTERVAL.getAccessor(items.getType());
        IMemberAccessor<IQuantity, IItem> wallIntervalAccessor = WALL_INTERVAL.getAccessor(items.getType());
        for (IItem item : items) {
          long cpuIntervalMillis = cpuIntervalAccessor.getMember(item).longValueIn(MILLISECOND);
          long wallIntervalMillis = wallIntervalAccessor.getMember(item).longValueIn(MILLISECOND);
          if (!Platform.isJ9() && Platform.isJavaVersionAtLeast(11)) {
            // fixme J9 engine have weird defaults and need fixing
            assertEquals(cpuInterval.toMillis(), cpuIntervalMillis);
            assertEquals(wallInterval.toMillis(), wallIntervalMillis);
          }
        }
      }
    } catch (QuantityConversionException e) {
      Assertions.fail(e.getMessage());
    }
  }

  protected static IItemFilter allocatedTypeFilter(String className) {
    return type -> {
      IMemberAccessor<IMCType, IItem> accessor = JdkAttributes.OBJECT_CLASS.getAccessor(type);
      return iItem -> {
        return accessor != null && accessor.getMember(iItem).getFullName().equals(className);
      };
    };
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
      checkConfig();
    }
  }

  protected void dump(Path recording) {
    if (!stopped) {
      profiler.dump(recording);
    }
  }

  protected void registerCurrentThreadForWallClockProfiling() {
    profiler.addThread();
  }

  private String getAmendedProfilerCommand() {
    String profilerCommand = getProfilerCommand();
    return (ALLOW_NATIVE_CSTACKS || profilerCommand.contains("cstack=")
            ? profilerCommand
            : profilerCommand + ",cstack=fp")
            // FIXME - test framework doesn't seem to be forking each test, so need to sync
            //  these across test cases for now
            + ",attributes=tag1;tag2;tag3";
  }

  protected abstract String getProfilerCommand();

  
  protected void verifyEventsPresent(String... expectedEventTypes) {
    verifyEventsPresent(jfrDump, expectedEventTypes);
  }

  protected void verifyEventsPresent(Path recording, String... expectedEventTypes) {  
    try {
      IItemCollection events = JfrLoaderToolkit.loadEvents(Files.newInputStream(recording));
      assertTrue(events.hasItems());
      for (String expectedEventType : expectedEventTypes) {
        IItemCollection filtered = events.apply(ItemFilters.type(expectedEventType));
        assertTrue(filtered.hasItems(),
                expectedEventType + " was empty for " + getAmendedProfilerCommand());
        System.out.println(expectedEventType + " count: " + filtered.stream().count());
      }
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t.getMessage());
    }
  }

  protected IItemCollection verifyEvents(String eventType) {
    return verifyEvents(jfrDump, eventType);
  }

  protected IItemCollection verifyEvents(Path recording, String eventType) {
    try {
      IItemCollection events = JfrLoaderToolkit.loadEvents(Files.newInputStream(recording));
      assertTrue(events.hasItems());
      IItemCollection collection = events.apply(ItemFilters.type(eventType));
        assertTrue(collection.hasItems(),
            eventType + " was empty for " + getAmendedProfilerCommand());
        System.out.println(eventType + " count: " + collection.stream().flatMap(IItemIterable::stream).count());
        return collection;
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t);
      return null;
    }
  }

  protected void verifyStackTraces(String eventType, String... patterns) {
    verifyStackTraces(jfrDump, eventType, patterns);
  }

  protected void verifyStackTraces(Path recording, String eventType, String... patterns) {
    Set<String> unmatched = new HashSet<>(Arrays.asList(patterns));
    outer: for (IItemIterable sample : verifyEvents(recording, eventType)) {
      IMemberAccessor<String, IItem> stackTraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(sample.getType());
      for (IItem item : sample) {
        String stackTrace = stackTraceAccessor.getMember(item);
        if (stackTrace != null) {
          unmatched.removeIf(stackTrace::contains);
          if (unmatched.isEmpty()) {
            break outer;
          }
        }
      }
    }
    assertTrue(unmatched.isEmpty(), "couldn't find datadog.ExecutionSample with " + unmatched);
  }
}