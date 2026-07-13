# Phase 2 — migrate dd-trace-java onto the all-native context API

- **Date:** 2026-07-09
- **Status:** Plan (execution in progress)
- **Related:** PR #631 (phase 1, java-profiler), PROF-15271, PROF-15361 (follow-up: batch reapply),
  design note `2026-07-02-all-native-context-storage-design.md` (§5/§7)
- **Scope:** cross-repo — `java-profiler` (small read-API addition) and `dd-trace-java` (the migration)

## Goal

Switch dd-trace-java's profiler bridge off the deprecated DirectByteBuffer (DBB) context APIs onto
the all-native API added in phase 1 (`setTraceContext` / `clearTraceContext` / `setContextValue` /
`clearContextValue`). This is where the virtual-thread use-after-free fix and the per-activation
perf win land (3 JNI calls → 1 on activation). After this, no production code uses the DBB path.

## Consumption loop (verified)

- java-profiler is `com.datadoghq:ddprof:1.47.0-SNAPSHOT`; dd-trace-java pins `ddprof = "1.46.0"` and
  `-PddprofUseSnapshot=true` derives next-minor → `1.47.0-SNAPSHOT` (exact match). `mavenLocal()` is
  already first in dd-trace-java's repositories.
- Dev loop: java-profiler `./gradlew publishToMavenLocal`; dd-trace-java builds/tests with
  `-PddprofUseSnapshot=true`. dd-trace-java uses **dependency locking**, so a full build needs
  `--write-locks`.

## Decisions locked (this session)

1. **`setContextValue` publishes (`valid=1`).** Setting a value makes it visible even with no active
   span — app context is visible independent of spans (dd-trace-java PR #11646). `clearContextValue`
   preserves the prior valid (removing a value must not resurrect a deactivated record). Mirrors the
   DBB single-setter vs bulk-setter asymmetry the tracer's reapply was built on. (Done: `5beb6987c`.)
2. **`setTraceContext` rejects `spanId == 0`** (IllegalArgumentException, thin Java wrapper; native
   asserts). Clearing is `clearTraceContext`. Out-of-range slots throw; data conditions (null /
   oversized / Dictionary full) stay soft.
3. **Reapply stays per-slot (#1), no batch API.** A per-slot native `setContextValue` loop preserves
   the current shape and is adequate for typical app-attr cardinality (0–2). A native batch is
   deferred to PROF-15361 and only if measurement warrants (JNI accessors are VM transitions too, so
   a `byte[][]` batch would not clearly win; a flattened primitive-array batch would, but is premature).
4. **Design note §5 "wipe and let instrumentation re-set" is superseded** by #11646's reapply model;
   we preserve reapply-on-activation/deactivation.

## API mapping (old DBB → new all-native)

| dd-trace-java use (DBB) | replacement |
| --- | --- |
| `profiler.setContext(root,span,hi,lo)` + `setContextValue(op)` + `setContextValue(res)` | one `profiler.setTraceContext(root,span,hi,lo, opOff,opVal, resOff,resVal)` |
| `profiler.setContext(0,0,0,0)` (clear) | `profiler.clearTraceContext()` |
| `ContextSetter.setContextValue` / `clearContextValue` (→ DBB `setContextAttribute`) | `profiler.setContextValue(slot,v)` / `clearContextValue(slot)` (native) |
| `ContextSetter.setContextValuesByIdAndBytes` (batch reapply) | per-slot native `setContextValue` loop |
| `ContextSetter.snapshotTags` / `JavaProfiler.copyTags` (DBB read; resets via `ThreadContext` ctor) | new native `copyContextTags` read (option A) |
| `ContextSetter.offsetOf` | **kept** — pure-Java `attributes.indexOf`, no DBB |

## java-profiler change (option A — needed for the test oracle)

`snapshot()` in dd-trace-java (test-only per the consumer audit) reads tag encodings via
`copyTags` → `currentContext().copyCustoms` — a DBB read whose `ThreadContext` ctor **resets** the
record, clobbering native writes. Add a small **native** read instead:

- `JavaProfiler.copyContextTags(int[] out)` + `native copyContextTags0(int[])` — copies the current
  thread's `enc[]` sidecar tag encodings directly from `ProfiledThread::current()` (no `ThreadContext`,
  no reset). Test/introspection only. Add a java-profiler test.

## dd-trace-java edits (per file)

- `DatadogProfiler`:
  - add `setTraceContext(...)` / `clearTraceContext()` (each: native call + `reapplyAppContext()`).
  - `setContextValue(int,String)` / `clearContextValue(int)` → native `profiler.*`.
  - `reapplyAppContext()` → per-slot `profiler.setContextValue(i, snapshot.stringAt(i))` loop (drop the
    batch + valid=0 fallback; native `setContextValue` publishes uniformly).
  - `syncNativeAppContext()` → native `setContextValue`/`clearContextValue`.
  - `recordAppContextValue` → drop `snapshotTags`/`contextScratch` (no encoding capture); simplify
    `AppContextSnapshot` to strings-only (`nonZeroCount` by string presence; drop `ids`/`utf8`).
  - `snapshot()` → `profiler.copyContextTags(scratch)` (native read).
  - keep `ContextSetter` only for `offsetOf`.
- `DatadogProfilingIntegration`: activate → one `setTraceContext(...)` folding op+resource; close /
  `clearContext()` → `clearTraceContext()`.
- `DatadogProfilingScope`: unchanged in shape (save/restore app context); its writes now land native.

## Verification

- java-profiler: `publishToMavenLocal` (1.47.0-SNAPSHOT, incl. the new native read); its own tests green.
- dd-trace-java: `:dd-java-agent:agent-profiling:profiling-ddprof` build + `DatadogProfilerTest`,
  `DatadogProfilerConfigTest`, `DatadogProfilerRecordingTest` green with `-PddprofUseSnapshot=true`
  (`--write-locks` as needed). Smoke: `dd-smoke-tests/profiling-integration-tests`.

## Follow-ups

- PROF-15361: batch reapply (flattened primitive-array), only if reapply shows up in profiling.
- Phase 3 (java-profiler): remove the DBB / `ThreadContext` / `ContextSetter` / `OtelContextStorage`
  subsystem once dd-trace-java is on the new API. dd-trace-java then needs its own `offsetOf` map.
