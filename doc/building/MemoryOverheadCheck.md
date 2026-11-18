# Memory Overhead Check

Every PR pipeline on GitLab checks the native memory of the profiler against a budget.
The check runs synthetic workloads with and without the profiler. A value over its limit
fails the pipeline. The `memcheck:comment` job posts the report as a PR comment.

The code is in `utils/memcheck/`. The jobs are in `.gitlab/memcheck/.gitlab-ci.yml`.

## What runs

Each run is a new JVM with `-Xms512m -Xmx512m -XX:+AlwaysPreTouch -XX:+UseG1GC
-XX:ActiveProcessorCount=4`. A run has a load phase and a 40 s steady state, with one
recording rotation after 20 s. `utils/memcheck/run_scenario.sh` holds the scenario table:

| Scenario | Workload | Profiler engines |
|---|---|---|
| `threads` | 200 registered threads | `wall=~5ms` |
| `traces` | 1 class with 5000 methods | `wall=~5ms` |
| `classesM` | 2000 classes with 20 methods each | `wall=~5ms` |
| `allocs` | 2000 object shapes | `memory=1024:a` |
| `mixed` | as `allocs` | `cpu=10ms,wall=~5ms,memory=262144:al` |

Each scenario runs in three arms: `counters` (profiler, no NMT), `nmt` (profiler and NMT
summary) and `noprof` (NMT, no profiler). The PR check runs only `nmt` and `noprof`.

| Job | Role |
|---|---|
| `memcheck:x64` | Two parallel jobs run the scenarios on one pod each: 3 `nmt` and 2 `noprof` runs. |
| `memcheck:report` | `Evaluate.java` checks the records against `utils/memcheck/budget.txt`. |
| `memcheck:comment` | Posts the report as a sticky PR comment. |
| `memcheck:unit-tests` | Runs `utils/memcheck/test/evaluate_test.sh`. |
| `memcheck-calibrate:x64` | Five parallel calibration jobs. Runs only on request, see below. |

## What is checked

- The `native_mem_*` counters of the profiler, as the mean of the `nmt` runs. These need
  no reference run, because without the profiler they are zero.
- NMT `Class` and `Internal`: the `nmt` mean minus the `noprof` mean on the same pod.
- NMT `Tracing` must not appear. The profiler alone allocates nothing in this category.
- In `classesM`, the counters grow with the number of methods that sampling reaches. This
  number changes with the load on the runner. The check corrects the counters to a fixed
  number of methods (`per_method` and `ref_methods` in the budget).

NMT `Code`, `GC` and total, and RSS, are in the report but have no limit. In the
calibration on pipeline 154255597, the profiled-minus-noprof delta of NMT `Code` and total
moved by up to 6.4 MiB between pods, and RSS by up to 13.5 MiB.

The shared amd64 runners give each pod a different CPU set, and the set can change during a
job. For this reason the JVM gets a fixed collector and CPU count. Pinning with `taskset`
made the JVM use Serial GC.

## Budget file

The format is in the javadoc of `utils/memcheck/src/Evaluate.java`. Each limit is:

`limit = measured + max(256 KiB, 4 × largest within-job SD)`, rounded up to 0.05 MiB.

A PR that exceeds a limit must fix the regression or raise the limit in `budget.txt`. The
PR description must give the reason.

## Recalibrate

Recalibrate when a change moves the measured values on purpose, or when the runner image
or JDK changes.

1. Push the branch to GitLab. Start a pipeline from the GitLab UI (Run pipeline) with
   `RUN_MEMCHECK_CALIBRATION=true`. A pipeline started through the API does not run the
   job, because its rule requires the `web` pipeline source.
2. Wait for the five `memcheck-calibrate:x64` jobs (about 30 minutes) and download their
   `build/memcheck-<n>/` artifacts.
3. Check that the `runner.txt` files agree on CPU model, memory limit and `pid_max`.
4. Run:

   ```bash
   java utils/memcheck/src/Evaluate.java --calibrate utils/memcheck/budget.txt new-budget.txt \
     memcheck-1 memcheck-2 memcheck-3 memcheck-4 memcheck-5
   ```

   This replaces each gated line and keeps all comments. It prints the old and new limit
   of each line.
5. Update the `# Set ...` comment in the new file, review the changes and replace
   `budget.txt` in the PR.

The `mixed` peak includes the CTimer table. Its size is `pid_max` × 4 B: 16 MiB on the
current runners, which have `pid_max` 4194304. On a runner with a smaller `pid_max`, the
`mixed` peak is smaller, and its limit can hide a regression of up to that difference.
