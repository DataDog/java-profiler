package com.datadoghq.profiler;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Duration;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestInfo;
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

  public static final String LAMBDA_QUALIFIER = Platform.isJavaVersionAtLeast(21) ? "$$Lambda." : "$$Lambda$";
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

  public static final IAttribute<String> OPERATION = attr("operation", "operation",
          "operation", PLAIN_TEXT);



  public static final IAttribute<String> THREAD_STATE =
          attr("state", "state", "Thread State", PLAIN_TEXT);

  public static final IAttribute<String> THREAD_EXECUTION_MODE =
          attr("mode", "mode", "Execution Mode", PLAIN_TEXT);

  public static final IAttribute<String> TAG_1 = attr("tag1", "", "", PLAIN_TEXT);
  public static final IAttribute<String> TAG_2 = attr("tag2", "", "", PLAIN_TEXT);
  public static final IAttribute<String> TAG_3 = attr("tag3", "", "", PLAIN_TEXT);

  public static final IAttribute<IMCStackTrace> STACK_TRACE = attr("stackTrace", "stackTrace", "", UnitLookup.STACKTRACE);

  public static final IAttribute<IQuantity> CPU_INTERVAL = attr("cpuInterval", "cpuInterval", "", TIMESPAN);
  public static final IAttribute<String> CPU_ENGINE = attr("cpuEngine", "", "", PLAIN_TEXT);

  public static final IAttribute<IQuantity> WALL_INTERVAL = attr("wallInterval", "wallInterval", "", TIMESPAN);

  public static final IAttribute<String> NAME = attr("name", "", "", PLAIN_TEXT);

  public static final IAttribute<IQuantity> COUNT = attr("count", "", "", NUMBER);

  protected JavaProfiler profiler;
  private Path jfrDump;

  private Duration cpuInterval;
  private Duration wallInterval;

  private Map<String, Object> testParams;

  protected static Map<String, Object> mapOf(Object ... vals) {
    Map<String, Object> map = new HashMap<>();
    for (int i = 0; i < vals.length; i += 2) {
      map.put(vals[i].toString(), vals[i + 1]);
    }
    return map;
  }

  protected AbstractProfilerTest(Map<String, Object> testParams) {
    this.testParams = testParams != null ? new HashMap<>(testParams) : Collections.emptyMap();
  }

  protected AbstractProfilerTest() {
    this(null);
  }

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

  protected final boolean isAsan() {
    return System.getenv("ASAN_OPTIONS") != null;
  }

  protected final boolean isTsan() {
    return System.getenv("TSAN_OPTIONS") != null;
  }

  protected boolean isPlatformSupported() {
    return true;
  }

  protected void withTestAssumptions() {}

  @BeforeEach
  public void setupProfiler(TestInfo testInfo) throws Exception {
    Assumptions.assumeTrue(isPlatformSupported());
    withTestAssumptions();

    String testConfig = System.getenv("TEST_CONFIGURATION");
    testConfig = testConfig == null ? "" : testConfig;
    Path rootDir = Paths.get("/tmp/recordings");
    Files.createDirectories(rootDir);

    String cstack = (String)testParams.get("cstack");

    if (cstack != null) {
      rootDir = rootDir.resolve(cstack);
      Files.createDirectories(rootDir);
    }

    jfrDump = Files.createTempFile(rootDir, (testConfig.isEmpty() ? "" : testConfig.replace('/', '_') + "-") + testInfo.getTestMethod().map(m -> m.getDeclaringClass().getSimpleName() + "_" + m.getName()).orElse("unknown"), ".jfr");
    profiler = JavaProfiler.getInstance();
    String command = "start," + getAmendedProfilerCommand() + ",jfr,file=" + jfrDump.toAbsolutePath();
    cpuInterval = command.contains("cpu") ? parseInterval(command, "cpu") : (command.contains("interval") ? parseInterval(command, "interval") : Duration.ZERO);
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
    System.out.println("===> keep_jfrs: " + Boolean.getBoolean("ddprof_test.keep_jfrs"));
    if (jfrDump != null && !Boolean.getBoolean("ddprof_test.keep_jfrs")) {
      Files.deleteIfExists(jfrDump);
    }
  }

  protected void before() throws Exception {
  }

  protected void after() throws Exception {
  }

  public static final boolean isInCI() {
    return Boolean.getBoolean("ddprof_test.ci");
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


  public final void stopProfiler() {
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

  public final void registerCurrentThreadForWallClockProfiling() {
    profiler.addThread();
  }

  private String getAmendedProfilerCommand() {
    String profilerCommand = getProfilerCommand();
    String testCstack = (String)testParams.get("cstack");
    if (testCstack != null) {
      profilerCommand += ",cstack=" + testCstack;
    } else if(!(ALLOW_NATIVE_CSTACKS || profilerCommand.contains("cstack="))) {
      profilerCommand += ",cstack=fp";
    }
    // FIXME - test framework doesn't seem to be forking each test, so need to sync
    //  these across test cases for now
    profilerCommand += ",attributes=tag1;tag2;tag3";
    return profilerCommand;
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

  public final IItemCollection verifyEvents(String eventType) {
    return verifyEvents(eventType, true);
  }

  protected IItemCollection verifyEvents(String eventType, boolean failOnEmpty) {
    return verifyEvents(jfrDump, eventType, failOnEmpty);
  }

  protected IItemCollection verifyEvents(Path recording, String eventType, boolean failOnEmpty) {
    try {
      IItemCollection events = JfrLoaderToolkit.loadEvents(Files.newInputStream(recording));
      assertTrue(events.hasItems());
      IItemCollection collection = events.apply(ItemFilters.type(eventType));
      System.out.println(eventType + " count: " + collection.stream().flatMap(IItemIterable::stream).count());
      if (failOnEmpty) {
        assertTrue(collection.hasItems(),
                eventType + " was empty for " + getAmendedProfilerCommand());
      }
      return collection;
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t);
      return null;
    }
  }

  protected final void verifyCStackSettings() {
    String cstack = (String)testParams.get("cstack");
    if (cstack == null) {
      // not a forced cstack mode
      return;
    }
    IItemCollection settings = verifyEvents("jdk.ActiveSetting");
    for (IItemIterable settingEvents : settings) {
      IMemberAccessor<String, IItem> nameAccessor = JdkAttributes.REC_SETTING_NAME.getAccessor(settingEvents.getType());
      IMemberAccessor<String, IItem> valueAccessor = JdkAttributes.REC_SETTING_VALUE.getAccessor(settingEvents.getType());
      for (IItem item : settingEvents) {
        String name  = nameAccessor.getMember(item);
        if (name.equals("cstack")) {
          assertEquals(cstack, valueAccessor.getMember(item));
        }
      }
    }
  }

  protected void verifyStackTraces(String eventType, String... patterns) {
    verifyStackTraces(jfrDump, eventType, patterns);
  }

  protected void verifyStackTraces(Path recording, String eventType, String... patterns) {
    Set<String> unmatched = new HashSet<>(Arrays.asList(patterns));
    long cumulatedEvents = 0;
    outer: for (IItemIterable sample : verifyEvents(recording, eventType, false)) {
      cumulatedEvents += sample.getItemCount();
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
    assertNotEquals(0, cumulatedEvents, "no events found for " + eventType);
    assertTrue(unmatched.isEmpty(), "couldn't find " + eventType + " with " + unmatched);
  }
}