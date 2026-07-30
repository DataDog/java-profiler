import com.datadoghq.profiler.JavaProfiler;

import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;

/**
 * Measures NM_THREAD_LOCAL while N worker threads are actually alive, instead
 * of after they've exited.
 *
 * ProfiledThread (the struct NM_THREAD_LOCAL accounts) is freed via a pthread
 * TLS destructor as soon as its owning thread exits (threadLocalData.cpp).
 * The counter is a live/current count, not a cumulative one. A JFR chunk
 * (and the NM_* counter snapshot in it) is only written at profiler stop /
 * process exit, so a sweep that spawns N threads and joins them all before
 * exiting -- as MemSweepMain's "threads" mode does -- reads the counter
 * after nearly every one of those N threads has already freed its own
 * ProfiledThread. The reading at that point reflects whatever handful of
 * long-lived JVM-internal threads happen to still have one, not N.
 *
 * This program spawns N threads, waits for all of them to register via
 * addThread(), then calls the public JavaProfiler.dump(Path) API to force a
 * JFR chunk write WHILE all N are still alive and busy-looping, giving an
 * accurate live count. See memory-sweep-results-linux.md.
 */
public class LiveThreadLocalSweep {
    public static void main(String[] args) throws Exception {
        int n = Integer.parseInt(args[0]);
        long holdMs = Long.parseLong(args[1]);
        String dumpPath = args[2];

        String libPath = System.getProperty("memsweep.libpath");
        if (libPath == null) {
            throw new IllegalStateException("pass -Dmemsweep.libpath=<path to the already-loaded agent .so/.dylib>");
        }
        JavaProfiler profiler = JavaProfiler.getInstance(libPath, System.getProperty("java.io.tmpdir"));
        profiler.addThread();

        CountDownLatch start = new CountDownLatch(1);
        CountDownLatch registered = new CountDownLatch(n);
        List<Thread> threads = new ArrayList<>();
        long deadline = System.currentTimeMillis() + holdMs;
        for (int i = 0; i < n; i++) {
            Thread t = new Thread(() -> {
                profiler.addThread();
                registered.countDown();
                try { start.await(); } catch (InterruptedException ignored) {}
                double sink = 0;
                while (System.currentTimeMillis() < deadline) {
                    for (int j = 0; j < 5000; j++) sink += Math.sqrt(j);
                }
                if (Double.isNaN(sink)) throw new AssertionError();
            }, "livesweep-thread-" + i);
            t.setDaemon(true);
            threads.add(t);
            t.start();
        }
        start.countDown();
        registered.await();
        Thread.sleep(500); // let addThread() calls fully land before snapshotting
        profiler.dump(Paths.get(dumpPath)); // NM_THREAD_LOCAL snapshot, all N threads still alive
        for (Thread t : threads) t.join();
    }
}
