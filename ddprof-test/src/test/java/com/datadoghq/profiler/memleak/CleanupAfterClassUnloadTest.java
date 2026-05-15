/*
 * Copyright 2026, Datadog, Inc
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

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;
import java.lang.ref.WeakReference;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Regression test for PROF-14545: SIGSEGV in Recording::cleanupUnreferencedMethods.
 *
 * <p>The bug: cleanupUnreferencedMethods() was called after finishChunk() released its
 * GetLoadedClasses pins. ~SharedLineNumberTable() called jvmti-&gt;Deallocate() on
 * JVMTI-allocated line-number-table memory that the JVM had already freed on class
 * unload → SIGSEGV.
 *
 * <p>The fix: two complementary changes:
 * <ol>
 *   <li>cleanupUnreferencedMethods() is now called inside finishChunk(), before
 *       DeleteLocalRef releases the GetLoadedClasses pins.</li>
 *   <li>fillJavaMethodInfo() copies the JVMTI line-number-table into a malloc'd buffer
 *       and immediately calls jvmti-&gt;Deallocate() on the original; cleanup calls free()
 *       on the malloc'd copy, which is safe regardless of class-unload state.</li>
 * </ol>
 *
 * <p>This test reproduces the crash scenario:
 * <ol>
 *   <li>A dynamically-loaded class with line number tables appears in profiling stack traces</li>
 *   <li>All references to the class and its class loader are dropped</li>
 *   <li>The JVM is encouraged to GC and unload the class (System.gc())</li>
 *   <li>AGE_THRESHOLD+1 dump cycles are triggered to age the method out of the method_map</li>
 *   <li>cleanupUnreferencedMethods() must not SIGSEGV when freeing the line number table</li>
 * </ol>
 */
public class CleanupAfterClassUnloadTest extends AbstractDynamicClassTest {

  // AGE_THRESHOLD in C++ is 3; run 4 dumps to ensure cleanup fires
  private static final int DUMPS_TO_AGE_OUT = 4;

  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms";
  }

  @Test
  @Timeout(60)
  public void testNoSigsegvAfterClassUnloadAndMethodCleanup() throws Exception {
    stopProfiler();

    Path baseFile = tempFile("prof14545-base");
    Path dumpFile = tempFile("prof14545-dump");

    try {
      profiler.execute(
          "start,cpu=1ms,jfr,mcleanup=true,file=" + baseFile.toAbsolutePath());
      Thread.sleep(200); // Let the profiler stabilize

      // 1. Load a class, execute its methods to appear in CPU profiling stack traces,
      //    then drop all strong references so the class can be GC'd.
      WeakReference<ClassLoader> loaderRef = loadAndProfileDynamicClass();

      // 2. Trigger one dump so the profiler captures the class in method_map.
      profiler.dump(dumpFile);
      Thread.sleep(50);

      // 3. Drop all references and aggressively GC to encourage class unloading.
      //    We poll until the WeakReference is cleared or we time out.
      long deadline = System.currentTimeMillis() + 8_000;
      while (loaderRef.get() != null && System.currentTimeMillis() < deadline) {
        System.gc();
        Thread.sleep(30);
      }
      assumeTrue(loaderRef.get() == null,
          "Skipping: class loader not GC'd within 8 s — class unloading is required for this test to be meaningful");

      // 4. Run AGE_THRESHOLD+1 dump cycles so the method ages out and cleanup fires.
      //    The method is no longer referenced (no stack traces) → age increments each cycle.
      //    After age >= 3 and the next cleanup pass, the entry is erased and
      //    SharedLineNumberTable::~SharedLineNumberTable() → jvmti->Deallocate() runs.
      //    Without the fix this is after DeleteLocalRef; with the fix it is before.
      for (int i = 0; i < DUMPS_TO_AGE_OUT; i++) {
        profiler.dump(dumpFile);
        Thread.sleep(50);
      }

      // 5. The profiler must still be alive. If it SIGSEGV'd during cleanup the JVM
      //    process would have died and this line would never be reached.
      profiler.stop();

      assertTrue(Files.size(dumpFile) > 0,
          "Profiler produced no output — it may have crashed during method_map cleanup");

    } finally {
      try { profiler.stop(); } catch (Exception ignored) {}
      try { Files.deleteIfExists(baseFile); } catch (IOException ignored) {}
      try { Files.deleteIfExists(dumpFile); } catch (IOException ignored) {}
    }
  }

  /**
   * Loads a dynamically-generated class with line number tables in a fresh ClassLoader,
   * invokes its methods on the current thread while CPU profiling is active so that
   * the profiler calls GetLineNumberTable and stores it in method_map, then returns a
   * WeakReference to the ClassLoader so callers can detect unloading.
   */
  private WeakReference<ClassLoader> loadAndProfileDynamicClass() throws Exception {
    String className = "com/datadoghq/profiler/generated/Prof14545Class" + (classCounter++);
    byte[] bytecode = generateClassBytecode(className, 5);

    IsolatedClassLoader loader = new IsolatedClassLoader();
    Class<?> clazz = loader.defineClass(className.replace('/', '.'), bytecode);

    // Spin-invoke the class methods for ~200ms so the CPU profiler has time to
    // capture this thread and include the dynamic class in a stack trace.
    long endTime = System.currentTimeMillis() + 200;
    Object instance = clazz.getDeclaredConstructor().newInstance();
    Method[] methods = clazz.getDeclaredMethods();
    while (System.currentTimeMillis() < endTime) {
      for (Method m : methods) {
        if (m.getParameterCount() == 0 && m.getReturnType() == int.class) {
          m.invoke(instance);
        }
      }
    }

    // Drop all strong references. Only the WeakReference remains.
    WeakReference<ClassLoader> ref = new WeakReference<>(loader);
    //noinspection UnusedAssignment
    loader = null;
    //noinspection UnusedAssignment
    clazz = null;
    //noinspection UnusedAssignment
    instance = null;
    return ref;
  }
}
