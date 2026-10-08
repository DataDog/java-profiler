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
| `analyze_phase0.py` | Host-side: `phase0-report.md` + `phase0-stats.csv` (mean/SD/CV/range per scenario × arm × metric, noise class, NMT delta vs no-profiler). |
| `results/2026-10-08-aarch64-docker-mac/` | First results (below). The CSV keeps only the `native_mem_*`, NMT and RSS rows. |
| `results/2026-10-08-x64-aws-m5d4xlarge/` | amd64 Linux results (below), same filtering. |

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

**perf events.** `NM_PERF` stays 0 unless the profiler can open perf events.
That needs the host's `kernel.perf_event_paranoid` low enough (check with
`sysctl kernel.perf_event_paranoid`), and the container must be allowed to
call `perf_event_open`, which Docker's defaults restrict. Untested so far;
start with:

```bash
DOCKER_EXTRA_ARGS="--cap-add=PERFMON --security-opt seccomp=unconfined" \
  REPS=10 NOPROF_REPS=3 ./utils/memcheck/phase0-container.sh build/memcheck-perf
```

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
2. **perf enabled** (either box): run with `DOCKER_EXTRA_ARGS` above and check
   `NM_PERF` is non-zero and stable.
3. **CPU-count sensitivity**: one run each with `CPUS=2` and `CPUS=8` to see
   which categories move — that decides how strictly the CI runner type has
   to be pinned.
4. **arm64 bare-metal box**: confirms whether Docker Desktop distorted
   anything, and whether arm64 can be a second gated platform.
5. Commit each result set under `results/<date>-<arch>-<host>/`.
6. Then the final run on the actual CI runner type (GitHub `ubuntu-latest`
   or the GitLab `arch:amd64` runners), and Phase 1: a report-only sticky PR
   comment from the nmt arm, baseline from `main` artifacts.

Open decisions (from the plan): GitHub vs GitLab for the PR gate; gate
reference (delta vs merge-base, committed budget file, or both); how much of
the `memory-usage-sweep-handoff` tooling to merge.
