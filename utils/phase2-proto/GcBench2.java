import org.objectweb.asm.*;
import java.util.*;
import java.util.concurrent.atomic.*;

public class GcBench2 {
    static volatile Object sink;
    public static void main(String[] a) throws Exception {
        long end = System.nanoTime() + Long.parseLong(a[0]) * 1_000_000_000L;
        List<Thread> ts = new ArrayList<>();
        for (int t = 0; t < 4; t++) {
            Thread th = new Thread(() -> { while (System.nanoTime() < end) level1(); });
            ts.add(th); th.start();
        }
        // Two churn threads: a fresh loader with 10 classes every ~50 ms each, each class sampled
        // while it spins, then dropped, so the profiler's pending set is rarely empty.
        AtomicLong n = new AtomicLong();
        for (int c = 0; c < 2; c++) {
            Thread churn = new Thread(() -> {
                try {
                    while (System.nanoTime() < end) {
                        L loader = new L();
                        for (int k = 0; k < 10; k++) {
                            String name = "gen/Churn" + n.incrementAndGet();
                            Class<?> cl = loader.def(name.replace('/', '.'), gen(name));
                            cl.getMethod("spin", long.class).invoke(null, 5_000_000L);
                        }
                    }
                } catch (Exception e) { throw new RuntimeException(e); }
            });
            churn.start(); ts.add(churn);
        }
        for (Thread th : ts) th.join();
    }
    static void level1() { level2(); }
    static void level2() { level3(); }
    static void level3() {
        Object[] ring = new Object[256];
        for (int i = 0; i < 100_000; i++) ring[i & 255] = new byte[512];
        sink = ring;
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
        mv.visitVarInsn(Opcodes.LLOAD, 2); mv.visitInsn(Opcodes.LCMP); mv.visitJumpInsn(Opcodes.IFGE, done);
        mv.visitJumpInsn(Opcodes.GOTO, loop);
        mv.visitLabel(done); mv.visitInsn(Opcodes.RETURN); mv.visitMaxs(0, 0); mv.visitEnd();
        cw.visitEnd();
        return cw.toByteArray();
    }
    static final class L extends ClassLoader {
        Class<?> def(String n, byte[] b) { return defineClass(n, b, 0, b.length); }
    }
}
