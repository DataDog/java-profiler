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

/**
 * Regression test for PROF-14545: SIGSEGV in Recording::cleanupUnreferencedMethods.
 *
 * <p>The bug: cleanupUnreferencedMethods() was called after finishChunk() released its
 * GetLoadedClasses pins. On JVM implementations that free JVMTI-allocated line number
 * table memory when a class is unloaded, the jvmti->Deallocate() call in
 * SharedLineNumberTable::~SharedLineNumberTable() would access freed memory → SIGSEGV.
 *
 * <p>The fix: cleanupUnreferencedMethods() is now called inside finishChunk(), before
 * DeleteLocalRef releases the GetLoadedClasses pins, ensuring Deallocate is always called
 * while the corresponding class is still loaded and pinned in memory.
 *
 * <p>This test reproduces the crash scenario:
 * <ol>
 *   <li>A dynamically-loaded class with line number tables appears in profiling stack traces</li>
 *   <li>All references to the class and its class loader are dropped</li>
 *   <li>The JVM is encouraged to GC and unload the class (System.gc())</li>
 *   <li>AGE_THRESHOLD+1 dump cycles are triggered to age the method out of the method_map</li>
 *   <li>cleanupUnreferencedMethods() must not SIGSEGV when freeing the line number table</li>
 * </ol>
 *
 * <p>Without the fix, this test may crash with SIGSEGV on JVM implementations that free
 * JVMTI-allocated memory on class unload. With the fix, it reliably passes.
 */
public class CleanupAfterClassUnloadTest extends AbstractProfilerTest {

  // AGE_THRESHOLD in C++ is 3; run 4 dumps to ensure cleanup fires
  private static final int DUMPS_TO_AGE_OUT = 4;

  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms";
  }

  private int classCounter = 0;

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
    byte[] bytecode = generateClassBytecode(className);

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

    // Generate 5 methods, each with multiple line number entries to ensure
    // GetLineNumberTable is called and returns a non-trivial table.
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
