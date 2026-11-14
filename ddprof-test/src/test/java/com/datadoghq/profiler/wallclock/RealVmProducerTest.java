/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import java.io.InputStream;
import java.lang.management.ManagementFactory;
import java.nio.file.Files;
import java.nio.file.Path;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/** Shared real-VM identity and retained-worker qualification checks. */
abstract class RealVmProducerTest extends AbstractProfilerTest {
  private static final String WORKER_NAME = "real-vm-producer";
  static final String DONOR_NAME = "real-vm-wrong-owner";
  private static final long BLOCKER = 0x665001L;
  private static final long UNBLOCKING_SPAN_ID = 0x665002L;
  private static volatile long workResult;

  protected abstract boolean expectsOpenJ9();

  @Override
  protected void withTestAssumptions() {
    assertEquals(expectsOpenJ9() ? "openj9" : "hotspot", System.getenv("DDPROF_EXPECTED_VM"));
    String vmName = System.getProperty("java.vm.name");
    assertNotNull(vmName, "Missing runtime VM identity");
    String normalizedName = vmName.toLowerCase(Locale.ROOT);
    if (expectsOpenJ9()) {
      assertTrue(normalizedName.contains("openj9"), "Expected genuine OpenJ9, got " + vmName);
      assertTrue(Platform.isJ9(), "Profiler platform detection disagrees with the real VM");
    } else {
      assertTrue(
          normalizedName.contains("hotspot") || normalizedName.contains("openjdk"),
          "Expected HotSpot, got " + vmName);
      assertFalse(normalizedName.contains("openj9"));
      assertFalse(Platform.isJ9());
      assertFalse(Platform.isZing());
    }
    assertEquals(vmName, ManagementFactory.getRuntimeMXBean().getVmName());
    System.out.println("REAL_VM availableProcessors=" + Runtime.getRuntime().availableProcessors());
    for (String property : runtimeProperties()) {
      assertNotNull(System.getProperty(property), "Missing runtime property " + property);
      assertFalse(System.getProperty(property).isEmpty(), "Empty runtime property " + property);
      System.out.println("REAL_VM " + property + "=" + System.getProperty(property));
    }
  }

  /** Creates any JVM recorder before the native engine can issue its first stack request. */
  @Override
  protected void beforeProfilerStart() throws Exception {
    beforeProducerWork();
  }

  /** The same live Java worker must remain usable across two distinct profiler sessions. */
  protected final void verifyRetainedWorkerAcrossRestart() throws Exception {
    ExecutorService worker = Executors.newSingleThreadExecutor(r -> new Thread(r, WORKER_NAME));
    ExecutorService donor = Executors.newSingleThreadExecutor(r -> new Thread(r, DONOR_NAME));
    Path second =
        Files.createTempFile(
            java.nio.file.Paths.get("/tmp/recordings"), "real-vm-producer-restart-", ".jfr");
    boolean restarted = false;
    try {
      if (!expectsOpenJ9()) {
        donor.submit(this::exerciseUnrelatedWork).get(10, TimeUnit.SECONDS);
        if (!delegatedStacks())
          worker.submit(this::exerciseUnrelatedWork).get(10, TimeUnit.SECONDS);
      }
      long firstId = worker.submit(this::exerciseProducer).get(10, TimeUnit.SECONDS);
      stopProfiler();
      verifyRecording(null, firstId);
      beforeProducerWork();
      profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + second.toAbsolutePath());
      restarted = true;
      if (!expectsOpenJ9()) {
        donor.submit(this::exerciseUnrelatedWork).get(10, TimeUnit.SECONDS);
        if (!delegatedStacks())
          worker.submit(this::exerciseUnrelatedWork).get(10, TimeUnit.SECONDS);
      }
      long secondId = worker.submit(this::exerciseProducer).get(10, TimeUnit.SECONDS);
      assertEquals(firstId, secondId, "The worker must survive the recording boundary");
      profiler.stop();
      restarted = false;
      verifyRecording(second, secondId);
    } finally {
      worker.shutdownNow();
      donor.shutdownNow();
      try {
        boolean workerStopped = worker.awaitTermination(5, TimeUnit.SECONDS);
        boolean donorStopped = donor.awaitTermination(5, TimeUnit.SECONDS);
        assertTrue(workerStopped && donorStopped, "Qualification worker or donor leaked");
      } finally {
        if (restarted) profiler.stop();
        if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) Files.deleteIfExists(second);
        else System.out.println("REAL_VM restart recording=" + second.toAbsolutePath());
      }
    }
  }

  /** Produces a genuine unrelated stack for the oracle's nonempty-stack negative control. */
  private void exerciseUnrelatedWork() {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(300);
    long result = 1;
    while (System.nanoTime() < deadline) {
      for (int i = 0; i < 256; i++) {
        result = result * 1103515245 + 12345;
      }
    }
    workResult = result;
  }

  /** Exercises real JNI entry points, with ordinary samples as the unsupported-engine control. */
  private long exerciseProducer() throws Exception {
    long wallStart = System.nanoTime();
    long deadline = wallStart + TimeUnit.MILLISECONDS.toNanos(300);
    long loopStart = System.nanoTime();
    long result = 1;
    while (System.nanoTime() < deadline) {
      for (int i = 0; i < 256; i++) {
        result = result * 1664525 + 1013904223;
      }
    }
    workResult = result;
    if ("datadog.ExecutionSample".equals(sampleEventType())) {
      System.out.println(
          "REAL_CPU_WORKER javaId="
              + Thread.currentThread().getId()
              + " wallNanos="
              + (System.nanoTime() - wallStart)
              + " setupNanos="
              + (loopStart - wallStart)
              + " threadCpuNanos="
              + ManagementFactory.getThreadMXBean().getCurrentThreadCpuTime());
      Path status = java.nio.file.Paths.get("/proc/thread-self/status");
      if (Files.isReadable(status)) {
        for (String line : Files.readAllLines(status)) {
          if (line.startsWith("Pid:") || line.startsWith("SigBlk:") || line.startsWith("SigPnd:")) {
            System.out.println("REAL_CPU_WORKER " + line);
          }
        }
      }
    }
    long token = profiler.beginTaskBlock();
    if (expectsOpenJ9()) {
      assertEquals(0L, token, "J9 wall engine must not activate unfiltered block tracking");
      assertFalse(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
    } else {
      assertNotEquals(0L, token, "HotSpot platform-thread JNI admission was rejected");
      Thread.sleep(50L);
      assertTrue(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
      assertFalse(
          profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID),
          "A token must close only once");
    }
    return Thread.currentThread().getId();
  }

  /** Requires real recording fields; absent values cannot masquerade as zero-valued data. */
  private void verifyRecording(Path recording, long workerId) throws Exception {
    verifyLoadedImages(recording);
    for (JfrEvent event : events(recording, "jdk.JVMInformation", true)) {
      assertEquals(System.getProperty("java.vm.name"), event.getString("jvmName"));
      assertEquals(System.getProperty("java.vm.version"), event.getString("jvmVersion"));
      assertNotNull(event.getLong("pid"), "Missing JVMInformation.pid");
      assertTrue(event.getLong("pid") > 0);
    }
    Map<String, String> properties = new HashMap<>();
    for (JfrEvent event : events(recording, "jdk.InitialSystemProperty", true)) {
      assertNotNull(event.getString("key"));
      assertNotNull(event.getString("value"));
      properties.put(event.getString("key"), event.getString("value"));
    }
    // JVMTI GetSystemProperties exposes VM-maintained properties, not all of
    // java.lang.System's Java-side defaults (e.g. java.vendor on HotSpot 25).
    for (String property : new String[] {"java.vm.name", "java.vm.version", "java.home"}) {
      assertEquals(
          System.getProperty(property),
          properties.get(property),
          "Recording is missing or misidentifies " + property);
    }
    for (String property : runtimeProperties()) {
      if (properties.containsKey(property)) {
        assertEquals(System.getProperty(property), properties.get(property));
      }
    }
    String engineSetting =
        "datadog.ExecutionSample".equals(sampleEventType()) ? "cpuEngine" : "wallEngine";
    boolean foundEngine = false;
    for (JfrEvent setting : events(recording, "jdk.ActiveSetting", true)) {
      if (!engineSetting.equals(setting.getString("name"))) continue;
      String engine = setting.getString("value");
      assertNotNull(engine, "Missing actual engine name");
      assertFalse(engine.isEmpty());
      assertNotEquals("None", engine, "A no-op engine cannot qualify ordinary samples");
      if (!expectsOpenJ9()) {
        assertEquals(
            delegatedStacks() ? "WallClock (JVMTI)" : "WallClock (ASGCT)",
            engine,
            "The actual selected wall engine must match the cell");
      } else if ("wallEngine".equals(engineSetting)) {
        assertEquals("J9WallClock", engine, "The explicit OpenJ9 JVMTI wall selector must be used");
      }
      System.out.println(
          "REAL_ENGINE recording="
              + (recording == null ? "initial" : recording)
              + " setting="
              + engineSetting
              + " selected="
              + engine);
      foundEngine = true;
    }
    assertTrue(foundEngine, "Missing actual " + engineSetting + " setting");
    boolean sampledWorker = false;
    int sampleCount = 0;
    int workerSampleCount = 0;
    int producerSampleCount = 0;
    Object unrelatedStack = null;
    Object wrongOwner = null;
    for (JfrEvent event : events(recording, sampleEventType(), true)) {
      sampleCount++;
      Object eventThread = event.get("eventThread");
      if (eventThread instanceof Map
          && DONOR_NAME.equals(((Map<?, ?>) eventThread).get("javaName"))) {
        assertNotNull(event.getThreadJavaId("eventThread"));
        assertNotEquals(workerId, event.getThreadJavaId("eventThread").longValue());
        wrongOwner = event.get("eventThread");
      }
      if (!isWorker(event, workerId)) continue;
      workerSampleCount++;
      assertNotNull(event.getLong("weight"), "Missing sample weight");
      assertTrue(event.getLong("weight") > 0);
      assertNotNull(event.getString("state"), "Missing sample state");
      if (event.getStackTraceString() != null
          && event.getStackTraceString().contains("RealVmProducerTest.exerciseUnrelatedWork")
          && !event.getStackTraceString().contains("RealVmProducerTest.exerciseProducer")) {
        unrelatedStack = event.get("stackTrace");
      }
      if (delegatedStacks()) {
        assertTrue(
            event.getLong("correlationId", 0L) > 0,
            "Delegated samples require a JVM stack correlation ID");
        assertTrue(event.getStackTrace().isEmpty(), "Delegated samples have no local stack");
        producerSampleCount++;
        sampledWorker = true;
      } else if (event.getStackTraceString() != null
          && event.getStackTraceString().contains("RealVmProducerTest.exerciseProducer")) {
        assertEquals(0L, event.getLong("correlationId", Long.MIN_VALUE));
        producerSampleCount++;
        sampledWorker = true;
      }
    }
    if (delegatedStacks()) {
      assertTrue(
          profiler.getDebugCounters().getOrDefault("jvmti_stacks_requested", 0L) > 0,
          "Each recording must actually request delegated stacks");
    }
    JfrEvents blocks = events(recording, "datadog.TaskBlock", !expectsOpenJ9());
    int blockCount = 0;
    int producerBlockCount = 0;
    for (JfrEvent block : blocks) {
      blockCount++;
      if (block.getLong("blocker", Long.MIN_VALUE) == BLOCKER) producerBlockCount++;
    }
    System.out.println(
        "REAL_POPULATION recording="
            + (recording == null ? "initial" : recording)
            + " sampleType="
            + sampleEventType()
            + " samples="
            + sampleCount
            + " workerSamples="
            + workerSampleCount
            + " qualifyingSamples="
            + producerSampleCount
            + " taskBlocks="
            + blockCount
            + " producerTaskBlocks="
            + producerBlockCount
            + " workerJavaId="
            + workerId
            + " stackEvidence="
            + (delegatedStacks() ? "native-request-only" : "resolved-local"));
    assertTrue(sampledWorker, "No qualifying ordinary sample for the retained worker");
    if (expectsOpenJ9()) {
      assertFalse(blocks.hasItems(), "Unsupported J9 wall engine must not emit TaskBlock");
    } else {
      TaskBlockAssertions.assertNoAnchorFields(blocks);
      TaskBlockAssertions.assertNoCorrelationId(blocks);
      assertPairedBlock(blocks, workerId);
      for (JfrEvent block : blocks) {
        if (block.getLong("blocker", Long.MIN_VALUE) != BLOCKER) continue;
        assertNotNull(wrongOwner, "Missing recorded wrong-owner negative-control sample");
        Object originalOwner = block.raw().get("eventThread");
        try {
          block.raw().put("eventThread", wrongOwner);
          assertThrows(
              AssertionError.class,
              () -> assertPairedBlock(blocks, workerId),
              "The oracle must reject the actual other recorded thread");
        } finally {
          block.raw().put("eventThread", originalOwner);
        }
        if (!delegatedStacks()) {
          assertNotNull(unrelatedStack, "Missing real unrelated-stack negative-control sample");
          Object originalStack = block.raw().get("stackTrace");
          try {
            block.raw().put("stackTrace", unrelatedStack);
            assertThrows(
                AssertionError.class,
                () -> assertPairedBlock(blocks, workerId),
                "A genuine nonempty but unrelated stack must fail the TaskBlock oracle");
          } finally {
            block.raw().put("stackTrace", originalStack);
          }
        }
        for (String field : new String[] {"spanId", "localRootSpanId", "unblockingSpanId"}) {
          Object original = block.raw().get(field);
          try {
            block.raw().put(field, block.getLong(field) + 1L);
            assertThrows(
                AssertionError.class,
                () -> assertPairedBlock(blocks, workerId),
                "The oracle must reject corrupt observed attribution: " + field);
          } finally {
            block.raw().put(field, original);
          }
        }
      }
      List<JfrEvent> duplicates = new ArrayList<>();
      for (JfrEvent block : blocks) {
        duplicates.add(block);
        if (block.getLong("blocker", Long.MIN_VALUE) == BLOCKER) duplicates.add(block);
      }
      assertThrows(
          AssertionError.class,
          () -> assertPairedBlock(duplicates, workerId),
          "The qualification oracle must reject a duplicate of the real matching event");
      assertPairedBlock(blocks, workerId);
      System.out.println(
          "REAL_ORACLE restored=true wrongOwner=rejected duplicate=rejected"
              + " attribution=rejected unrelatedStack="
              + (!delegatedStacks() ? "rejected" : "not-local"));
    }
    verifyAdditionalRecording(recording, workerId);
  }

  /** Initializes the JVM recorder before native sampling can request its CPU-time sampler. */
  protected void beforeProducerWork() throws Exception {
    assertTrue(
        profiler.execute("status").contains("Profiler is not active"),
        "The JVM recorder must be initialized before native sampling can request stacks");
  }

  /** Verifies the VM-owned half separately from native request and direct-TaskBlock evidence. */
  protected void verifyAdditionalRecording(Path recording, long workerId) throws Exception {}

  /** Every event for our blocker must have exact attribution, workload stack and cardinality. */
  private static void assertPairedBlock(Iterable<JfrEvent> blocks, long workerId) {
    int matching = 0;
    for (JfrEvent event : blocks) {
      assertNotNull(event.getLong("blocker"), "Missing blocker");
      if (event.getLong("blocker") != BLOCKER) continue;
      assertTrue(isWorker(event, workerId), "TaskBlock attributed to the wrong worker");
      assertNotNull(event.getLong("duration"), "Missing TaskBlock duration");
      assertTrue(event.getLong("duration") > 0);
      assertEquals(Long.valueOf(0L), event.getLong("spanId"));
      assertEquals(Long.valueOf(0L), event.getLong("localRootSpanId"));
      assertEquals(Long.valueOf(UNBLOCKING_SPAN_ID), event.getLong("unblockingSpanId"));
      assertEquals("SLEEPING", event.getString("observedBlockingState"));
      assertNotNull(event.getStackTraceString(), "Missing TaskBlock stack");
      assertTrue(
          event.getStackTraceString().contains("RealVmProducerTest.exerciseProducer"),
          "TaskBlock must resolve the paired producer's own workload stack");
      matching++;
    }
    assertEquals(1, matching, "Exactly one TaskBlock must result from the successful close");
  }

  /** Bind the actual mapped profiler image to this test classpath, not just a requested path. */
  private void verifyLoadedImages(Path recording) throws Exception {
    String resource =
        "/META-INF/native-libs/"
            + (Platform.isMac() ? "macos" : "linux")
            + "-"
            + (Platform.isAarch64() ? "arm64" : "x64")
            + (Platform.isMusl() ? "-musl" : "")
            + "/libjavaProfiler."
            + (Platform.isMac() ? "dylib" : "so");
    String expectedHash;
    try (InputStream packaged = JavaProfiler.class.getResourceAsStream(resource)) {
      assertNotNull(packaged, "Missing candidate native resource " + resource);
      expectedHash = sha256(packaged);
    }
    boolean profilerMapped = false;
    boolean vmMapped = false;
    for (JfrEvent library : events(recording, "jdk.NativeLibrary", true)) {
      String name = library.getString("name");
      assertNotNull(name);
      boolean profilerImage = name.contains("javaProfiler-dd-tmp");
      boolean vmImage = expectsOpenJ9() ? name.contains("libj9vm") : name.contains("libjvm.");
      if (!profilerImage && !vmImage) continue;
      String hash;
      try (InputStream image = Files.newInputStream(java.nio.file.Paths.get(name))) {
        hash = sha256(image);
      }
      if (profilerImage) {
        assertEquals(expectedHash, hash, "Mapped profiler differs from the candidate classpath");
        profilerMapped = true;
      }
      vmMapped |= vmImage;
      System.out.println("REAL_IMAGE path=" + name + " sha256=" + hash);
    }
    assertTrue(profilerMapped, "No mapped candidate profiler image in the recording");
    assertTrue(vmMapped, "No actual VM image in the recording");
  }

  private static String sha256(InputStream input) throws Exception {
    MessageDigest digest = MessageDigest.getInstance("SHA-256");
    byte[] buffer = new byte[8192];
    int count;
    while ((count = input.read(buffer)) != -1) digest.update(buffer, 0, count);
    StringBuilder value = new StringBuilder();
    for (byte b : digest.digest()) value.append(String.format(Locale.ROOT, "%02x", b & 0xff));
    return value.toString();
  }

  private JfrEvents events(Path recording, String type, boolean required) {
    return recording == null
        ? verifyEvents(type, required)
        : verifyEvents(recording, type, required);
  }

  /** A matching name alone cannot prove retained-worker identity across recordings. */
  private static boolean isWorker(JfrEvent event, long workerId) {
    Object value = event.get("eventThread");
    assertTrue(value instanceof Map, "Missing resolved eventThread");
    Map<?, ?> thread = (Map<?, ?>) value;
    if (!WORKER_NAME.equals(thread.get("javaName"))) return false;
    assertTrue(thread.get("javaThreadId") instanceof Number, "Missing worker Java ID");
    assertEquals(workerId, ((Number) thread.get("javaThreadId")).longValue());
    return true;
  }

  private static String[] runtimeProperties() {
    return new String[] {
      "java.vm.name", "java.vm.version", "java.vendor", "java.version", "java.home", "os.arch"
    };
  }

  protected boolean delegatedStacks() {
    return false;
  }

  protected String sampleEventType() {
    return "datadog.MethodSample";
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,wallsampler=jvmti,filter=,wallprecheck=true";
  }
}
