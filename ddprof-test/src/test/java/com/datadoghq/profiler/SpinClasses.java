/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

/**
 * Defines throwaway classes with {@code public static void spin(long nanos)}, which busy-waits
 * so that CPU samples land in it. Each class gets its own class loader, so nothing else gives it
 * jmethodIDs and it can be unloaded once the caller drops it.
 */
public final class SpinClasses {
    private SpinClasses() {}

    /**
     * Defines {@code internalName} (slash-separated) in a fresh class loader.
     *
     * @param internalName the class name in internal form, e.g. {@code a/b/C}
     * @return the defined class
     */
    public static Class<?> define(String internalName) {
        return new Loader().define(internalName);
    }

    private static final class Loader extends ClassLoader {
        Class<?> define(String internalName) {
            byte[] bytes = generate(internalName);
            return defineClass(internalName.replace('/', '.'), bytes, 0, bytes.length);
        }
    }

    private static byte[] generate(String internalName) {
        ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
        cw.visit(Opcodes.V1_8, Opcodes.ACC_PUBLIC, internalName, null, "java/lang/Object", null);

        MethodVisitor mv = cw.visitMethod(Opcodes.ACC_PUBLIC | Opcodes.ACC_STATIC, "spin", "(J)V", null, null);
        mv.visitCode();
        // long deadline = System.nanoTime() + nanos;
        mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/System", "nanoTime", "()J", false);
        mv.visitVarInsn(Opcodes.LLOAD, 0);
        mv.visitInsn(Opcodes.LADD);
        mv.visitVarInsn(Opcodes.LSTORE, 2);
        // while (System.nanoTime() < deadline) {}
        Label loop = new Label();
        Label done = new Label();
        mv.visitLabel(loop);
        mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/System", "nanoTime", "()J", false);
        mv.visitVarInsn(Opcodes.LLOAD, 2);
        mv.visitInsn(Opcodes.LCMP);
        mv.visitJumpInsn(Opcodes.IFGE, done);
        mv.visitJumpInsn(Opcodes.GOTO, loop);
        mv.visitLabel(done);
        mv.visitInsn(Opcodes.RETURN);
        mv.visitMaxs(0, 0);
        mv.visitEnd();

        cw.visitEnd();
        return cw.toByteArray();
    }
}
