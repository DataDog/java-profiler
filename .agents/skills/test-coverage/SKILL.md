---
name: test-coverage
description: Measure C++ and Java test coverage of origin/main across every Linux platform (glibc/musl × x64/aarch64) and test JVM CI tests there (HotSpot, OpenJ9, GraalVM), one worktree and subagent per libc×arch, then merge everything into one report. Use when asked for full, merged or cross-platform coverage.
---

# Test coverage across Linux platforms

Each cell runs `:ddprof-lib:coverageReport -PenableCoverage` in a container through
`utils/run-containers-tests.sh --coverage-out`; `utils/merge-coverage.sh` merges the
cells. Read [doc/building/CodeCoverage.md](../../../doc/building/CodeCoverage.md)
first: the C++ numbers cover the `-O0 -DDEBUG` build only. macOS is not part of the
matrix. Optional arguments: `ref=<git ref>` (default `origin/main`) and
`tests=<pattern>` (passed as `--tests`, for a quick smoke run).

## 1. Preflight

Stop and report on the first failure:
- A container runtime answers: `podman info`, else `docker info`. Use it as `RT` for
  every cell. Docker on macOS needs `colima start` first.
- The host has gcovr 8.3+ (`gcovr --version`; install with `pip install gcovr`) and
  `java` on `PATH`. They are needed only for step 4, but check now.
- Free disk: about 3 GB per worktree plus the container images.
- Memory: `RT info --format '{{.Host.MemTotal}}'` (podman) or `'{{.MemTotal}}'`
  (docker), in bytes. Gradle, the `-O0` compile and the test JVMs of one cell need
  about 8 GB; with less, the Gradle daemon is killed ("Gradle build daemon
  disappeared unexpectedly"). Set `SLOTS` = memory / 8 GB, at most 4. If it is 0,
  stop and ask the user to give the VM more memory (`podman machine set --memory`,
  `colima start --memory`).
- Other containers: list `RT ps`. Running containers share that memory; ask the
  user before stopping any.
- Base images: for each `java-profiler-base:<libc>-<arch>` that exists, run
  `RT run --rm --platform linux/<amd64|arm64> <image> gcovr --version`. If it fails, that agent's first cell must
  pass `--rebuild-base`; the script then rebuilds the JDK images on top of it.

The non-native architecture runs emulated (QEMU or Rosetta) and takes several times
longer than the ~30 minutes of a native cell. Tell the user the slot count and that
estimate before starting.

## 2. Worktrees

```bash
git fetch origin main
COMMIT=$(git rev-parse <ref>)
RUN=$(pwd)/build/test-coverage/$(git rev-parse --short=12 $COMMIT)-$(date -u +%Y%m%dT%H%M%SZ)
for c in glibc-x64 glibc-aarch64 musl-x64 musl-aarch64; do
  git worktree add --detach "$RUN/wt-$c" $COMMIT
done
```

Keep `RUN` under `$HOME`: colima shares only `$HOME` with its VM. Check that the
worktree's `utils/run-containers-tests.sh` accepts `--coverage-out`
(`grep -q -- --coverage-out`); if it does not, the ref predates coverage mode — stop.

## 3. Subagents

Run at most `SLOTS` subagents at a time, in the background (general-purpose): launch
the first `SLOTS` in one message, and launch the next one when an agent sends its
final per-cell report (interim "waiting" notifications do not free a slot). Start
with the emulated architecture's agents: they take longest.
Cells per agent: the JVMs CI tests on each platform (`test_workflow.yml` matrices).
CI's `8-orcl` and `8-ibm` (glibc x64) have no container image and are not covered;
say so in the report. Keep this table in sync when the CI matrices change.

| Agent | JDKs |
|---|---|
| glibc-x64 | 8 8-j9 11 11-j9 17 17-j9 17-graal 21 21-graal 25 25-graal |
| glibc-aarch64 | 8-j9 11-j9 17 17-j9 17-graal 21 21-graal 25 25-graal |
| musl-x64 | 8 11 17 21 25 |
| musl-aarch64 | 8 11 17 21 25 |

Give each agent this brief, filled in:

> Run java-profiler coverage cells for libc=`<libc>`, arch=`<arch>`, one at a time,
> in worktree `<RUN>/wt-<libc>-<arch>`. JDKs, in order: `<list>`. Runtime: `<RT>`.
> For each JDK `<jdk>`, let `<cell>` be `<RUN>/cells/<libc>-<arch>-<jdk>` and `<log>`
> be `<RUN>/logs/<libc>-<arch>-<jdk>.log` (absolute paths; `mkdir -p <RUN>/logs`).
> Start the cell detached so no tool timeout kills it:
> `cd <wt> && nohup bash -c './utils/run-containers-tests.sh --container=<RT>
> --libc=<libc> --arch=<arch> --jdk=<jdk> --coverage-out=<cell> [--tests=<pattern>];
> echo $? > <cell>.exit' > <log> 2>&1 &`.
> Then wait until `<cell>.exit` exists (Monitor with an until-loop, or a background
> `while [ ! -f <cell>.exit ]; do sleep 60; done`, re-armed if it times out). Do not
> start the next cell before the current one finishes.
> Classify each cell from the exit code, `<cell>/cell.properties` and the log:
> `passed` (exit 0); `failed` (a task failed on its own terms: compile error, test
> failures, gtest failure — name the task and tests); `blocked` (no
> `cell.properties`: image build, download or container failure; or Gradle was
> killed: "Gradle build daemon disappeared unexpectedly", exit 137, `Killed`). If
> the log says a coverage tool is missing (`checkCoverageTools`), the cached base
> image predates it: rerun that cell once with `--rebuild-base`. Retry any other
> `blocked` cell once. Do not edit code, change tests or retry `failed` cells. Never print more than 30 log lines. Never put the word "gradlew" in a shell
> command: a hook blocks it — search logs for `What went wrong` or `FAILED` instead.
> Report one line per cell: jdk, status, gradle_exit, failing task/tests or the
> blocking error, log path.

While they run, answer the user from their notifications only; if asked for
progress, list which `$RUN/cells/*.exit` files exist.

## 4. Merge

After all four agents send their final reports, merge every cell that has `cell.properties` (a
`failed` cell still holds the coverage of the tests that ran):

```bash
cells=(); for p in "$RUN"/cells/*/cell.properties; do cells+=("${p%/cell.properties}"); done
"$RUN/wt-glibc-x64/utils/merge-coverage.sh" --source-root="$RUN/wt-glibc-x64" \
  --out="$RUN/merged" "${cells[@]}"
```

If gcovr rejects a tracefile, report the gcovr error and the cell; do not drop the
cell silently.

## 5. Report

- The commit, and a per-cell table: libc, arch, jdk, `passed`/`failed`/`blocked`,
  failing tests or blocking error.
- The merged totals from `$RUN/merged/summary.md`, and paths to
  `merged/cpp/index.html` and `merged/java/html/index.html`.
- Which cells are missing from the merge and why, and that every `failed` or missing
  cell lowers the numbers. The C++ report is the debug build only.

Leave `$RUN` in place. Offer to remove the worktrees
(`git worktree remove "$RUN"/wt-*`); `cells/`, `logs/` and `merged/` stay until the
user deletes them. On Linux with rootful Docker the container writes `cells/` as
root; remove them with `sudo` or from a container.
