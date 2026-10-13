# Spec: keepbest-only-merges-the-incoming-scan-s

## Problem

This review round has nine change requests against the rc-6 reference-chain test and tooling
layer. They fall into seven clusters (see `.sphinx/address/design.md`):

1. `LeakTagCorrelationScenario.keepBest()` drops the gate violations collected so far whenever a
   later scan wins on payload quality. Separately, `run()` prints NOT_FOUND ahead of the violation
   markers, and the tight-window variant of `LeakTagCorrelationReferenceChainTest` accepts
   NOT_FOUND. Together these let a transient/noise gate regression pass.
2. `utils/run-refchains-repro.sh` expands possibly-empty arrays as `"${A[@]}"` under `set -u`.
   On bash 3.2 (macOS `/bin/bash`) that aborts with "unbound variable", although the script
   claims to support bash 3.2.
3. `ReferenceChainLeakDemo`: (a) the cache is seeded after `JavaProfiler.getInstance()`,
   which contradicts the load-bearing header comment that says seeding happens on the first
   line of `main`; (b) `heapUsedFraction()` reports 0.0 when the heap max is undefined, which
   turns off all throttling.
4. `ReferenceChainJfrParserTest` reads a fixture at a fixed shared path that nobody ever deletes,
   so a stale fixture from an older revision can satisfy the existence check.
5. `AggressiveLeakReferenceChainTest` evaluates the state-mutating seam `shouldRunPassForTest0()`
   inside `assertFalse`, against whatever search state an earlier class left behind.
6. `ReferenceChainTrackingTest` dumps to fixed-name JFR files in the CWD at four sites.
7. `.claude/commands/build-and-summarize` keeps the UNKNOWN artifact schema in two places. Its
   failure exit masks Gradle's status. Under `set -e`, a failed build aborts at `wait`, so the
   summary never runs at all.

## Correct behaviour

- **R1:** every transient-rooted (depth ≤ 1, rootKind starting `first_observed_via:`) or
  NoisePayload chain seen in any scanned dump ends up in the final result's
  `transientViolations`/`noiseChains`. This holds whichever dump's payload is kept and in
  whatever order the dumps arrive. Duplicate violation strings appear once.
- **R2:** the payload fields come from the winning scan only. The newer scan wins iff its quality
  is ≥ the current best's. Quality order: no chain < out-of-pool < in-pool < in-pool and
  correlated. A null scan keeps best, and a null best takes the scan. Early-break conditions are
  unchanged.
- **R3:** result precedence. No result at all → NOT_FOUND. Any transient violation →
  TRANSIENT_CHAIN_MARKER + list. Otherwise any noise chain → NOISE_CHAIN_MARKER + list. Otherwise
  no payload chain → NOT_FOUND. Otherwise out of pool → TAG_OUT_OF_POOL. Otherwise no live object →
  NO_LIVE_OBJECT. Otherwise FOUND + tag. Violations are reported even when no payload chain was
  ever found.
- **R4:** `run-refchains-repro.sh` launches on bash 3.2 with `set -u` when GC_JVM_OPTS and/or
  JAVA_LOG_OPTS are empty, adding no extra arguments. When they are non-empty, each element stays
  exactly one argument, with no globbing or splitting. The bash-3.2 commitment stays.
- **R5:** in `ReferenceChainLeakDemo.main`, cache construction and `seed(cache, 300)` are the
  first statements, ahead of argument validation, `getInstance()`, printing, and sleeping. The
  header comment states that order.
- **R6:** when `MemoryUsage.getMax() <= 0`, the denominator is `Runtime.maxMemory()` if it is a real
  bound (`> 0` and `!= Long.MAX_VALUE`). Otherwise the fraction reported is exactly `HIGH_WATERMARK`,
  which means throttled growth with no critical pause. An unknown limit never means unthrottled.
  When getMax() > 0 the behaviour is unchanged.
- **R7:** the roundtrip fixture is consume-once. The gtest unlinks it before any assertion can bail
  out. The Java test deletes it after loading, whether loading succeeds or throws. A missing
  fixture means the test skips. It is never validated stale. The path format and its
  TMPDIR//tmp resolution are unchanged on both sides. `.trunc` is untouched.
- **R8:** `shouldRunPassForTest0()` never appears inside an assertion expression. In the
  flat-floor control it runs right after `resetReferenceChainSearchForTest0()`, so it lands on a
  fresh tracker (`_search_started == false`). Its result goes into a local, and a comment notes
  that the call mutates state. The heap-floor ring seeding survives until the call: no
  `resetKlassPopulationForTest0()` runs between seeding and the call. Setup and the
  `restoreHeapFloorDefaults()` teardown order are unchanged.
- **R9:** every dump target in `ReferenceChainTrackingTest` comes from
  `Files.createTempFile(<stem>-, ".jfr")` followed immediately by `Files.deleteIfExists`. It is
  created before any resource that needs try/finally cleanup (no thread is started before it)
  and deleted in finally. `java.nio.file.Paths` is no longer imported.
- **R10:** `build-and-summarize` contains exactly one UNKNOWN md/json literal, in the shell
  function `write_unknown_summary`. Both UNKNOWN paths go through it: an unusable log, and a
  generator failure (exception, or python3 missing). The UNKNOWN JSON has the same keys, in the
  same order, as the success-path JSON. `$LOG` in the JSON is escaped for `\` and `"`.
- **R11:** the exit code is Gradle's status when Gradle failed. Otherwise it is the generator's
  rc when the generator failed, and 0 otherwise. A failed Gradle build reaches the summary step
  (`wait` no longer aborts under `set -e`). An unusable log leaves summary_rc at 0.

## Constraints

- Test/tooling-only change set. No production native or Java API change, and no new seams
  (`JavaProfilerApiSurfaceTest` seam list unchanged).
- Java 8 source level for ddprof-test and ddprof-stresstest: no `var`, no newer APIs.
- Shell must stay bash 3.2 compatible where the script already claims it (`run-refchains-repro.sh`).
  `build-and-summarize` must stay POSIX-sh-like bash with no bash-4-only features.
- Follow the local style: 2-space indent in ddprof-test, 4-space in ddprof-stresstest, and
  comments that explain the "why".
- Minimal edits. Do not touch `ThreadLocalLeakScenario`, `MemoryGovernor`, or other test classes
  outside the listed sites.

## Scope

### Primary fixes
- `ddprof-test/.../referencechains/LeakTagCorrelationScenario.java:392-406` (review line 322): one-directional merge loses violations. Make `keepBest` merge the loser's violations into the winner, and update three comments.
- `utils/run-refchains-repro.sh:151-153` (review line 148): empty-array expansion under `set -u` on bash 3.2. Use the `${A[@]+"${A[@]}"}` guard.
- `ddprof-stresstest/.../repro/ReferenceChainLeakDemo.java:74-78,104-111,146,165-166` (review line 57): code no longer matches the load-bearing ordering comment. Seed first in `main`, pass the cache into `run`.
- `ddprof-stresstest/.../repro/ReferenceChainLeakDemo.java:270-273` (review line 277): unknown max is read as empty heap. Fall back to Runtime.maxMemory, then HIGH_WATERMARK.
- `ddprof-test/.../referencechains/ReferenceChainJfrParserTest.java:62-86` (review line 55) plus `ddprof-lib/src/test/cpp/referenceChainJfrRoundtrip_ut.cpp:235-249,279`: stale shared fixture. Make it consume-once.
- `ddprof-test/.../referencechains/AggressiveLeakReferenceChainTest.java:165-167` (+ L33 javadoc): mutating seam evaluated inside an assertion. Reset the search right before the call, hoist it into a local, comment it.
- `ddprof-test/.../referencechains/ReferenceChainTrackingTest.java:304`: fixed-name CWD dump path. Use createTempFile, created at the start of the method.
- `.claude/commands/build-and-summarize:117-125,254-261` (review line 258): UNKNOWN schema duplicated. Use a single shell writer `write_unknown_summary`.
- `.claude/commands/build-and-summarize:262` (review line 265): exit masks Gradle status. Use `exit $(( status != 0 ? status : summary_rc ))`, add a final `exit "$status"`, and add companion C-1 (`wait` under `set -e`, L44-45). Without C-1 the status fix is dead code.

### Auto-expanded sibling fixes
- **S-1** `LeakTagCorrelationScenario.java:361-371`: gate violation hidden by marker precedence. NOT_FOUND is printed before the violation checks.
  FLOW: tight variant → child `run()` → no byte[] chain in any dump but ≥1 transient/noise chain → NOT_FOUND → `LeakTagCorrelationReferenceChainTest.java:189-200` escape hatch → pass.
  PRECONDITION: a gate regression where the payload is never resolved. REACHABLE: yes. CONCLUSION: MEDIUM, the same masking as the primary.
- **S-2** `ReferenceChainTrackingTest.java:487`: fixed-name CWD dump path (`referencechains-cache-leak-scratch.jfr`, named in the finding).
  FLOW: `shouldReconstructReferrerChainThroughUnboundedCacheLeak` → dump/verify loop on a CWD path. PRECONDITION: parallel workers or a shared checkout, or an aborted earlier run. REACHABLE: yes. CONCLUSION: LOW.
- **S-3** `ReferenceChainTrackingTest.java:690`: fixed-name CWD warmup dump (`referencechains-abandoned-test-warmup.jfr`).
  FLOW: `shouldReportAbandonedSearchOnTinyFrontierCap` debug branch → `dump(warmupDumpPath)`. PRECONDITION: as for S-2. REACHABLE: yes (debug). CONCLUSION: LOW.
- **S-4** `ReferenceChainTrackingTest.java:722`: fixed-name CWD dump (`referencechains-abandoned-test.jfr`) that `verifyEvents` reads.
  FLOW: the same test's retry loop → `verifyEvents(dumpPath, ...)`. PRECONDITION: as for S-2. REACHABLE: yes. CONCLUSION: LOW.

Considered and discarded: `ThreadLocalLeakScenario.keepBest` (no violation lists).
`MemoryGovernor.java:148,184` (outside the PR, and the cgroup signal covers the
undefined-heap-max case). `ContendedCallTraceStorageTest.java:70` and
`memleak/LivenessTrackingTest.java:71,107` (outside the PR, pre-existing; candidates for a
follow-up). Bash arrays in `sweep-refchains-*.sh` and `build-and-summarize` (never empty, or the
script is bash-4-only by construction).

## Assumptions
- Behaviour change accepted: a violation in an early dump now fails a run that later fully correlates, and the tight variant fails on violations-with-no-payload.
- `Runtime.maxMemory()` returns `Long.MAX_VALUE` when there is no limit.
- Consume-once leaves a narrow staleness window: an old-revision gtest wrote the file, nothing consumed it, and the gtest is then skipped. A per-build stamp would need build-logic changes and is out of scope.
- With several configs in one invocation, a later Java config may SKIP the parser test because an earlier config consumed the fixture. This is acceptable.
- R8 deliberately departs from the reviewer's "reset search/population" wording: the population reset would wipe the seeded heap-floor ring and make the control vacuous.
- No runtime evidence was gathered in planning. The bash idioms were checked on /bin/bash 3.2.57.
