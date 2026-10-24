/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import org.objectweb.asm.ClassReader;
import org.objectweb.asm.ClassVisitor;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

/** Extends the real Java intervals around a nested continuation's native entry in a forked JVM. */
final class ContinuationTransitionSupport {
    static final String HOOK = "ddprof.test.continuation-transition-hook";

    private ContinuationTransitionSupport() {}

    /** Writes a java.base patch because HotSpot does not permit retransformation of Continuation. */
    static void writePatch(Path directory) throws Exception {
        int[] sites = {0};
        ClassWriter writer;
        try (InputStream input = ClassLoader.getSystemResourceAsStream("jdk/internal/vm/Continuation.class")) {
            if (input == null) throw new IllegalStateException("Continuation class bytes are unavailable");
            ClassReader reader = new ClassReader(input);
            writer = new ClassWriter(reader, ClassWriter.COMPUTE_FRAMES);
            reader.accept(new ClassVisitor(Opcodes.ASM9, writer) {
                @Override
                public MethodVisitor visitMethod(int access, String name, String descriptor,
                                                 String signature, String[] exceptions) {
                    MethodVisitor visitor = super.visitMethod(access, name, descriptor, signature, exceptions);
                    if (!name.equals("run") || !descriptor.equals("()V")) return visitor;
                    return new MethodVisitor(Opcodes.ASM9, visitor) {
                        @Override
                        public void visitMethodInsn(int opcode, String owner, String name,
                                                    String descriptor, boolean isInterface) {
                            boolean entry = owner.equals("jdk/internal/vm/Continuation")
                                    && name.equals("enterSpecial");
                            if (entry) {
                                sites[0]++;
                                hook(1);
                            }
                            super.visitMethodInsn(opcode, owner, name, descriptor, isInterface);
                            if (entry) hook(2);
                        }

                        /** Dispatches through a java.base interface without adding a bootstrap helper. */
                        private void hook(int phase) {
                            Label absent = new Label();
                            Label done = new Label();
                            super.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/System", "getProperties",
                                    "()Ljava/util/Properties;", false);
                            super.visitLdcInsn(HOOK);
                            super.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "java/util/Properties", "get",
                                    "(Ljava/lang/Object;)Ljava/lang/Object;", false);
                            super.visitInsn(Opcodes.DUP);
                            super.visitJumpInsn(Opcodes.IFNULL, absent);
                            super.visitTypeInsn(Opcodes.CHECKCAST, "java/util/function/BiConsumer");
                            super.visitVarInsn(Opcodes.ALOAD, 0);
                            super.visitLdcInsn(phase);
                            super.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Integer", "valueOf",
                                    "(I)Ljava/lang/Integer;", false);
                            super.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/function/BiConsumer", "accept",
                                    "(Ljava/lang/Object;Ljava/lang/Object;)V", true);
                            super.visitJumpInsn(Opcodes.GOTO, done);
                            super.visitLabel(absent);
                            super.visitInsn(Opcodes.POP);
                            super.visitLabel(done);
                        }
                    };
                }
            }, ClassReader.EXPAND_FRAMES);
        }
        if (sites[0] != 2) throw new IllegalStateException("Expected both enterSpecial call sites, found " + sites[0]);
        Path output = directory.resolve("jdk/internal/vm/Continuation.class");
        Files.createDirectories(output.getParent());
        Files.write(output, writer.toByteArray());
    }
}
