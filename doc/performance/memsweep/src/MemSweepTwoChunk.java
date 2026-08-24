import com.datadoghq.profiler.JavaProfiler;

import java.io.File;
import java.net.URL;
import java.net.URLClassLoader;
import java.nio.file.Paths;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

/**
 * `classes` workload variant that forces an intermediate profiler.dump() near
 * the end of the run, then keeps running to the normal exit-time chunk write.
 *
 * NM_METHOD_MAP (like NM_DICTIONARY) is populated by Lookup::resolveMethod()
 * during writeCpool(), which runs AFTER that same chunk's NM_* counter
 * snapshot -- see flightRecorder.cpp's finishChunk() (updateNativeMemStats()/
 * writeNativeMem() at lines ~820/822, writeCpool() at line ~835). A
 * single-chunk run therefore always reads NM_METHOD_MAP as of the *previous*
 * chunk (zero, for the only chunk). Forcing an intermediate dump gives the
 * final chunk (written normally at process exit) a prior chunk's growth to
 * report, the same "dump near the end" technique already used for
 * NM_DICTIONARY in memory-sweep-results-linux.md.
 *
 * Usage: MemSweepTwoChunk <n> <totalDurationMs> <genDir> <dumpAtMs> <dumpPath>
 */
public class MemSweepTwoChunk {
    public static void main(String[] args) throws Exception {
        int n = Integer.parseInt(args[0]);
        long durationMs = Long.parseLong(args[1]);
        File genDir = new File(args[2]);
        long dumpAtMs = Long.parseLong(args[3]);
        String dumpPath = args[4];

        String libPath = System.getProperty("memsweep.libpath");
        if (libPath == null) {
            throw new IllegalStateException("pass -Dmemsweep.libpath=<path to the already-loaded agent .so/.dylib>");
        }
        JavaProfiler profiler = JavaProfiler.getInstance(libPath, System.getProperty("java.io.tmpdir"));
        profiler.addThread();

        URLClassLoader loader = new URLClassLoader(new URL[]{genDir.toURI().toURL()}, MemSweepTwoChunk.class.getClassLoader());
        List<Class<?>> classes = new ArrayList<>();
        List<Method> methods = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            Class<?> c = Class.forName("GenClass" + i, true, loader);
            classes.add(c);
            methods.add(c.getMethod("compute", long.class));
        }

        long start = System.currentTimeMillis();
        long deadline = start + durationMs;
        long dumpAt = start + dumpAtMs;
        boolean dumped = false;
        long sink = 0;
        while (System.currentTimeMillis() < deadline) {
            for (int i = 0; i < n; i++) sink += (long) methods.get(i).invoke(null, (long) i);
            if (!dumped && System.currentTimeMillis() >= dumpAt) {
                profiler.dump(Paths.get(dumpPath));
                dumped = true;
            }
        }
        if (sink == Long.MIN_VALUE) throw new AssertionError();
        if (classes.size() != n) throw new AssertionError();
        // Agent was attached via -agentpath; the VMDeath shutdown hook flushes
        // the final JFR chunk (with the post-dump growth visible) at exit.
    }
}
