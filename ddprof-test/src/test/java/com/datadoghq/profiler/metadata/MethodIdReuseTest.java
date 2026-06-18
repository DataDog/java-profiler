/*
 * Copyright 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.metadata;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.FileChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

/**
 * Regression test for PROF-15130: duplicate {@code jdk.types.Method} constant-pool ids.
 *
 * <p>{@code resolveMethod()} used to assign {@code mi->_key = _method_map->size() + 1}, but
 * {@code cleanupUnreferencedMethods()} (enabled by default, erases methods unreferenced for
 * {@code AGE_THRESHOLD = 3} chunks) shrinks the map. After an erase, {@code size()+1} reissues an
 * id still owned by a surviving method, so two live methods share one id in a single chunk's
 * method constant pool. First-wins strict parsers (JMC / jafar / the Datadog backend) then render
 * a phantom (wrong-but-valid) method, while last-wins OpenJDK {@code jfr} renders correctly. JMC's
 * loader is last-wins and therefore CANNOT see the duplicate — so this test parses the raw chunk
 * constant pools itself, which is the precise oracle.
 *
 * <p>The fix replaced {@code size()+1} with a free-list id allocator
 * ({@code MethodMap::allocId()/freeId()}): an id is recycled only after the owning method is
 * erased, so no two live methods ever share an id.
 *
 * <p>Deterministic erase+reuse driver: each {@code dump()} produces a chunk and runs
 * {@code cleanupUnreferencedMethods}. Phase 1 touches a LARGE set of distinct lambda call targets
 * (high ids). Phases 2..N (&ge; AGE_THRESHOLD dumps) stop touching the phase-1 lambdas (so they age
 * out and get erased) while touching a DIFFERENT persistent set plus brand-new lambdas (which draw
 * recycled ids). The oracle asserts no {@code jdk.types.Method} id maps to two distinct method
 * definitions within any chunk.
 */
public class MethodIdReuseTest extends AbstractProfilerTest {

    // Phases beyond AGE_THRESHOLD (3) so phase-1 methods are definitely erased.
    private static final int PHASE1_DUMPS = 3;
    private static final int PHASE2_DUMPS = 7; // well beyond AGE_THRESHOLD; many erase+reuse chunks
    private static final int DISTINCT_TARGETS_PER_PHASE = 600;

    // Generated lambda call targets. A large, churned set maximises method-pool turnover so the
    // free-list / size()+1 schemes diverge.
    private final List<Runnable> phase1Targets = new ArrayList<>();
    private final List<Runnable> persistentTargets = new ArrayList<>();

    protected static volatile long sink;

    private static Runnable makeBusyTarget(final int seed) {
        return () -> {
            long acc = seed;
            for (int i = 0; i < 50_000; i++) {
                acc += (i ^ (acc >> 1)) + seed;
            }
            sink += acc;
        };
    }

    private void buildTargets() {
        for (int i = 0; i < DISTINCT_TARGETS_PER_PHASE; i++) {
            phase1Targets.add(makeBusyTarget(1_000 + i));
            persistentTargets.add(makeBusyTarget(9_000_000 + i));
        }
    }

    private void runFor(List<Runnable> targets, List<Runnable> extra, long millis) {
        long deadline = System.currentTimeMillis() + millis;
        int idx = 0;
        while (System.currentTimeMillis() < deadline) {
            targets.get(idx % targets.size()).run();
            if (extra != null && !extra.isEmpty()) {
                extra.get(idx % extra.size()).run();
            }
            idx++;
        }
    }

    @Test
    public void methodPoolIdsAreUniquePerChunk() throws Exception {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        Assumptions.assumeFalse(Platform.isJ9());

        buildTargets();
        registerCurrentThreadForWallClockProfiling();
        waitForProfilerReady(2000);

        List<Path> dumps = new ArrayList<>();

        // Phase 1: touch the large phase-1 lambda set (+ persistent set) so they all get resolved
        // and assigned high method-pool ids.
        for (int d = 0; d < PHASE1_DUMPS; d++) {
            runFor(phase1Targets, persistentTargets, 600);
            Path rec = Files.createTempFile("prof15130-reuse-p1-" + d + "-", ".jfr");
            dumps.add(rec);
            dump(rec);
            System.out.println("[PROF-15130] phase1 dump #" + d + " -> " + rec.toAbsolutePath());
        }

        // Phase 2: STOP touching phase-1 lambdas (they age out and get erased after AGE_THRESHOLD
        // dumps) while touching the persistent set + brand-new lambdas that draw recycled ids.
        for (int d = 0; d < PHASE2_DUMPS; d++) {
            List<Runnable> fresh = new ArrayList<>();
            for (int i = 0; i < DISTINCT_TARGETS_PER_PHASE; i++) {
                fresh.add(makeBusyTarget(50_000_000 + d * 100_000 + i));
            }
            runFor(persistentTargets, fresh, 600);
            Path rec = Files.createTempFile("prof15130-reuse-p2-" + d + "-", ".jfr");
            dumps.add(rec);
            dump(rec);
            System.out.println("[PROF-15130] phase2 dump #" + d + " -> " + rec.toAbsolutePath());
        }

        stopProfiler();

        System.out.println("[PROF-15130] produced dump files:");
        for (Path p : dumps) {
            System.out.println("[PROF-15130]   " + p.toAbsolutePath());
        }

        // Oracle: across every chunk in every dump, no method-pool id maps to two distinct method
        // definitions.
        int totalDuplicates = 0;
        for (Path dump : dumps) {
            int dups = countDuplicateMethodIds(dump);
            System.out.println("[PROF-15130] " + dump.getFileName() + " duplicate method-pool ids: " + dups);
            totalDuplicates += dups;
        }

        assertEquals(0, totalDuplicates,
                "Found " + totalDuplicates + " jdk.types.Method constant-pool id(s) mapping to two "
                        + "distinct method definitions (PROF-15130). See stdout for the dump files.");
    }

    @Override
    protected String getProfilerCommand() {
        // wall+cpu maximise sample density so the churned lambdas land in stacktraces and thus the
        // method pool. Method cleanup is left ENABLED (default) — that is what triggers the bug.
        return "cpu=1ms,wall=~1ms";
    }

    // ───────────────────────── raw JFR method-pool oracle ─────────────────────────
    //
    // A minimal, dependency-free JFR reader that walks every chunk in the file, parses the
    // metadata to learn the field layout of jdk.types.Method / jdk.types.Symbol / java.lang.Class,
    // then reads each constant-pool checkpoint and detects any jdk.types.Method id that resolves to
    // two DISTINCT method definitions within the same chunk. This is the precise duplicate-id
    // oracle (JMC's last-wins loader would silently hide it).

    /** @return number of method-pool ids in the file that map to &gt;1 distinct definition. */
    static int countDuplicateMethodIds(Path file) throws IOException {
        byte[] all;
        try (FileChannel ch = FileChannel.open(file, StandardOpenOption.READ)) {
            long size = ch.size();
            ByteBuffer bb = ByteBuffer.allocate((int) size);
            while (bb.hasRemaining() && ch.read(bb) > 0) { /* read fully */ }
            all = bb.array();
        }
        int duplicates = 0;
        long pos = 0;
        while (pos + 8 <= all.length) {
            // Chunk magic "FLR\0"
            if (!(all[(int) pos] == 'F' && all[(int) pos + 1] == 'L' && all[(int) pos + 2] == 'R'
                    && all[(int) pos + 3] == 0)) {
                break;
            }
            Chunk chunk = new Chunk(all, (int) pos);
            duplicates += chunk.countDuplicateMethodIds();
            if (chunk.chunkSize <= 0) {
                break;
            }
            pos += chunk.chunkSize;
        }
        return duplicates;
    }

    private static final class Chunk {
        final byte[] f;
        final int base;        // chunk start offset within the file
        final long chunkSize;
        final long cpOffset;   // checkpoint offset, relative to chunk start
        final long metaOffset; // metadata offset, relative to chunk start

        // metadata: classId -> ClassDef
        final Map<Long, ClassDef> classes = new HashMap<>();
        long methodTypeId = -1, symbolTypeId = -1, classTypeId = -1, stringTypeId = -1;

        Chunk(byte[] f, int base) {
            this.f = f;
            this.base = base;
            // Header (big-endian): magic(4) major(2) minor(2) chunkSize(8) cpOffset(8) metaOffset(8)
            this.chunkSize = beLong(base + 8);
            this.cpOffset = beLong(base + 16);
            this.metaOffset = beLong(base + 24);
            parseMetadata();
        }

        // Resolution tables, unioned across all checkpoints in the chunk (last-wins is fine: a
        // symbol/class id is stable within a chunk). Used only to render readable defs.
        private final Map<Long, String> symbols = new HashMap<>();
        private final Map<Long, Long> classNameRef = new HashMap<>(); // class id -> name symbol ref
        // id -> set of DISTINCT raw [type,name,descriptor] ref-tuples seen for that method id.
        // size() > 1 ⇒ the id carried two different method definitions in this chunk ⇒ the bug.
        private final Map<Long, Set<String>> methodRefTuples = new LinkedHashMap<>();

        int countDuplicateMethodIds() {
            // Follow the checkpoint delta chain.
            Set<Long> visited = new HashSet<>();
            long off = base + cpOffset;
            while (off >= base && off < base + chunkSize && !visited.contains(off)) {
                visited.add(off);
                long[] p = {off};
                readVarLong(p); // size
                readVarLong(p); // typeId (EventCheckpoint)
                readVarLong(p); // start
                readVarLong(p); // duration
                long deltaRaw = readVarLong(p);
                long delta = (deltaRaw >>> 1) ^ -(deltaRaw & 1); // zig-zag
                p[0] += 1; // flush byte
                long poolCount = readVarLong(p);
                for (long i = 0; i < poolCount; i++) {
                    long classId = readVarLong(p);
                    long count = readVarLong(p);
                    ClassDef cd = classes.get(classId);
                    if (cd == null) {
                        // Unknown layout — cannot safely parse further in this checkpoint.
                        return duplicateCount();
                    }
                    boolean isMethod = classId == methodTypeId;
                    boolean isSymbol = classId == symbolTypeId;
                    boolean isClass = classId == classTypeId;
                    for (long e = 0; e < count; e++) {
                        long id = readVarLong(p);
                        if (isSymbol) {
                            String s = readString(p);
                            symbols.put(id, s);
                        } else if (isMethod) {
                            long typeRef = 0, nameRef = 0, descRef = 0;
                            for (FieldDef fd : cd.fields) {
                                Object v = readField(p, fd);
                                if (v instanceof Long) {
                                    if ("type".equals(fd.name)) typeRef = (Long) v;
                                    else if ("name".equals(fd.name)) nameRef = (Long) v;
                                    else if ("descriptor".equals(fd.name)) descRef = (Long) v;
                                }
                            }
                            // Record the DISTINCT raw ref-tuple for this id. Two different tuples
                            // for one id within the chunk is exactly the PROF-15130 collision.
                            String tuple = typeRef + ":" + nameRef + ":" + descRef;
                            methodRefTuples.computeIfAbsent(id, k -> new HashSet<>()).add(tuple);
                        } else if (isClass) {
                            long nameRef = 0;
                            for (FieldDef fd : cd.fields) {
                                Object v = readField(p, fd);
                                if ("name".equals(fd.name) && v instanceof Long) {
                                    nameRef = (Long) v;
                                }
                            }
                            classNameRef.put(id, nameRef);
                        } else {
                            // skip every field of this entry
                            for (FieldDef fd : cd.fields) {
                                readField(p, fd);
                            }
                        }
                    }
                }
                if (delta == 0) break;
                off += delta;
            }
            return duplicateCount();
        }

        private int duplicateCount() {
            int dups = 0;
            for (Map.Entry<Long, Set<String>> en : methodRefTuples.entrySet()) {
                if (en.getValue().size() > 1) {
                    dups++;
                    System.out.println("[PROF-15130]   DUPLICATE method id=" + en.getKey()
                            + " defs=" + renderTuples(en.getValue()));
                }
            }
            return dups;
        }

        private List<String> renderTuples(Set<String> tuples) {
            List<String> out = new ArrayList<>();
            for (String t : tuples) {
                String[] parts = t.split(":");
                long typeRef = Long.parseLong(parts[0]);
                long nameRef = Long.parseLong(parts[1]);
                long descRef = Long.parseLong(parts[2]);
                String cls = "<cls#" + typeRef + ">";
                Long cnr = classNameRef.get(typeRef);
                if (cnr != null) {
                    String s = symbols.get(cnr);
                    if (s != null) cls = s;
                }
                String nm = symbols.getOrDefault(nameRef, "<sym#" + nameRef + ">");
                String desc = symbols.getOrDefault(descRef, "<sym#" + descRef + ">");
                out.add(cls + "." + nm + desc);
            }
            return out;
        }

        private Object readField(long[] p, FieldDef fd) {
            if (fd.dimension == 1) {
                long n = readVarLong(p);
                for (long i = 0; i < n; i++) {
                    readScalar(p, fd);
                }
                return null;
            }
            return readScalar(p, fd);
        }

        private Object readScalar(long[] p, FieldDef fd) {
            if (fd.constantPool) {
                return readVarLong(p); // a constant-pool reference id
            }
            ClassDef t = classes.get(fd.typeId);
            String tn = t != null ? t.name : null;
            if ("java.lang.String".equals(tn)) {
                return readString(p);
            }
            if ("boolean".equals(tn) || "byte".equals(tn)) {
                p[0] += 1;
                return null;
            }
            if ("short".equals(tn) || "char".equals(tn) || "int".equals(tn) || "long".equals(tn)) {
                return readVarLong(p);
            }
            if ("float".equals(tn)) { p[0] += 4; return null; }
            if ("double".equals(tn)) { p[0] += 8; return null; }
            // inline struct: read its fields recursively
            if (t != null) {
                for (FieldDef sub : t.fields) {
                    readField(p, sub);
                }
            }
            return null;
        }

        // ── metadata parsing ──
        private void parseMetadata() {
            long[] p = {base + metaOffset};
            readVarLong(p); // size
            readVarLong(p); // typeId (Metadata event)
            readVarLong(p); // start
            readVarLong(p); // duration
            readVarLong(p); // metadataId
            long stringCount = readVarLong(p);
            String[] pool = new String[(int) stringCount];
            for (int i = 0; i < stringCount; i++) {
                pool[i] = readString(p);
            }
            // root element
            Element root = readElement(p, pool);
            // walk to find <class> elements
            collectClasses(root);
            for (ClassDef cd : classes.values()) {
                switch (cd.name) {
                    case "jdk.types.Method": methodTypeId = cd.id; break;
                    case "jdk.types.Symbol": symbolTypeId = cd.id; break;
                    case "java.lang.Class": classTypeId = cd.id; break;
                    case "java.lang.String": stringTypeId = cd.id; break;
                    default: break;
                }
            }
        }

        private void collectClasses(Element el) {
            if ("class".equals(el.name)) {
                String name = el.attrs.get("name");
                String idStr = el.attrs.get("id");
                if (name != null && idStr != null) {
                    ClassDef cd = new ClassDef();
                    cd.id = Long.parseLong(idStr);
                    cd.name = name;
                    for (Element child : el.children) {
                        if ("field".equals(child.name)) {
                            FieldDef fd = new FieldDef();
                            fd.name = child.attrs.get("name");
                            fd.typeId = Long.parseLong(child.attrs.get("class"));
                            String cp = child.attrs.get("constantPool");
                            fd.constantPool = "true".equals(cp);
                            String dim = child.attrs.get("dimension");
                            fd.dimension = dim != null ? Integer.parseInt(dim) : 0;
                            cd.fields.add(fd);
                        }
                    }
                    classes.put(cd.id, cd);
                }
            }
            for (Element child : el.children) {
                collectClasses(child);
            }
        }

        private Element readElement(long[] p, String[] pool) {
            Element el = new Element();
            long nameIdx = readVarLong(p);
            el.name = pool[(int) nameIdx];
            long attrCount = readVarLong(p);
            for (long i = 0; i < attrCount; i++) {
                long k = readVarLong(p);
                long v = readVarLong(p);
                el.attrs.put(pool[(int) k], pool[(int) v]);
            }
            long childCount = readVarLong(p);
            for (long i = 0; i < childCount; i++) {
                el.children.add(readElement(p, pool));
            }
            return el;
        }

        // ── low-level readers ──
        private long beLong(long off) {
            long v = 0;
            for (int i = 0; i < 8; i++) {
                v = (v << 8) | (f[(int) off + i] & 0xffL);
            }
            return v;
        }

        private long readVarLong(long[] p) {
            long result = 0;
            int shift = 0;
            int i = (int) p[0];
            for (int b = 0; b < 9; b++) {
                int by = f[i++] & 0xff;
                if (b == 8) {
                    result |= ((long) by) << shift;
                    p[0] = i;
                    return result;
                }
                result |= ((long) (by & 0x7f)) << shift;
                if ((by & 0x80) == 0) {
                    p[0] = i;
                    return result;
                }
                shift += 7;
            }
            p[0] = i;
            return result;
        }

        private String readString(long[] p) {
            int i = (int) p[0];
            int enc = f[i++] & 0xff;
            p[0] = i;
            switch (enc) {
                case 0: return null;          // null
                case 1: return "";            // empty
                case 3: {                     // UTF-8
                    long len = readVarLong(p);
                    String s = new String(f, (int) p[0], (int) len, java.nio.charset.StandardCharsets.UTF_8);
                    p[0] += len;
                    return s;
                }
                case 4: {                     // char array
                    long len = readVarLong(p);
                    StringBuilder sb = new StringBuilder((int) len);
                    for (long c = 0; c < len; c++) {
                        sb.append((char) readVarLong(p));
                    }
                    return sb.toString();
                }
                case 5: {                     // latin1
                    long len = readVarLong(p);
                    String s = new String(f, (int) p[0], (int) len, java.nio.charset.StandardCharsets.ISO_8859_1);
                    p[0] += len;
                    return s;
                }
                default:
                    throw new IllegalStateException("Unknown JFR string encoding " + enc);
            }
        }
    }

    private static final class ClassDef {
        long id;
        String name;
        final List<FieldDef> fields = new ArrayList<>();
    }

    private static final class FieldDef {
        String name;
        long typeId;
        boolean constantPool;
        int dimension;
    }

    private static final class Element {
        String name;
        final Map<String, String> attrs = new HashMap<>();
        final List<Element> children = new ArrayList<>();
    }
}
