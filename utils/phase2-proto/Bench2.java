import com.datadoghq.profiler.JavaProfiler;
import org.objectweb.asm.*;
import java.lang.management.ManagementFactory;
import javax.management.ObjectName;
import java.nio.file.*;
import java.util.*;

// Bench2 <classes> <none|true|false|lazy> <load|sample> <lib>
// load:   like Bench (load-only, no profiled calls into the generated classes).
// sample: additionally calls every generated class round-robin for SAMPLE_MS under the profiler,
//         then dumps (which is when lazy resolution happens) before measuring NMT.
public class Bench2 {
    static int METHODS = 50;
    static long SAMPLE_MS = 8000;
    static String nmt(String arg) throws Exception {
        return (String) ManagementFactory.getPlatformMBeanServer().invoke(
            new ObjectName("com.sun.management:type=DiagnosticCommand"), "vmNativeMemory",
            new Object[]{new String[]{arg}}, new String[]{String[].class.getName()});
    }
    public static void main(String[] a) throws Exception {
        int n = Integer.parseInt(a[0]);
        String mode = a[1];
        boolean sample = a[2].equals("sample");
        JavaProfiler prof = null;
        if (!mode.equals("none")) {
            prof = JavaProfiler.getInstance(a[3], null);
            prof.execute("start,cpu=1ms,cstack=vm,fjmethodid=" + mode + ",jfr,file=/tmp/jmbench/b2-" + mode + ".jfr");
        }
        load(2000, "W"); System.gc(); Thread.sleep(200);
        nmt("baseline");
        long t0 = System.nanoTime();
        List<Runnable> keep = load(n, "B");
        System.out.println("load_ms=" + (System.nanoTime() - t0) / 1_000_000);
        if (sample) {
            long end = System.currentTimeMillis() + SAMPLE_MS;
            while (System.currentTimeMillis() < end) {
                for (Runnable r : keep) r.run();
            }
            if (prof != null) {
                long d0 = System.nanoTime();
                prof.dump(Paths.get("/tmp/jmbench/b2-" + mode + "-dump.jfr"));
                System.out.println("dump_ms=" + (System.nanoTime() - d0) / 1_000_000);
                Map<String, Long> c = prof.getDebugCounters();
                System.out.println("resolved=" + c.get("method_resolve_lazy_resolved"));
            }
        }
        java.util.regex.Pattern p = java.util.regex.Pattern.compile("^-\\s+(.+?) \\(reserved=.*?committed=\\d+KB(?: ([+-]\\d+)KB)?");
        for (String line : nmt("summary.diff").split("\n")) {
            java.util.regex.Matcher m = p.matcher(line);
            if (m.find()) {
                System.out.println("CAT " + m.group(1).trim() + "=" + (m.group(2) == null ? "0" : m.group(2)));
            } else if (line.trim().startsWith("Total:")) {
                java.util.regex.Matcher t = java.util.regex.Pattern.compile("committed=\\d+KB ([+-]\\d+)KB").matcher(line);
                if (t.find()) System.out.println("CAT Total=" + t.group(1));
            }
        }
        System.out.println(keep.size());
    }
    static List<Runnable> load(int n, String p) throws Exception {
        List<Runnable> out = new ArrayList<>();
        L loader = null;
        for (int i = 0; i < n; i++) {
            if (i % 100 == 0) loader = new L();
            String name = "gen/" + p + i;
            Class<?> c = loader.def(name.replace('/', '.'), gen(name));
            out.add((Runnable) c.getConstructor().newInstance());
        }
        return out;
    }
    static byte[] gen(String name) {
        ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_MAXS);
        cw.visit(Opcodes.V1_8, Opcodes.ACC_PUBLIC, name, null, "java/lang/Object", new String[]{"java/lang/Runnable"});
        MethodVisitor ctor = cw.visitMethod(Opcodes.ACC_PUBLIC, "<init>", "()V", null, null);
        ctor.visitCode(); ctor.visitVarInsn(Opcodes.ALOAD, 0);
        ctor.visitMethodInsn(Opcodes.INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
        ctor.visitInsn(Opcodes.RETURN); ctor.visitMaxs(0, 0); ctor.visitEnd();
        for (int i = 0; i < METHODS; i++) {
            MethodVisitor mv = cw.visitMethod(Opcodes.ACC_PUBLIC | Opcodes.ACC_STATIC, "m" + i, "()I", null, null);
            mv.visitCode(); mv.visitLdcInsn(i); mv.visitInsn(Opcodes.IRETURN); mv.visitMaxs(0, 0); mv.visitEnd();
        }
        // run(): sum of all m_i, so every method of the class can appear in samples.
        MethodVisitor run = cw.visitMethod(Opcodes.ACC_PUBLIC, "run", "()V", null, null);
        run.visitCode(); run.visitInsn(Opcodes.ICONST_0);
        for (int i = 0; i < METHODS; i++) {
            run.visitMethodInsn(Opcodes.INVOKESTATIC, name, "m" + i, "()I", false);
            run.visitInsn(Opcodes.IADD);
        }
        run.visitInsn(Opcodes.POP); run.visitInsn(Opcodes.RETURN); run.visitMaxs(0, 0); run.visitEnd();
        cw.visitEnd();
        return cw.toByteArray();
    }
    static final class L extends ClassLoader {
        Class<?> def(String n, byte[] b) { return defineClass(n, b, 0, b.length); }
    }
}
