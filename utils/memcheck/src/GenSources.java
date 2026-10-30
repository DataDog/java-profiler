/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Writes the .java sources {@link MemCheckMain} loads. Run as a plain,
 * unprofiled process and compiled by an external {@code javac}, so the profiled
 * JVM never loads the compiler's own classes.
 *
 * <p>Usage: {@code GenSources <traces|classesM|allocs> <N> <outDir> [methodsPerClass]}
 */
public class GenSources {
    private static final String BODY =
            "    double s = 0;\n" +
            "    for (int j = 0; j < 200; j++) s += Math.sqrt(x + j);\n" +
            "    return (long) s;\n";

    public static void main(String[] args) throws IOException {
        String mode = args[0];
        int n = Integer.parseInt(args[1]);
        File dir = new File(args[2]);
        dir.mkdirs();
        switch (mode) {
            case "traces":
                // One class, N static methods -> N distinct call-trace shapes.
                write(dir, "GenTraces", methods(n));
                break;
            case "classesM":
                // N classes with M methods each -> N classes, N*M methods.
                int methodsPerClass = Integer.parseInt(args[3]);
                for (int i = 0; i < n; i++) {
                    write(dir, "GenClassM" + i, methods(methodsPerClass));
                }
                break;
            case "allocs":
                // N distinct object shapes: the field count varies, so the
                // classes also differ in allocation size.
                for (int i = 0; i < n; i++) {
                    String name = "GenAlloc" + i;
                    StringBuilder sb = new StringBuilder();
                    for (int f = 0; f <= i % 8; f++) sb.append("  long f").append(f).append(";\n");
                    sb.append("  public static Object alloc(long x) {\n")
                      .append("    ").append(name).append(" o = new ").append(name).append("();\n")
                      .append("    o.f0 = x;\n")
                      .append("    return o;\n")
                      .append("  }\n");
                    write(dir, name, sb.toString());
                }
                break;
            default:
                throw new IllegalArgumentException(mode);
        }
    }

    private static String methods(int count) {
        StringBuilder sb = new StringBuilder();
        for (int m = 0; m < count; m++) {
            sb.append("  public static long m").append(m).append("(long x) {\n").append(BODY).append("  }\n");
        }
        return sb.toString();
    }

    private static void write(File dir, String className, String members) throws IOException {
        try (FileWriter w = new FileWriter(new File(dir, className + ".java"))) {
            w.write("public class " + className + " {\n" + members + "}\n");
        }
    }
}
