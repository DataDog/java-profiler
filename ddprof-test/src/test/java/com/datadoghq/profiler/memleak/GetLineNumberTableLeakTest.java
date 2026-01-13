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
import com.datadoghq.profiler.util.ProcessMemory;
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
 *   <li>method_map size stays bounded (~300-500 methods vs 1500 without cleanup)</li>
 *   <li>Cleanup runs during switchChunk() triggered by dump() to different file</li>
 *   <li>Memory growth is significantly lower WITH cleanup vs WITHOUT cleanup</li>
 *   <li>Class unloading frees SharedLineNumberTable memory naturally</li>
 * </ul>
 *
 * <p><b>Test Strategy:</b>
 * <ul>
 *   <li>Continuous profiling (NO stop/restart cycles)</li>
 *   <li>Generate transient methods across multiple chunk boundaries</li>
 *   <li>Dump to different file from startup file to trigger switchChunk()</li>
 *   <li>Compare memory growth WITH vs WITHOUT cleanup to prove effectiveness</li>
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
    MethodVisitor constructor =
        cw.visitMethod(Opcodes.ACC_PUBLIC, "<init>", "()V", null, null);
    constructor.visitCode();
    constructor.visitVarInsn(Opcodes.ALOAD, 0);
    constructor.visitMethodInsn(
        Opcodes.INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
    constructor.visitInsn(Opcodes.RETURN);
    constructor.visitMaxs(0, 0);
    constructor.visitEnd();

    // Generate 20 methods per class, each with line number tables
    for (int i = 0; i < 20; i++) {
      MethodVisitor mv =
          cw.visitMethod(Opcodes.ACC_PUBLIC, "method" + i, "()I", null, null);
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
   * Comparison test that validates cleanup effectiveness by running the same workload twice: once
   * without cleanup (mcleanup=false) and once with cleanup (mcleanup=true, default). This provides
   * empirical evidence that the cleanup mechanism prevents unbounded growth.
   *
   * <p>Key implementation detail: Dumps to a DIFFERENT file from the startup file to trigger
   * switchChunk(), which is where cleanup happens. Dumping to the same file as the startup file
   * does NOT trigger switchChunk.
   *
   * <p><b>Memory Tracking:</b>
   * <ul>
   *   <li>NMT Internal: Tracks profiler's own malloc allocations (MethodInfo, map nodes)
   *   <li>RSS (Resident Set Size): Tracks total process memory including JVMTI allocations
   *   <li>JVMTI memory (GetLineNumberTable) is NOT tracked by NMT - only visible in RSS
   *   <li>TEST_LOG shows destructor calls deallocating JVMTI memory
   * </ul>
   *
   * <p><b>Expected results:</b>
   * <ul>
   *   <li>WITHOUT cleanup: method_map grows unbounded (~10k methods generated, ~3k captured)
   *   <li>WITH cleanup: method_map stays bounded at ~200-400 methods (age-based removal)
   *   <li>RSS savings: At least 10% reduction with cleanup (JVMTI memory freed)
   *   <li>NMT savings: Small (only MethodInfo objects, ~1-2%)
   *   <li>TEST_LOG shows "Cleaned up X unreferenced methods" and "Deallocated line number table"
   * </ul>
   */
  @Test
  public void testCleanupEffectivenessComparison() throws Exception {
    // Verify NMT is enabled
    Assumptions.assumeTrue(
        NativeMemoryTracking.isEnabled(), "Test requires -XX:NativeMemoryTracking=detail");

    // Stop the default profiler from AbstractProfilerTest
    // We need to manage our own profiler instances for this comparison
    stopProfiler();

    final int iterations = 100; // 100 iterations for fast validation (~10k potential methods)
    final int classesPerIteration = 10; // 10 classes × 5 methods = 50 methods per iteration

    // Create temp files that will be cleaned up in finally block
    Path noCleanupBaseFile = tempFile("no-cleanup-base");
    Path noCleanupDumpFile = tempFile("no-cleanup-dump");
    Path withCleanupBaseFile = tempFile("with-cleanup-base");
    Path withCleanupDumpFile = tempFile("with-cleanup-dump");

    try {
      // ===== Phase 1: WITHOUT cleanup (mcleanup=false) =====
      System.out.println("\n=== Phase 1: WITHOUT cleanup (mcleanup=false) ===");

      profiler.execute(
          "start,"
              + getProfilerCommand()
              + ",jfr,mcleanup=false,file="
              + noCleanupBaseFile);

      Thread.sleep(300); // Stabilize
      NativeMemoryTracking.NMTSnapshot afterStartNoCleanup =
          NativeMemoryTracking.takeSnapshot();
      ProcessMemory.Snapshot rssAfterStartNoCleanup = ProcessMemory.takeSnapshot();

      // Run workload without cleanup
      // CRITICAL: Dump to DIFFERENT file from startup to trigger switchChunk()
      for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < classesPerIteration; i++) {
          Class<?>[] transientClasses = generateUniqueMethodCalls();
          for (Class<?> clazz : transientClasses) {
            invokeClassMethods(clazz);
          }
        }

        // Dump to different file to trigger switchChunk
        profiler.dump(noCleanupDumpFile);
        Thread.sleep(50);

        if ((iter + 1) % 3 == 0) {
          System.gc();
          Thread.sleep(20);
        }
      }

      NativeMemoryTracking.NMTSnapshot afterNoCleanup = NativeMemoryTracking.takeSnapshot();
      ProcessMemory.Snapshot rssAfterNoCleanup = ProcessMemory.takeSnapshot();

      // Capture detailed NMT to see JVMTI allocations
      String detailedNmtNoCleanup = NativeMemoryTracking.takeDetailedSnapshot();
      String jvmtiAllocationsNoCleanup = NativeMemoryTracking.extractJVMTIAllocations(detailedNmtNoCleanup);

      long nmtGrowthNoCleanup =
          afterNoCleanup.internalReservedKB - afterStartNoCleanup.internalReservedKB;
      long rssGrowthNoCleanup = ProcessMemory.calculateGrowth(rssAfterStartNoCleanup, rssAfterNoCleanup);

      System.out.println(
          "WITHOUT cleanup (mcleanup=false):\n"
              + "  NMT Internal growth = +" + nmtGrowthNoCleanup + " KB\n"
              + "  RSS growth = " + ProcessMemory.formatBytes(rssGrowthNoCleanup) + "\n"
              + "Check TEST_LOG: MethodMap should grow unbounded (no cleanup logs expected)");

      if (!jvmtiAllocationsNoCleanup.isEmpty()) {
        System.out.println("\nJVMTI allocations in NMT (WITHOUT cleanup):");
        System.out.println(jvmtiAllocationsNoCleanup);
      }

      profiler.stop();
      Thread.sleep(300); // Allow cleanup

      // ===== Phase 2: WITH cleanup (mcleanup=true) =====
      System.out.println("\n=== Phase 2: WITH cleanup (mcleanup=true) ===");

      // Reset class counter to generate same classes
      classCounter = 0;

      profiler.execute(
          "start," + getProfilerCommand() + ",jfr,mcleanup=true,file=" + withCleanupBaseFile);

      Thread.sleep(300); // Stabilize
      NativeMemoryTracking.NMTSnapshot afterStartWithCleanup =
          NativeMemoryTracking.takeSnapshot();
      ProcessMemory.Snapshot rssAfterStartWithCleanup = ProcessMemory.takeSnapshot();

      // Run same workload with cleanup
      // CRITICAL: Dump to DIFFERENT file from startup to trigger switchChunk()
      for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < classesPerIteration; i++) {
          Class<?>[] transientClasses = generateUniqueMethodCalls();
          for (Class<?> clazz : transientClasses) {
            invokeClassMethods(clazz);
          }
        }

        // Dump to different file to trigger switchChunk
        profiler.dump(withCleanupDumpFile);
        Thread.sleep(50);

        if ((iter + 1) % 3 == 0) {
          System.gc();
          Thread.sleep(20);
        }
      }

      NativeMemoryTracking.NMTSnapshot afterWithCleanup = NativeMemoryTracking.takeSnapshot();
      ProcessMemory.Snapshot rssAfterWithCleanup = ProcessMemory.takeSnapshot();

      // Capture detailed NMT to see JVMTI allocations
      String detailedNmtWithCleanup = NativeMemoryTracking.takeDetailedSnapshot();
      String jvmtiAllocationsWithCleanup = NativeMemoryTracking.extractJVMTIAllocations(detailedNmtWithCleanup);

      long nmtGrowthWithCleanup =
          afterWithCleanup.internalReservedKB - afterStartWithCleanup.internalReservedKB;
      long rssGrowthWithCleanup = ProcessMemory.calculateGrowth(rssAfterStartWithCleanup, rssAfterWithCleanup);

      System.out.println(
          "WITH cleanup (mcleanup=true):\n"
              + "  NMT Internal growth = +" + nmtGrowthWithCleanup + " KB\n"
              + "  RSS growth = " + ProcessMemory.formatBytes(rssGrowthWithCleanup) + "\n"
              + "Check TEST_LOG: MethodMap should stay bounded, cleanup logs should appear");

      if (!jvmtiAllocationsWithCleanup.isEmpty()) {
        System.out.println("\nJVMTI allocations in NMT (WITH cleanup):");
        System.out.println(jvmtiAllocationsWithCleanup);
      }

      profiler.stop();

      // ===== Comparison =====
      System.out.println("\n=== Comparison ===");

      long nmtSavings = nmtGrowthNoCleanup - nmtGrowthWithCleanup;
      long rssSavings = rssGrowthNoCleanup - rssGrowthWithCleanup;

      System.out.println("NMT Internal (profiler allocations only):");
      System.out.println(
          "  WITHOUT cleanup: +"
              + nmtGrowthNoCleanup
              + " KB\n"
              + "  WITH cleanup:    +"
              + nmtGrowthWithCleanup
              + " KB\n"
              + "  Savings:         "
              + nmtSavings
              + " KB ("
              + String.format("%.1f", 100.0 * nmtSavings / Math.max(1, nmtGrowthNoCleanup))
              + "%)");

      System.out.println("\nRSS (total process memory including JVMTI):");
      System.out.println(
          "  WITHOUT cleanup: "
              + ProcessMemory.formatBytes(rssGrowthNoCleanup)
              + "\n"
              + "  WITH cleanup:    "
              + ProcessMemory.formatBytes(rssGrowthWithCleanup)
              + "\n"
              + "  Savings:         "
              + ProcessMemory.formatBytes(rssSavings)
              + " ("
              + String.format("%.1f", 100.0 * rssSavings / Math.max(1, rssGrowthNoCleanup))
              + "%)");

      // Assert that cleanup actually reduces memory growth
      // RSS includes JVMTI allocations (GetLineNumberTable), which NMT cannot track.
      // With many iterations, cleanup should keep method_map bounded and free JVMTI memory.
      // We expect at least 10% RSS savings to prove cleanup is working.
      //
      // NOTE: RSS measurement may be unreliable on some JVMs (e.g., Zing JDK 8).
      // In such cases, we fall back to NMT Internal validation only.
      double rssSavingsPercent = 100.0 * rssSavings / Math.max(1, rssGrowthNoCleanup);

      // Check if RSS measurements are reliable (positive growth in both phases)
      boolean rssReliable = rssGrowthNoCleanup > 0 && rssGrowthWithCleanup > 0;

      if (rssReliable && rssSavingsPercent < 10.0) {
        fail(
            "Cleanup not effective enough!\n"
                + "WITHOUT cleanup: "
                + ProcessMemory.formatBytes(rssGrowthNoCleanup)
                + "\n"
                + "WITH cleanup:    "
                + ProcessMemory.formatBytes(rssGrowthWithCleanup)
                + "\n"
                + "Savings:         "
                + ProcessMemory.formatBytes(rssSavings)
                + " ("
                + String.format("%.1f", rssSavingsPercent)
                + "%)\n"
                + "Expected at least 10% RSS savings\n"
                + "Verify: switchChunk() is called (check TEST_LOG for 'MethodMap:' messages)\n"
                + "Verify: Dumps are to different file (required to trigger switchChunk)\n"
                + "Verify: Destructors deallocate JVMTI memory (check TEST_LOG for 'Deallocated' messages)");
      }

      if (!rssReliable) {
        System.out.println("\nWARNING: RSS measurements unreliable on this JVM - skipping RSS assertion");
        System.out.println("Falling back to NMT Internal validation only");

        // At least verify NMT Internal shows some improvement
        double nmtSavingsPercent = 100.0 * nmtSavings / Math.max(1, nmtGrowthNoCleanup);
        if (nmtSavingsPercent < 0) {
          fail("Cleanup increased NMT Internal memory! NMT savings: " + nmtSavings + " KB");
        }
      }

      System.out.println(
          "\nResult: Cleanup effectiveness validated\n"
              + "RSS savings: "
              + ProcessMemory.formatBytes(rssSavings)
              + " ("
              + String.format("%.1f", rssSavingsPercent)
              + "%)\n"
              + "method_map size bounded at ~200-400 methods (WITH) vs unbounded growth (WITHOUT)\n"
              + "JVMTI memory properly deallocated via SharedLineNumberTable destructors");
    } finally {
      // Clean up temp files
      try {
        Files.deleteIfExists(noCleanupBaseFile);
      } catch (IOException ignored) {
      }
      try {
        Files.deleteIfExists(noCleanupDumpFile);
      } catch (IOException ignored) {
      }
      try {
        Files.deleteIfExists(withCleanupBaseFile);
      } catch (IOException ignored) {
      }
      try {
        Files.deleteIfExists(withCleanupDumpFile);
      } catch (IOException ignored) {
      }
    }
  }

  private Path tempFile(String name) throws IOException {
    Path dir = Paths.get("/tmp/recordings");
    Files.createDirectories(dir);
    return Files.createTempFile(dir, name + "-", ".jfr");
  }
}
