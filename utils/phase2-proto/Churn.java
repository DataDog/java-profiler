import org.objectweb.asm.*;
import java.lang.management.*;
// Churn <run_s>: Bench3's loader churn without the profiler; prints unloaded class count.
public class Churn {
    public static void main(String[] a) throws Exception {
        long end = System.currentTimeMillis() + Long.parseLong(a[0]) * 1000;
        long n = 0;
        while (System.currentTimeMillis() < end) {
            Bench3.L loader = new Bench3.L();
            for (int c = 0; c < 10; c++) {
                String name = "gen/X" + (n++);
                loader.def(name.replace('/', '.'), Bench3.gen(name)).getMethod("spin", long.class).invoke(null, 1_000_000L);
            }
        }
        System.out.println("loaded=" + n + " unloaded=" + ManagementFactory.getClassLoadingMXBean().getUnloadedClassCount());
    }
}
