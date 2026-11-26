/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.util.Enumeration;
import org.objectweb.asm.ClassReader;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.commons.ClassRemapper;
import org.objectweb.asm.commons.Remapper;

/** Prefix-relocates real Netty classes and native resources without changing their behavior. */
final class ShadedNettyClassLoader extends ClassLoader {
  static final String PREFIX = "ddproffixture.";
  private static final String NATIVE_PREFIX = "META-INF/native/libddproffixture_netty_";

  ShadedNettyClassLoader(ClassLoader parent) {
    super(parent);
  }

  @Override
  protected Class<?> findClass(String name) throws ClassNotFoundException {
    if (!name.startsWith(PREFIX + "io.netty.")) {
      throw new ClassNotFoundException(name);
    }
    String original = name.substring(PREFIX.length()).replace('.', '/') + ".class";
    try (InputStream input = getParent().getResourceAsStream(original)) {
      if (input == null) {
        throw new ClassNotFoundException(original);
      }
      ClassWriter output = new ClassWriter(0);
      Remapper remapper =
          new Remapper() {
            @Override
            public String map(String internalName) {
              return internalName.startsWith("io/netty/")
                  ? PREFIX.replace('.', '/') + internalName
                  : internalName;
            }
          };
      new ClassReader(input).accept(new ClassRemapper(output, remapper), 0);
      byte[] bytes = output.toByteArray();
      return defineClass(name, bytes, 0, bytes.length);
    } catch (IOException error) {
      throw new ClassNotFoundException(name, error);
    }
  }

  @Override
  public URL getResource(String name) {
    return getParent().getResource(originalResource(name));
  }

  @Override
  public Enumeration<URL> getResources(String name) throws IOException {
    return getParent().getResources(originalResource(name));
  }

  private static String originalResource(String name) {
    return name.startsWith(NATIVE_PREFIX)
        ? "META-INF/native/libnetty_" + name.substring(NATIVE_PREFIX.length())
        : name;
  }
}
