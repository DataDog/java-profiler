/*
 * Copyright 2025, Datadog, Inc
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
import java.util.stream.IntStream;

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

    // Phase 1: Warmup - generate unique classes to populate _method_map
    System.out.println("Phase 1: Warmup - generating unique classes...");
    final int warmupFlushes = 100;
    final int steadyStateFlushes = 200;
    final int checkpointInterval = 50;

    // Track snapshots to detect super-linear growth
    NativeMemoryTracking.NMTSnapshot[] checkpoints = new NativeMemoryTracking.NMTSnapshot[7];
    checkpoints[0] = baseline;
    int checkpointIndex = 1;

    // Cache the generated classes for reuse in steady state
    Class<?>[] cachedClasses = new Class<?>[warmupFlushes * 5];
    int cachedClassIndex = 0;

    for (int i = 0; i < warmupFlushes; i++) {
      // Generate unique classes and cache them
      Class<?>[] newClasses = generateUniqueMethodCalls();
      System.arraycopy(newClasses, 0, cachedClasses, cachedClassIndex, newClasses.length);
      cachedClassIndex += newClasses.length;

      // Flush profiler to trigger method resolution and GetLineNumberTable calls
      dump(tempFile("warmup-" + i));

      // Take checkpoint snapshots
      if ((i + 1) % checkpointInterval == 0) {
        NativeMemoryTracking.NMTSnapshot progress = NativeMemoryTracking.takeSnapshot();
        checkpoints[checkpointIndex++] = progress;

        long mallocGrowthKB = progress.mallocKB - baseline.mallocKB;
        long internalGrowthKB = progress.internalReservedKB - baseline.internalReservedKB;
        System.out.println(
            String.format(
                "After %d warmup flushes: malloc=%d KB (+%d KB), Internal=%d KB (+%d KB)",
                (i + 1),
                progress.mallocKB,
                mallocGrowthKB,
                progress.internalReservedKB,
                internalGrowthKB));
      }
    }

    // Phase 2: Steady state - reuse existing classes with profiler restarts
    // Stop/start cycles trigger SharedLineNumberTable destructors, exposing leaks
    System.out.println(
        String.format(
            "Phase 2: Steady state - reusing %d cached classes with profiler restarts...",
            cachedClassIndex));
    NativeMemoryTracking.NMTSnapshot afterWarmup = checkpoints[checkpointIndex - 1];

    // Restart profiler every 10 flushes to trigger destructor calls
    final int flushesPerRestart = 10;
    int flushCount = 0;

    for (int restart = 0; restart < steadyStateFlushes / flushesPerRestart; restart++) {
      // Stop profiler to destroy Recording and trigger all SharedLineNumberTable destructors
      if (restart > 0) {
        profiler.stop();
        Thread.sleep(50); // Allow cleanup to complete

        // Restart profiler (creates new Recording, repopulates _method_map from same classes)
        profiler.execute(
            "start," + getProfilerCommand() + ",jfr,file=" + tempFile("restart-" + restart));
      }

      // Perform flushes with cached classes
      for (int i = 0; i < flushesPerRestart; i++) {
        flushCount++;

        // Reuse cached classes (cycle through them)
        invokeCachedClasses(cachedClasses, flushCount);

        // Flush profiler
        dump(tempFile("steady-" + flushCount));
      }

      // Take checkpoint snapshots at intervals
      if ((flushCount) % checkpointInterval == 0) {
        NativeMemoryTracking.NMTSnapshot progress = NativeMemoryTracking.takeSnapshot();
        checkpoints[checkpointIndex++] = progress;

        long mallocGrowthKB = progress.mallocKB - baseline.mallocKB;
        long mallocGrowthFromWarmupKB = progress.mallocKB - afterWarmup.mallocKB;
        long internalGrowthKB = progress.internalReservedKB - baseline.internalReservedKB;
        System.out.println(
            String.format(
                "After %d steady flushes (%d restarts): malloc=%d KB (+%d KB total, +%d KB from warmup), Internal=%d KB (+%d KB)",
                flushCount,
                restart + 1,
                progress.mallocKB,
                mallocGrowthKB,
                mallocGrowthFromWarmupKB,
                progress.internalReservedKB,
                internalGrowthKB));
      }
    }

    // Take final snapshot
    NativeMemoryTracking.NMTSnapshot afterFlushes = checkpoints[6];
    long totalMallocGrowthKB = afterFlushes.mallocKB - baseline.mallocKB;
    long warmupMallocGrowthKB = afterWarmup.mallocKB - baseline.mallocKB;
    long steadyStateMallocGrowthKB = afterFlushes.mallocKB - afterWarmup.mallocKB;
    long internalGrowthKB = afterFlushes.internalReservedKB - baseline.internalReservedKB;

    // Calculate growth rates for steady state intervals (should plateau)
    // checkpoints[2] = after 100 warmup flushes
    // checkpoints[3-6] = steady state at 50, 100, 150, 200 flushes
    long[] steadyStateGrowths = new long[4];
    for (int i = 0; i < 4; i++) {
      steadyStateGrowths[i] = checkpoints[i + 3].mallocKB - checkpoints[i + 2].mallocKB;
    }

    // Assert that steady state growth is minimal and doesn't accelerate
    // With fix: growth should be small (<5 MB) and stable even with restarts
    // Without fix: each restart triggers 10,000 method destructor leaks
    //   Expected leak: 10,000 methods × 100 bytes × 20 restarts = ~20 MB
    long maxSteadyStateGrowth = 0;
    for (int i = 0; i < steadyStateGrowths.length; i++) {
      maxSteadyStateGrowth = Math.max(maxSteadyStateGrowth, steadyStateGrowths[i]);

      System.out.println(
          String.format(
              "Steady state interval %d: +%d KB (includes %d profiler restarts)",
              i + 1,
              steadyStateGrowths[i],
              checkpointInterval / flushesPerRestart));

      // Assert individual intervals don't show excessive growth
      // With restarts, each interval includes 5 stop/start cycles
      // If leak exists: 5 restarts × 10,000 methods × 100 bytes = ~5 MB
      if (steadyStateGrowths[i] > 8 * 1024) { // 8 MB per interval
        fail(
            String.format(
                "malloc growth in steady state is excessive (leak detected)!\n"
                    + "Steady state interval %d (flushes %d-%d with %d restarts): +%d KB\n"
                    + "Expected: malloc should stay flat (destructors properly deallocate)\n"
                    + "Actual: continued growth indicates leaked line number tables on destructor calls",
                i + 1,
                (i) * 50,
                (i + 1) * 50,
                checkpointInterval / flushesPerRestart,
                steadyStateGrowths[i]));
      }
    }

    // Verify total steady state growth is bounded
    // With fix: should be < 10 MB (normal JVM operations like GC, minor allocations)
    // Without fix: 20 restarts × 10,000 methods × 100 bytes = ~20 MB leak
    NativeMemoryTracking.assertMallocMemoryBounded(
        afterWarmup,
        afterFlushes,
        15 * 1024 * 1024, // 15 MB - accounts for restarts but no leaks
        "malloc memory grew excessively during steady state - indicates potential leak!");

    // Print summary
    System.out.println(
        String.format(
            "\nTest completed successfully:\n"
                + "  Phase 1 (Warmup - unique classes):\n"
                + "    Flushes: %d\n"
                + "    malloc growth: +%d KB\n"
                + "  Phase 2 (Steady state - reused classes with restarts):\n"
                + "    Flushes: %d\n"
                + "    Profiler restarts: %d (triggers destructor calls)\n"
                + "    malloc growth: +%d KB (should plateau)\n"
                + "  Total:\n"
                + "    malloc: %d KB → %d KB (+%d KB, +%d allocs)\n"
                + "    Internal category: %d KB → %d KB (+%d KB)\n"
                + "  Note: JVMTI allocations tracked under Internal category → malloc\n"
                + "  Note: Restarts destroy Recording, triggering SharedLineNumberTable destructors",
            warmupFlushes,
            warmupMallocGrowthKB,
            steadyStateFlushes,
            steadyStateFlushes / flushesPerRestart,
            steadyStateMallocGrowthKB,
            baseline.mallocKB,
            afterFlushes.mallocKB,
            totalMallocGrowthKB,
            afterFlushes.mallocCount - baseline.mallocCount,
            baseline.internalReservedKB,
            afterFlushes.internalReservedKB,
            internalGrowthKB));
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

  private int fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
  }

  private Path tempFile(String name) throws IOException {
    Path dir = Paths.get("/tmp/recordings");
    Files.createDirectories(dir);
    return Files.createTempFile(dir, name + "-", ".jfr");
  }
}
