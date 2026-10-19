import com.datadoghq.profiler.JavaProfiler;
import org.objectweb.asm.*;
import java.lang.management.*;
import java.nio.file.*;
import java.util.*;
import java.util.concurrent.atomic.*;

// Bench3 <lib> <dump_interval_s> <generation_ms> <run_s> [threads]
// Worst case for phase 2: worker threads keep creating a class loader with CLASSES classes, spin
// in each class for generation_ms / CLASSES, then drop the loader. The JVM unloads them on its own
// schedule (no System.gc()). The main thread dumps every dump_interval_s. Reports how many raw
// frames resolved vs. came back unloaded (class gone before the dump).
public class Bench3 {
    static final int CLASSES = 10;
    static volatile long sink;
    public static void main(String[] a) throws Exception {
        String lib = a[0];
        long dumpMs = Long.parseLong(a[1]) * 1000;
        long genMs = Long.parseLong(a[2]);
        long runMs = Long.parseLong(a[3]) * 1000;
        int threads = a.length > 4 ? Integer.parseInt(a[4]) : 4;
        JavaProfiler prof = JavaProfiler.getInstance(lib, null);
        prof.execute("start,cpu=10ms,cstack=vm,fjmethodid=" + System.getProperty("mode", "lazy") + ",jfr,file=/tmp/jmbench/b3.jfr");
        AtomicBoolean stop = new AtomicBoolean();
        AtomicLong generations = new AtomicLong();
        AtomicLong counter = new AtomicLong();
        List<Thread> workers = new ArrayList<>();
        for (int t = 0; t < threads; t++) {
            Thread w = new Thread(() -> {
                long garbage = 0;
                while (!stop.get()) {
                    try {
                        L loader = new L();
                        for (int c = 0; c < CLASSES; c++) {
                            String name = "gen/C" + counter.incrementAndGet();
                            Class<?> k = loader.def(name.replace('/', '.'), gen(name));
                            k.getMethod("spin", long.class).invoke(null, genMs * 1_000_000L / CLASSES);
                        }
                        // Some allocation, so the heap moves as in a real application.
                        for (int i = 0; i < 2000; i++) garbage += new byte[256].length;
                        generations.incrementAndGet();
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                }
                sink = garbage;
            });
            w.start();
            workers.add(w);
        }
        long start = System.currentTimeMillis();
        int dumps = 0;
        long maxDumpMs = 0;
        while (System.currentTimeMillis() - start < runMs) {
            Thread.sleep(dumpMs);
            long d0 = System.nanoTime();
            prof.dump(Paths.get("/tmp/jmbench/b3-dump.jfr"));
            maxDumpMs = Math.max(maxDumpMs, (System.nanoTime() - d0) / 1_000_000);
            dumps++;
        }
        stop.set(true);
        for (Thread w : workers) w.join();
        Map<String, Long> c = prof.getDebugCounters();
        long resolved = c.getOrDefault("method_resolve_lazy_resolved", 0L);
        long unloaded = c.getOrDefault("method_resolve_lazy_unloaded", 0L);
        long stale = c.getOrDefault("method_resolve_lazy_stale", 0L);
        long notCurrent = c.getOrDefault("method_resolve_lazy_not_current", 0L);
        long unreadable = c.getOrDefault("method_resolve_lazy_unreadable", 0L);
        long used = c.getOrDefault("unload_capture_used", 0L);
        long skipped = c.getOrDefault("jmethodid_skipped_count", 0L);
        long gcs = 0;
        StringBuilder gcInfo = new StringBuilder();
        for (GarbageCollectorMXBean gc : ManagementFactory.getGarbageCollectorMXBeans()) {
            gcInfo.append(gc.getName().replace(' ', '_')).append('=').append(gc.getCollectionCount()).append(' ');
        }
        System.out.printf("RESULT dump_s=%d gen_ms=%d dumps=%d generations=%d classes_loaded=%d unloaded_classes=%d "
                        + "skipped=" + skipped + " resolved=%d unloaded=%d stale=%d not_current=%d unreadable=%d used=%d failed_pct=%.1f lost_pct=%.1f max_dump_ms=%d %s%n",
                dumpMs / 1000, genMs, dumps, generations.get(), counter.get(),
                ManagementFactory.getClassLoadingMXBean().getUnloadedClassCount(),
                resolved, unloaded, stale, notCurrent, unreadable, used,
                // failed: frames resolve() refused; lost: those the capture did not name either.
                100.0 * (unloaded + stale + notCurrent + unreadable) / Math.max(1, resolved + unloaded + stale + notCurrent + unreadable),
                100.0 * Math.max(0, unloaded + stale + notCurrent + unreadable - used) / Math.max(1, resolved + unloaded + stale + notCurrent + unreadable),
                maxDumpMs, gcInfo);
        StringBuilder uc = new StringBuilder();
        for (Map.Entry<String, Long> e : new TreeMap<>(c).entrySet()) {
            if (e.getKey().startsWith("unload_capture_")) uc.append(e.getKey().substring(15)).append('=').append(e.getValue()).append(' ');
        }
        System.out.println("CAPTURE " + uc);
        prof.stop();
    }
    static byte[] gen(String name) {
        ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
        cw.visit(Opcodes.V1_8, Opcodes.ACC_PUBLIC, name, null, "java/lang/Object", null);
        MethodVisitor mv = cw.visitMethod(Opcodes.ACC_PUBLIC | Opcodes.ACC_STATIC, "spin", "(J)V", null, null);
        mv.visitCode();
        mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/System", "nanoTime", "()J", false);
        mv.visitVarInsn(Opcodes.LLOAD, 0); mv.visitInsn(Opcodes.LADD); mv.visitVarInsn(Opcodes.LSTORE, 2);
        Label loop = new Label(), done = new Label();
        mv.visitLabel(loop);
        mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/System", "nanoTime", "()J", false);
        mv.visitVarInsn(Opcodes.LLOAD, 2); mv.visitInsn(Opcodes.LCMP);
        mv.visitJumpInsn(Opcodes.IFGE, done); mv.visitJumpInsn(Opcodes.GOTO, loop);
        mv.visitLabel(done); mv.visitInsn(Opcodes.RETURN); mv.visitMaxs(0, 0); mv.visitEnd();
        cw.visitEnd();
        return cw.toByteArray();
    }
    static final class L extends ClassLoader {
        Class<?> def(String n, byte[] b) { return defineClass(n, b, 0, b.length); }
    }
}
