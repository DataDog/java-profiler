# logs-backend Crash Simulation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Reproduce, inside java-profiler's own test suite, the confirmed profiler memory-safety bug that crashes logs-backend services (Java 25, thread-churn × recording-dump), so we can find the root cause and guard against regressions.

**Architecture:** Two layers. **Layer 1** is a no-JVM gtest concurrency stress (`stress_threadLifecycle_ut.cpp`) that drives the profiler's own thread-lifecycle + dump data structures under ASan/TSan to surface the UAF/race at its origin. **Layer 2** adds a `DumpStormAntagonist` and a **Java 25** cell to the existing black-box chaos/reliability suite (JVM-safe detectors only: `gmalloc` + crash-on-signal).

**Tech Stack:** C++17, GoogleTest (`com.datadoghq.gtest` Gradle plugin, auto-discovers `src/test/cpp/*.cpp`), ASan/TSan via `buildGtestAsan`/`buildGtestTsan`; Java chaos harness (`ddprof-stresstest`), GitLab CI (`.gitlab/reliability`, `.gitlab/sanitizer-tests`), SDKMAN.

**Spec:** `doc/plans/2026-05-29-logs-backend-crash-simulation-design.md`

**Branch:** Work on `prof-logs-backend-crash-sim` (do not commit to `main`).

**Execution environment (IMPORTANT — overrides the bare `./gradlew` lines below):**
This host is macOS/arm64; the test is `#ifdef __linux__` and the sanitizers are Linux-only.
ALL build/run steps execute via the repo's Docker runner on **JDK 25**, which gives faithful
Linux ASan/TSan:
- Debug build + gtests: `./utils/run-containers-tests.sh --config=debug --gtest --jdk=25 --mount`
- ASan: `./utils/run-containers-tests.sh --config=asan --gtest --jdk=25 --mount`
- TSan: `./utils/run-containers-tests.sh --config=tsan --gtest --jdk=25 --mount`
- Interactive iteration: add `--shell` to drop into the container and run the built
  `*_stress_threadLifecycle_ut*` binary directly with `--gtest_filter=StressThreadLifecycle.*`.

The `./gradlew :ddprof-lib:buildGtest*` commands in the tasks are the *in-container* equivalents;
run them through the Docker wrapper above, not directly on the host.

**Commit policy:** Per project rule, do NOT `git commit` during execution. Author + verify, then
leave changes in the working tree for the user to review and commit. The `git commit` steps in
the tasks are deferred until the user approves.

---

## File Structure

| File | Status | Responsibility |
|---|---|---|
| `ddprof-lib/src/test/cpp/stress_threadLifecycle_ut.cpp` | Create | Layer-1 concurrency reproducer: churn workers (ProfiledThread + ThreadFilter) vs. dump thread (CallTraceStorage + Dictionary), under ASan/TSan. |
| `ddprof-stresstest/src/chaos/java/com/datadoghq/profiler/chaos/DumpStormAntagonist.java` | Create | Layer-2 antagonist: forces frequent recording rotation/dump concurrently with churn. |
| `ddprof-stresstest/src/chaos/java/com/datadoghq/profiler/chaos/Main.java` | Modify | Register `dump-storm` antagonist in `create()`. |
| `.gitlab/reliability/chaos_check.sh` | Modify | Add a Java 25 install/cell alongside the existing `21.0.3-tem`. |
| `.gitlab/reliability/.gitlab-ci.yml` | Modify | Add `JDK` dimension (21, 25) to the chaos matrix; include `dump-storm` in the antagonist set. |

**Reference neighbors (read before coding):** `thread_teardown_safety_ut.cpp` (ProfiledThread lifecycle idioms, sigaction guards, PROF-14603), `threadFilter_ut.cpp` (ThreadFilter construction/`init`), `test_callTraceStorage.cpp` + `stress_callTraceStorage.cpp` (CallTraceStorage `put`/`processTraces`/`clear`, `ASGCT_CallFrame`, `gtest_crash_handler.h`), `dictionary_ut.cpp` (Dictionary `lookup`/`clear`).

**Note on test nature:** This is a *characterization/reproduction* harness, not classic TDD. Success criterion for Phase 1 is: the harness runs **clean when the code is correct**, and we run it under ASan/TSan on current `main` to see whether it surfaces the corruption. If it stays clean on `main`, that is itself a result — it narrows the root cause to a path that requires real JVMTI/JVM state (→ Layer 2).

---

## Phase 1 — Layer 1: gtest concurrency reproducer

### Task 1: Scaffold the stress test file (compiles, runs, passes)

**Files:**
- Create: `ddprof-lib/src/test/cpp/stress_threadLifecycle_ut.cpp`

- [ ] **Step 1: Create the file with includes, crash-handler hook, and one trivial test**

```cpp
/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Layer-1 reproducer for the logs-backend crash (Java 25, thread-churn ×
 * recording-dump). Drives the profiler's own thread-lifecycle and dump data
 * structures concurrently, with NO JVM in the process, so ASan/TSan can flag
 * the use-after-free / race at its origin.
 *
 * See doc/plans/2026-05-29-logs-backend-crash-simulation-design.md
 */
#include "gtest/gtest.h"

#ifdef __linux__

#include "callTraceStorage.h"
#include "callTraceHashTable.h"
#include "dictionary.h"
#include "threadFilter.h"
#include "thread.h"
#include "arch.h"

#include <atomic>
#include <thread>
#include <vector>
#include <cstring>
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr const char STRESS_TEST_NAME[] = "StressThreadLifecycle";

TEST(StressThreadLifecycle, Smoke) {
  // Sanity: structures construct and tear down without a JVM.
  CallTraceStorage storage;
  Dictionary dict;
  EXPECT_EQ(0u, dict.lookup("smoke") == 0u ? 0u : 0u); // lookup is callable
  storage.clear();
  SUCCEED();
}

#endif // __linux__
```

- [ ] **Step 2: Build under the normal (non-sanitizer) gtest config**

Run: `./gradlew :ddprof-lib:buildGtestDebug --no-daemon`
Expected: BUILD SUCCESSFUL; a binary matching `stress_threadLifecycle_ut` appears under `ddprof-lib/build/bin/gtest/`.

- [ ] **Step 3: Run the smoke test**

Run: `find ddprof-lib/build/bin/gtest -name '*stress_threadLifecycle_ut*' -type f -executable -exec {} \;`
Expected: `[  PASSED  ] 1 test.`

- [ ] **Step 4: Commit**

```bash
git add ddprof-lib/src/test/cpp/stress_threadLifecycle_ut.cpp
git commit -m "test: scaffold thread-lifecycle stress reproducer"
```

---

### Task 2: Churn workers modelling onThreadStart / onThreadEnd

Models `Profiler::onThreadStart`/`onThreadEnd`: each worker initialises its `ProfiledThread`, registers a filter slot, does work, then unregisters and releases — the exact sequence in `profiler.cpp:75-130`.

**Files:**
- Modify: `ddprof-lib/src/test/cpp/stress_threadLifecycle_ut.cpp`

- [ ] **Step 1: Add the churn-worker test (verify ThreadFilter ctor/init against `threadFilter_ut.cpp` first)**

```cpp
// Shared filter, mirroring Profiler::_thread_filter (one instance, many threads).
static ThreadFilter g_filter;
static std::atomic<bool> g_run{false};

static void churn_worker() {
  while (!g_run.load(std::memory_order_acquire)) { /* spin until start */ }
  for (int i = 0; i < 2000 && g_run.load(std::memory_order_relaxed); i++) {
    // onThreadStart sequence
    ProfiledThread::initCurrentThread();
    ProfiledThread* self = ProfiledThread::current();
    ASSERT_NE(nullptr, self);
    ThreadFilter::SlotID slot = g_filter.registerThread();
    self->setFilterSlotId(slot);
    g_filter.add(self->tid(), slot);

    // minimal "work" so the thread is live across a scheduling quantum
    std::this_thread::yield();

    // onThreadEnd sequence
    g_filter.remove(slot);
    g_filter.unregisterThread(slot);
    self->setFilterSlotId(-1);
    ProfiledThread::release();
  }
}

TEST(StressThreadLifecycle, ChurnOnly) {
  g_filter.init("*");           // enable filtering; confirm arg form via threadFilter_ut.cpp
  ASSERT_TRUE(g_filter.enabled());
  g_run.store(true, std::memory_order_release);

  std::vector<std::thread> ts;
  for (int t = 0; t < 16; t++) ts.emplace_back(churn_worker);
  for (auto& t : ts) t.join();

  g_run.store(false);
  SUCCEED();
}
```

- [ ] **Step 2: Build and run (Debug)**

Run: `./gradlew :ddprof-lib:buildGtestDebug --no-daemon && find ddprof-lib/build/bin/gtest -name '*stress_threadLifecycle_ut*' -type f -executable -exec {} --gtest_filter=StressThreadLifecycle.ChurnOnly \;`
Expected: `[  PASSED  ]`. If it crashes, capture the stack — that may already be the bug.

- [ ] **Step 3: Commit**

```bash
git add ddprof-lib/src/test/cpp/stress_threadLifecycle_ut.cpp
git commit -m "test: add thread-churn worker to lifecycle stress"
```

---

### Task 3: Concurrent dump thread (CallTraceStorage + Dictionary)

Models `Profiler::dump`: while workers churn, a dump thread repeatedly walks call traces and clears the dictionary — `CallTraceStorage::processTraces` + `Dictionary::clear` from the design's Family-2 B.

**Files:**
- Modify: `ddprof-lib/src/test/cpp/stress_threadLifecycle_ut.cpp`

- [ ] **Step 1: Add a shared storage + dump thread, and have workers `put()` traces (mirror `put()` usage in `test_callTraceStorage.cpp`)**

```cpp
static CallTraceStorage g_storage;
static Dictionary g_dict;

// Build a small fake stack and record it (signal-handler-style put()).
static void record_trace(int salt) {
  ASGCT_CallFrame frames[4];
  std::memset(frames, 0, sizeof(frames));
  for (int i = 0; i < 4; i++) {
    frames[i].bci = i + salt;
    frames[i].method_id = reinterpret_cast<jmethodID>(static_cast<intptr_t>(0x1000 + i + salt));
  }
  g_storage.put(4, frames, false, 1);
  g_dict.lookup("logs-backend-sim");
}

static void dump_thread() {
  while (g_run.load(std::memory_order_relaxed)) {
    g_storage.processTraces([](const std::unordered_set<CallTrace*>& traces) {
      volatile size_t n = 0;
      for (CallTrace* t : traces) if (t) n += 1; // touch each, like writeStackTraces
      (void)n;
    });
    g_dict.clear();      // models Dictionary::clear() during Profiler::dump
    g_storage.clear();   // models chunk rotation
  }
}
```

Then, inside `churn_worker`'s loop, add `record_trace(i)` right after `g_filter.add(...)`.

- [ ] **Step 2: Add the combined test that runs churn + dump together**

```cpp
TEST(StressThreadLifecycle, ChurnDuringDump) {
  g_filter.init("*");
  ASSERT_TRUE(g_filter.enabled());
  g_run.store(true, std::memory_order_release);

  std::thread dumper(dump_thread);
  std::vector<std::thread> ts;
  for (int t = 0; t < 16; t++) ts.emplace_back(churn_worker);
  for (auto& t : ts) t.join();

  g_run.store(false);
  dumper.join();
  SUCCEED();
}
```

- [ ] **Step 3: Build and run (Debug)**

Run: `./gradlew :ddprof-lib:buildGtestDebug --no-daemon && find ddprof-lib/build/bin/gtest -name '*stress_threadLifecycle_ut*' -type f -executable -exec {} --gtest_filter=StressThreadLifecycle.ChurnDuringDump \;`
Expected: `[  PASSED  ]` in a correct build (or a crash that reproduces the bug).

- [ ] **Step 4: Commit**

```bash
git add ddprof-lib/src/test/cpp/stress_threadLifecycle_ut.cpp
git commit -m "test: drive concurrent dump against thread churn"
```

---

### Task 4: Run under AddressSanitizer on `main` (the reproduction experiment)

**Files:** none (investigation step — record findings).

- [ ] **Step 1: Build the ASan gtest binaries**

Run: `./gradlew :ddprof-lib:buildGtestAsan --no-daemon --parallel`
Expected: BUILD SUCCESSFUL.

- [ ] **Step 2: Run the new test under ASan, many iterations**

Run:
```bash
bin=$(find ddprof-lib/build/bin/gtest -type f -executable -name 'asan_*stress_threadLifecycle_ut*')
for i in $(seq 1 50); do "$bin" --gtest_filter='StressThreadLifecycle.*' || { echo "ASAN HIT on iter $i"; break; }; done
```
Expected outcome is one of:
- ASan reports `heap-use-after-free` / `heap-buffer-overflow` with a profiler stack → **bug reproduced**; record the report verbatim (this is the root-cause pointer).
- All 50 iterations PASS → record "ASan clean at unit level"; proceed to TSan (Task 5).

- [ ] **Step 3: Record findings**

Append the ASan output (or "clean") to the design doc under a new "## 8. Reproduction results" section.

```bash
git add doc/plans/2026-05-29-logs-backend-crash-simulation-design.md
git commit -m "docs: record ASan reproduction results"
```

---

### Task 5: Run under ThreadSanitizer on `main`

**Files:** none (investigation step).

- [ ] **Step 1: Build the TSan gtest binaries**

Run: `./gradlew :ddprof-lib:buildGtestTsan --no-daemon --parallel`
Expected: BUILD SUCCESSFUL. (TSan must run on a non-Kata runner — locally is fine; in CI it uses the `docker-in-docker:amd64`→EC2 path per `.gitlab/sanitizer-tests/.gitlab-ci.yml`.)

- [ ] **Step 2: Run the new test under TSan**

Run:
```bash
bin=$(find ddprof-lib/build/bin/gtest -type f -executable -name 'tsan_*stress_threadLifecycle_ut*')
GTEST_DEATH_TEST_STYLE=threadsafe "$bin" --gtest_filter='StressThreadLifecycle.*'
```
Expected: either a `data race` report naming a profiler structure (record it) or clean.

- [ ] **Step 3: Record findings and commit (as in Task 4 Step 3).**

```bash
git add doc/plans/2026-05-29-logs-backend-crash-simulation-design.md
git commit -m "docs: record TSan reproduction results"
```

---

## Phase 2 — Layer 2: chaos antagonist + Java 25

### Task 6: `DumpStormAntagonist`

Forces frequent recording rotation/dump concurrently with churn. The harness is black-box (patched `dd-java-agent`), so it cannot call `dump0` directly; it drives dumps by keeping the profiler busy and relying on the agent's short recording interval (configured in Task 8). This antagonist supplies the *concurrent churn-with-allocation* pressure that makes each rotation race thread teardown.

**Files:**
- Create: `ddprof-stresstest/src/chaos/java/com/datadoghq/profiler/chaos/DumpStormAntagonist.java`

- [ ] **Step 1: Create the antagonist (mirror `ThreadChurnAntagonist` structure exactly)**

```java
/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
package com.datadoghq.profiler.chaos;

import java.time.Duration;
import java.util.ArrayList;
import java.util.List;

/**
 * Spawns short-lived, frequently-renamed threads that each generate distinct
 * stack shapes, maximising churn in the profiler's thread-name table and call-
 * trace storage right as recording chunks rotate.
 *
 * <p>Targets the dump path observed in production crashes:
 * {@code Recording::switchChunk/writeCpool}, {@code updateJavaThreadNames ->
 * ThreadInfo::set}, {@code Dictionary::clear}. Pair with a short profiler
 * recording interval (see chaos_check.sh) so dumps fire continuously.
 */
public final class DumpStormAntagonist implements Antagonist {

    private final int concurrentThreads;
    private volatile boolean running;
    private Thread driver;

    public DumpStormAntagonist() {
        this(96);
    }

    public DumpStormAntagonist(int concurrentThreads) {
        this.concurrentThreads = concurrentThreads;
    }

    @Override
    public String name() {
        return "dump-storm";
    }

    @Override
    public void start() {
        running = true;
        driver = new Thread(this::loop, "chaos-dump-storm");
        driver.setDaemon(true);
        driver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        try {
            if (driver != null) driver.join(timeout.toMillis());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void loop() {
        long seq = 0;
        while (running) {
            List<Thread> batch = new ArrayList<>(concurrentThreads);
            for (int i = 0; i < concurrentThreads && running; i++) {
                final long id = seq++;
                Thread t = new Thread(() -> distinctStack(id, 0));
                // Frequent renames hammer updateThreadName/ThreadInfo::set.
                t.setName("dump-storm-" + id);
                t.setDaemon(true);
                t.start();
                batch.add(t);
            }
            for (Thread t : batch) {
                try {
                    t.join(500L);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
        }
    }

    // Recurse to a per-thread depth so each thread yields a unique stack shape,
    // forcing new call-trace + symbol entries that the dump path must serialise.
    private long distinctStack(long id, int depth) {
        if (depth >= (int) (id % 32)) {
            long r = id;
            for (int i = 0; i < 5000; i++) r = (r * 1103515245L + 12345L) & 0x7fffffffL;
            return r;
        }
        return distinctStack(id, depth + 1) + depth;
    }
}
```

- [ ] **Step 2: Compile the stresstest module**

Run: `./gradlew :ddprof-stresstest:compileChaosJava --no-daemon` (confirm the source-set task name via `./gradlew :ddprof-stresstest:tasks --all | grep -i chaos`)
Expected: BUILD SUCCESSFUL.

- [ ] **Step 3: Commit**

```bash
git add ddprof-stresstest/src/chaos/java/com/datadoghq/profiler/chaos/DumpStormAntagonist.java
git commit -m "test: add dump-storm chaos antagonist"
```

---

### Task 7: Register the antagonist

**Files:**
- Modify: `ddprof-stresstest/src/chaos/java/com/datadoghq/profiler/chaos/Main.java`

- [ ] **Step 1: Add the `dump-storm` case to `create()`** (after the `trace-context` case, before `default`):

```java
            case "dump-storm":
                return new DumpStormAntagonist();
```

- [ ] **Step 2: Compile**

Run: `./gradlew :ddprof-stresstest:compileChaosJava --no-daemon`
Expected: BUILD SUCCESSFUL.

- [ ] **Step 3: Smoke-run the harness briefly (no agent needed to prove wiring)**

Run: `./gradlew :ddprof-stresstest:run -PchaosArgs="--duration 5s --antagonists dump-storm" --no-daemon` (adapt to the module's actual run task; otherwise run the built class directly with `--duration 5s --antagonists dump-storm`).
Expected: logs `antagonist started: dump-storm` then `completed cleanly`.

- [ ] **Step 4: Commit**

```bash
git add ddprof-stresstest/src/chaos/java/com/datadoghq/profiler/chaos/Main.java
git commit -m "test: register dump-storm antagonist"
```

---

### Task 8: Add Java 25 + dump-storm to the chaos CI matrix

**Files:**
- Modify: `.gitlab/reliability/chaos_check.sh`
- Modify: `.gitlab/reliability/.gitlab-ci.yml`

- [ ] **Step 1: Parameterise the JDK in `chaos_check.sh`**

Replace the hardcoded install (`.gitlab/reliability/chaos_check.sh:16`):
```bash
timeout 300 sdk install java 21.0.3-tem 1>/dev/null 2>/dev/null
```
with a parameterised version + a short recording interval so dumps fire continuously:
```bash
JDK_CANDIDATE="${CHAOS_JDK:-21.0.3-tem}"
timeout 300 sdk install java "${JDK_CANDIDATE}" 1>/dev/null 2>/dev/null
sdk use java "${JDK_CANDIDATE}"
# Force frequent recording rotation so the dump path is exercised under churn.
export DD_PROFILING_UPLOAD_PERIOD=5
```
(Validate the exact env var name against the dd-java-agent build used by the harness; the intent is "shortest safe upload/recording period".)

- [ ] **Step 2: Validate YAML/script edits**

Run: `bash -n .gitlab/reliability/chaos_check.sh && python3 -c "import yaml,sys; yaml.safe_load(open('.gitlab/reliability/.gitlab-ci.yml')); print('yaml ok')"`
Expected: no syntax errors; `yaml ok`.

- [ ] **Step 3: Add a `CHAOS_JDK` dimension and `dump-storm` to the chaos matrix in `.gitlab/reliability/.gitlab-ci.yml`**

In `.reliability_chaos_job.parallel.matrix`, add the JDK dimension (keep 21 as control):
```yaml
  parallel:
    matrix:
      - CONFIG: ["profiler", "profiler+tracer"]
        ALLOCATOR: ["gmalloc", "jemalloc", "tcmalloc"]
        CHAOS_JDK: ["21.0.3-tem", "25.0.3-tem"]
```
And ensure the run invocation passes the dump-storm antagonist (in `chaos_check.sh`'s harness call, set the antagonist list to include `thread-churn,vthread-churn,dump-storm`). Confirm `25.0.3-tem` (or the closest available 25.x) is a valid SDKMAN candidate; if not, pin the available 25 build.

- [ ] **Step 4: Re-validate YAML**

Run: `python3 -c "import yaml; yaml.safe_load(open('.gitlab/reliability/.gitlab-ci.yml')); print('yaml ok')"`
Expected: `yaml ok`.

- [ ] **Step 5: Commit**

```bash
git add .gitlab/reliability/chaos_check.sh .gitlab/reliability/.gitlab-ci.yml
git commit -m "ci: run chaos suite on Java 25 with dump-storm antagonist"
```

---

## Self-Review notes

- **Spec coverage:** §4.1 Layer 1 → Tasks 1-5; §4.2 Layer 2 `DumpStormAntagonist` → Tasks 6-7, Java 25 matrix → Task 8; §3 gaps (JDK 21, no dump stress, sanitizers gtest-only) all addressed. §6 validation (ASan/TSan on main) → Tasks 4-5.
- **Known unknowns flagged inline (not placeholders):** exact `ThreadFilter::init` arg form (verify vs `threadFilter_ut.cpp`), the chaos module's run/compile task names, the dd-java-agent recording-period env var, and SDKMAN's 25.x candidate string. Each step says what to confirm and against what.
- **Type consistency:** `g_filter`/`g_storage`/`g_dict`/`g_run` used consistently across Tasks 2-3; antagonist `name()` returns `"dump-storm"` matching the `create()` case and the CI antagonist list.
