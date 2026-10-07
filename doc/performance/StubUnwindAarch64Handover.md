# StubUnwindCpuTest on aarch64: investigation handover

Status as of 2026-10-07. Branch `investigate/stub-unwind-aarch64`, cut from
`main` at `3aa1d34d4`. This document is the only change on the branch; it is a
starting point for continuing the investigation on a native aarch64 machine.

## Summary

`StubUnwindCpuTest.testStubUnwinding` (`ddprof-test/.../cpu/StubUnwindCpuTest.java`)
has two separate problems on glibc aarch64 debug CI jobs. Both are present on
`main` and unrelated to any open PR:

1. **Real, intermittent unwind failures.** Samples contain
   `break_unwind_stub_failed`, which the test asserts must not happen on
   aarch64. `@RetryTest(10)` hides this: the test reports PASSED after one or
   more failed attempts.
2. **Pathologically slow attempts.** Sometimes one attempt of the fixed
   workload takes ~10 minutes instead of ~2 seconds, which pushed whole CI jobs
   into the 3h job timeout (cancelled) on several PRs.

## Evidence

All jobs below run on the same `arm-4core-linux` runner pool ("arm linux
shared"). Slow jobs are spread across JDKs and commits, interleaved in time
with fast ones.

| Run | Commit | aarch64 job | Duration | StubUnwindCpuTest |
|---|---|---|---|---|
| 37440354306 (`main`) | `3aa1d34d4` | 21-graal debug | 156 min | vm +81 min, vmx +57 min |
| 37440354306 (`main`) | `3aa1d34d4` | 17-graal debug | 14 min | attempt 1 failed, then passed |
| 37472164131 (PR #839) | `71c668aa2` | 17-graal, 21-graal, 17, 25 debug | cancelled at 180 min | vm ~65 min, vmx >100 min |
| 37472164131 (PR #839) | `71c668aa2` | 21 debug | 91 min | vm: attempts 1-3 failed, 4 passed |
| 37459854565 (PR #838) | `d8eeb61f2` | 17-graal debug | cancelled at 180 min | vm 73 min, vmx 96 min |
| 37482889888 (PR #840) | `ecb767b20` | all | ~14 min | fast |

Failure message of every failed attempt seen:

```
[Retrying] Attempt N/10 due to failure: unwinding produced an error frame:
StubScan{sawBreakFrame=true, breakFrame=.break_unwind_stub_failed(), sawWorkloadFrame=true,
sawItableStub=true, sawItableUnwound=true, sawIntrinsicStub=true, sawIntrinsicUnwound=true}
```

`stub info` counters printed by the passing attempt (`walkvm_stub_info_*`):

| Job | vm | vmx |
|---|---|---|
| `main` 17-graal (fast) | hit=1916 fallback=9 | hit=3200 fallback=7 |
| `main` 21-graal (slow) | hit=656979 fallback=677 | hit=6836081 fallback=1093 |
| PR #839 21 (slow) | hit=341513 fallback=814 | |

The workload is fixed (40 rounds), so ~1000x more stub-info hits means the
registered thread was sampled ~1000x more often, i.e. it ran ~1000x longer:
6.8M samples at the 100us wall interval is ~11 minutes, matching the observed
per-attempt time.

Where to get the raw data: the `(build) test-linux-glibc-aarch64 (...)`
artifact of a run contains `test-raw.log` with the test's stdout/stderr,
including every `[Retrying]` line and the `stub info:` line. Console job logs
only show the final PASSED line. Artifacts only exist for jobs that finished
(cancelled jobs upload nothing).

```bash
gh run download 37440354306 --repo DataDog/java-profiler \
  -n "(build) test-linux-glibc-aarch64 (21-graal, debug, regular)" -D /tmp/a
grep -E "StubUnwindCpuTest > .*(PASSED|FAILED)|\[Retrying\]|stub info:" /tmp/a/test-raw.log
```

## Code pointers

- Test: `ddprof-test/src/test/java/com/datadoghq/profiler/cpu/StubUnwindCpuTest.java`.
  Profiler command `wall=100us` (`wall=1ms` under ASan), `cstack=vm`/`vmx`.
  The aarch64-only assertion is `assertTrue(!scan.sawBreakFrame, ...)`.
- Feature under test: #816, commit `129c8f0f4` "Improve AArch64 runtime stub
  unwinding with precomputed per-stub unwind info"; `hotspot/stubUnwindInfo.h`.
- Stub branch of the walker: `ddprof-lib/src/main/cpp/hotspot/hotspotSupport.cpp`,
  around line 742 (`JitCodeCache::findRuntimeStubInfo`) through line 795
  (`fillFrame(..., "break_unwind_stub_failed")`). Order of attempts:
  1. `frame.unwindStub(start, name, pc, sp, fp, stub_info)`
     (`hotspot/hotspotStackFrame.h:113`) with the precomputed info;
  2. the `nm->frameSize()` fallback (only when `depth > 0` and
     `frameSize() > 0`; counted as `WALKVM_STUB_FRAMESIZE_FALLBACK`);
  3. otherwise `break_unwind_stub_failed`.
- Stub lookup: `JitCodeCache::findRuntimeStubInfo` in
  `ddprof-lib/src/main/cpp/hotspot/jitCodeCache.cpp:149`, taken under
  `_stubs_lock` (shared) from the signal handler.
- Debug builds record each failed stub unwind with the stub's name
  (`unwindFailures->record(UNWIND_FAILURE_STUB, name)`), emitted into the
  recording as `datadog.UnwindFailure` events (`kind="stub"`, `name`, `count`;
  `Recording::writeUnwindFailures` in `flightRecorder.cpp`).

## Suggested next steps

1. **Reproduce natively without retries.** Locally change `@RetryTest(10)` to
   `@RetryTest(1)` (or remove it) and keep recordings:

   ```bash
   ./.claude/commands/build-and-summarize :ddprof-test:testDebug -Ptests=StubUnwindCpuTest -PkeepJFRs
   ```

   Loop it (for example 20 runs) to get a failure rate and per-attempt
   durations; note the JDK, since CI saw it on 17, 21, 25 and their Graal builds.

2. **Name the failing stubs.** On a failing recording:

   ```bash
   jfr print --events datadog.UnwindFailure <recording.jfr>
   jfr print --events datadog.MethodSample <recording.jfr> | grep -B3 -A10 break_unwind_stub_failed
   ```

   With `cstack=vmx` the stub's name appears as a native frame just above the
   break frame. Check whether failures cluster on particular stubs (itable /
   vtable stubs, arraycopy, SHA-256 / MD5 / Adler32 intrinsics) and whether
   they had precomputed info (`findRuntimeStubInfo` hit) or fell through
   (`depth == 0` excludes the frameSize fallback, so a failure on the very
   first frame is a candidate).

3. **Explain the slow attempts.** Hypothesis, unverified: with a debug build
   and 100us wall sampling of the registered thread, the per-sample cost
   (walkVM, stub lookup under `_stubs_lock`, JFR recording) sometimes
   approaches the sampling interval, so the thread spends almost all its time
   in the signal handler and the workload crawls. Things to check:
   - time per attempt vs the `walkvm_stub_info_hit` count;
   - whether slow attempts correlate with failed attempts, or are independent
     (in PR #839's 21 job every slow attempt also failed; `main` 17-graal had a
     fast failed attempt);
   - `perf` on the test JVM during a slow attempt: where the signal-handler time
     goes (stub lookup, `_stubs_lock` contention, unwinding, JFR buffer writes);
   - whether `wall=1ms` (the ASan setting) avoids the slowdown.

4. **CI hygiene, after root-causing.** `@RetryTest(10)` turns a real failure
   into a pass and multiplies the runtime of each slow attempt by up to ten.
   Once the failure is understood, consider fewer retries, or none, for this
   test.

## Out of scope / already ruled out

- PR #838 (GOT-slot liveness) was suspected at first because two of its runs
  hit the timeout, but `main` and PR #839 show the same slowdown.
- The CI bot's "All N test jobs passed" comment on PR #839 counted the jobs
  cancelled at the time limit as passed.
