/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.io.IOException;
import java.lang.instrument.Instrumentation;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.jar.Attributes;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;

/**
 * Test-only {@code -javaagent} that keeps its {@link Instrumentation} so a child JVM can call
 * {@code retransformClasses} through the profiler's JVMTI hooks.
 */
public final class RetransformAgent {
  private static volatile Instrumentation instrumentation;

  private RetransformAgent() {}

  public static void premain(String args, Instrumentation inst) {
    instrumentation = inst;
  }

  /** Returns null without the agent; the JVM loads this class from the child's class path. */
  static Instrumentation instrumentation() {
    return instrumentation;
  }

  /** Writes a manifest-only agent jar that names this class and allows retransformation. */
  static Path writeAgentJar(Path dir) throws IOException {
    Manifest manifest = new Manifest();
    Attributes attributes = manifest.getMainAttributes();
    attributes.put(Attributes.Name.MANIFEST_VERSION, "1.0");
    attributes.putValue("Premain-Class", RetransformAgent.class.getName());
    attributes.putValue("Can-Retransform-Classes", "true");
    Path jar = Files.createTempFile(dir, "retransform-agent-", ".jar");
    new JarOutputStream(Files.newOutputStream(jar), manifest).close();
    return jar;
  }
}
