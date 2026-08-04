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
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

abstract class AbstractDynamicClassTest extends AbstractProfilerTest {

  protected int classCounter = 0;

  /**
   * Generates ASM bytecode for a class with a constructor and {@code methodCount} public
   * int-returning no-arg methods, each with multiple line-number table entries.
   */
  protected byte[] generateClassBytecode(String className, int methodCount) {
    ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
    cw.visit(Opcodes.V1_8, Opcodes.ACC_PUBLIC, className, null, "java/lang/Object", null);

    MethodVisitor ctor = cw.visitMethod(Opcodes.ACC_PUBLIC, "<init>", "()V", null, null);
    ctor.visitCode();
    ctor.visitVarInsn(Opcodes.ALOAD, 0);
    ctor.visitMethodInsn(Opcodes.INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
    ctor.visitInsn(Opcodes.RETURN);
    ctor.visitMaxs(0, 0);
    ctor.visitEnd();

    for (int i = 0; i < methodCount; i++) {
      MethodVisitor mv = cw.visitMethod(Opcodes.ACC_PUBLIC, "method" + i, "()I", null, null);
      mv.visitCode();

      Label l1 = new Label();
      mv.visitLabel(l1);
      mv.visitLineNumber(100 + i * 3, l1);
      mv.visitInsn(Opcodes.ICONST_0);
      mv.visitVarInsn(Opcodes.ISTORE, 1);

      Label l2 = new Label();
      mv.visitLabel(l2);
      mv.visitLineNumber(101 + i * 3, l2);
      mv.visitVarInsn(Opcodes.ILOAD, 1);
      mv.visitInsn(Opcodes.ICONST_1);
      mv.visitInsn(Opcodes.IADD);
      mv.visitVarInsn(Opcodes.ISTORE, 1);

      Label l3 = new Label();
      mv.visitLabel(l3);
      mv.visitLineNumber(102 + i * 3, l3);
      mv.visitVarInsn(Opcodes.ILOAD, 1);
      mv.visitInsn(Opcodes.IRETURN);

      mv.visitMaxs(0, 0);
      mv.visitEnd();
    }

    cw.visitEnd();
    return cw.toByteArray();
  }

  protected static Path tempFile(String prefix) throws IOException {
    Path dir = Paths.get(System.getProperty("java.io.tmpdir"), "recordings");
    Files.createDirectories(dir);
    return Files.createTempFile(dir, prefix + "-", ".jfr");
  }

  protected static class IsolatedClassLoader extends ClassLoader {
    public Class<?> defineClass(String name, byte[] bytecode) {
      return defineClass(name, bytecode, 0, bytecode.length);
    }
  }
}
