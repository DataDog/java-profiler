<!-- Copyright 2026, Datadog, Inc -->
# StubUnwindCpuTest on aarch64: investigation handover and resolution

Status as of 2026-10-07: **both problems root-caused and fixed** on branch
`investigate/stub-unwind-aarch64` (see [Resolution](#resolution)). The original
handover notes follow the resolution unchanged.

## Resolution

Reproduced natively on an aarch64 host (JDK 21.0.12 and 25.0.4) with
`@RetryTest(1)`: both `vm` and `vmx` failed on the first attempt, and the
attempts took 46 s and 105 s of recording plus minutes of JFR parsing.

### 1. `break_unwind_stub_failed`: the `I2C/C2I adapters` blob

Every failed sample (`datadog.UnwindFailure`, plus a temporary dump of the
failing pc and phase table) was in the `I2C/C2I adapters` blob. One blob packs
several entry points back to back (JDK 21, G1):

| offset | code | correct rule |
|---|---|---|
| `0x00` | i2c: frameless argument shuffle, ends in `br x8` | pc = lr |
| `0x2c` | c2i unverified entry (inline-cache check) | pc = lr |
| `0x54` | c2i entry, class-init barrier | pc = lr |
| `0x88` | c2i entry barrier: `stp x10,xzr`, fp frame, `push_CPU_state`, runtime call | sp+16 / fp frame |
| `0x1a0` | `patch_callers_callsite`: fp frame, `push_CPU_state`, runtime call | fp frame |
| `0x294` | `skip_fixup`: `sub sp,#16`, `br` to the interpreter | pc = lr / sp+16 |

`analyzeStubUnwind()` truncated everything after the first mid-stub `br` to
`SU_UNSUPPORTED`, so only the i2c part had rules; every c2i PC fell back to the
legacy heuristics, which have no rule for adapters. The fix (all in
`hotspot/stubUnwindInfo.cpp`):

- **Restart after `br`, adapters blob only.** In the `I2C/C2I adapters` blob
  the instruction after a register jump is a further entry point (entry state)
  or an in-stub branch target, which branch validation already checks. The
  caller passes `multi_entry` for that blob name only; in every other blob the
  code after a `br` may be a jump-table entry or a return point reached through
  a register, so it keeps falling back. Even in the adapters blob, an ADR target
  after a restart degrades, and an ADRP into the blob's own pages disables the
  restart.
- **SIMD structure loads/stores** (`st1 {..}, [sp], x8` / `ld1 {..}, [sp], #32`,
  emitted by `push_CPU_state`/`pop_CPU_state`) were treated as neutral although
  they write back sp, a latent soundness bug. The multiple-structure immediate
  form is now modeled exactly, as is the register form when the offset register
  holds a constant from `mov xN, #imm` (ORR/MOVZ/MOVN) on straight-line code.
  Single-structure forms and unknown offsets make sp unknown.
- **x29 reload from its save slot** (`pop_CPU_state` restores x29 with the other
  GPRs) keeps the frame established; `mov sp, x29` makes sp known again.
- The constant and the x29 save slot are not part of the unwind rule that
  branch validation compares, so they are dropped at every in-stub branch
  target.
- Logical immediates writing sp (`and sp, x8, #-16`, the i2c stack-argument
  alignment) now make sp unknown; move-wide/logical writes to x29 drop the frame.

The captured blob is a regression fixture (`Jdk21I2CC2IAdaptersBlob` in
`stubUnwindInfo_ut.cpp`). With the fix, a standalone harness running the test
workload under a 150-frame stack showed 0 stub break frames in about 890k samples
(JDK 21 and 25, `vm` and `vmx`), versus 11 in 212k before.

Remaining risk, adapters blob only: code after a `br` that is reached by an
*indirect* jump through an address loaded from memory, with a frame
established, would get the entry rule. The adapters' `br`s are tail jumps that
leave the blob (to compiled code, the interpreter, or runtime stubs).

### 2. Slow attempts: per-sample cost exceeds the 100 us wall interval

`unwinding_ticks_async` showed the sampled thread spending ~97% of its time in
the signal handler. The test runs under the Gradle/JUnit executor with ~150 Java
frames on the stack; walking them in the `-O0 -DDEBUG` build costs ~160 us per
sample (perf: unoptimized code, plus the DEBUG-only
`SafeAccess::countIfLongjmpProtected` TLS lookup and counter increment per
safefetch, ~1,800 safefetches per sample). With the cost above the interval, the
workload only runs between handler invocations. The cost is a cliff, not linear
in depth:

| extra stack depth (debug, `wall=100us`) | workload time |
|---|---|
| 0 | 243 ms |
| 50 | 360 ms |
| 150 | 35.6 s |

The release build at depth 150 takes 255 ms, so production profiling is not
affected. If the per-sample cost on the CI runners sits near the interval, small
variations would explain the bimodal fast/slow jobs. This was not checked on
CI. The ~600k deep samples then take minutes to parse in
`JfrEvents.reduce` / `JfrEvent.getStackTraceString` (jafar `Values.resolvedDeep`).

The test now uses `wall=1ms` for debug builds as it already did for ASan, and
runs 10x the workload rounds there so that the number of samples per stub stays
the same. 1 ms with the original 40 rounds was too sparse: a musl amd64 JDK 21
debug job saw no itable-stub sample in either attempt. With 400 rounds, 5/5
forced reruns passed locally with no retries, at 2.7 s (`vm`) / 1.9 s (`vmx`)
per attempt and ~1,250 precomputed-info hits each. `@RetryTest` was lowered from
10 to 2: one retry absorbs sampling noise in the stub-presence assertions, while
an unwind regression (which reproduced on nearly every attempt) still fails.

### Same cliff in other tests

`BoundMethodHandleProfilerTest` also sampled at `wall=100us` on debug builds.
On JDK 25 aarch64 it took 14 s on CI before, and 138 s locally with or without
the analyzer change, and it stalled two CI jobs until the 3h timeout. It now
uses `wall=1ms` on debug builds too (4.4 s locally); it only asserts that some
samples exist. `MegamorphicCallTest` still samples at 100us on debug builds and
is at risk of the same cliff; it needs itable-stub sample density, so a fix
there would have to scale the workload like `StubUnwindCpuTest` does.

### Local build note

On this host clang picks the GCC 14 toolchain, which has no libstdc++ headers
installed (`'cstddef' file not found`); building with
`-Pnative.forceCompiler=g++` (GCC 13) works.

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
