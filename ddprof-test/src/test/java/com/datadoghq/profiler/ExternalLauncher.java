package com.datadoghq.profiler;

public class ExternalLauncher {
    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            throw new RuntimeException();
        }
        if (args[0].equals("library")) {
            JVMAccess.getInstance();
        } else if (args[0].equals("profiler")) {
            JavaProfiler.getInstance();
        }
    }
}
