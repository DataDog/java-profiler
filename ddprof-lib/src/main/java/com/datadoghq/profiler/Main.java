package com.datadoghq.profiler;

import java.io.IOException;

public class Main {
    public static void main(String... args) throws IOException {
        String command = args.length > 0 ? args[0] : "status";
        JavaProfiler profiler = JavaProfiler.getInstance();
        profiler.execute(command);
        profiler.stop();
    }
}
