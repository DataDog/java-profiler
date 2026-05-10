# Utility Scripts

This directory contains utility scripts for managing the java-profiler project.

---

## Release

### `release.sh`

Triggers the Validated Release workflow using GitHub CLI to create a new release.

**Prerequisites:**
- [GitHub CLI](https://cli.github.com/) installed and authenticated
- Git repository is up to date
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
2. Interactive commit selection (or use `--commit`)
3. Triggers GitHub Actions "Validated Release" workflow
4. Workflow runs pre-release tests, creates annotated git tag
5. Tag push triggers GitLab build pipeline
6. GitLab builds multi-platform artifacts and publishes to Maven Central
7. GitHub workflows create release with assets

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

---

## Testing

### `run-docker-tests.sh`

Runs tests in Docker across various OS/libc/JDK combinations, mirroring the CI matrix locally.

**Usage:**
```bash
./utils/run-docker-tests.sh [options]
  --libc=glibc|musl               (default: glibc)
  --jdk=8|11|17|21|25|8-j9|...   (default: 21)
  --arch=x64|aarch64              (default: auto-detect)
  --config=debug|release|asan|tsan (default: debug)
  --tests="TestPattern"           (optional)
  --gtest                         (enable C++ gtests)
  --shell                         (drop to shell instead of running tests)
  --mount                         (mount local repo instead of cloning)
  --rebuild                       (force rebuild of Docker images)
```

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
