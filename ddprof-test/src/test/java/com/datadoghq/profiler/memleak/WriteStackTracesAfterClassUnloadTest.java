/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
package com.datadoghq.profiler.memleak;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

import java.io.IOException;
import java.lang.ref.WeakReference;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Regression test for PROF-14547: SIGSEGV in {@code Profiler::processCallTraces} during
 * {@code Recording::writeStackTraces}.
 *
 * <p><b>Bug:</b> {@code MethodInfo::_line_number_table->_ptr} held a raw pointer to JVMTI-allocated
 * memory returned by {@code GetLineNumberTable}. When the underlying class was unloaded, the JVM
 * freed that memory, leaving {@code _ptr} dangling. The crash manifested when
 * {@code MethodInfo::getLineNumber(bci)} dereferenced the freed memory while
 * {@code writeStackTraces} iterated traces that still referenced the now-unloaded method
 * (a peer manifestation of PROF-14545, which crashes inside
 * {@code SharedLineNumberTable::~SharedLineNumberTable} via {@code Deallocate}).
 *
 * <p><b>Test scenario (timing-sensitive — catches the bug aggressively under ASan):</b>
 * <ol>
 *   <li>Aggressively profile a dynamically-loaded class so its methods land in many CPU samples.
 *       Each sample creates an entry in {@code call_trace_storage} and a {@code MethodInfo} entry
 *       in {@code _method_map} that holds a {@code shared_ptr<SharedLineNumberTable>}.</li>
 *   <li>Drop all strong references to the class and its loader; encourage unloading via
 *       {@code System.gc()} until the {@code WeakReference} is cleared.</li>
 *   <li>Immediately dump — within the same chunk if possible — so the freshly-unloaded method's
 *       traces are still in {@code call_trace_storage} when {@code writeStackTraces} runs.</li>
 *   <li>The lambda inside {@code processCallTraces} resolves the unloaded method via
 *       {@code Lookup::resolveMethod} and calls {@code MethodInfo::getLineNumber(bci)} on a
 *       {@code MethodInfo} whose {@code _line_number_table->_ptr} was freed by the JVM →
 *       SIGSEGV without the fix.</li>
 * </ol>
 *
 * <p>With the fix (PROF-14547), {@code SharedLineNumberTable} owns a malloc'd copy of the entries
 * (the JVMTI allocation is deallocated immediately at capture time inside
 * {@code Lookup::fillJavaMethodInfo}), so {@code _ptr} stays valid regardless of class unload.
 *
 * <p><b>Limitations:</b>
 * <ul>
 *   <li>Not authored "blind" — the implementation existed before the test was written.</li>
 *   <li>Without ASan/UBSan, the freed JVMTI region may still hold plausible bytes at read time
 *       and the test will report green even on a buggy binary. ASan/UBSan builds are the
 *       authoritative signal here.</li>
 *   <li>Class unload is JVM-discretionary; if the {@code WeakReference} doesn't clear within
 *       the deadline the test {@code assumeTrue}-skips rather than passing spuriously.</li>
 *   <li>{@code mcleanup=false} is set deliberately so a SIGSEGV here is unambiguously the
 *       PROF-14547 read path, not the PROF-14545 cleanup path covered by
 *       {@code CleanupAfterClassUnloadTest}.</li>
 * </ul>
 */
public class WriteStackTracesAfterClassUnloadTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    // Aggressive CPU sampling to ensure the dynamic class lands in many traces.
    return "cpu=1ms";
  }

  private int classCounter = 0;

  @Test
  @Timeout(60)
  public void testNoSigsegvInWriteStackTracesAfterClassUnload() throws Exception {
    stopProfiler();

    Path baseFile = tempFile("prof14547-base");
    Path dumpFile = tempFile("prof14547-dump");

    try {
      // mcleanup=false isolates the test to the PROF-14547 read path; the
      // PROF-14545 cleanup path is covered separately by CleanupAfterClassUnloadTest.
      profiler.execute("start,cpu=1ms,jfr,mcleanup=false,file=" + baseFile.toAbsolutePath());
      try {
        Thread.sleep(200); // let the profiler stabilize

        // 1. Load a class, hammer its methods on this thread so the CPU profiler captures
        //    many traces referencing it. Drop strong refs and return only a WeakReference.
        WeakReference<ClassLoader> loaderRef = loadAndProfileDynamicClass();

        // 2. Drop refs and GC until the class actually unloads.
        long deadline = System.currentTimeMillis() + 8_000;
        while (loaderRef.get() != null && System.currentTimeMillis() < deadline) {
          System.gc();
          Thread.sleep(20);
        }

        // Skip the test (rather than pass spuriously) if the JVM declined to unload.
        // Without unload the JVMTI line-number-table memory is never freed and the bug
        // cannot manifest — running the dumps would prove nothing.
        assumeTrue(loaderRef.get() == null,
            "JVM did not unload the dynamic class within the deadline; cannot exercise PROF-14547");

        // 3. Immediately dump several times. The first dump runs writeStackTraces over
        //    the trace_buffer that still contains the unloaded method's traces; subsequent
        //    dumps cover the rotation tail. With the bug, getLineNumber dereferences the
        //    freed JVMTI memory → SIGSEGV. With the fix, _ptr is a malloc'd copy → safe.
        for (int i = 0; i < 4; i++) {
          profiler.dump(dumpFile);
          Thread.sleep(10);
        }

        // 4. If the profiler crashed inside processCallTraces the JVM would have died and we
        //    would never reach this line. The non-empty-output assertion is secondary — the
        //    primary signal is reaching profiler.stop() at all.
        assertTrue(Files.size(dumpFile) > 0,
            "Profiler produced no output — SIGSEGV during writeStackTraces is suspected");
      } finally {
        try {
          profiler.stop();
        } finally {
          profiler.resetThreadContext();
        }
      }

    } finally {
      try { Files.deleteIfExists(baseFile); } catch (IOException ignored) {}
      try { Files.deleteIfExists(dumpFile); } catch (IOException ignored) {}
    }
  }

  private WeakReference<ClassLoader> loadAndProfileDynamicClass() throws Exception {
    String className = "com/datadoghq/profiler/generated/Prof14547Class" + (classCounter++);
    byte[] bytecode = generateClassBytecode(className);

    IsolatedClassLoader loader = new IsolatedClassLoader();
    Class<?> clazz = loader.defineClass(className.replace('/', '.'), bytecode);

    // Hammer methods for ~300ms so the CPU profiler at 1ms captures plenty of samples
    // referencing this class. The longer this runs, the more traces survive into the
    // dump-after-unload window.
    long endTime = System.currentTimeMillis() + 300;
    Object instance = clazz.getDeclaredConstructor().newInstance();
    Method[] methods = clazz.getDeclaredMethods();
    while (System.currentTimeMillis() < endTime) {
      for (Method m : methods) {
        if (m.getParameterCount() == 0 && m.getReturnType() == int.class) {
          m.invoke(instance);
        }
      }
    }

    WeakReference<ClassLoader> ref = new WeakReference<>(loader);
    //noinspection UnusedAssignment
    loader = null;
    //noinspection UnusedAssignment
    clazz = null;
    //noinspection UnusedAssignment
    instance = null;
    return ref;
  }

  private byte[] generateClassBytecode(String className) {
    ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
    cw.visit(Opcodes.V1_8, Opcodes.ACC_PUBLIC, className, null, "java/lang/Object", null);

    MethodVisitor ctor = cw.visitMethod(Opcodes.ACC_PUBLIC, "<init>", "()V", null, null);
    ctor.visitCode();
    ctor.visitVarInsn(Opcodes.ALOAD, 0);
    ctor.visitMethodInsn(Opcodes.INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
    ctor.visitInsn(Opcodes.RETURN);
    ctor.visitMaxs(0, 0);
    ctor.visitEnd();

    // Several methods, each with multiple line number entries — guarantees a non-trivial
    // line number table is allocated by JVMTI and stored in MethodInfo._line_number_table.
    for (int i = 0; i < 5; i++) {
      MethodVisitor mv = cw.visitMethod(Opcodes.ACC_PUBLIC, "method" + i, "()I", null, null);
      mv.visitCode();

      Label l1 = new Label(); mv.visitLabel(l1); mv.visitLineNumber(100 + i * 3, l1);
      mv.visitInsn(Opcodes.ICONST_0);
      mv.visitVarInsn(Opcodes.ISTORE, 1);

      Label l2 = new Label(); mv.visitLabel(l2); mv.visitLineNumber(101 + i * 3, l2);
      mv.visitVarInsn(Opcodes.ILOAD, 1);
      mv.visitInsn(Opcodes.ICONST_1);
      mv.visitInsn(Opcodes.IADD);
      mv.visitVarInsn(Opcodes.ISTORE, 1);

      Label l3 = new Label(); mv.visitLabel(l3); mv.visitLineNumber(102 + i * 3, l3);
      mv.visitVarInsn(Opcodes.ILOAD, 1);
      mv.visitInsn(Opcodes.IRETURN);

      mv.visitMaxs(0, 0);
      mv.visitEnd();
    }

    cw.visitEnd();
    return cw.toByteArray();
  }

  private static Path tempFile(String prefix) throws IOException {
    Path dir = Paths.get("/tmp/recordings");
    Files.createDirectories(dir);
    return Files.createTempFile(dir, prefix + "-", ".jfr");
  }

  private static class IsolatedClassLoader extends ClassLoader {
    public Class<?> defineClass(String name, byte[] bytecode) {
      return defineClass(name, bytecode, 0, bytecode.length);
    }
  }
}
