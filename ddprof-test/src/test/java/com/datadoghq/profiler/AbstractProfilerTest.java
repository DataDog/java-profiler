/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Duration;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.BiConsumer;
import java.util.function.Consumer;
import java.util.function.Predicate;
import java.util.function.Supplier;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestInfo;

import static org.junit.jupiter.api.Assertions.*;

public abstract class AbstractProfilerTest {
  private static final boolean ALLOW_NATIVE_CSTACKS = true;

  private boolean stopped = true;
  private Map<Path, Long> sanitizerLogSizesBefore = new HashMap<>();

  public static final String LAMBDA_QUALIFIER = Platform.isJavaVersionAtLeast(21) ? "$$Lambda." : "$$Lambda$";

  // Field-name constants for the JFR fields tests commonly read via JfrEvent.getXxx(...).
  // These replace the old JMC-typed IAttribute constants of the same names one-for-one, so
  // subclasses keep referencing AbstractProfilerTest.SPAN_ID etc. unchanged - only the call
  // pattern around them (JfrEvent.getLong(SPAN_ID) instead of SPAN_ID.getAccessor(type).getMember(item))
  // changes at each site.
  public static final String SIZE = "size";
  public static final String WEIGHT = "weight";
  public static final String LOCAL_ROOT_SPAN_ID = "localRootSpanId";
  public static final String SPAN_ID = "spanId";
  public static final String OPERATION = "operation";
  public static final String THREAD_STATE = "state";
  public static final String THREAD_EXECUTION_MODE = "mode";
  public static final String TAG_1 = "tag1";
  public static final String TAG_2 = "tag2";
  public static final String TAG_3 = "tag3";
  public static final String STACK_TRACE = "stackTrace";
  public static final String CPU_INTERVAL = "cpuInterval";
  public static final String CPU_ENGINE = "cpuEngine";
  public static final String WALL_INTERVAL = "wallInterval";
  public static final String NAME = "name";
  public static final String COUNT = "count";

  /**
   * {@code size * weight}: an estimated true byte contribution of a subsampled allocation/
   * liveness event, replacing JMC's computed {@code SCALED_SIZE} attribute. {@code weight} is
   * stored as either an integer or float field depending on event type (see jfrMetadata.cpp),
   * hence the {@code double} read.
   */
  public static double scaledSize(JfrEvent item) {
    return item.getLong(SIZE, 0) * item.getDouble(WEIGHT, 1.0);
  }

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

  private static long getPid() {
    try {
      String name = java.lang.management.ManagementFactory.getRuntimeMXBean().getName();
      return Long.parseLong(name.split("@")[0]);
    } catch (NumberFormatException e) {
      return 0L;
    }
  }

  private static List<Path> getSanitizerLogPaths() {
    List<Path> paths = new ArrayList<>();
    String pid = String.valueOf(getPid());
    for (String envVar : new String[]{"ASAN_OPTIONS", "UBSAN_OPTIONS"}) {
      String options = System.getenv(envVar);
      if (options == null) continue;
      for (String opt : options.split(":")) {
        if (opt.startsWith("log_path=")) {
          String template = opt.substring("log_path=".length());
          String path = template.replace("%p", pid);
          paths.add(Paths.get(path));
        }
      }
    }
    return paths;
  }

  private void dumpSanitizerLogs() {
    for (Path logPath : getSanitizerLogPaths()) {
      try {
        if (!Files.exists(logPath)) continue;
        long sizeBefore = sanitizerLogSizesBefore.getOrDefault(logPath, 0L);
        long currentSize = Files.size(logPath);
        if (currentSize <= sizeBefore) continue;
        byte[] bytes = Files.readAllBytes(logPath);
        if (bytes.length > (int) sizeBefore) {
          String newContent = new String(bytes, (int) sizeBefore, bytes.length - (int) sizeBefore);
          String label = logPath.getFileName().toString().toUpperCase();
          System.err.println("=== " + label + " errors detected during test ===");
          System.err.println(newContent);
          System.err.println("=== End " + label + " errors ===");
        }
      } catch (Exception e) {
        // best effort
      }
    }
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

    jfrDump = Files.createTempFile(rootDir, testInfo.getTestMethod().map(m -> m.getDeclaringClass().getSimpleName() + "_" + m.getName()).orElse("unknown") + (testConfig.isEmpty() ? "" : "-" + testConfig.replace('/', '_')), ".jfr");
    profiler = JavaProfiler.getInstance();
    beforeProfilerStart();
    String command = "start," + getAmendedProfilerCommand() + ",jfr,file=" + jfrDump.toAbsolutePath();
    cpuInterval = command.contains("cpu") ? parseInterval(command, "cpu") : (command.contains("interval") ? parseInterval(command, "interval") : Duration.ZERO);
    wallInterval = parseInterval(command, "wall");
    // Record sanitizer log sizes before test so we can dump new errors after
    sanitizerLogSizesBefore.clear();
    for (Path logPath : getSanitizerLogPaths()) {
      try {
        if (Files.exists(logPath)) {
          sanitizerLogSizesBefore.put(logPath, Files.size(logPath));
        }
      } catch (Exception e) {
        // best effort
      }
    }

    System.out.println("===> command: " + command);
    profiler.execute(command);
    stopped = false;
    before();
  }

  @AfterEach
  public void cleanup() throws Exception {
    after();
    stopProfiler();
    dumpSanitizerLogs();
    System.out.println("===> keep_jfrs: " + Boolean.getBoolean("ddprof_test.keep_jfrs"));
    if (jfrDump != null && !Boolean.getBoolean("ddprof_test.keep_jfrs")) {
      Files.deleteIfExists(jfrDump);
    }
  }

  protected void before() throws Exception {
  }

  /**
   * Runs after the profiler instance is available but before the recording starts.
   *
   * <p>Tests may override this hook when their setup must predate profiler thread-event
   * registration.
   *
   * @throws Exception if setup fails
   */
  protected void beforeProfilerStart() throws Exception {
  }

  protected void after() throws Exception {
  }

  public static final boolean isInCI() {
    return Boolean.getBoolean("ddprof_test.ci");
  }

  private void checkConfig() {
    JfrEvents profilerConfig = verifyEvents("datadog.DatadogProfilerConfig");
    for (JfrEvent item : profilerConfig) {
      long cpuIntervalMillis = item.getLong(CPU_INTERVAL, 0);
      long wallIntervalMillis = item.getLong(WALL_INTERVAL, 0);
      if (!Platform.isJ9() && Platform.isJavaVersionAtLeast(11)) {
        // fixme J9 engine have weird defaults and need fixing
        // Only assert intervals that were explicitly requested in the profiler
        // command; engines not requested carry default intervals that do not
        // match the (absent) command value.
        if (cpuInterval.toMillis() > 0) {
          assertEquals(cpuInterval.toMillis(), cpuIntervalMillis);
        }
        if (wallInterval.toMillis() > 0) {
          assertEquals(wallInterval.toMillis(), wallIntervalMillis);
        }
      }
    }
  }

  /** Matches allocation/liveness events whose sampled object's class full name equals {@code className}. */
  protected static Predicate<JfrEvent> allocatedTypeFilter(String className) {
    return item -> className.equals(item.getClassName("objectClass"));
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
      profiler.clearTraceContext();
      stopped = true;
      checkConfig();
    }
  }

  protected void dump(Path recording) {
    if (!stopped) {
      profiler.dump(recording);
    }
  }

  /**
   * Waits for the profiler to reach RUNNING state by polling getStatus().
   * This ensures all engines are initialized and ready to collect samples
   * before test workload begins.
   *
   * @param timeoutMs Maximum time to wait in milliseconds
   * @throws IllegalStateException if profiler doesn't reach RUNNING state within timeout
   * @throws InterruptedException if interrupted while waiting
   */
  protected void waitForProfilerReady(long timeoutMs) throws InterruptedException {
    long deadline = System.currentTimeMillis() + timeoutMs;
    long waitTime = 0;

    while (System.currentTimeMillis() < deadline) {
      String status = profiler.getStatus();
      if (status.contains("Running          : true")) {
        System.out.println("[Profiler Ready] Took " + waitTime + "ms to initialize");
        return;
      }
      Thread.sleep(10);
      waitTime += 10;
    }

    // Timeout reached - throw with diagnostic info
    String finalStatus = profiler.getStatus();
    throw new IllegalStateException(
            "Profiler failed to reach RUNNING state within " + timeoutMs + "ms\n" +
            "Final status:\n" + finalStatus);
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
    // Only add attributes if not already specified
    if (!profilerCommand.contains("attributes=")) {
      profilerCommand += ",attributes=tag1;tag2;tag3";
    }
    return profilerCommand;
  }

  protected abstract String getProfilerCommand();


  protected void verifyEventsPresent(String... expectedEventTypes) {
    verifyEventsPresent(jfrDump, expectedEventTypes);
  }

  protected void verifyEventsPresent(Path recording, String... expectedEventTypes) {
    try {
      JfrEvents events = JfrEvents.load(recording, new HashSet<>(Arrays.asList(expectedEventTypes))::contains);
      for (String expectedEventType : expectedEventTypes) {
        JfrEvents filtered = events.byType(expectedEventType);
        assertTrue(filtered.hasItems(),
                expectedEventType + " was empty for " + getAmendedProfilerCommand());
        System.out.println(expectedEventType + " count: " + filtered.count());
      }
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t.getMessage(), t);
    }
  }

  /**
   * Like {@link #verifyEventsPresent}, but for a single event type where the caller doesn't need
   * the materialized collection back — stops parsing as soon as one matching event is found
   * (see {@link JfrEvents#load(Path, Predicate, Predicate)}), instead of resolving every event of
   * a possibly high-volume type just to confirm it's non-empty.
   */
  protected void verifyEventPresent(String eventType) {
    verifyEventPresent(jfrDump, eventType);
  }

  protected void verifyEventPresent(Path recording, String eventType) {
    try {
      JfrEvents events = JfrEvents.load(recording, eventType::equals, item -> true);
      assertTrue(events.hasItems(), eventType + " was empty for " + getAmendedProfilerCommand());
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t, t);
    }
  }

  /**
   * Materializes every matching event, deep-resolved (including its stack trace, if the event
   * type has one), into memory. For high-volume event types, prefer {@link #verifyEventPresent}
   * (presence only), {@link #streamEvents} (per-event checks) or {@link #reduceEvents} (folding into an
   * accumulator) to avoid exhausting the test heap.
   */
  public final JfrEvents verifyEvents(String eventType) {
    return verifyEvents(eventType, true);
  }

  protected JfrEvents verifyEvents(String eventType, boolean failOnEmpty) {
    return verifyEvents(jfrDump, eventType, failOnEmpty);
  }

  protected JfrEvents verifyEvents(Path recording, String eventType, boolean failOnEmpty) {
    try {
      JfrEvents collection = JfrEvents.load(recording, eventType);
      System.out.println(eventType + " count: " + collection.count());
      if (failOnEmpty) {
        assertTrue(collection.hasItems(),
                eventType + " was empty for " + getAmendedProfilerCommand());
      }
      return collection;
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t, t);
      return null;
    }
  }

  /**
   * Like {@link #verifyEvents(String)}, but for callers that only need per-event checks and/or a
   * count (e.g. {@code NativememSampledProfilerTest}'s per-sample field validation) rather than
   * the materialized {@link JfrEvents} collection — never holds more than one event in memory at
   * a time. See {@link JfrEvents#forEach} for the idempotency requirement on {@code consumer}.
   */
  protected long streamEvents(String eventType, Consumer<JfrEvent> consumer) {
    return streamEvents(jfrDump, eventType, consumer);
  }

  protected long streamEvents(Path recording, String eventType, Consumer<JfrEvent> consumer) {
    try {
      return JfrEvents.forEach(recording, eventType::equals, consumer);
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t, t);
      return 0;
    }
  }

  /**
   * Like {@link #streamEvents}, but for callers that fold matching events into an accumulator
   * (e.g. {@code NativeLibrariesTest}'s per-mode/per-library sample counts) instead of running
   * independent per-event checks. See {@link JfrEvents#reduce} for the per-attempt reset contract.
   */
  protected <T> T reduceEvents(String eventType, Supplier<T> initial, BiConsumer<T, JfrEvent> accumulator) {
    return reduceEvents(jfrDump, eventType, initial, accumulator);
  }

  protected <T> T reduceEvents(Path recording, String eventType, Supplier<T> initial, BiConsumer<T, JfrEvent> accumulator) {
    try {
      return JfrEvents.reduce(recording, eventType::equals, initial, accumulator);
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t, t);
      return null;
    }
  }

  protected final void verifyCStackSettings() {
    String cstack = (String)testParams.get("cstack");
    if (cstack == null) {
      // not a forced cstack mode
      return;
    }
    JfrEvents settings = verifyEvents("jdk.ActiveSetting");
    for (JfrEvent item : settings) {
      String name = item.getString("name");
      if ("cstack".equals(name)) {
        assertEquals(cstack, item.getString("value"));
      }
    }
  }

  protected void verifyStackTraces(String eventType, String... patterns) {
    verifyStackTraces(jfrDump, eventType, patterns);
  }

  protected void verifyStackTraces(Path recording, String eventType, String... patterns) {
    Set<String> unmatched = new HashSet<>(Arrays.asList(patterns));
    long[] cumulatedEvents = {0};
    try {
      // Stops parsing once every pattern has matched, instead of materializing every event of
      // eventType up front — see JfrEvents.load(Path, Predicate, Predicate).
      JfrEvents.load(recording, eventType::equals, item -> {
        cumulatedEvents[0]++;
        String stackTrace = item.getStackTraceString();
        unmatched.removeIf(stackTrace::contains);
        return unmatched.isEmpty();
      });
    } catch (Throwable t) {
      fail(getProfilerCommand() + " " + t, t);
    }
    assertNotEquals(0, cumulatedEvents[0], "no events found for " + eventType);
    assertTrue(unmatched.isEmpty(), "couldn't find " + eventType + " with " + unmatched);
  }

  /**
   * Returns the value of a named counter from {@code datadog.ProfilerCounter} events in the JFR
   * recording. These events are written before the final cleanup ({@code processTraces}), so they
   * capture the pre-cleanup state.
   *
   * @return the counter value, or -1 if no matching event is found
   */
  public long getRecordedCounterValue(String counterName) {
    JfrEvents events = verifyEvents("datadog.ProfilerCounter", false);
    for (JfrEvent item : events) {
      String name = item.getString(NAME);
      if (counterName.equals(name)) {
        return item.getLong(COUNT, -1);
      }
    }
    return -1;
  }
}
