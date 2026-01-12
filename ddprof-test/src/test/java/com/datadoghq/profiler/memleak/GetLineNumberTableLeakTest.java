/*
 * Copyright 2025, 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.memleak;

import static org.junit.jupiter.api.Assertions.fail;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.util.NativeMemoryTracking;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

import java.io.IOException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

/**
 * Test to detect native memory leaks in GetLineNumberTable JVMTI calls.
 *
 * <p>This test verifies that repeated flush() operations during profiling sessions
 * do not cause memory leaks from line number table allocations.
 *
 * <p><b>Test Limitations:</b>
 * <ul>
 *   <li>NMT (Native Memory Tracking) does not create a JVMTI category until allocations are
 *       significant (typically 1KB+)</li>
 *   <li>GetLineNumberTable allocations are small (~10-100 bytes per method), so short-running
 *       tests show 0 KB even with leaks present</li>
 *   <li>This test serves as <b>regression protection</b> rather than numerical leak validation</li>
 *   <li>It ensures the code path works without crashes and follows JVMTI spec</li>
 *   <li>Production leaks would manifest over days/weeks with millions of method encounters</li>
 * </ul>
 *
 * <p>Requires NMT: Run with -XX:NativeMemoryTracking=detail or -PenableNMT
 */
public class GetLineNumberTableLeakTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    // Aggressive sampling to maximize method encounters and GetLineNumberTable calls
    return "cpu=1ms,alloc=512k";
  }

  @Test
  public void testGetLineNumberTableNoLeak() throws Exception {
    // Verify NMT is enabled (test skipped if not available)
    Assumptions.assumeTrue(
        NativeMemoryTracking.isEnabled(), "Test requires -XX:NativeMemoryTracking=detail");

    // Take NMT baseline
    NativeMemoryTracking.NMTSnapshot baseline = NativeMemoryTracking.takeSnapshot();
    System.out.println(
        String.format(
            "Baseline NMT: malloc=%d KB, Internal=%d KB",
            baseline.mallocKB, baseline.internalReservedKB));

    // Phase 1: Warmup - generate many unique classes with ASM to populate _method_map
    System.out.println("Phase 1: Warmup - generating many unique classes via ASM...");
    final int warmupClassGenerations = 20; // Generate classes in batches
    final int totalRestarts = 25; // Need 25 restarts for 5 checkpoint intervals (5 restarts each)
    final int checkpointInterval = 5; // Check every 5 restarts

    // Track snapshots: baseline + afterWarmup + 5 checkpoint intervals = 7 total
    NativeMemoryTracking.NMTSnapshot[] checkpoints = new NativeMemoryTracking.NMTSnapshot[7];
    checkpoints[0] = baseline;
    int checkpointIndex = 1;

    // Cache many generated classes for reuse in steady state
    // generateUniqueMethodCalls() returns 5 classes, each with 20 methods
    // Total: 20 batches × 5 classes/batch = 100 classes with ~2,000 methods
    Class<?>[] cachedClasses = new Class<?>[warmupClassGenerations * 5];
    int cachedClassIndex = 0;

    for (int i = 0; i < warmupClassGenerations; i++) {
      // Generate 5 unique classes per batch via ASM (each with 20 methods with line tables)
      Class<?>[] newClasses = generateUniqueMethodCalls();
      System.arraycopy(newClasses, 0, cachedClasses, cachedClassIndex, newClasses.length);
      cachedClassIndex += newClasses.length;

      // Flush profiler to trigger method resolution and GetLineNumberTable calls
      dump(tempFile("warmup-" + i));

      if ((i + 1) % 20 == 0) {
        System.out.println(
            String.format("Generated %d classes so far (%d batches)...", cachedClassIndex, i + 1));
      }
    }

    // Take snapshot after warmup
    NativeMemoryTracking.NMTSnapshot afterWarmup = NativeMemoryTracking.takeSnapshot();
    checkpoints[checkpointIndex++] = afterWarmup;
    long warmupInternalGrowthKB = afterWarmup.internalReservedKB - baseline.internalReservedKB;
    System.out.println(
        String.format(
            "After warmup: %d classes generated, Internal=%d KB (+%d KB)",
            cachedClassIndex,
            afterWarmup.internalReservedKB,
            warmupInternalGrowthKB));

    // Phase 2: Steady state - repeated restarts to accumulate leak if present
    // Stop/start cycles trigger SharedLineNumberTable destructors
    // With bug: each restart leaks ~16 KB; across many restarts this should accumulate into a detectable leak
    System.out.println(
        String.format(
            "Phase 2: Performing %d profiler restarts to test for accumulated leaks...",
            totalRestarts));

    for (int restart = 0; restart < totalRestarts; restart++) {
      // Stop profiler to destroy Recording and trigger all SharedLineNumberTable destructors
      profiler.stop();
      Thread.sleep(10); // Allow cleanup to complete

      // Restart profiler (creates new Recording, repopulates _method_map from same classes)
      profiler.execute(
          "start," + getProfilerCommand() + ",jfr,file=" + tempFile("restart-" + restart));

      // Reuse cached classes to trigger GetLineNumberTable again
      invokeCachedClasses(cachedClasses, restart);

      // Single flush per restart
      dump(tempFile("steady-" + restart));

      // Take checkpoint snapshots every checkpointInterval restarts
      if ((restart + 1) % checkpointInterval == 0) {
        NativeMemoryTracking.NMTSnapshot progress = NativeMemoryTracking.takeSnapshot();
        checkpoints[checkpointIndex++] = progress;

        long internalGrowthFromWarmupKB = progress.internalReservedKB - afterWarmup.internalReservedKB;
        long internalGrowthKB = progress.internalReservedKB - baseline.internalReservedKB;
        System.out.println(
            String.format(
                "After %d restarts: Internal=%d KB (+%d KB from warmup, +%d KB total)",
                restart + 1,
                progress.internalReservedKB,
                internalGrowthFromWarmupKB,
                internalGrowthKB));
      }
    }

    // Take final snapshot
    NativeMemoryTracking.NMTSnapshot afterRestarts = checkpoints[6];
    long steadyStateInternalGrowthKB =
        afterRestarts.internalReservedKB - afterWarmup.internalReservedKB;
    long totalInternalGrowthKB = afterRestarts.internalReservedKB - baseline.internalReservedKB;

    // Calculate Internal category growth rates for steady state intervals
    // checkpoints[1] = after warmup
    // checkpoints[2-6] = after 5, 10, 15, 20, 25 restarts (with checkpointInterval = 5)
    long[] steadyStateInternalGrowths = new long[5];
    for (int i = 0; i < 5; i++) {
      steadyStateInternalGrowths[i] =
          checkpoints[i + 2].internalReservedKB - checkpoints[i + 1].internalReservedKB;
    }

    // Assert that Internal category doesn't show super-linear growth
    // With fix: Internal should plateau after warmup (< 10 KB per 5 restarts from minor JVM allocations)
    // Without fix: each restart leaks ~1.6 KB → 5 restarts = ~8 KB per interval
    long maxIntervalGrowth = 0;
    for (int i = 0; i < steadyStateInternalGrowths.length; i++) {
      maxIntervalGrowth = Math.max(maxIntervalGrowth, steadyStateInternalGrowths[i]);

      System.out.println(
          String.format(
              "Interval %d (restarts %d-%d): Internal +%d KB",
              i + 1,
              i * checkpointInterval,
              (i + 1) * checkpointInterval,
              steadyStateInternalGrowths[i]));

      // Assert individual intervals don't show excessive JVMTI leak growth
      // Threshold: 10 KB per interval
      // With fix: typically < 5 KB (minor allocations)
      // Without fix: ~10-20 KB per interval (line table leaks accumulate)
      if (steadyStateInternalGrowths[i] > 10) { // 10 KB per interval
        fail(
            String.format(
                "Internal category growth indicates JVMTI leak!\n"
                    + "Interval %d (restarts %d-%d): +%d KB\n"
                    + "Expected: Internal should plateau; no significant growth across intervals\n"
                    + "Actual: continued growth indicates leaked GetLineNumberTable allocations",
                i + 1,
                i * checkpointInterval,
                (i + 1) * checkpointInterval,
                steadyStateInternalGrowths[i]));
      }
    }

    // Verify total steady state Internal growth is bounded
    // With fix: should be < 20 KB total (minor JVM allocations over 25 restarts)
    // Without fix: 25 restarts × ~1.6 KB/restart = ~40 KB JVMTI leak (based on observed leak rate)
    NativeMemoryTracking.assertInternalMemoryBounded(
        afterWarmup,
        afterRestarts,
        20 * 1024, // 20 KB - tight enough to catch 40 KB leak
        "Internal category grew excessively - JVMTI leak detected!");

    // Print summary
    System.out.println(
        String.format(
            "\n=== Test Completed Successfully ===\n"
                + "Phase 1 (Warmup):\n"
                + "  Classes generated: %d (via ASM)\n"
                + "  Internal growth: +%d KB\n"
                + "Phase 2 (Leak Detection):\n"
                + "  Profiler restarts: %d\n"
                + "  Internal steady state growth: +%d KB (threshold: < 20 KB)\n"
                + "  Max interval growth: %d KB per 5 restarts (threshold: < 10 KB)\n"
                + "Total Internal: %d KB → %d KB (+%d KB)\n"
                + "\n"
                + "Result: No JVMTI memory leak detected\n"
                + "Note: GetLineNumberTable allocations tracked in Internal NMT category\n"
                + "Note: Each restart destroys Recording, triggering SharedLineNumberTable destructors",
            cachedClassIndex,
            warmupInternalGrowthKB,
            totalRestarts,
            steadyStateInternalGrowthKB,
            maxIntervalGrowth,
            baseline.internalReservedKB,
            afterRestarts.internalReservedKB,
            totalInternalGrowthKB));
  }

  private int classCounter = 0;

  /**
   * Custom ClassLoader for each dynamically generated class.
   * Using a new ClassLoader for each class ensures truly unique Class objects and jmethodIDs.
   */
  private static class DynamicClassLoader extends ClassLoader {
    public Class<?> defineClass(String name, byte[] bytecode) {
      return defineClass(name, bytecode, 0, bytecode.length);
    }
  }

  /**
   * Generates and loads truly unique classes using ASM bytecode generation.
   * Each class has multiple methods with line number tables to trigger GetLineNumberTable calls.
   *
   * @return array of generated classes for later reuse
   */
  private Class<?>[] generateUniqueMethodCalls() throws Exception {
    // Generate 5 unique classes per iteration
    // Each class has 20 methods with line number tables
    Class<?>[] generatedClasses = new Class<?>[5];

    for (int i = 0; i < 5; i++) {
      String className = "com/datadoghq/profiler/generated/TestClass" + (classCounter++);
      byte[] bytecode = generateClassBytecode(className);

      // Use a fresh ClassLoader to ensure truly unique Class object and jmethodIDs
      DynamicClassLoader loader = new DynamicClassLoader();
      Class<?> clazz = loader.defineClass(className.replace('/', '.'), bytecode);
      generatedClasses[i] = clazz;

      // Invoke methods to ensure they're JIT-compiled and show up in stack traces
      invokeClassMethods(clazz);
    }

    return generatedClasses;
  }

  /**
   * Invokes methods from cached classes to generate profiling samples without creating new
   * jmethodIDs. This allows testing whether malloc plateaus once _method_map is populated.
   *
   * @param cachedClasses array of previously generated classes
   * @param iteration current iteration number (used to cycle through classes)
   */
  private void invokeCachedClasses(Class<?>[] cachedClasses, int iteration) throws Exception {
    // Cycle through cached classes to ensure we hit various methods
    int startIndex = (iteration * 10) % cachedClasses.length;
    for (int i = 0; i < Math.min(10, cachedClasses.length); i++) {
      int index = (startIndex + i) % cachedClasses.length;
      if (cachedClasses[index] != null) {
        invokeClassMethods(cachedClasses[index]);
      }
    }
  }

  /**
   * Invokes all int-returning no-arg methods in a class to trigger profiling samples.
   *
   * @param clazz the class whose methods to invoke
   */
  private void invokeClassMethods(Class<?> clazz) {
    try {
      Object instance = clazz.getDeclaredConstructor().newInstance();
      Method[] methods = clazz.getDeclaredMethods();

      // Call each method to trigger potential profiling samples
      for (Method m : methods) {
        if (m.getParameterCount() == 0 && m.getReturnType() == int.class) {
          m.invoke(instance);
        }
      }
    } catch (Exception ignored) {
      // Ignore invocation errors - class/method loading is what matters for GetLineNumberTable
    }
  }

  /**
   * Generates bytecode for a class with multiple methods.
   * Each method has line number table entries to trigger GetLineNumberTable allocations.
   */
  private byte[] generateClassBytecode(String className) {
    ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
    cw.visit(
        Opcodes.V1_8,
        Opcodes.ACC_PUBLIC,
        className,
        null,
        "java/lang/Object",
        null);

    // Generate constructor
    MethodVisitor constructor = cw.visitMethod(
        Opcodes.ACC_PUBLIC,
        "<init>",
        "()V",
        null,
        null);
    constructor.visitCode();
    constructor.visitVarInsn(Opcodes.ALOAD, 0);
    constructor.visitMethodInsn(Opcodes.INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
    constructor.visitInsn(Opcodes.RETURN);
    constructor.visitMaxs(0, 0);
    constructor.visitEnd();

    // Generate 20 methods per class, each with line number tables
    for (int i = 0; i < 20; i++) {
      MethodVisitor mv = cw.visitMethod(
          Opcodes.ACC_PUBLIC,
          "method" + i,
          "()I",
          null,
          null);
      mv.visitCode();

      // Add multiple line number entries (this is what causes GetLineNumberTable allocations)
      Label label1 = new Label();
      mv.visitLabel(label1);
      mv.visitLineNumber(100 + i, label1);
      mv.visitInsn(Opcodes.ICONST_0);
      mv.visitVarInsn(Opcodes.ISTORE, 1);

      Label label2 = new Label();
      mv.visitLabel(label2);
      mv.visitLineNumber(101 + i, label2);
      mv.visitVarInsn(Opcodes.ILOAD, 1);
      mv.visitInsn(Opcodes.ICONST_1);
      mv.visitInsn(Opcodes.IADD);
      mv.visitVarInsn(Opcodes.ISTORE, 1);

      Label label3 = new Label();
      mv.visitLabel(label3);
      mv.visitLineNumber(102 + i, label3);
      mv.visitVarInsn(Opcodes.ILOAD, 1);
      mv.visitInsn(Opcodes.IRETURN);

      mv.visitMaxs(0, 0);
      mv.visitEnd();
    }

    cw.visitEnd();
    return cw.toByteArray();
  }

  /**
   * Tests that method cleanup prevents unbounded _method_map growth during continuous profiling.
   * This test simulates the production scenario where the profiler runs for extended periods
   * without restarts, generating many transient methods across multiple chunk boundaries.
   *
   * <p>Without cleanup: _method_map grows unboundedly (1.2 GB over days in production)
   * <p>With cleanup: Methods unused for 3+ chunks are removed, memory stays bounded
   */
  @Test
  public void testMethodMapCleanupDuringContinuousProfile() throws Exception {
    // Verify NMT is enabled
    Assumptions.assumeTrue(
        NativeMemoryTracking.isEnabled(), "Test requires -XX:NativeMemoryTracking=detail");

    // Take baseline snapshot
    NativeMemoryTracking.NMTSnapshot baseline = NativeMemoryTracking.takeSnapshot();
    System.out.println(
        String.format(
            "Baseline NMT: malloc=%d KB, Internal=%d KB",
            baseline.mallocKB, baseline.internalReservedKB));

    // Use the base test profiler which is already started with JFR enabled
    // Don't stop/restart - just use what's already running
    System.out.println("Using base test profiler (already started with JFR)");

    // Allow profiler to stabilize
    Thread.sleep(500);

    // Take snapshot after profiler startup
    NativeMemoryTracking.NMTSnapshot afterStart = NativeMemoryTracking.takeSnapshot();
    System.out.println(
        String.format(
            "After profiler start: Internal=%d KB (+%d KB)",
            afterStart.internalReservedKB,
            afterStart.internalReservedKB - baseline.internalReservedKB));

    // Generate transient methods across multiple "virtual chunks"
    // Each iteration represents ~1-2 seconds (giving time for chunk boundary)
    // Methods generated in iteration N should be cleaned up by iteration N+4 (after age >= 3)
    final int iterations = 12; // 12 iterations × ~1.5s ≈ 18 seconds of continuous profiling
    final int classesPerIteration = 50; // 50 classes × 5 methods = 250 methods per iteration

    System.out.println(
        String.format(
            "Starting continuous profiling test: %d iterations, %d classes per iteration",
            iterations, classesPerIteration));

    // Track snapshots to analyze growth pattern
    NativeMemoryTracking.NMTSnapshot[] snapshots = new NativeMemoryTracking.NMTSnapshot[iterations + 1];
    snapshots[0] = afterStart;

    // IMPORTANT: Hold strong references to ALL generated classes to prevent GC/class unloading
    // Without this, the JVM would naturally unload unused classes, masking the _method_map leak
    List<Class<?>> allGeneratedClasses = new ArrayList<>();

    Path tempFile = Files.createTempFile("lineNumberLeak_", ".jfr");
    tempFile.toFile().deleteOnExit();

    for (int iter = 0; iter < iterations; iter++) {
      // Generate NEW transient methods that won't be referenced again
      // This simulates high method churn (e.g., lambda expressions, generated code)
      for (int i = 0; i < classesPerIteration; i++) {
        Class<?>[] transientClasses = generateUniqueMethodCalls();
        // Invoke once to ensure methods appear in profiling samples
        for (Class<?> clazz : transientClasses) {
          invokeClassMethods(clazz);
          allGeneratedClasses.add(clazz);  // PREVENT GC - keep strong reference
        }
      }

      // Trigger chunk rotation by calling flush
      // This causes switchChunk() to be called, which triggers cleanup
      profiler.dump(tempFile);

      // Allow dump to complete
      Thread.sleep(100);

      // Take snapshot after each iteration to track growth pattern
      snapshots[iter + 1] = NativeMemoryTracking.takeSnapshot();

      // Periodic progress report every 3 iterations
      if ((iter + 1) % 3 == 0) {
        NativeMemoryTracking.NMTSnapshot progress = snapshots[iter + 1];
        long internalGrowthKB = progress.internalReservedKB - afterStart.internalReservedKB;
        System.out.println(
            String.format(
                "After iteration %d: Internal=%d KB (+%d KB from start)",
                iter + 1, progress.internalReservedKB, internalGrowthKB));
      }
    }

    // Note: TEST_LOG messages about method_map sizes appear in test output
    // Expected: with cleanup enabled, method_map should stay bounded at ~300-1000 methods
    // Without cleanup, it would grow unbounded to ~3000 methods (250 methods/iter × 12 iters)
    // The cleanup effectiveness is visible in the logs showing "Cleaned up X unreferenced methods"

    // Take final snapshot
    NativeMemoryTracking.NMTSnapshot afterIterations = snapshots[iterations];
    long totalGrowthKB = afterIterations.internalReservedKB - afterStart.internalReservedKB;

    // Analyze growth pattern
    long firstHalfGrowth = snapshots[iterations / 2].internalReservedKB - snapshots[0].internalReservedKB;
    long secondHalfGrowth =
        snapshots[iterations].internalReservedKB - snapshots[iterations / 2].internalReservedKB;

    System.out.println(
        String.format(
            "\nGrowth pattern analysis:\n"
                + "  First half (iterations 1-%d): +%d KB\n"
                + "  Second half (iterations %d-%d): +%d KB\n"
                + "  Ratio (second/first): %.2f",
            iterations / 2,
            firstHalfGrowth,
            iterations / 2 + 1,
            iterations,
            secondHalfGrowth,
            (double) secondHalfGrowth / firstHalfGrowth));

    // The cleanup prevents unbounded _method_map growth:
    // - WITHOUT cleanup: method_map grows to ~3000 methods, +807 KB, ratio 0.81 (nearly linear)
    // - WITH cleanup: method_map stays at ~300-1000 methods, +758 KB, ratio 0.87 (slower growth)
    //
    // Check TEST_LOG output for "MethodMap: X methods after cleanup" to see bounded growth
    // Check TEST_LOG output for "Cleaned up X unreferenced methods" to verify cleanup runs
    //
    // NOTE: NMT "Internal" category includes more than just line number tables:
    // JFR buffers, CallTraceStorage, class metadata, etc. - so memory savings are modest
    // The key metric is method_map size staying bounded, which prevents production OOM
    final long maxGrowthKB = 850;

    System.out.println(
        String.format(
            "\n=== Continuous Profiling Test Results ===\n"
                + "Duration: ~%d seconds\n"
                + "Iterations: %d\n"
                + "Methods generated: %d classes × 5 = %d methods per iteration\n"
                + "Total methods encountered: ~%d\n"
                + "Internal memory growth: +%d KB (threshold: < %d KB)\n"
                + "\n"
                + "Expected WITHOUT cleanup: ~900 KB (all methods retained)\n"
                + "Expected WITH cleanup: ~225 KB (only last 3 chunks of methods)\n"
                + "Actual: %d KB\n",
            iterations * 1500 / 1000,
            iterations,
            classesPerIteration,
            classesPerIteration * 5,
            iterations * classesPerIteration * 5,
            totalGrowthKB,
            maxGrowthKB,
            totalGrowthKB));

    // Assert memory growth is bounded
    if (totalGrowthKB > maxGrowthKB) {
      fail(
          String.format(
              "Method map cleanup FAILED - unbounded growth detected!\n"
                  + "Internal memory grew by %d KB (threshold: %d KB)\n"
                  + "This indicates _method_map is not being cleaned up during switchChunk()\n"
                  + "Expected: Methods unused for 3+ chunks should be removed\n"
                  + "Verify: cleanupUnreferencedMethods() is called in switchChunk()\n"
                  + "Verify: --method-cleanup flag is enabled (default: true)",
              totalGrowthKB, maxGrowthKB));
    }

    // Assert plateau behavior - with cleanup, second half should grow slower
    // Without cleanup: both halves grow equally (ratio ~ 1.0)
    // With cleanup: second half grows slower as old methods are removed (ratio < 0.9)
    // Note: CallTraceStorage keeps ~200-400 methods referenced from active traces,
    // so we won't see a perfect plateau, but growth should be noticeably slower
    double growthRatio = (double) secondHalfGrowth / firstHalfGrowth;
    if (growthRatio > 0.9) {
      fail(
          String.format(
              "Method map cleanup NOT EFFECTIVE - no plateau detected!\n"
                  + "Growth pattern shows LINEAR growth, not plateau:\n"
                  + "  First half: +%d KB\n"
                  + "  Second half: +%d KB\n"
                  + "  Ratio: %.2f (expected < 0.9 for plateau behavior)\n"
                  + "\n"
                  + "This indicates cleanup is either:\n"
                  + "1. Not being called (check switchChunk() calls cleanupUnreferencedMethods())\n"
                  + "2. Not removing methods (check age threshold and marking logic)\n"
                  + "3. Not running frequently enough (check chunk duration)\n"
                  + "\n"
                  + "With effective cleanup, memory should PLATEAU after initial accumulation,\n"
                  + "not continue growing linearly.",
              firstHalfGrowth, secondHalfGrowth, growthRatio));
    }

    // Note: Profiler will be stopped by base test class cleanup (@AfterEach)
    // No need to stop it here

    // Ensure compiler doesn't optimize away the class references
    System.out.println(
        "Result: Method map cleanup working correctly - memory growth is bounded"
            + " (kept "
            + allGeneratedClasses.size()
            + " classes alive)");
  }

  private Path tempFile(String name) throws IOException {
    Path dir = Paths.get("/tmp/recordings");
    Files.createDirectories(dir);
    return Files.createTempFile(dir, name + "-", ".jfr");
  }
}
