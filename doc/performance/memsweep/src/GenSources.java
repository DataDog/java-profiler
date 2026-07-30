import java.io.File;
import java.io.FileWriter;

/**
 * Writes .java sources for the traces/classes sweep dimensions. Run as a
 * plain (unprofiled) process, then compiled with an external `javac`
 * subprocess, so the profiled JVM never loads the compiler's own classes.
 */
public class GenSources {
    public static void main(String[] args) throws Exception {
        String mode = args[0];
        int n = Integer.parseInt(args[1]);
        File dir = new File(args[2]);
        dir.mkdirs();
        if (mode.equals("traces")) {
            StringBuilder sb = new StringBuilder();
            sb.append("public class GenTraces {\n");
            for (int i = 0; i < n; i++) {
                sb.append("  public static long m").append(i).append("(long x) {\n")
                  .append("    double s = 0;\n")
                  .append("    for (int j = 0; j < 200; j++) s += Math.sqrt(x + j);\n")
                  .append("    return (long) s;\n")
                  .append("  }\n");
            }
            sb.append("}\n");
            write(new File(dir, "GenTraces.java"), sb.toString());
        } else if (mode.equals("classes")) {
            for (int i = 0; i < n; i++) {
                String name = "GenClass" + i;
                String src = "public class " + name + " {\n" +
                        "  public static long compute(long x) {\n" +
                        "    double s = 0;\n" +
                        "    for (int j = 0; j < 200; j++) s += Math.sqrt(x + j);\n" +
                        "    return (long) s;\n" +
                        "  }\n" +
                        "}\n";
                write(new File(dir, name + ".java"), src);
            }
        } else {
            throw new IllegalArgumentException(mode);
        }
    }

    private static void write(File f, String content) throws Exception {
        try (FileWriter w = new FileWriter(f)) {
            w.write(content);
        }
    }
}
