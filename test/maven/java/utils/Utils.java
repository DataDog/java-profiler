package utils;

import java.io.File;

public class Utils {
        public static String getJavaProfilerLib() {
            try {
                File root = new File(Utils.class
                    .getResource("Utils.class").toURI()).getParentFile();
                while (!root.getName().startsWith("java-profiler")) {
                    root = root.getParentFile();
                }
                return root.toPath().resolve("build/libjavaProfiler.so").toAbsolutePath().toString();
            } catch (Throwable t) {
                 throw new RuntimeException("Could not find asyncProfiler lib", t);
            }
        }
}
