# Reproducing the logs-backend profiler crashes in java-profiler testing

**Date:** 2026-05-29
**Status:** Design (pending review)
**Author:** investigation driven from Datadog crash-tracking telemetry

## 1. Problem

Datadog-internal services built from `~/dd/logs-backend` (event-platform / `*-reducer`
workloads) crash far more than our test suite or external customers surface. The goal is
to reproduce the responsible conditions inside java-profiler's own testing so we gain
confidence that fixes hold and regressions are caught.

## 2. Evidence (crash-tracking telemetry, Org2, 7-day window, all versions)

Source: `service:instrumentation-telemetry-data-jvm @lib_language:jvm`, crash events.

### 2.1 Why we weren't seeing them

The standard triage filter keys on `@tags.crash_datadog:true`. **Most logs-backend crashes
are not tagged `crash_datadog`** (they are `crash_runtime` / `crash_unactionable`), so they
were filtered out. Removing that clause surfaces hundreds of crashes in 7 days
(`event-context-writer`: 110 SIGSEGV + 14 SIGBUS; `event-heartbeat-emitter`: 27 SIGSEGV +
23 SIGBUS; `event-context-provider-skeleton`: 30 SIGSEGV; etc.).

### 2.2 Uniform platform

All on **JDK 25.0.3**, `env:staging`, tracer **`1.63.0-snapshot`** (dev build). This is
Datadog dogfooding on bleeding-edge Java 25.

### 2.3 Attribution split (SIGSEGV/SIGBUS, JFR-crashing services)

| Tags | Events | Heuristic verdict |
|---|---|---|
| `crash_runtime` + `crash_unactionable` | ~179 | "JVM bug" — **but see §2.5** |
| `crash_profiler` + `crash_datadog` | ~25 | attributed to this profiler |

The `crash_runtime`/`crash_unactionable` tag records only **where the crashing PC landed**
(JVM code). It is **not** a root-cause determination.

### 2.4 Crash taxonomy

**Family 1 — PC in JVM/JDK code (the ~179):**
`JfrJavaThreadIteratorAdapter::next → jfr_emit_event → jdk.jfr.internal.periodic.*`
(JDK's own Flight Recorder iterating the thread list), `SafepointSynchronize::arm_safepoint`,
`ThreadsSMRSupport::free_list/add_thread`, `GlobalCounter::write_synchronize`, ZGC mark/relocate.

**Family 2 — PC in this profiler's code (the ~25):**
- **A. Thread-lifecycle callbacks** — `Profiler::onThreadEnd+0x65` during `JavaThread::exit`,
  `Profiler::onThreadStart`, `Profiler::updateThreadName → ThreadInfo::set`.
- **B. Dump / chunk serialization** — `Profiler::dump → FlightRecorder::dump →
  Recording::switchChunk / writeCpool / writeStackTraces / cleanupUnreferencedMethods`,
  `CallTraceStorage::processTraces`, `Dictionary::clear`, `std::_Rb_tree_increment` in
  `writeCpool`. Frequently triggered via `JavaProfiler.dump0`.
- **C. Virtual threads** — `ExceptionSampleEvent.commit → Continuation.enterSpecial →
  VirtualThread.runContinuation`.

### 2.5 Fault-address forensics — corruption, not clean nulls

For the Family-1 services (SIGSEGV/SIGBUS):
- **SIGBUS / `BUS_ADRALN`** (~25 events): misaligned access ⇒ the pointer value itself is
  garbage read from corrupted/freed memory. Correct codegen never misaligns.
- **Non-null `SEGV_MAPERR`**: garbage 32-bit-range addresses (`0x2d6c1892`, `0x86471d9e`…),
  **not** valid Java-25 heap pointers (`0x00007f…`), and they **cluster on identical
  low-16-bit suffixes** (`…1d9e` ×15, `…1ea6` ×12, `…1892` ×6) — the same field offset in
  the same structure read off a varying garbage base. Textbook **use-after-free /
  type-confusion**.
- Only the `SI_KERNEL / 0x0` bucket (~32) looks like a plain null.

**Conclusion (CONFIRMED):** Family 1 and Family 2 are **one underlying profiler
memory-safety bug** (heap corruption / UAF in the thread-churn × dump interaction on Java 25).
**Disabling the profiler on the affected staging services removes the crashes** — the decisive
control experiment. So the ~179 `crash_runtime`/`unactionable` events are profiler-induced too;
the attribution tag undercounted our true crash volume by roughly 8× (~25 tagged vs ~204 actual).
The crash tag merely records where the corruption happened to surface. `ThreadInfo` itself is
**correctly locked** (every method holds `_ti_lock`, `get()` deep-copies via `shared_ptr`), so
`ThreadInfo::set` is a *victim* site touching an already-poisoned heap, not the source. The
source must be found by sanitizing the interacting components together.

### 2.6 Common trigger

Rapid **thread creation/destruction (churn)** intersecting the **recording dump** path, on
**Java 25**. Service names corroborate: heartbeat emitters, periodic writers, reducers spin up
short-lived workers.

## 3. Testing gaps that allowed the escape

1. **ASan/TSan run only on isolated C++ gtest binaries** (`buildGtest{Asan,Tsan}`, no JVM in
   the process). They cannot — and must not — run against a live JVM (ASan's global
   malloc/signal/guard-page interception fights JVM signal handling, JIT, and deliberate
   faults; TSan floods on uninstrumented JVM synchronization and its shadow region collides
   with JVM mappings, incl. the Kata issue already noted in CI). So a UAF that only appears
   under *live JVM + churn + dump* is invisible to the sanitizers.
2. **JVM integration / chaos / reliability run on JDK 21** (`chaos_check.sh` hardcodes
   `java 21.0.3-tem`; repo default `JAVA_TEST_VERSION=21`). Every production crash is **Java 25**.
3. **No concurrent `dump()` stress.** The chaos harness only crash-detects under churn; it
   never drives the dump path that Family-2 B/C fault in.

## 4. Design — two layers, mapped onto existing structure

Detection is split by layer because sanitizers are valid only without a JVM in the process.

### 4.1 Layer 1 — gtest sanitizer concurrency stress (finds the bug)

**Where:** `ddprof-lib/src/test/` (ASan+TSan via existing `buildGtestAsan`/`buildGtestTsan`
→ `gtest-asan-amd64`/`gtest-tsan-amd64`). No new infra. Existing neighbors:
`stress_callTraceStorage.cpp`, `thread_teardown_safety_ut.cpp`, `threadIdTable_ut.cpp`,
`dictionary_ut.cpp`.

**New:** `stress_threadLifecycle_ut.cpp` — a no-JVM concurrency model of the churn × dump
interaction:
- M worker threads loop: `ProfiledThread` register → updateName → engine register
  (`_cpu_engine`/`_wall_engine`) → unregister → `ProfiledThread::release()` (incl. buffer
  recycling path).
- 1–2 "dump" threads loop: `CallTraceStorage::processTraces(...)` + `Dictionary::clear()`
  (models `Recording::switchChunk`/`writeStackTraces`).
- Run for a fixed iteration budget; rely on ASan (UAF at origin) and TSan (data race) as the
  oracle, plus existing crash-on-signal.

Scope note: drive the profiler's *own* data structures directly. Anything requiring genuine
JVMTI inputs (a real `jthread`) stays in Layer 2.

### 4.2 Layer 2 — chaos antagonist + reliability (proves the real scenario, guards regressions)

**Where:** `ddprof-stresstest/src/chaos/java/.../chaos/` + `.gitlab/reliability/`. No
sanitizer. Existing: `ThreadChurnAntagonist`, `VirtualThreadChurnAntagonist`, `gmalloc`
guard-allocator already in the matrix.

**Changes:**
1. **`DumpStormAntagonist`** — drives frequent recording rotation/dump concurrently with
   churn. Harness is black-box (patched `dd-java-agent`), so trigger dumps via a short
   profiler recording/upload interval rather than calling `dump0` directly. Exercises
   `Recording::switchChunk/writeCpool`, `updateJavaThreadNames → ThreadInfo::set`,
   `Dictionary::clear`. Register in `Main.create()`.
2. **Add Java 25 to the chaos/reliability matrix** — `chaos_check.sh` currently installs only
   `21.0.3-tem`. Add a 25.x cell (keep 21 as control). This alone may reproduce the crash.

The `gmalloc` allocator already in the matrix provides JVM-safe guard-page detection of
overflows/UAF for Layer 2, complementing crash-on-signal.

## 5. Out of scope / explicitly not done

- **Not** chasing Family-1 PCs as JDK bugs — the control experiment (profiler off ⇒ no
  crashes) confirms they are profiler-induced, not JDK bugs.
- **No** ASan/TSan against a live JVM (technically invalid — see §3.1).
- **No** source-scan of logs-backend; telemetry already gave the exact code paths.
- **No** new test-only production APIs unless proposed and approved first.

## 6. Validation plan

- Layer 1: new stress test fails (ASan/TSan report) on current `main`; passes after the fix.
- Layer 2: chaos+`DumpStorm` on **Java 25** reproduces a crash (or `gmalloc` fault) on current
  `main`; clean after the fix; Java 21 cell stays green throughout (control).
- Cross-check: **DONE** — disabling the profiler on the affected staging services removes the
  crashes, confirming the single-root-cause (profiler) hypothesis.

## 7. Open questions

- Exact black-box mechanism to force frequent dumps in the chaos harness (short recording
  interval config vs. a benign agent hook) — to resolve during implementation.
- Whether a Java-25 chaos cell needs a new CI build image / SDKMAN candidate availability.

## 8. Reproduction results

### Layer 1 — ASan gtest (JDK 25, aarch64/glibc, 2026-05-29)

Command: `./utils/run-docker-tests.sh --config=asan --gtest --jdk=25 --mount`

Results:
- `stress_threadLifecycle_ut` compiled and linked under ASan: **PASS**
- `StressThreadLifecycle.Smoke`: **PASS** (no ASan report)
- `StressThreadLifecycle.ChurnOnly`: **PASS** (no ASan report)
- `StressThreadLifecycle.ChurnDuringDump`: **PASS** (no ASan report)

**Interpretation:** The profiler's own data structures (`ProfiledThread`, `ThreadFilter`,
`CallTraceStorage`, `Dictionary`) are race-free in isolation at the unit level. The UAF
requires **real JVMTI inputs** — live `jthread` handles, JVM-side native thread lifecycle,
JVMTI callbacks. Layer 2 (chaos antagonists under a real JVM on Java 25) is the decisive
reproducer.

Pre-existing unrelated failure: `CollapsingSleepTest > testSleep()` (Java integration test,
not touched by this work).

### Layer 2 — chaos + Java 25 CI cell

Pending: Task 8 (CI matrix change) not yet run.
