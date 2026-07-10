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
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

import java.io.IOException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Exploratory stress test for jmethodID invalidation, motivated by PROF-15385 (SIGSEGV in
 * {@code Lookup::fillJavaMethodInfo} copying a JVMTI line-number table for a stale jmethodID,
 * fixed by guarding that copy with {@code SafeAccess::isReadableRange}).
 *
 * <p>That fix addressed one call site. This test does not target a specific call site; it tries
 * to manufacture the same underlying condition — jmethodIDs whose declaring class is unloaded
 * while the profiler is actively resolving/dumping — at high enough concurrency and volume that
 * any *other*, currently-unguarded, use of a stale jmethodID has a chance to surface on its own.
 *
 * <p><b>Approach:</b>
 * <ul>
 *   <li>Several driver threads continuously define throwaway classes in fresh, disposable
 *       {@link ClassLoader}s, invoke their methods a few times (so the jmethodIDs are actually
 *       captured by the profiler), then drop every reference.</li>
 *   <li>A dedicated thread calls {@code System.gc()} on a tight loop for the duration of the
 *       test, to encourage the JVM to actually unload those discarded classes/loaders while the
 *       other threads are still running — rather than letting them merely accumulate.</li>
 *   <li>The main thread calls {@code profiler.dump()} repeatedly throughout, so
 *       {@code writeStackTraces}/{@code Lookup::resolveMethod}/{@code cleanupUnreferencedMethods}
 *       run concurrently with class unloading, not just class-loading.</li>
 *   <li>Both the {@code cpu} and {@code alloc} engines are active, since each has its own path
 *       into {@code Lookup} and its own timing relative to unload.</li>
 * </ul>
 *
 * <p><b>Pass/fail signal:</b> a SIGSEGV/SIGABRT kills the whole JVM, so JUnit would never get to
 * report a failure directly -- reaching {@code profiler.stop()} at all is one necessary signal.
 * But that alone would pass vacuously if the churn never actually raced class unload against
 * {@code Lookup::resolveMethod}/{@code fillJavaMethodInfo}. To rule that out, this test reads the
 * native whitebox counters ({@code JavaProfiler#getDebugCounters()}) for {@code
 * jmethodid_skipped_count} and {@code line_number_table_unreadable} -- both are incremented in
 * {@code fillJavaMethodInfo} exactly when {@code SafeAccess::isReadableRange} rejects a stale
 * jmethodID's class/method metadata or line-number table (see flightRecorder.cpp) -- and asserts
 * at least one of them increased during the churn window. A pass therefore means both "no crash"
 * and "a stale jmethodID was actually observed and safely guarded." We cannot run this under ASan
 * here, since the profiler under test must run as a live JVMTI agent inside the same JVM process
 * the test is driving, not as a standalone ASan-instrumented binary the way the gtest-level native
 * unit tests can.
 *
 * <p><b>Limitations:</b> class unloading is JVM-discretionary and best-effort here — this test
 * does not wait for or verify that any particular class actually unloads (unlike
 * {@code CleanupAfterClassUnloadTest}/{@code WriteStackTracesAfterClassUnloadTest}, which target
 * one specific, already-diagnosed race and gate on a confirmed unload). It relies on volume and
 * concurrency to make unload-during-use likely across many call sites at once, but a clean run
 * is evidence of nothing more than "no crash was hit this time" for whatever code paths happened
 * to be exercised.
 */
public class JMethodIDInvalidationStressTest extends AbstractDynamicClassTest {

  private static final int CHURN_THREADS = 4;
  private static final long DURATION_MILLIS = 5_000;
  private static final AtomicLong CLASS_COUNTER = new AtomicLong();
  private static final AtomicLong CHURN_ITERATIONS = new AtomicLong();

  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms,alloc=512k";
  }

  @Test
  @Timeout(60)
  public void testProfilerSurvivesConcurrentClassUnloadDuringDump() throws Exception {
    stopProfiler();

    Path baseFile = tempFile("jmethodid-churn-base");
    Path dumpFile = tempFile("jmethodid-churn-dump");

    AtomicBoolean running = new AtomicBoolean(true);
    List<Thread> churnThreads = new ArrayList<>();
    Thread gcThread = null;

    try {
      profiler.execute(
          "start," + getProfilerCommand() + ",jfr,mcleanup=true,file=" + baseFile.toAbsolutePath());
      Thread.sleep(200); // let the profiler stabilize

      Map<String, Long> before = profiler.getDebugCounters();

      for (int i = 0; i < CHURN_THREADS; i++) {
        Thread t = new Thread(() -> churnLoop(running), "jmethodid-churn-" + i);
        t.setDaemon(true);
        churnThreads.add(t);
        t.start();
      }

      gcThread = new Thread(() -> {
        while (running.get()) {
          System.gc();
          try {
            Thread.sleep(20);
          } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return;
          }
        }
      }, "jmethodid-churn-gc");
      gcThread.setDaemon(true);
      gcThread.start();

      // Drive dumps from the main thread for the whole churn window so
      // writeStackTraces/resolveMethod/cleanupUnreferencedMethods run concurrently
      // with class unloading, not just after it.
      long deadline = System.currentTimeMillis() + DURATION_MILLIS;
      int dumps = 0;
      while (System.currentTimeMillis() < deadline) {
        profiler.dump(dumpFile);
        dumps++;
        Thread.sleep(50);
      }

      running.set(false);
      for (Thread t : churnThreads) {
        t.join(5_000);
      }
      gcThread.join(5_000);

      // Reaching this line means the profiler survived the whole churn window.
      Map<String, Long> after = profiler.getDebugCounters();
      profiler.stop();

      assertTrue(Files.size(dumpFile) > 0,
          "Profiler produced no output after " + dumps + " dumps under jmethodID churn");

      long churnIterations = CHURN_ITERATIONS.get();
      assertTrue(churnIterations > 0,
          "Churn threads never completed a single load/invoke/discard iteration -- the "
              + "counter-delta assertion below would be meaningless without this, since it "
              + "can't tell 'no stale jmethodID was hit' apart from 'churn never ran at all' "
              + "(e.g. a regression in generateChurnClassBytecode or IsolatedClassLoader).");

      long skippedDelta = after.getOrDefault("jmethodid_skipped_count", 0L)
          - before.getOrDefault("jmethodid_skipped_count", 0L);
      long unreadableLineTableDelta = after.getOrDefault("line_number_table_unreadable", 0L)
          - before.getOrDefault("line_number_table_unreadable", 0L);

      assertTrue(skippedDelta > 0 || unreadableLineTableDelta > 0,
          "Churn window completed without the profiler ever encountering a stale/unmapped "
              + "jmethodID (jmethodid_skipped_count delta=" + skippedDelta
              + ", line_number_table_unreadable delta=" + unreadableLineTableDelta
              + ") -- this test is meant to prove the guard actually fires under class-unload "
              + "churn, not just that the JVM didn't crash; if this keeps failing, the churn "
              + "isn't racing unload against resolveMethod/fillJavaMethodInfo tightly enough "
              + "(consider more churn threads or a longer window).");
    } finally {
      running.set(false);
      for (Thread t : churnThreads) {
        try {
          t.join(2_000);
        } catch (InterruptedException ignored) {
        }
      }
      if (gcThread != null) {
        try {
          gcThread.join(2_000);
        } catch (InterruptedException ignored) {
        }
      }
      try {
        profiler.stop();
      } catch (Exception ignored) {
      }
      try {
        Files.deleteIfExists(baseFile);
      } catch (IOException ignored) {
      }
      try {
        Files.deleteIfExists(dumpFile);
      } catch (IOException ignored) {
      }
    }
  }

  private void churnLoop(AtomicBoolean running) {
    while (running.get()) {
      try {
        String className =
            "com/datadoghq/profiler/generated/JMethodIDChurn" + CLASS_COUNTER.incrementAndGet();
        byte[] bytecode = generateChurnClassBytecode(className);

        IsolatedClassLoader loader = new IsolatedClassLoader();
        Class<?> clazz = loader.defineClass(className.replace('/', '.'), bytecode);
        Object instance = clazz.getDeclaredConstructor().newInstance();
        Method compute = clazz.getDeclaredMethod("compute", int.class);
        Method allocate = clazz.getDeclaredMethod("allocate", int.class);

        for (int i = 0; i < 20; i++) {
          compute.invoke(instance, i);
          allocate.invoke(instance, i);
        }
        // loader/clazz/instance/compute/allocate go out of scope here with no other
        // references -- eligible for unload as soon as the GC-pressure thread runs.
        CHURN_ITERATIONS.incrementAndGet();
      } catch (Throwable t) {
        // A reflective/loading failure here is not itself a signal; the failure mode
        // this test watches for is a JVM crash, not a Java-level exception. But we
        // still need churn to actually be happening for the counter-delta assertion
        // below to mean anything -- CHURN_ITERATIONS tracks that separately.
      }
    }
  }

  /**
   * Generates a class with a {@code compute(int)} method (multi-line-number arithmetic, so
   * {@code GetLineNumberTable} on it returns more than one entry) and an {@code allocate(int)}
   * method (array allocation, so the alloc engine's stack capture includes this jmethodID too).
   */
  private byte[] generateChurnClassBytecode(String internalName) {
    ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
    cw.visit(Opcodes.V1_8, Opcodes.ACC_PUBLIC, internalName, null, "java/lang/Object", null);

    MethodVisitor ctor = cw.visitMethod(Opcodes.ACC_PUBLIC, "<init>", "()V", null, null);
    ctor.visitCode();
    ctor.visitVarInsn(Opcodes.ALOAD, 0);
    ctor.visitMethodInsn(Opcodes.INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
    ctor.visitInsn(Opcodes.RETURN);
    ctor.visitMaxs(0, 0);
    ctor.visitEnd();

    // public int compute(int x) {
    //   int r = x;        // line 10
    //   r = r*1103515245 + 12345;  // line 11
    //   return r;         // line 12
    // }
    MethodVisitor compute = cw.visitMethod(Opcodes.ACC_PUBLIC, "compute", "(I)I", null, null);
    compute.visitCode();
    Label l1 = new Label();
    compute.visitLabel(l1);
    compute.visitLineNumber(10, l1);
    compute.visitVarInsn(Opcodes.ILOAD, 1);
    compute.visitVarInsn(Opcodes.ISTORE, 2);
    Label l2 = new Label();
    compute.visitLabel(l2);
    compute.visitLineNumber(11, l2);
    compute.visitVarInsn(Opcodes.ILOAD, 2);
    compute.visitLdcInsn(1103515245);
    compute.visitInsn(Opcodes.IMUL);
    compute.visitLdcInsn(12345);
    compute.visitInsn(Opcodes.IADD);
    compute.visitVarInsn(Opcodes.ISTORE, 2);
    Label l3 = new Label();
    compute.visitLabel(l3);
    compute.visitLineNumber(12, l3);
    compute.visitVarInsn(Opcodes.ILOAD, 2);
    compute.visitInsn(Opcodes.IRETURN);
    compute.visitMaxs(0, 0);
    compute.visitEnd();

    // public int[] allocate(int seed) {
    //   int[] a = new int[16];
    //   a[0] = seed;
    //   return a;
    // }
    MethodVisitor allocate = cw.visitMethod(Opcodes.ACC_PUBLIC, "allocate", "(I)[I", null, null);
    allocate.visitCode();
    allocate.visitIntInsn(Opcodes.BIPUSH, 16);
    allocate.visitIntInsn(Opcodes.NEWARRAY, Opcodes.T_INT);
    allocate.visitVarInsn(Opcodes.ASTORE, 2);
    allocate.visitVarInsn(Opcodes.ALOAD, 2);
    allocate.visitInsn(Opcodes.ICONST_0);
    allocate.visitVarInsn(Opcodes.ILOAD, 1);
    allocate.visitInsn(Opcodes.IASTORE);
    allocate.visitVarInsn(Opcodes.ALOAD, 2);
    allocate.visitInsn(Opcodes.ARETURN);
    allocate.visitMaxs(0, 0);
    allocate.visitEnd();

    cw.visitEnd();
    return cw.toByteArray();
  }
}
