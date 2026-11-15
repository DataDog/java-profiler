/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.JavaProfiler;
import com.sun.management.ThreadMXBean;
import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.management.ManagementFactory;
import java.lang.reflect.Method;
import org.junit.jupiter.api.Test;
import org.objectweb.asm.ClassReader;
import org.objectweb.asm.ClassVisitor;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

/** Guards the Java blocking-hook gate independently of JNI/JVM allocation during native hooks. */
public class BlockingHookAllocationTest {
  @Test
  public void warmedVirtualThreadGateAllocatesNoJavaObjects() throws Throwable {
    Method method = JavaProfiler.class.getDeclaredMethod("isVirtualThread", Thread.class);
    method.setAccessible(true);
    MethodHandle gate = MethodHandles.lookup().unreflect(method);
    ThreadMXBean bean = (ThreadMXBean) ManagementFactory.getThreadMXBean();
    assertTrue(bean.isThreadAllocatedMemorySupported(), "Allocation accounting is required");
    bean.setThreadAllocatedMemoryEnabled(true);
    Thread thread = Thread.currentThread();
    for (int i = 0; i < 10; i++) measureGateAllocations(gate, bean, thread, 100_000);
    assertEquals(
        0L,
        measureGateAllocations(gate, bean, thread, 100_000),
        "The warmed primitive gate must not allocate varargs arrays or boxed results");
  }

  private static long measureGateAllocations(
      MethodHandle gate, ThreadMXBean bean, Thread thread, int iterations) throws Throwable {
    // Warm the same accounting call sites: their first linkage is outside the gate contract.
    long before = bean.getThreadAllocatedBytes(thread.getId());
    int virtual = 0;
    for (int i = 0; i < iterations; i++) {
      if ((boolean) gate.invokeExact(thread)) virtual++;
    }
    long allocated = bean.getThreadAllocatedBytes(thread.getId()) - before;
    assertEquals(0, virtual, "The JUnit worker is a platform thread, including on pre-Loom JDKs");
    return allocated;
  }

  @Test
  public void blockingHookBytecodeUsesOnlyTheExactPrimitiveGate() throws Exception {
    int[] hookGates = {0};
    int[] exactCalls = {0};
    new ClassReader(JavaProfiler.class.getName())
        .accept(
            new ClassVisitor(Opcodes.ASM9) {
              @Override
              public MethodVisitor visitMethod(
                  int access,
                  String name,
                  String descriptor,
                  String signature,
                  String[] exceptions) {
                if (!name.equals("isVirtualThread")
                    && !name.equals("parkEnter")
                    && !name.equals("parkExit")
                    && !name.equals("blockEnter")
                    && !name.equals("blockExit")) return null;
                return new MethodVisitor(Opcodes.ASM9) {
                  @Override
                  public void visitIntInsn(int opcode, int operand) {
                    assertNotEquals(
                        Opcodes.NEWARRAY, opcode, "Hook paths cannot allocate primitive arrays");
                  }

                  @Override
                  public void visitTypeInsn(int opcode, String type) {
                    assertNotEquals(
                        Opcodes.ANEWARRAY, opcode, "Hook paths cannot allocate varargs arrays");
                  }

                  @Override
                  public void visitMultiANewArrayInsn(String descriptor, int dimensions) {
                    fail("Hook paths cannot allocate multidimensional arrays");
                  }

                  @Override
                  public void visitMethodInsn(
                      int opcode, String owner, String method, String desc, boolean isInterface) {
                    assertFalse(
                        owner.equals("java/lang/reflect/Method"),
                        "Reflective invocation allocates varargs");
                    assertFalse(
                        owner.equals("java/lang/Boolean"),
                        "The gate must return a primitive boolean");
                    if (owner.equals("java/lang/invoke/MethodHandle")) {
                      assertEquals("invokeExact", method);
                      assertEquals("(Ljava/lang/Thread;)Z", desc);
                      exactCalls[0]++;
                    }
                    if (owner.equals("com/datadoghq/profiler/JavaProfiler")
                        && method.equals("isVirtualThread")) {
                      assertEquals("(Ljava/lang/Thread;)Z", desc);
                      hookGates[0]++;
                    }
                  }
                };
              }
            },
            0);
    assertEquals(
        4, hookGates[0], "Each park/block entry and exit must use the virtual-thread gate");
    assertEquals(1, exactCalls[0], "The shared gate must invoke the cached handle exactly");
  }
}
