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
2. For patch releases, offers to run `prepare-patch.sh` to backport pending
   main PRs onto the release branch first; if you accept, the script exits
   so you can merge the resulting PR and re-run
3. Interactive commit selection (or use `--commit`)
4. Triggers GitHub Actions "Validated Release" workflow
5. Workflow runs pre-release tests, creates the annotated tag, and opens an
   exact single-commit version-bump PR as `github-actions[bot]`
6. The final commit is pushed through the release SSH identity, producing the
   `synchronize` event that starts normal PR CI even though `GITHUB_TOKEN`
   created the PR
7. A separate `dd-octo-sts[bot]` identity adds `trivial`; the approval workflow
   validates permissions, refs, SHAs, and the exact one-line version diff before
   approving that exact commit
8. The release workflow waits for the exact approval and the aggregate
   `release-bump-ci` check, then performs the SHA-locked squash merge itself
9. Tag push triggers GitLab, which publishes the Maven artifacts, and the
   GitHub release workflows attach the release assets

For a major release, the generated `N.0.0` commit remains on
`release/N.0._` and is tagged there. The bump PR moves `main` directly from
its recorded source commit to `N.1.0`; the workflow never pushes a generated
commit directly to protected `main`.

A new release branch initially remains at its tagged `X.Y.0` minor version.
The first patch creates and tags an `X.Y.1` release commit, then opens the
validated bump PR for `X.Y.2-SNAPSHOT`. Later patches release the untagged
development version left by the preceding bump PR. An already-tagged patch
version greater than zero is rejected because it means that preceding bump PR
did not merge.

The repository's Actions settings must allow GitHub Actions to create and
approve pull requests. A dry run never creates a PR, adds a label, requests
approval, or merges anything.

### Testing release automation

`.github/scripts/tests/test_release_automation.sh` is a single hermetic shell
test. It validates success,
authorization failures, fork/bot PRs, malformed or extra diffs, version
rollovers, merge commits, and stale SHAs using temporary local fixtures. Its
fixture mode does not load credentials or invoke `gh`, so it cannot publish,
tag, push, create a PR, approve, or merge anything remotely.

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

---

## Testing

### `run-containers-tests.sh`

Runs tests in containers across various OS/libc/JDK combinations, mirroring the CI matrix locally. Defaults to Podman; use `--container=docker` to use Docker.

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
  --matrix                        (preview a full matrix)
  --run                           (execute an inferred matrix without prompting)
  --fail-fast                     (stop matrix execution on first failure)
```

Examples:
```bash
# Run a single C++ gtest binary in ASan mode
./utils/run-containers-tests.sh --config=asan --gtest-task=elfparser_ut

# Use Docker instead of the default Podman runtime
./utils/run-containers-tests.sh --container=docker --libc=glibc --jdk=21

# Preview selected JDKs across every supported libc/architecture pair
./utils/run-containers-tests.sh --libc=all --jdk=8,17,21 --arch=all

# Run all supported musl cells without an interactive prompt
./utils/run-containers-tests.sh --matrix --libc=musl --run

# Run all OpenJ9 cells
./utils/run-containers-tests.sh --matrix --jdk=j9 --run
```

Single-value commands run one container test configuration immediately. When any dimension expands to multiple cells, the script prints a compact status table first; interactive terminals ask for confirmation, while non-interactive runs require `--run` to execute. Matrix execution prints the status table again after all cells finish and writes summaries to `build/reports/container-matrix/summary.md` and `build/reports/container-matrix/summary.json`. Matrix gtest runs require a short `--gtest-task` name so the task follows each cell's configuration. Cells not run because of `--fail-fast` are reported as cancelled separately from unsupported cells that are skipped.

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

## CI / Ops

### `update-sonatype-credentials.sh`

Updates the Sonatype (Maven Central) OSSRH credentials stored in AWS SSM, used by the CI publish pipeline.

**Prerequisites:**
- AWS CLI authenticated with `ssm:PutParameter` permission

**Usage:**
```bash
./utils/update-sonatype-credentials.sh <username> <token>
```
