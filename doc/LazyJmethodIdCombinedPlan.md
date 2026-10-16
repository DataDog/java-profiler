# Combining #864 and #867: plan

> **Working notes. Remove before the PR lands.**
> Branch: `investigate/lazy-jmethodid-vm-resolution`, off #864's `investigate/lazy-jmethodid-resolution`.
> Co-authors: Roman Kennke, Zhengyu Gu (#867). Started 2026-10-16.

Keep #864's safety model (class registry, trace-ID frame tags, redefinition marks) and add #867's
two strong ideas: resolving frames from VM memory, and keeping names of classes that get unloaded.
Leave out #867's one-chunk-per-GC writing.

## Goal

- Memory savings for **all** classes, ideally with **no jmethodIDs at all** for raw frames, not even
  for sampled classes.
- No extra GC-pause time and no recording-size growth.
- Names even for classes unloaded before the dump (`method_resolve_lazy_unloaded` close to 0).
- No JNI/JVMTI when naming raw frames.

## What to take from #867, and what to leave

| Take | Leave out |
|---|---|
| `ResolvedMethod` / `readMethod()`: names, signatures, Thread.run detection from VM memory | One JFR chunk per GC (pause and size cost) |
| Line-number decoding (`VMLineNumberStream`, `compressedLineNumberTable()`, `codeSize()`) | Rotating dictionaries inside the GC callback (likely cause of the mixed-up names) |
| `fillJavaMethodNames()` / `fillJavaMethodInfo(mi, ResolvedMethod)` refactor | Flipping the default without an opt-in (separate rollout decision) |
| `ContextClassLoaderUnloadTest`, plus its gtest additions where they still apply | The code-coverage commits and `.bak` files (their own PR) |
| The "capture names before classes unload" idea, made incremental and file-free | |

## Phase 1: resolve raw frames from VM memory instead of allocating jmethodIDs

1. Bring over #867's `ResolvedMethod`, `readMethod()`, `VMLineNumberStream`, the new vmStructs
   fields (`_constmethod_code_size`, `_constmethod_flags`, `_klass_super`, the version-dependent
   "has line-number table" constant) and `fillJavaMethodNames()`. Zhengyu as author or co-author.
2. `resolveViaRegistry()`: after `pin()`, the trace-ID check and `containsMethod()`, call
   `readMethod()` under crash protection while the class is still pinned. Return a `ResolvedMethod`
   instead of a jmethodID. Drop the dump-time `GetClassMethods`.
3. Key raw frames in Lookup's method table by (untagged `Method*`, trace-ID tag), so resolved rows
   can be reused across dumps without being mistaken for a later class at the same address. The
   per-dump cache (`_raw_method_cache`) becomes unnecessary or holds the row. Open: whether rows
   reused across dumps need a redefinition check through the registry mark (probably yes).
4. Partial mode (`fjmethodid=false`, and lazy's fallback without JFR): replace the `FindClass`
   lookup with `readMethod()`. It keeps today's redefinition gap for system-loader classes; note it,
   or cover it with the registry marks.
5. Bonus: lazy mode no longer needs dereferenceable jmethodIDs, so it could run on JDK 26+. Check
   that nothing else in its path depends on `_can_dereference_jmethod_id`.
6. Validation: sweep the OpenJDK GA tags for what `readMethod()` and the line decoding rely on (the
   compressed line-table format and its UNSIGNED5 change in JDK 20, the "has line-number table"
   flag that moved between 20 and 21, `Klass::_super`); compare decoded line tables with JVMTI
   `GetLineNumberTable` on real JVMs in a CI test; rerun NMT (expected: jmethodID memory ≈ 0 even
   for sampled classes).

### Phase 1 status (2026-10-16)

- Code: commit "Resolve raw frames from VM metadata instead of allocating jmethodIDs".
- Steps 1, 2, 4 done; step 3 settled: refused frames never touch MethodMap rows, rows are keyed by
  (untagged `Method*`, low 13 tag bits, `RAW_METHOD_MARK`) and refilled at first use in every chunk,
  so no redefinition re-check is needed for reused rows. Step 5 (JDK 26+) open.
- Line-table bound is HotSpot's own (`bci <= code_size`, `ConstMethod::verify_on()`), not #867's `<`.
- Sweep: `_flags`/`_code_size`/`Klass::_super` and the has-line-number-table constant checked on
  JDK 11-26 GA tags; 8u via containers.
- `LazyLineNumberConsistencyTest` (VM vs JVMTI line tables): 0 mismatches on macOS JDK 25 and in
  every aarch64 container cell (glibc 17/21/25 debug, 21 ASan; musl 8/11/21 debug), 249-389 common
  frames each. All `*Lazy*` tests pass in those cells; JFR trace ID matches in every debug cell.
  glibc 8/11 are not runnable on aarch64 (skipped as in CI). gtests: debug + release pass on macOS,
  debug in every container cell.
- NMT (JDK 25, debug, 1M methods, KB committed): sampled run with ~9.3k raw frames resolved keeps
  Class at the no-profiler level (+14,234 vs +14,236; preloading +22,982). Compared against the
  shipping modes and no profiler only; #864 is superseded. Dump +~10 ms vs `fjmethodid=true`. Harness:
  `/tmp/jmbench/Bench2.java`.

## Phase 2: keep names of classes that unload before the dump, cheaply

1. Capture only methods whose frames are still unresolved **and** whose class can be unloaded.
   Record "unloadable" in the registry entry at registration, from the class loader (boot,
   platform and application loaders never unload).
2. Know what's pending without scanning every trace during a pause. Prototype and measure both:
   (a) a bounded lock-free "first seen" set the sampler fills and the hook drains; (b) walking only
   the traces created since the last capture (trace IDs grow monotonically within a storage
   instance).
3. In `GarbageCollectionStart` (VM stopped), copy names and line tables with `readMethod()` into a
   pre-resolved cache keyed by (`Method*`, tag). No JNI, no JVMTI, no file writes, no dictionary
   rotation. Incremental: only methods first seen since the last GC.
4. Skip when nothing unloadable is pending; also skip young-only pauses if they can be told apart
   (open question: GC cause through VM state?).
5. Do the same capture in the pre-redefinition hook for that class's pending frames, so frames
   refused after a redefinition keep their names too.
6. At dump time, when `pin()` reports the class gone, use the pre-resolved name instead of
   "unknown"; drop cache entries once written.
7. Validation: the GC-pause benchmark from the #867 review must show safepoint times unchanged
   compared with `fjmethodid=true`, recording size unchanged, and `ContextClassLoaderUnloadTest`
   must find names for frames of unloaded classes.

## Tests

- Everything in #864.
- #867's class-unload test.
- A JVMTI-against-VM line-table comparison test.
- The GC-pause and recording-size benchmark as a nightly or slow test, with thresholds.
- `LazyRedefinitionStressTest` extended to check that frames refused after a redefinition still
  have names (phase 2, step 5).

## Order and PR structure

1. **One PR for #864 + phase 1** (this branch), superseding #864 and #867, co-authored with
   Zhengyu. Phase 1 rewrites #864's dump path (no dump-time jmethodID allocation), so #864 does not
   land on its own. The PR description says what changed since #864's two review rounds. Needs
   Zhengyu's agreement first, via the (unposted) #867 review.
2. **Phase 2 as a separate follow-up PR**: names for unloaded classes. It is additive (without it
   those frames stay "unknown", as in #864), the riskiest part (GC-callback work, where #867's
   pause cost came from), and conditional on the GC-pause benchmark. Zhengyu might want to lead it.
3. Default flip after a nightly soak, watching the counters.

## Risks and open questions

- More parsing of HotSpot internals for names and line tables; the phase 1 sweep is meant to
  contain that.
- Pending-frame tracking in phase 2 must keep signal-handler work and memory bounded.
- Whether young pauses can be told apart without GC-specific internals.
- Whether partial mode gets the registry's redefinition marks, or stays as today.

## Hand-over to the Linux box (x64)

State at hand-over (2026-10-16): phase 1 complete on this branch, validated on macOS arm64 and in
aarch64 containers (see "Phase 1 status"). Draft PR open against `main`; it carries #864's commits
and will replace #864 (and #867's core), pending agreement with Zhengyu. The #867 review is still
unposted.

To do on x64, in this order:

1. **Tests.** `./utils/run-containers-tests.sh --arch=x64 --tests='*.Lazy*' --gtest` for glibc
   8/11/17/21/25 debug, glibc 21 ASan, musl 21. On musl the test runner takes a regex:
   `--tests='com.datadoghq.profiler.cpu.Lazy.*'`. Watch `LazyLineNumberConsistencyTest`'s
   `mismatches=` line and `LazyTraceIdJfrValidationTest`'s `profiler trace id=` line.
2. **JDK 26+ (phase 1 step 5).** No container image has 26. Lazy mode is gated only on
   `VMStructs::hasKlassMethods()` and trace-ID calibration, not on `_can_dereference_jmethod_id`
   (false on > 25), so it may already run; check that walkVM's jmethodID lookup and the redefinition
   preload behave with JDK-8268406's `JmethodIDTable`. Either make it work or state it is out of
   scope in the PR.
3. **Renaissance, same setup as #864's tables** (release build, `cpu=10ms,cstack=vm`, `-Xms=-Xmx`,
   5 fresh JVMs per mode, modes interleaved, first dump after 10 s; `dotty`, `finagle-http`, `als`;
   JDK 11/21/25), `fjmethodid=true` vs `lazy`:
   - NMT Class + Internal over no profiler. Expected: lazy close to its own registry cost, since
     sampled classes no longer get jmethodIDs (#864 saved only 35-55% here).
   - Dump latency, first and later dumps. #864's first lazy dump was 2-4x `true` (dump-time
     jmethodID allocation, now gone). New risk: later dumps resolve raw frames every time instead
     of matching `true`. On macOS (debug, 1,600 generated classes) lazy was 18.9 / ~16 ms vs `true`
     15.2 / ~13.4 ms (first / later). If `finagle-http` later dumps are clearly slower, skip
     `readMethod()` for rows filled in an earlier chunk while the class pins with the same trace ID
     and is not redefined.
   - Counter renamed: `method_resolve_lazy_class_loaded` -> `method_resolve_lazy_resolved` (raw
     frames resolved per dump); use it to confirm lazy mode is active.
4. **Synthetic NMT**, optional: the harness below, both variants, on x64.

Then: review pass over the phase 1 code (VM reader, line tables, MethodMap raw keys, partial mode),
rewrite the PR description from #864's (step 3 of "How it works", overhead table, counters, new
tests, changes since #864's reviews), remove this file, and ask Zhengyu before un-drafting.

<details><summary>NMT harness (<code>Bench2.java</code>, was <code>/tmp/jmbench</code> on the Mac)</summary>

Needs ASM 9 and the profiler's Java classes on the classpath. Run with
`-XX:NativeMemoryTracking=summary`:
`java -XX:NativeMemoryTracking=summary -cp asm.jar:<ddprof-lib classes>:. Bench2 20000 <none|true|false|lazy> <load|sample> <libjavaProfiler.so>`.
Results on macOS: `load` lazy Class +14,233 KB / Internal +191 KB vs `true` +22,981 / +8,136;
`sample` lazy +14,234 / +471 vs `true` +22,982 / +8,409, with ~9.3k raw frames resolved.

```java
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
```

</details>

## Measurements to compare against (from the #867 review)

macOS arm64, JDK 25, G1, ~650–950 young GCs/s, 15 s: safepoint time per young GC 0.34 ms (no
profiler), 0.35 ms (`fjmethodid=true`), 0.36 ms (#864), 0.84 ms (#867). NMT, 1M methods in
custom-loader classes: preloading ~15.8 MiB; #864 ~1 MiB. Harness: `/tmp/gcbench` and
`/tmp/jmbench` on the Mac (not in the repo).
