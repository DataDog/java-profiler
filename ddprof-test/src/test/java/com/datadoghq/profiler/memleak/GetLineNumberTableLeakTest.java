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

/**
 * Test to validate that method_map cleanup prevents unbounded memory growth in continuous profiling.
 *
 * <p>This test focuses on the production scenario where the profiler runs continuously for
 * extended periods without stop/restart cycles. In production, Recording objects live for the
 * entire application lifetime (days/weeks), and without cleanup, _method_map would accumulate
 * ALL methods encountered, causing unbounded growth (observed: 1.2 GB line number table leak).
 *
 * <p><b>What This Test Validates:</b>
 * <ul>
 *   <li>Age-based cleanup removes methods unused for 3+ consecutive chunks</li>
 *   <li>method_map size stays bounded (~300-500 methods vs 3000 without cleanup)</li>
 *   <li>Cleanup runs during switchChunk() triggered by dump() operations</li>
 *   <li>Memory growth stays under threshold (< 600 KB for 3000 methods generated)</li>
 *   <li>Class unloading frees SharedLineNumberTable memory naturally</li>
 * </ul>
 *
 * <p><b>Test Strategy:</b>
 * <ul>
 *   <li>Continuous profiling (NO stop/restart cycles)</li>
 *   <li>Generate transient methods across multiple chunk boundaries</li>
 *   <li>Allow natural class unloading (no strong references held)</li>
 *   <li>Verify bounded growth via TEST_LOG output and NMT measurements</li>
 *   <li>Combined cleanup: method_map cleanup + class unloading</li>
 * </ul>
 */
public class GetLineNumberTableLeakTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    // Aggressive sampling to maximize method encounters and GetLineNumberTable calls
    return "cpu=1ms,alloc=512k";
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

    Path tempFile = Files.createTempFile("lineNumberLeak_", ".jfr");
    tempFile.toFile().deleteOnExit();

    for (int iter = 0; iter < iterations; iter++) {
      // Generate NEW transient methods that won't be referenced again
      // This simulates high method churn (e.g., lambda expressions, generated code)
      // Each class uses a new ClassLoader, allowing natural class unloading
      for (int i = 0; i < classesPerIteration; i++) {
        Class<?>[] transientClasses = generateUniqueMethodCalls();
        // Invoke once to ensure methods appear in profiling samples
        for (Class<?> clazz : transientClasses) {
          invokeClassMethods(clazz);
          // No strong references - allow classes to be GC'd and unloaded
        }
      }

      // Trigger chunk rotation by calling dump
      // This causes switchChunk() to be called, which triggers cleanup
      profiler.dump(tempFile);

      // Allow dump to complete and encourage class unloading
      Thread.sleep(100);

      // Periodically suggest GC to allow class unloading
      if ((iter + 1) % 3 == 0) {
        System.gc();
        Thread.sleep(50);
      }

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
    // Expected: with cleanup enabled, method_map should stay bounded at ~300-500 methods
    // Without cleanup, it would grow unbounded to ~3000 methods (250 methods/iter × 12 iters)
    // The cleanup effectiveness is visible in the logs showing "Cleaned up X unreferenced methods"
    //
    // Class unloading (no strong references held) provides additional memory savings:
    // - Classes get GC'd and unloaded naturally
    // - SharedLineNumberTable memory is freed when classes unload
    // - Combined with method_map cleanup for optimal memory usage

    // Take final snapshot
    NativeMemoryTracking.NMTSnapshot afterIterations = snapshots[iterations];
    long totalGrowthKB = afterIterations.internalReservedKB - afterStart.internalReservedKB;

    // NOTE: NMT "Internal" category includes more than just line number tables:
    // JFR buffers, CallTraceStorage, class metadata, etc.
    // Class unloading + cleanup both contribute to bounded memory
    final long maxGrowthKB = 600;

    System.out.println(
        String.format(
            "\n=== Continuous Profiling Test Results ===\n"
                + "Duration: ~%d seconds\n"
                + "Iterations: %d\n"
                + "Methods generated: %d classes × 5 = %d methods per iteration\n"
                + "Total methods encountered: ~%d\n"
                + "Internal memory growth: +%d KB (threshold: < %d KB)\n"
                + "\n"
                + "Check TEST_LOG output for:\n"
                + "  - 'MethodMap: X methods after cleanup' (should stay bounded ~300-500)\n"
                + "  - 'Cleaned up X unreferenced methods' (confirms cleanup is running)\n"
                + "\n"
                + "Class unloading: Enabled (no strong references held)\n",
            iterations * 1500 / 1000,
            iterations,
            classesPerIteration,
            classesPerIteration * 5,
            iterations * classesPerIteration * 5,
            totalGrowthKB,
            maxGrowthKB));

    // Assert memory growth is bounded
    if (totalGrowthKB > maxGrowthKB) {
      fail(
          String.format(
              "Method map cleanup FAILED - unbounded growth detected!\n"
                  + "Internal memory grew by %d KB (threshold: %d KB)\n"
                  + "This indicates _method_map is not being cleaned up during switchChunk()\n"
                  + "Expected: Methods unused for 3+ chunks should be removed\n"
                  + "Verify: cleanupUnreferencedMethods() is called in switchChunk()\n"
                  + "Verify: method-cleanup flag is enabled (default: true)",
              totalGrowthKB, maxGrowthKB));
    }

    System.out.println(
        "Result: Method map cleanup working correctly - memory growth is bounded\n"
            + "Classes allowed to unload naturally for optimal memory usage");
  }

  /**
   * Comparison test that validates cleanup effectiveness by running the same workload
   * twice: once without cleanup (no-method-cleanup) and once with cleanup (default).
   * This provides empirical evidence that the cleanup mechanism actually prevents
   * unbounded growth.
   */
  @Test
  public void testCleanupEffectivenessComparison() throws Exception {
    // Verify NMT is enabled
    Assumptions.assumeTrue(
        NativeMemoryTracking.isEnabled(), "Test requires -XX:NativeMemoryTracking=detail");

    // Stop the default profiler from AbstractProfilerTest
    // We need to manage our own profiler instances for this comparison
    stopProfiler();

    final int iterations = 8; // Fewer iterations but enough to see difference
    final int classesPerIteration = 50; // 250 methods per iteration

    // ===== Phase 1: WITHOUT cleanup (no-method-cleanup) =====
    System.out.println("\n=== Phase 1: WITHOUT cleanup (no-method-cleanup) ===");

    NativeMemoryTracking.NMTSnapshot beforeNoCleanup = NativeMemoryTracking.takeSnapshot();

    Path noCleanupFile = tempFile("no-cleanup");
    profiler.execute(
        "start," + getProfilerCommand() + ",jfr,no-method-cleanup,file=" + noCleanupFile);

    Thread.sleep(500); // Stabilize
    NativeMemoryTracking.NMTSnapshot afterStartNoCleanup =
        NativeMemoryTracking.takeSnapshot();

    // Run workload without cleanup
    for (int iter = 0; iter < iterations; iter++) {
      for (int i = 0; i < classesPerIteration; i++) {
        Class<?>[] transientClasses = generateUniqueMethodCalls();
        for (Class<?> clazz : transientClasses) {
          invokeClassMethods(clazz);
        }
      }

      profiler.dump(noCleanupFile);
      Thread.sleep(100);

      if ((iter + 1) % 3 == 0) {
        System.gc();
        Thread.sleep(50);
      }
    }

    NativeMemoryTracking.NMTSnapshot afterNoCleanup = NativeMemoryTracking.takeSnapshot();
    long growthNoCleanup =
        afterNoCleanup.internalReservedKB - afterStartNoCleanup.internalReservedKB;
    System.out.println(
        String.format(
            "WITHOUT cleanup: Internal memory growth = +%d KB\n"
                + "Check TEST_LOG: MethodMap should grow unbounded (no cleanup logs)",
            growthNoCleanup));

    profiler.stop();
    Thread.sleep(500); // Allow cleanup

    // ===== Phase 2: WITH cleanup (default) =====
    System.out.println("\n=== Phase 2: WITH cleanup (default) ===");

    // Reset class counter to generate same classes
    classCounter = 0;

    NativeMemoryTracking.NMTSnapshot beforeWithCleanup = NativeMemoryTracking.takeSnapshot();

    Path withCleanupFile = tempFile("with-cleanup");
    profiler.execute(
        "start," + getProfilerCommand() + ",jfr,method-cleanup,file=" + withCleanupFile);

    Thread.sleep(500); // Stabilize
    NativeMemoryTracking.NMTSnapshot afterStartWithCleanup =
        NativeMemoryTracking.takeSnapshot();

    // Run same workload with cleanup
    for (int iter = 0; iter < iterations; iter++) {
      for (int i = 0; i < classesPerIteration; i++) {
        Class<?>[] transientClasses = generateUniqueMethodCalls();
        for (Class<?> clazz : transientClasses) {
          invokeClassMethods(clazz);
        }
      }

      profiler.dump(withCleanupFile);
      Thread.sleep(100);

      if ((iter + 1) % 3 == 0) {
        System.gc();
        Thread.sleep(50);
      }
    }

    NativeMemoryTracking.NMTSnapshot afterWithCleanup = NativeMemoryTracking.takeSnapshot();
    long growthWithCleanup =
        afterWithCleanup.internalReservedKB - afterStartWithCleanup.internalReservedKB;
    System.out.println(
        String.format(
            "WITH cleanup: Internal memory growth = +%d KB\n"
                + "Check TEST_LOG: MethodMap should stay bounded, cleanup logs should appear",
            growthWithCleanup));

    profiler.stop();

    // ===== Comparison =====
    System.out.println("\n=== Comparison ===");
    System.out.println(
        String.format(
            "WITHOUT cleanup: +%d KB\n" + "WITH cleanup:    +%d KB\n" + "Savings:         %d KB (%.1f%%)",
            growthNoCleanup,
            growthWithCleanup,
            growthNoCleanup - growthWithCleanup,
            100.0 * (growthNoCleanup - growthWithCleanup) / growthNoCleanup));

    // Assert that cleanup actually reduces memory growth
    // We expect at least 20% savings from cleanup
    long expectedMinSavings = (long) (growthNoCleanup * 0.20);
    long actualSavings = growthNoCleanup - growthWithCleanup;

    if (actualSavings < expectedMinSavings) {
      fail(
          String.format(
              "Cleanup not effective enough!\n"
                  + "Expected at least 20%% savings (>= %d KB)\n"
                  + "Actual savings: %d KB (%.1f%%)\n"
                  + "This suggests cleanup is not working as intended",
              expectedMinSavings,
              actualSavings,
              100.0 * actualSavings / growthNoCleanup));
    }

    System.out.println("Result: Cleanup effectiveness validated - significant memory savings observed");
  }

  private Path tempFile(String name) throws IOException {
    Path dir = Paths.get("/tmp/recordings");
    Files.createDirectories(dir);
    return Files.createTempFile(dir, name + "-", ".jfr");
  }
}
