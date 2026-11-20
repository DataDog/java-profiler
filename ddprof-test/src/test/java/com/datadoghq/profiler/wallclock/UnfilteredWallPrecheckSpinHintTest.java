/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.InputStream;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import org.junit.jupiter.api.Test;
import org.objectweb.asm.ClassReader;
import org.objectweb.asm.ClassVisitor;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

/** Checks the Java-8-compatible spin hint without initializing the integration fixture. */
public class UnfilteredWallPrecheckSpinHintTest {
  /** Verifies that the parked worker's deadline-loop backedge contains Thread.yield. */
  @Test
  public void parkedWorkerDeadlineLoopYields() throws Exception {
    boolean[] foundDeadlineLoopWithYield = {false};
    try (InputStream bytes = getClass().getResourceAsStream("UnfilteredWallPrecheckTest.class")) {
      assertNotNull(bytes);
      new ClassReader(bytes)
          .accept(
              new ClassVisitor(Opcodes.ASM9) {
                @Override
                public MethodVisitor visitMethod(
                    int access,
                    String name,
                    String descriptor,
                    String signature,
                    String[] exceptions) {
                  if (!name.startsWith("lambda$runPreExistingParkedWorker$")) {
                    return null;
                  }
                  return new MethodVisitor(Opcodes.ASM9) {
                    private final Map<Label, Integer> labels = new HashMap<>();
                    private final Set<Integer> yields = new HashSet<>();
                    private final Set<Integer> clocks = new HashSet<>();
                    private int calls;

                    @Override
                    public void visitLabel(Label label) {
                      labels.put(label, calls);
                    }

                    @Override
                    public void visitMethodInsn(
                        int opcode, String owner, String method, String desc, boolean isInterface) {
                      if (opcode == Opcodes.INVOKESTATIC
                          && desc.equals("()V")
                          && owner.equals("java/lang/Thread")
                          && method.equals("yield")) {
                        yields.add(calls);
                      }
                      if (opcode == Opcodes.INVOKESTATIC
                          && desc.equals("()J")
                          && owner.equals("java/lang/System")
                          && method.equals("nanoTime")) {
                        clocks.add(calls);
                      }
                      calls++;
                    }

                    @Override
                    public void visitJumpInsn(int opcode, Label label) {
                      Integer start = labels.get(label);
                      if (opcode == Opcodes.GOTO
                          && start != null
                          && yields.stream().anyMatch(call -> call >= start)
                          && clocks.stream().anyMatch(call -> call >= start)) {
                        foundDeadlineLoopWithYield[0] = true;
                      }
                    }
                  };
                }
              },
              ClassReader.SKIP_DEBUG | ClassReader.SKIP_FRAMES);
    }
    assertTrue(
        foundDeadlineLoopWithYield[0], "The runnable deadline loop must invoke Thread.yield");
  }
}
