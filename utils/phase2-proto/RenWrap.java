import com.datadoghq.profiler.JavaProfiler;
import java.nio.file.*;
import java.util.*;

// RenWrap <lib> <dump_interval_s> <renaissance args...>, with the Renaissance jar on the class path.
// Starts the profiler in fjmethodid=lazy mode (DDPROF_CAPTURE_UNLOADING picks the capture variant),
// dumps every dump_interval_s like dd-trace-java, and prints the lazy-resolution and capture
// counters when the JVM exits (Renaissance calls System.exit()).
public class RenWrap {
    public static void main(String[] a) throws Exception {
        JavaProfiler prof = JavaProfiler.getInstance(a[0], null);
        long dumpMs = Long.parseLong(a[1]) * 1000;
        prof.execute("start,cpu=10ms,wall=50ms,cstack=vm,fjmethodid=" + System.getProperty("mode", "lazy")
                + ",jfr,file=/tmp/jmbench/ren.jfr");
        Thread dumper = new Thread(() -> {
            try {
                while (true) {
                    Thread.sleep(dumpMs);
                    prof.dump(Paths.get("/tmp/jmbench/ren-dump.jfr"));
                }
            } catch (Exception e) {
                // exit
            }
        });
        dumper.setDaemon(true);
        dumper.start();
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            try {
                prof.dump(Paths.get("/tmp/jmbench/ren-dump.jfr"));
            } catch (Exception e) {
                // report what we have
            }
            StringBuilder sb = new StringBuilder("COUNTERS ");
            for (Map.Entry<String, Long> e : new TreeMap<>(prof.getDebugCounters()).entrySet()) {
                String k = e.getKey();
                if (k.startsWith("unload_capture_") || k.startsWith("method_resolve_lazy_")) {
                    sb.append(k.replace("unload_capture_", "uc_").replace("method_resolve_lazy_", "lazy_"))
                      .append('=').append(e.getValue()).append(' ');
                }
            }
            System.out.println(sb);
        }));
        String[] rest = Arrays.copyOfRange(a, 2, a.length);
        Class.forName("org.renaissance.core.Launcher").getMethod("main", String[].class).invoke(null, (Object) rest);
    }
}
