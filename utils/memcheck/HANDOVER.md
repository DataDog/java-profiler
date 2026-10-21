# Memcheck Phase 0 — handover

> **Branch-only working notes. Delete this file before opening a PR from this
> branch** — design/handover docs are not committed to `main`.

Ticket: [PROF-16186](https://datadoghq.atlassian.net/browse/PROF-16186). The
plan is in the ticket comment of 2026-10-08 ("Plan: memory part of the PR
overhead check"). This file covers what Phase 0 is, what has been done, and how
to continue it on another machine.

## Goal of Phase 0

Measure the run-to-run noise of every memory metric the PR check could use, on
the hardware the check will run on, so that thresholds come from data:

- the profiler's own `native_mem_*` counters (always on in release builds,
  emitted as `datadog.ProfilerCounter` JFR events);
- JVM NMT committed memory per category, where the plan is to gate on `Class`
  and `Internal`, use `Tracing` as a tripwire, and report `Code`/`Metaspace`;
- RSS/`RssAnon`, report only.

## What is on this branch

All under `utils/memcheck/`:

| File | Role |
|---|---|
| `src/MemCheckMain.java` | Workload driver (from `MemSweepMain` on `memory-usage-sweep-handoff`). Load phase → `MEMCHECK_LOADED`; steady state; one recording rotation at `dumpAfterMs` → `MEMCHECK_DUMP_END`. `-Dmemcheck.noProfiler=true` for the control arm. |
| `src/GenSources.java` | Generates the classes the `traces`/`classesM`/`allocs` modes load; compiled by an external `javac` so the profiled JVM never loads the compiler. |
| `src/CollectRun.java` | Folds one run into a JSON record: last counter values (final + mid-run recording, via `jdk.jfr.consumer`), NMT committed KB per category, `VmRSS`/`RssAnon`/`RssFile`. Java because the test image has no python3. |
| `run_scenario.sh` | One run of one scenario in one arm. Scenario table (sizes, engines) is at the top. |
| `phase0.sh` | Interleaved repetitions of all scenarios × arms; failures are logged, not fatal. |
| `phase0-container.sh` | Host wrapper: builds the release lib from a clean clone of the committed HEAD inside the test image, then runs `phase0.sh`. |
| `ci-phase0.sh` | The same run directly on a CI runner (no container, no core pinning): records the runner's shape in `runner.txt`, builds the release lib from the checkout, runs `phase0.sh`. |
| `.gitlab/memcheck/.gitlab-ci.yml` | GitLab job `memcheck-phase0:x64` that runs `ci-phase0.sh` (below). |
| `analyze_phase0.py` | Host-side: `phase0-report.md` + `phase0-stats.csv` (mean/SD/CV/range per scenario × arm × metric, noise class, NMT delta vs no-profiler). |
| `results/2026-10-08-aarch64-docker-mac/` | First results (below). The CSV keeps only the `native_mem_*`, NMT and RSS rows. |
| `results/2026-10-08-x64-aws-m5d4xlarge/` | amd64 Linux results (below), same filtering. |
| `results/2026-10-09-x64-aws-m5d4xlarge-cpus{2,8}/` | CPU-count sensitivity on the same box, 3 reps (below). |
| `results/2026-10-21-gitlab-amd64-shared/` | First GitLab CI run, 5 jobs, unpinned (below). `runner.txt` per job, internal host details stripped. |
| `results/2026-10-21-x64-aws-m5d4xlarge-warmup-cpus{2,4}/` | Verification of the warm-up: `classesM` on 2 CPUs (6 reps), `classesM`/`traces`/`allocs` on 4 CPUs (3 reps). |

Scenarios (each run is a fresh JVM, `-Xms512m -Xmx512m -XX:+AlwaysPreTouch`,
40 s steady state, rotation at 20 s, sample 5 s after the rotation):

| Scenario | Workload | Engines |
|---|---|---|
| `threads` | 200 registered threads | `wall=~5ms` |
| `traces` | 1 class, 5000 methods | `wall=~5ms` |
| `classesM` | 2000 classes × 20 methods | `wall=~5ms` |
| `allocs` | 2000 object shapes | `memory=1024:a` |
| `mixed` | as `allocs` | `cpu=10ms,wall=~5ms,memory=262144:al` |

Arms: `counters` (profiler, NMT off), `nmt` (profiler + NMT summary),
`noprof` (no profiler, NMT on).

## Running it on another machine

Prerequisites: Docker, python3 on the host, and the test image. Build the image
once with the existing container script (it builds the image, then drops you
into a shell; just `exit`):

```bash
./utils/run-containers-tests.sh --container=docker --jdk=21 --libc=glibc --shell
```

That produces `java-profiler-test:glibc-jdk21-<x64|aarch64>`, which
`phase0-container.sh` picks by host architecture. Then:

```bash
# Full run: ~115 runs, about 1.5 h. The profiler is built from the committed HEAD.
REPS=10 NOPROF_REPS=3 ./utils/memcheck/phase0-container.sh build/memcheck
python3 utils/memcheck/analyze_phase0.py build/memcheck
# -> build/memcheck/phase0-report.md, build/memcheck/phase0-stats.csv

# Smoke test first (one short rep of one scenario, ~5 min incl. the build):
REPS=1 NOPROF_REPS=1 SCENARIOS=traces STEADY_MS=10000 DUMP_AFTER_MS=4000 \
  ./utils/memcheck/phase0-container.sh build/memcheck-smoke

# Re-run without rebuilding the profiler (reuses OUT/lib):
SKIP_BUILD=1 ./utils/memcheck/phase0-container.sh build/memcheck
```

Keep `CPUS=4` (the default) unless you are deliberately testing CPU-count
sensitivity: CI runners are 4-core, and some categories scale with CPU count.
The container is pinned to cores `0..CPUS-1` (`--cpuset-cpus`). An earlier
version used `--cpus`, a CFS quota: on a 16-core host the JVM then saw 4 CPUs
but `nproc`, the affinity mask and the profiler's
`sysconf(_SC_NPROCESSORS_ONLN)` saw 16. The Mac set was not affected, because
the Docker Desktop VM itself had 4 CPUs (`cpus: 4` in its report).

**perf events: not measured, and `NM_PERF` is left out of the gate.** No
scenario opens a perf event. `cpu=` and `event=cpu` both pick the ctimer
engine (per-thread `timer_create` CPU timers) and fall back to perf events only
if ctimer fails (`selectCpuEngine` in `profiler.cpp`), which does not happen on
Linux. So `NM_PERF` is 0 even with perf events allowed, and the gate would see
the perf engine only if a scenario used a perf-only event. Tested on the x64
box (`perf_event_paranoid=2`, no host change needed):

| container | `cycles` (hardware) | `page-faults`, `context-switches` (software) |
|---|---|---|
| default Docker | fails | fails |
| `--cap-add=PERFMON --security-opt seccomp=unconfined` | fails | starts |
| `--privileged` | fails | starts |

The VM does not appear to expose hardware PMU events. Note also that this
fork's event table has no `cpu-clock`: `event=cpu-clock` fails as an
unsupported event.

With a perf event, `NM_PERF` is not a useful gate metric anyway: it is
dominated by `PerfEvents::start` allocating one `PerfEvent` per possible
thread ID, `calloc(pid_max, sizeof(PerfEvent))`. `PerfEvent` is 128 bytes
because it inherits the cache-line-padded `SpinLock` (`1abf1ebd3`). With
`pid_max=4194304` that is exactly 512 MiB in `NM_PERF`, a constant set by the
host's `pid_max`. Only the pages of thread IDs that actually get an event are
touched: in a 200-thread `threads` run the 512 MiB mapping had 36 KiB
resident (`smaps`). Filed as
[PROF-16244](https://datadoghq.atlassian.net/browse/PROF-16244).

Without Docker, `phase0.sh` runs directly given `DDPROF_LIB`,
`DDPROF_CLASSES`, `MEMCHECK_CLASSES`, `WORKDIR`, `OUTDIR` and a JDK 21 with
`javac`/`jcmd` (see the header of `run_scenario.sh`).

## Results so far: aarch64, Docker Desktop on a Mac, 4 CPUs

JDK 21.0.8, profiler `a60c7b1cf`, 10 reps, 115 runs, 0 failures. Full report:
`results/2026-10-08-aarch64-docker-mac/phase0-report.md`.

- **Counters: every non-zero live/max/post-flush value had SD ≤ max(1 %, 64 KiB)**
  in all five scenarios. Totals (~20–25 MiB): SD 4–69 KiB (≤ 0.3 %).
  `calltrace` is the noisiest (≤ ~40 KiB); `line_tables`/`method_map`
  ≤ 23 KiB; `dictionary`, `native_symbols`, `thread_local`, `liveness`
  identical in every run.
- **NMT on shifts the logical counters by < 30 KiB**, so the nmt arm can double
  as the counter arm in CI (halves the cost).
- **NMT `Class` SD ≤ 1 KiB, `Internal` ≤ 7 KiB**; profiler adds +0.1…+2.9 and
  +0.15…+3.0 MiB respectively, scaling with class count → gateable.
- **NMT `Tracing` does not exist** in either arm with ddprof standalone, so the
  tripwire is "category appears".
- **NMT `Code` is profiler-driven and fairly stable**: +12.1 MiB in `classesM`,
  +6.8 MiB in `traces`, SD ≤ 516 KiB (CV < 1 %). A candidate for a banded gate.
- `Thread` (SD up to 54 KiB, JIT threads), `Metaspace` (SD up to 431 KiB, no
  profiler delta), `Arena Chunk` → report only / exclude.
- **RSS** with a fixed, pre-touched heap: SD 0.1–6 MiB; profiler adds 18–47 MiB.
  Far quieter than the DOE workload (~30 MiB SD), still not gate material.
- The data argues for dropping the 5 % term from the planned threshold formula:
  noise is far below 5 %, and 5 % of a large category (`native_symbols`,
  ~10 MiB) would hide a ~500 KiB regression. `max(256 KiB, 4·SD)` fits.

Caveats of this first pass:

- Docker Desktop VM, not a real Linux host; `perf_event_paranoid=4`, so
  `NM_PERF` = 0 and the cpu engine in `mixed` did not use perf events.
- Sampling only reaches part of each workload: `traces` captured ~1000 of 5000
  stack shapes in the 10 s smoke test, and `classesM` (40k methods) reaches
  only 0.44 MiB of `method_map`. Fine for detecting per-item cost regressions,
  but the absolute numbers are not production-sized.

## Results: amd64, AWS m5d.4xlarge (Xeon 8259CL), real Linux, 4 pinned cores

JDK 21.0.8, profiler `adbd3fff8` (the profiler code is identical to
`a60c7b1cf`; the commit only adds `utils/memcheck`), 10 reps, 115 runs,
0 failures. Kernel 6.8, `perf_event_paranoid=2`, default Docker seccomp, so
`NM_PERF` is still 0. Full report: `results/2026-10-08-x64-aws-m5d4xlarge/`.

The gate candidates (counters, NMT `Class`/`Internal`) keep their noise
classes. Of the 14 class changes against the Mac set, all but one are in
report-only categories: `Compiler` and `Arena Chunk` go stable→noisy in some
scenarios, `GC` goes stable→banded in `classesM` noprof, and `RssFile` goes
noisy→stable. The exception is `Code`, which goes stable→banded in `traces`.

- **Counters are quieter than on the Mac**: every live/max/post-flush SD is
  ≤ 17 KiB (Mac: ≤ 70 KiB). Totals 22.4–26.4 MiB, SD 4–14 KiB. `calltrace`
  ≤ 11 KiB, `method_map`/`dictionary`/`line_tables` ≤ 7 KiB (`dictionary` was
  identical in every Mac run).
- **NMT on shifts the logical counters by ≤ 12 KiB** (largest
  |counters − nmt| mean over live/max/post-flush, `classesM` total), so the
  nmt arm can still double as the counter arm.
- **Absolute counter values depend on the architecture**: `native_symbols` is
  12.87 MiB on x64 and 9.84 MiB on aarch64 (constant within each), and
  `calltrace`/`method_map`/`line_tables` differ by up to ~0.1 MiB. So baselines
  have to be per-architecture, and a gate compares x64 with x64 only.
- **NMT `Class` and `Internal`**: the profiler deltas are the same on both
  architectures to within 0.06 MiB (`Class` +0.11…+2.94, `Internal`
  +0.15…+3.05 MiB), with SD ≤ 1 KiB and ≤ 5 KiB. Confirmed gateable.
- **NMT `Tracing` is absent on x64 too.**
- **NMT `Code` is weaker here than on the Mac**: the profiler delta is about
  half (+3.2 MiB `traces`, +4.9 MiB `classesM`, against +6.8/+12.1), and the
  nmt-arm SD reaches 411 KiB in `traces` (13 % of the delta; "banded"). A band
  of 4·SD ≈ 1.6 MiB is still usable, but `Code` is a soft gate at best.
- `Compiler` is noisy on x64 (SD up to 352 KiB), `GC` reaches 416 KiB SD in
  `classesM`, and `Thread` is +0.01 MiB in `threads` (Mac: +0.55). Report only.
- **RSS**: SD 0.1–4.5 MiB (Mac 0.1–6.2), profiler delta +23…+32 MiB. `RssFile`
  is stable here (SD ≤ 0.1 MiB; Mac up to 2.1 MiB). Still report only.
- `max(256 KiB, 4·SD)` still fits: the 256 KiB floor dominates for every
  counter on x64.

## CPU-count sensitivity: same x64 box, CPUS=2 and CPUS=8

3 reps per arm (45 runs each, 0 failures), library from the CPUS=4 run. Each
mean is compared with the 10-rep CPUS=4 set against the planned threshold
`max(256 KiB, 4·SD of the CPUS=4 set)`.

- **Profiler counters: no live/max/post-flush metric crosses the threshold**
  at 2 or 8 CPUs. They do not depend on the core count.
- **NMT `Internal`, and `Class` outside `classesM`**: the profiler deltas are
  unchanged at 2 and 8 CPUs (within 0.1 MiB).
- **NMT `Class` in `classesM` on 2 CPUs is unstable, and the profiler does not
  cause it.** The scenario loads ~42,800 instance classes (2000 generated
  classes, plus roughly one per reflectively invoked method: 2000 × 20). On 2
  CPUs, between 40,594 and 42,845 of them were loaded at sample time (low in
  5 of 9 nmt runs), and `Class` committed tracks that count (~1.7 KiB per
  class), so it dropped by up to 3.7 MiB. All runs at 4 and 8 CPUs
  reached the full count. The workload simply had not finished at sample
  time. CI runners slower than this box could show the same thing at 4 cores.
  Fixed by the warm-up described in "Warm-up before the steady state" below.
- **CPU-dependent, so the runner type has to be pinned for these**: NMT `GC`
  (−4.0 MiB at 2 CPUs, +8.1 MiB at 8, in every scenario) and therefore NMT `total`; `Code` (up to −6.4 MiB
  at 2 and +3.9 MiB at 8 in the nmt arm, and the profiler delta moves too);
  `Metaspace`; `Arena Chunk`; RSS in `classesM`/`traces`.
- **Conclusion for CI**: gating on the counters and on `Internal` is safe
  across runner sizes. `Class` is safe once the `classesM` workload is made
  deterministic. Anything report-only can still vary with the runner's core
  count, so baselines should come from the same runner type.

## Warm-up before the steady state (harness change, 2026-10-21)

**Cause of the 2-CPU `Class` spread.** `traces`, `classesM` and `allocs` call
each generated method through `Method.invoke`. Every call goes through a
per-method method handle, and `MethodHandle.maybeCustomize()` customizes its
LambdaForm, spinning one `LambdaForm$MH` hidden class, once the handle's
`customizationCount` reaches `CUSTOMIZE_THRESHOLD` (default 127), so on its
128th call. Each method is called once per pass, so in `classesM` all ~40,000
of these classes load together after ~128 passes. Class-load logging on 2
CPUs put the burst at 20–26 s after `MEMCHECK_LOADED`, on top of the NMT
sample (~25 s). A run with `CUSTOMIZE_THRESHOLD=60` moved it to 10–14 s, as
predicted, and the total stayed at 40,018.

**Correction.** An earlier suggestion here (in the session, not in this file)
was to fall back to waiting until the loaded-class count stops changing.
That would not work: the count stays flat for ~20 s before the burst.

**Fix.** `MemCheckMain` runs 130 passes of the reflective workloads before
`MEMCHECK_LOADED` (`WARMUP_PASSES`); `threads` is unchanged. The JVM runs in its
default configuration. The rejected alternative, `-Djava.lang.invoke.MethodHandle.CUSTOMIZE_THRESHOLD=0`
plus one pass (0 and −1 both mean "customize on the first call", since the
check is `count >= threshold`), also fixed `Class` but changed JIT behaviour:
NMT `Code` moved by up to −28 MiB, and the profiler's `Code` delta in
`classesM` went from +4.85 to +1.44 MiB.

**Verified** (`results/2026-10-21-...-warmup-*`, same x64 box):

- 2 CPUs: all 6 nmt runs had 42,847 classes at sample time and `Class`
  committed 70,037–70,040 KiB. Class-load logging: ~20 classes load after
  `MEMCHECK_LOADED` (dumper thread, rotation, shutdown), against ~40,000
  before.
- 4 CPUs against the committed CPUS=4 set: NMT `Class` and `Internal` within
  0.2 MiB in every arm, so the profiler's `Class`/`Internal` deltas are
  unchanged. The profiler's `Code` delta moved by ≤ 0.4 MiB, while absolute
  `Code` rose in both arms (+3 MiB in `traces`). `Code` SD at 4 CPUs is lower
  (`traces` 411 → 135 KiB).
- **Baseline boundary for the `classesM` counters**: `method_map` 370 →
  981 KiB, `line_tables` 195 → 361 KiB, max `calltrace` 5.55 → 6.54 MiB,
  total live +0.78 MiB, total max +1.73 MiB. SDs stay ≤ 21 KiB, and the
  2-CPU and 4-CPU values agree within 38 KiB, so the shift does not depend
  on runner speed. Unverified, but consistent with this: the customized
  LambdaForm frames are now in sampled stacks for the whole recording
  instead of from ~20 s on. `traces`/`allocs` counters did not cross the
  threshold.
- So the committed result sets above stay valid for noise classes and for
  `Class`/`Internal`, but not as baselines for `classesM` counters or for
  absolute `Code`.

## Gotchas found on the way

- `memory=N:a:l` silently **disables** liveness: the field after the flags is
  the subsample ratio. Use `memory=N:al`.
- `jcmd VM.native_memory` needs the target JVM started with
  `-XX:NativeMemoryTracking=summary`; NMT inflates malloc chunk overhead
  (`native_mem_chunk_overhead_bytes.*`), not the logical counters.
- On a Linux host the bind-mounted repo belongs to the host user, so `git
  clone` inside the container fails with "dubious ownership" unless
  `safe.directory` is set (`phase0-container.sh` now sets it). Docker Desktop
  hides this.
- The final JFR file only contains chunks after the mid-run rotation; gauges
  (`live`, `max`) are absolute, so that is fine, and `post_flush_*` describes
  the rotation.

## Next steps

1. ~~**amd64 Linux box**~~ — done, see the x64 results above. Same noise
   classes; the absolute values are per-architecture.
2. ~~**perf enabled**~~: dropped, see "perf events" above.
3. ~~**CPU-count sensitivity**~~: done, see above. The `classesM` follow-up
   is done too (warm-up, above).
4. **arm64 bare-metal box**: confirms whether Docker Desktop distorted
   anything, and whether arm64 can be a second gated platform.
5. Commit each result set under `results/<date>-<arch>-<host>/`.
6. **Final run on the CI runner type: GitLab `arch:amd64`** (decided
   2026-10-21; the PR-comment helper `.gitlab/scripts/upsert-github-pr-comment.sh`
   and the benchmark/reliability precedent are on GitLab). Job
   `memcheck-phase0:x64` in `.gitlab/memcheck/.gitlab-ci.yml`: 5 parallel
   jobs × (3 reps of counters/nmt + 1 noprof) of all scenarios, ~45 min each.
   Splitting it shows how much the means move *between* jobs (a PR job
   against a baseline job), which no run so far has measured.
   - Trigger: GitLab → Run pipeline on the branch, variable
     `RUN_MEMCHECK_PHASE0=true`. A web-started pipeline also passes the PR
     gate in `prepare.sh`, so it runs the whole PR pipeline alongside;
     that is also the load a real PR job would share nodes with.
   - Analysis: download the `build/memcheck-<n>/` artifacts; check that
     `runner.txt` agrees across jobs (CPU count, quota, model); run
     `analyze_phase0.py` per job and compare per-job means against
     `max(256 KiB, 4·SD)`.
   - The job's image (`BUILD_IMAGE_X64_GLIBC`, el8) has JDK 21.0.3; the
     committed sets used 21.0.8. Baselines will come from CI, so this only
     limits direct comparison with the committed sets.
   **First run (2026-10-21, `7cd55c5ec`, 5 jobs, 175 runs, 0 failures),
   unpinned.** `results/2026-10-21-gitlab-amd64-shared/`.
   - Each job got a pod in `gitlab-runner-amd64-shared` on a Xeon 8375C node
     with 52, 66, 68, 72 or 93 usable CPUs, no CPU quota (`cpu.max` = max)
     and a 6 GiB memory limit. The JVM sized itself to all of them: NMT `GC`
     in `threads` was 132–156 MiB per job (52 MiB at 4 pinned CPUs).
   - No gated metric moved between jobs by more than `max(256 KiB, 4·SD)`
     (largest ratio 0.37); only NMT `Code` crossed it, in one job.
   - Profiler counters: `threads`, `traces`, `allocs`, `mixed` SD ≤ 69 KiB.
     `classesM` was much noisier than on the pinned box: within-job SD up to
     292 KiB for `native_mem_max_bytes` and 238 KiB for `calltrace` max
     (≤ 17 KiB pinned), in two of the five jobs (52 and 93 CPUs); the other
     three had 20–56 KiB. Five jobs are too few to tell CPU count from node
     load.
   - `JAVA_TOOL_OPTIONS` is set in CI (proxy settings). Every JVM in the
     harness picks it up; it is the same for baseline and PR jobs.

   **Change after the first run:** `ci-phase0.sh` runs the scenarios under
   `taskset` on the first `CPUS` (4) CPUs the pod is allowed, so the JVM,
   `nproc` and the profiler see 4 cores, as in the pinned container runs.
   Other pods can still run on those cores (no quota). Also fixed:
   `jdk.txt` (it captured the `JAVA_TOOL_OPTIONS` line), scratch files moved
   out of the artifact paths (`build/mc-scratch`), `JAVA_TOOL_OPTIONS` kept
   out of `runner.txt`. Next: rerun the 5-job pipeline and compare. If
   `classesM` is still noisy, the options are a larger floor for `classesM`,
   gating it on live instead of max values, or dedicated runners.
7. Phase 1: a report-only sticky PR comment from the nmt arm, baseline from
   `main` artifacts.

Open decisions: gate reference (delta vs merge-base, committed budget file,
or both); how much of the `memory-usage-sweep-handoff` tooling to merge.
