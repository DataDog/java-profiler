package com.datadoghq.loader;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.ThreadLocalRandom;

import com.datadoghq.profiler.JavaProfiler;

public class DynamicLibraryLoader {

    static {
        System.loadLibrary("loader");
    }

    public static void main(String... args) throws Exception {
        DynamicLibraryLoader loader = new DynamicLibraryLoader();
        String jfrDump = args[0];
        for (int i = 1; i < args.length; i++) {
            String[] split = args[i].split(":");
            if (!loader.loadLibrary(split[0], split[1])) {
                System.err.println("Could not load " + split[0] + " and invoke " + split[1]);
                System.exit(1);
            }
        }
        startProfilerAndDoWork(jfrDump);
    }

    private static void startProfilerAndDoWork(String jfrFile) throws Exception {
        JavaProfiler ap = JavaProfiler.getInstance();
        Path jfrDump = Paths.get(jfrFile);
        ap.execute("start,loglevel=TRACE,cpu=1m,wall=1ms,filter=0,jfr,file=" + jfrDump.toAbsolutePath());
        ap.addThread();
        work();
        ap.stop();
    }

    private static void work() throws Exception {
        Thread.sleep(10);
        long blackhole = System.nanoTime();
        for (int i = 0; i < 10_000_000; i++) {
            blackhole ^= ThreadLocalRandom.current().nextLong();
        }
        Thread.sleep(10);
        System.err.println(blackhole);
    }


    private native boolean loadLibrary(String libraryFile, String functionName);

}
