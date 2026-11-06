# Utility Scripts

<!-- Copyright 2026, Datadog, Inc -->

This directory contains utility scripts for managing the java-profiler project.

---

## Release

### `release.sh`

Triggers the Validated Release workflow using GitHub CLI to create a new release.

**Prerequisites:**
- [GitHub CLI](https://cli.github.com/) installed and authenticated
- [jq](https://jqlang.github.io/jq/) installed
- Git repository is up to date
- The authenticated user has write, maintain, or admin repository access
- You are on the correct branch for the release type

**Usage:**
```bash
./utils/release.sh <release_type> [options]
```

**Arguments:**
- `release_type`: Type of release (`major`, `minor`, or `patch`)

**Options:**
- `--no-dry-run`: Actually perform the release (default is dry-run)
- `--skip-tests`: Skip pre-release tests (emergency releases only)
- `--branch <name>`: Specify branch to release from (default: current branch)
- `--commit <sha>`: Specify commit SHA to release (default: interactive selection)
- `--help`: Show help message

**Branch rules:**
- **Major/Minor releases**: must be run from `main`
- **Patch releases**: must be run from a `release/X.Y._` branch

**Release flow:**
1. Validates inputs and branch rules
2. Fetches and verifies the selected branch is up to date with
   `origin` (a checked-out local branch that's behind or ahead of origin
   fails fast with pull instructions)
3. For patch releases, asks whether to pick PRs from `main` to backport onto
   the release branch first; if you accept, you select which PRs, a combined
   backport PR is opened, and the script exits so you can merge it and re-run
4. Interactive commit selection (or use `--commit`)
5. Triggers GitHub Actions "Validated Release" workflow
6. Workflow runs pre-release tests, then creates the annotated tag on the
   selected commit (and a release branch for minor/major releases)
7. Tag push triggers GitLab, which publishes the Maven artifacts, and the
   GitHub release workflows attach the release assets

No file modifications or version-bump PRs are needed — the version is
computed from git tags at build time. The next build from `main` (or the
release branch) automatically sees the new tag and computes the next
snapshot version.

Interactive pickers (branch and commit selection) support ↑/↓/Enter, and
can be cancelled at any time with `q` or Ctrl-C.

A dry run never creates a tag, pushes a branch, or triggers GitLab.

If workflow monitoring loses its API connection, the script checks the run's
status and reconnects to the same run, making up to three monitoring attempts
per monitoring window. All attempts share a one-hour deadline. When the deadline
is reached, the script allows up to ten seconds for a final status query, including
when it must retry a query interrupted by the shared deadline. If the result remains
unconfirmed, an interactive session asks whether to watch the same run for another
hour. Answering `y` or `yes` renews the deadline and monitoring attempts. Answering
`n`, pressing Enter, or reaching EOF stops monitoring with
`WORKFLOW STATUS UNKNOWN` and a nonzero exit. Unattended sessions stop without
prompting. The remote workflow keeps running when local monitoring stops.
`RELEASE_MONITOR_TIMEOUT_SECONDS` overrides the default 3600-second deadline.
Check the existing run before starting another release.
Recognized completed outcomes retain GitHub's exact conclusion in the output.
Only a confirmed `success` exits zero; other recognized conclusions exit nonzero.
Only `failure` and `startup_failure` are labelled as workflow failures.

### Testing release automation

`.github/scripts/tests/test_release_automation.sh` is a single hermetic shell
test. It validates release tag/branch creation, version computation,
trivial-PR authorization, and recovery from workflow monitoring errors using
temporary local Git repositories and a GitHub CLI fixture. It does not load
credentials or contact GitHub, so it cannot publish, tag, push, or merge
anything remotely.
The terminal interaction tests require Python 3.

```bash
.github/scripts/tests/test_release_automation.sh
```

---

## Backport

### `backport-pr.sh`

Cherry-picks a merged PR onto a release branch, pushes the backport branch, and opens a PR.

**Prerequisites:**
- [GitHub CLI](https://cli.github.com/) installed and authenticated
- [jq](https://jqlang.github.io/jq/) installed
- Clean working tree

**Usage:**
```bash
./utils/backport-pr.sh [--dry-run] [<release-name>] <pr-number-or-url>
```

**Arguments:**
- `<release-name>`: Target release branch suffix, e.g. `1.9._` (maps to `release/1.9._`). If omitted, an interactive picker is shown.
- `<pr-number-or-url>`: PR number (`420`) or full GitHub URL.
- `--dry-run`: Preview without making changes.

**Examples:**
```bash
./utils/backport-pr.sh 1.9._ 420
./utils/backport-pr.sh 420          # interactive branch selection
./utils/backport-pr.sh --dry-run 1.9._ 420
```

### `prepare-patch.sh`

Finds PRs merged to `main` since a release branch diverged, lets you
multi-select which ones to backport, cherry-picks them onto a single new
branch off the release branch, runs `./gradlew buildDebug` to catch a
combination that doesn't build before pushing, and opens one combined PR.
Also invoked interactively from `release.sh` when preparing a patch release.

**Prerequisites:**
- [GitHub CLI](https://cli.github.com/) installed and authenticated
- [jq](https://jqlang.github.io/jq/) installed
- Clean working tree

**Usage:**
```bash
./utils/prepare-patch.sh [--branch release/X.Y._] [--no-dry-run]
```

**Options:**
- `--branch <name>`: Release branch to prepare. If omitted, an interactive picker is shown.
- `--no-dry-run`: Actually cherry-pick, push, and open the PR (default is dry-run).

**Examples:**
```bash
./utils/prepare-patch.sh --branch release/1.9._            # dry-run, preview only
./utils/prepare-patch.sh                                   # interactive branch selection, dry-run
./utils/prepare-patch.sh --no-dry-run --branch release/1.9._
```

Test candidate discovery with local Git repositories and a GitHub CLI fixture:

```bash
bash utils/tests/test_prepare_patch.sh
```

---

## Testing

### `run-containers-tests.sh`

Runs tests in containers across various OS/libc/JDK combinations, mirroring the CI matrix locally. Defaults to Podman; on macOS use Docker via colima (`--container=docker`) — podman's credential-helper lookup for the Datadog registries (ddtool) fails outside the CI network and aborts container commands.

**Usage:**
```bash
./utils/run-containers-tests.sh [options]
  --libc=glibc|musl|all[,..]      (default: glibc)
  --jdk=8|11|17|21|25|8-j9|...|regular|j9|graal|all[,..]
                                    (default: 21)
  --arch=x64|aarch64|all[,..]     (default: auto-detect)
  --config=debug|release|asan|tsan|all[,..] (default: debug)
  --container=podman|docker       (default: podman)
  --tests="TestPattern"           (optional)
  --gtest                         (enable C++ gtests)
  --gtest-task=Task               (run one C++ gtest task)
  --shell                         (drop to shell instead of running tests)
  --mount                         (mount local repo instead of cloning)
  --rebuild                       (force rebuild of container images)
  --coverage-out=DIR              (single cell: coverageReport, exported to DIR)
  --matrix                        (preview a full matrix)
  --run                           (execute an inferred matrix without prompting)
  --fail-fast                     (stop matrix execution on first failure)
```

Examples:
```bash
# Run a single C++ gtest binary in ASan mode
./utils/run-containers-tests.sh --config=asan --gtest-task=elfparser_ut

# Use Docker via colima (recommended on macOS)
./utils/run-containers-tests.sh --container=docker --libc=glibc --jdk=21

# Preview selected JDKs across every supported libc/architecture pair
./utils/run-containers-tests.sh --libc=all --jdk=8,17,21 --arch=all

# Run all supported musl cells without an interactive prompt
./utils/run-containers-tests.sh --matrix --libc=musl --run

# Run all OpenJ9 cells
./utils/run-containers-tests.sh --matrix --jdk=j9 --run
```

Single-value commands run one container test configuration immediately. When any dimension expands to multiple cells, the script prints a compact status table first; interactive terminals ask for confirmation, while non-interactive runs require `--run` to execute. Matrix execution prints the status table again after all cells finish and writes summaries to `build/reports/container-matrix/summary.md` and `build/reports/container-matrix/summary.json`. Matrix gtest runs require a short `--gtest-task` name so the task follows each cell's configuration. Cells not run because of `--fail-fast` are reported as cancelled separately from unsupported cells that are skipped.

`--coverage-out=DIR` runs `:ddprof-lib:coverageReport -PenableCoverage` for one cell and replaces in `DIR` the reports (`reports/`, including the gcovr tracefile `reports/cpp/coverage.json`), the JaCoCo `.exec` files (`jacoco/`), the classes they were recorded against (`classes/`) and `cell.properties` (libc, arch, jdk, tests filter, commit, Gradle exit code). The export also runs when Gradle fails; the script still exits with Gradle's code, or with 70 when Gradle passed but the export failed. With `--coverage-out`, a `--tests` pattern must not contain quotes, `$`, backticks or backslashes. The script can run from a git worktree: it also mounts the main repository's git dir, read-only.

### `merge-coverage.sh`

Merges `--coverage-out` directories from several cells into one C++ report (gcovr `--add-tracefile`) and one Java report (JaCoCo CLI `merge` + `report`), plus `summary.md`. All cells and `--source-root` must be at the same commit. Needs `java`, `python3` and a gcovr at least as new as the containers' (an older one rejects their tracefiles); the JaCoCo CLI comes from `$JACOCO_CLI` or is downloaded from Maven Central with `curl` and checked against a pinned SHA-256. `--out` is replaced on each run, and `summary.md` marks which cells each report includes. The `test-coverage` skill drives the full Linux matrix and this merge.

```bash
./utils/merge-coverage.sh --source-root=. --out=build/coverage-merged cells/glibc-x64-21 cells/musl-aarch64-17
```

### `check-signal-reachability.py`

Static async-signal-safety check. Builds a call graph from the relocations of the debug object files (`objdump -dr`) and reports every function reachable from a signal handler or malloc hook that calls an unsafe symbol (heap allocation, locks, stdio, dynamic-loader calls, dynamic TLS, logging). The entry points, unsafe symbols and known findings are data lists at the top of the script. ELF objects only (Linux x64/aarch64); needs GNU `objdump` and `c++filt`.

**Usage:**
```bash
./utils/check-signal-reachability.py --obj-dir ddprof-lib/build/obj/main/debug [--allowlist <file>]
./utils/check-signal-reachability.py --self-test   # planted violations in utils/tests/signal-reachability-fixture.cpp
./gradlew :ddprof-lib:checkSignalReachability      # opt-in; SKIPPED when the debug objects are not ELF
```

Exit codes: `0` no findings outside the allowlist (or self-test passed), `1` new findings (one `<object>:<caller> -> <unsafe symbol> (via <path>)` line each), `2` usage/environment error. `--allowlist` replaces the built-in known findings; one entry per line: `<caller>[|<caller>...] -> <unsafe symbol>  # <JIRA-KEY>`.

### Source quality checks

Standalone, stdlib-only checks over the git-tracked files. Each prints one `<path>[:<line>]: <problem>` line per violation and exits `0` clean, `1` violations, `2` environment error; `--root` selects the checkout (default: the one containing the script).

| Script | Checks |
|---|---|
| `check-jvm-boundary-includes.py` | Shared code in `ddprof-lib/src/main/cpp` does not `#include "hotspot/"`, `"j9/"` or `"zing/"` headers (quoted or angle-bracket form), except the boundary files and the known exceptions (mirrors `doc/architecture/JvmSupportLayer.md#known-boundary-exceptions`). |
| `check-doc-index.py` | Every `doc/**/*.md` is linked from `doc/README.md` and has a PascalCase file name. |
| `check-sigsetjmp-shape.py` | Every `sigsetjmp()` has a `JmpCtxScope` in effect, `savemask` 1, and a landing pad that starts with `SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();` then `<scope>.restore();` (the `guards.h` pattern). The glibc cancellation buffer in `libraryPatcher_linux.cpp` is the one exception. |
| `check-tracked-artifacts.py` | No tracked path under `docs/sphinx/` or `.sphinx/`, and no `*.scratch*` path. |
| `check-copyright.py` | Source files the branch adds or modifies since `--base` (default: the PR base in CI, else `origin/main`) follow the `AGENTS.md` copyright rule. |
| `check-claude-md.py` | `CLAUDE.md` is the canonical redirect stub to `AGENTS.md`; `--write` restores it. |

`.githooks/pre-push` runs `check-copyright.py` and `check-claude-md.py` on every pushed branch commit, so a violation stops the push before CI sees it (see `review-marker.py` below for the trust model). Set `branch.<name>.gh-merge-base` for a branch stacked on another feature branch.

**Usage:**
```bash
./utils/check-doc-index.py                 # any one check
./gradlew :ddprof-lib:qualityChecks        # signal-reachability check (+ --self-test on Linux) plus all six; run by CI (ci.yml source-invariant-checks job)
```

CI runs every `utils/tests/*.sh` suite in the `script-tests` job of `.github/workflows/ci.yml`, with Node.js 22 for the Pi adapter cases.

### `patch-dd-java-agent.sh`

Patches a `dd-java-agent.jar` with a locally-built ddprof library for quick local testing without a full dd-trace-java rebuild.

**Usage:**
```bash
DD_AGENT_JAR=path/to/dd-java-agent.jar DDPROF_JAR=path/to/ddprof.jar \
  ./utils/patch-dd-java-agent.sh
```

---

## Upstream Tracking

See [README_UPSTREAM_TRACKER.md](README_UPSTREAM_TRACKER.md) for full documentation.

### `check_upstream_changes.sh`

Wrapper to compare local files against a given upstream async-profiler commit and produce a change report.

### `track_upstream_changes.sh`

Core change detection and report generation logic.

### `generate_tracked_files.sh`

Identifies which local files should be tracked against upstream (based on async-profiler copyright headers).

### `check_contribution_candidates.sh`

Identifies divergences from upstream async-profiler that could be contributed back.

### `find_contribution_candidates.sh`

Core diff analysis and report generation for contribution candidate detection.

---

## Review

### `review-marker.py`

Records that the agentic pre-PR review covered a branch, and checks it. Used by the `pre-pr-review` skill, `.githooks/pre-push` and the `require-fresh-review` hook, which runs in Claude Code (`.claude/hooks/`) and, through the thin adapter `.pi/extensions/require-fresh-review.ts`, in Pi. Pi loads project extensions only after project trust is granted.

- The marker certifies commits: `write` refuses uncommitted tracked changes and records the `git patch-id --verbatim` (git 2.39+) of the diff from the merge base to `HEAD`. An advancing base or a clean rebase keeps it fresh, unless the base changed lines next to the branch's hunks (context lines anchor each hunk's position, so this errs toward stale). Any change to the branch's diff, whitespace or position included, makes it stale. Untracked files are ignored.
- Markers live in `<git-common-dir>/review-markers/` (one file per branch, named by hash), shared by all worktrees and never committed.
- `install-hook` writes a shim to `<git-common-dir>/hooks/pre-push` that runs `.githooks/pre-push` as of `refs/remotes/origin/main`, which loads `review-marker.py` from the same ref; the Claude Code hook loads it from there too. All run with `python3 -I`, so files in the checkout, which may be an untrusted branch (e.g. a fork PR), are not executed or imported. When that ref lacks the scripts (the gate is not merged yet, or there is no `origin` remote), both hooks allow everything. Out of scope: Claude Code runs `.claude/` hooks from the session's own checkout under its workspace-trust model. It never sets `core.hooksPath`, which would replace global hooks such as Datadog's secret scanner; those chain to `.git/hooks`.
- The same shim also runs `check-copyright.py` and `check-claude-md.py` from that ref (see Source quality checks).
- For `gh pr create`, the Claude Code hook also runs `.github/scripts/check_pr_ticket.py` from that ref on the PR title and body; a command it cannot judge passes, and the CI `PR ticket reference` workflow checks it.
- Exit codes: 0 fresh, written or installed; 1 missing or stale; 2 usage or environment error (e.g. missing base ref, git older than 2.39).
- Known limits, all accepted:
  - An edit moved between two places whose surrounding lines are identical keeps the same digest, because hunk positions are left out so that rebases stay fresh.
  - A fresh marker skips the network, so `pre-push` does not notice an open PR retargeted to a base other than the marker's.
  - A branch pushed under another name (`git push origin fix:topic`) is found by `pre-push` but not by `gh pr ready`, which blocks rather than allows.

**Usage:**
```bash
git show refs/remotes/origin/main:utils/review-marker.py | python3 -I - install-hook   # once per clone
./utils/review-marker.py write --tool sphinx --session <id> --base origin/main
./utils/review-marker.py check                                   # current branch
./utils/review-marker.py check --branch <b> --commit <sha>       # as pre-push does
bash utils/tests/test_review_marker.sh                           # tests
```

### `gradle-command-policy.py`

Denies shell commands that run `gradlew` directly instead of through `.claude/commands/build-and-summarize`, except `gradlew --stop` and `gradlew --version`. Reads the command on stdin; exit 2 with the reason on stderr denies it. The `require-gradle-wrapper` hook runs it in Claude Code (`.claude/hooks/`) and, through `.pi/extensions/require-gradle-wrapper.ts`, in Pi.

- The hook loads the policy from `refs/remotes/origin/main` with `python3 -I`, like `review-marker.py`, and allows everything when that ref lacks it.
- Deny by default: the command is split into simple commands at `;`, `&`, `|`, parentheses, braces, backticks and newlines, and any simple command that names `gradlew` is denied unless it starts with a read-only tool (`cat`, `grep`, `git`, `ls`, `find`, `echo`, ...). Quoted scripts such as `bash -c '...'` are checked the same way. So `if ./gradlew test`, `env -u X ./gradlew build` and `> log ./gradlew build` are denied without listing each prefix.
- Accepted false blocks: a non-reader command that only names the file, such as `mv gradlew gradlew.old`, and heredoc lines that start with `./gradlew`.
- Not covered: indirection such as `G=./gradlew; $G build`, a system `gradle`, and allowed tools that run their arguments, such as `find . -exec ./gradlew build \;`, an `awk -f` script that calls `system()`, or a git alias. The hook stops accidental direct runs, not deliberate ones.

**Usage:**
```bash
echo './gradlew build' | python3 utils/gradle-command-policy.py   # exit 2
bash utils/tests/test_gradle_hook.sh                              # tests
```

---

## CI / Ops

### `update-sonatype-credentials.sh`

Updates the Sonatype (Maven Central) OSSRH credentials stored in AWS SSM, used by the CI publish pipeline.

**Prerequisites:**
- AWS CLI authenticated with `ssm:PutParameter` permission

**Usage:**
```bash
./utils/update-sonatype-credentials.sh <username> <token>
```
