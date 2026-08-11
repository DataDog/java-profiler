<!-- Copyright 2026, Datadog, Inc -->

# Tag-Based Versioning

## Problem

The current versioning system stores the development version as a hardcoded
line in `build.gradle.kts` (`version = "1.49.0-SNAPSHOT"`). Every release
requires a post-release "bump PR" that modifies this line to the next
snapshot version. This bump PR is auto-approved via a complex STS/gated-merge
pipeline (`validate-release-bump.sh`, `wait-release-bump.sh`,
`approve-trivial.yml`, `release-bump-ci`). Under new GitHub restrictions on
auto-approved PRs, this pipeline fails constantly.

## Goal

Eliminate the stored version and the bump-PR pipeline entirely. Compute the
version at build time from git tags. Releases create only a tag (and a release
branch for minor/major). The next build automatically sees the new tag and
computes the next snapshot — no file modifications, no PRs.

## Version Computation Rules

| Branch type | Most recent reachable tag | Computed version |
|---|---|---|
| `main` | `v_X.Y.Z` | `X.(Y+1).0-SNAPSHOT` |
| `release/X.Y._` | `v_X.Y.Z` | `X.Y.(Z+1)-SNAPSHOT` |
| Feature branch | (same as its base) | snapshot + `-<branch>-SNAPSHOT` suffix |
| Tag commit `v_X.Y.Z` | itself | `X.Y.Z` (release version, no snapshot) |

"Most recent reachable tag" = the tag with the highest semver that is an
ancestor of (or equal to) HEAD, found via `git tag --merged HEAD` filtered to
`v_*` and sorted by version using `sort -V` (version sort, not lexical sort).
This is critical: `sort -V` correctly orders `v_1.9.0` before `v_1.10.0`,
whereas plain `sort` would not.

### Major releases

A major release from `main` with most recent tag `v_1.49.0`:
- Release version: `2.0.0` (major bump of the tag)
- Tag `v_2.0.0` is created on HEAD
- Release branch `release/2.0._` is created
- Next build from `main` sees `v_2.0.0` → computes `2.1.0-SNAPSHOT`

### Minor releases

A minor release from `main` with most recent tag `v_1.49.0`:
- Release version: `1.50.0` (minor bump of the tag)
- Tag `v_1.50.0` is created on HEAD
- Release branch `release/1.50._` is created
- Next build from `main` sees `v_1.50.0` → computes `1.51.0-SNAPSHOT`

### Patch releases

A patch release from `release/1.48._` with most recent tag `v_1.48.2`:
- Release version: `1.48.3` (patch bump of the tag)
- Tag `v_1.48.3` is created on HEAD
- Next build from `release/1.48._` sees `v_1.48.3` → computes `1.48.4-SNAPSHOT`

### First patch on a new release branch

After a minor release creates `v_1.50.0` and `release/1.50._`, the first patch
from `release/1.50._`:
- Most recent reachable tag: `v_1.50.0`
- Computed snapshot: `1.50.1-SNAPSHOT`
- Release version: `1.50.1` (strip snapshot)
- Tag `v_1.50.1` created on HEAD

This is identical to any subsequent patch — no special "first patch" logic
needed, because the version is always computed from tags, not from a stored
`.0` base.

## Architecture

### Single source of truth: `utils/compute-version.sh`

A standalone shell script that computes the version from git tags. It is:
- Sourced/called by CI scripts (`includes.sh`, `prepare.sh`, `release.sh`)
- Called by Gradle at configuration time (via `exec`) for local and CI builds
- Independently testable

**Interface:**
```
utils/compute-version.sh [--release] [--major] [--minor] [--patch] [--branch-suffix <branch>]
```
- No flags: print the current snapshot version for HEAD
- `--release`: print the release version (strip `-SNAPSHOT`, apply bump)
- `--major`/`--minor`/`--patch`: override the bump type for `--release`
- `--branch-suffix <branch>`: append `-<branch>-SNAPSHOT` for non-main,
  non-release branches (replaces the ad-hoc suffix logic in `includes.sh`)

**Output:** single line to stdout: `X.Y.Z` or `X.Y.Z-SNAPSHOT` or
`X.Y.Z-<branch>-SNAPSHOT`. Exit 1 on error (no tags found, ambiguous state).

**Branch detection:** The script detects the current branch from
`git rev-parse --abbrev-ref HEAD` (or `CI_COMMIT_BRANCH` / `GITHUB_REF_NAME`
in CI). For `main`, it applies minor bump. For `release/X.Y._`, it extracts
X.Y and applies patch bump. For other branches, it applies the same bump as
the branch's base (main → minor) and appends the branch suffix.

### Gradle integration

`build.gradle.kts`:
- Remove `version = "1.49.0-SNAPSHOT"` hardcoded line
- Remove `com.dipien.semantic-version` plugin and buildscript classpath
- Remove `apply(plugin = "com.dipien.semantic-version")`
- Compute version at configuration time:
  ```kotlin
  val computedVersion = providers.exec {
    commandLine(rootProject.layout.projectDirectory.file("utils/compute-version.sh").asFile.absolutePath)
  }.standardOutput.asText.get().trim()
  version = findProperty("ddprof_version") as? String ?: computedVersion
  ```
- The `-Pddprof_version` override remains for CI jobs that need to force a
  specific version (e.g., tag builds where `CI_COMMIT_TAG` is set).

**Shallow clone handling:** The `providers.exec` call runs on every Gradle
configuration. GitHub Actions CI workflows (`ci.yml`, `test_workflow.yml`,
`nightly.yml`, `codecheck.yml`) currently use shallow `actions/checkout`
(default `fetch-depth: 1`). On a shallow clone, `git tag --merged HEAD` may
return incomplete results. **All GitHub Actions workflows that invoke Gradle
must set `fetch-depth: 0`.** This is a required change — the script will
exit 1 if no tags are reachable, failing the build loudly rather than
silently producing a wrong version. The list of workflows requiring
`fetch-depth: 0`:
- `.github/workflows/ci.yml` (all checkout steps)
- `.github/workflows/test_workflow.yml` (all checkout steps)
- `.github/workflows/nightly.yml`
- `.github/workflows/codecheck.yml`
- `.github/workflows/cache_java.yml`

GitLab CI does full clones, so no changes needed there.

### Files removed

- `gradle/scm.gradle`
- `gradle/semantic-version.gradle`
- `com.dipien:semantic-version-gradle-plugin` dependency
- `.github/scripts/validate-release-bump.sh`
- `.github/scripts/wait-release-bump.sh`
- `.github/chainguard/self.release-bump.label-pr.sts.yaml`

### Files removed or heavily simplified (release automation)

- `.github/workflows/approve-trivial.yml` — **simplified** (remove release-bump
  validation path and the `release_bump` classification step; keep only generic
  trivial-PR approval for dependabot). The `self.approve-trivial.approve-pr.sts.yaml`
  STS policy is **kept unchanged** — it remains valid for dependabot PRs.
- `.github/workflows/ci.yml` — remove `release-bump-ci` job AND remove
  `validate-release-bump.sh` / `wait-release-bump.sh` from the
  `release-automation-tests` job's `bash -n` / `shellcheck` / execution list
  (lines 38-48). If these removed scripts are still listed, every PR's CI fails.
- `.github/scripts/tests/test_release_automation.sh` — **rewritten** for new flow

### Files modified

- `build.gradle.kts` — compute version dynamically, remove dipien plugin
- `ddprof-lib/build.gradle.kts` — `componentVersion` already falls back to
  `version.toString()`, so it picks up the computed root version automatically.
  No change needed.
- `malloc-shim/build.gradle.kts` — has its own hardcoded `version = "0.1"`
  (line 18). This is **intentional and unrelated** to the profiler version.
  The `PROFILER_VERSION` macro in malloc-shim uses `project.version` which is
  `0.1` — this is pre-existing behavior and is **not changed**. The profiler's
  own `PROFILER_VERSION` comes from `ddprof-lib`'s `componentVersion` which
  inherits the root version. No change needed.
- `.gitlab/scripts/includes.sh` — `get_version()` calls `compute-version.sh`
  instead of `./gradlew printVersion`. **The branch-suffix logic (lines 20-26)
  is removed** — `compute-version.sh --branch-suffix` handles this internally
  and correctly skips the suffix for `release/*` branches (the current code
  incorrectly appends a suffix for release branches).
- `.github/scripts/release.sh` — eliminate bump PR flow; just compute, tag,
  create branch, push
- `.github/workflows/release-validated.yml` — eliminate bump PR steps, STS
  label token, wait step, and all `bump_*` outputs. The `validate-inputs` job
  switches from `./gradlew printVersion` to `compute-version.sh --release`.
- `utils/release.sh` — update usage text and flow description to remove
  bump-PR references
- `utils/README.md` — update to remove bump-PR flow description
- `.github/workflows/ci.yml` — add `fetch-depth: 0` to all checkout steps
- `.github/workflows/test_workflow.yml` — add `fetch-depth: 0` to all checkout steps
- `.github/workflows/nightly.yml` — add `fetch-depth: 0`
- `.github/workflows/codecheck.yml` — add `fetch-depth: 0`
- `.github/workflows/cache_java.yml` — add `fetch-depth: 0`

### Files unchanged

- `.github/workflows/gh_release.yml` — already tag-triggered, no changes
- `.github/workflows/update_assets.yml` — already tag-triggered, no changes
- `.github/workflows/increment-milestones-on-tag.yaml` — already tag-based
- `.github/workflows/create-next-milestone.yaml` — already tag-based
- `.github/workflows/dependabot-automerge.yml` — unrelated
- `.github/chainguard/self.approve-trivial.approve-pr.sts.yaml` — kept for dependabot
- `build-logic/` — `PROFILER_VERSION` macro flows from `nativeBuild.version`
  which is set from `componentVersion` → root `version`. No changes needed.

## Release Flow (New)

### GitLab trigger mechanism

The GitLab pipeline is triggered by both branch pushes and tag pushes (GitLab
mirrors the GitHub repo). The build-deploy pipeline's `prepare:start` job
runs `when: always` for any push. The `build-artifact` and `deploy-artifact`
jobs use `.skip-on-release` which skips only on `release/*` branches — on a
tag build, `CI_COMMIT_BRANCH` is empty, so these jobs **do run**. The
`get_version()` function short-circuits on `CI_COMMIT_TAG` to return the tag
version. Therefore: **a tag push alone is sufficient to trigger the full
build-and-publish pipeline on GitLab.** No branch push is needed for the
build to happen.

### Minor release from main

1. Operator runs `utils/release.sh minor` (or triggers workflow_dispatch)
2. `release.sh`:
   - Validates branch is `main`
   - Calls `compute-version.sh --release --minor` → `1.50.0`
   - Checks `v_1.50.0` tag doesn't already exist
   - Creates annotated tag `v_1.50.0` on HEAD
   - Creates branch `release/1.50._` from HEAD
   - Pushes tag + branch (`git push --atomic origin v_1.50.0 release/1.50._`)
3. Tag push triggers `gh_release.yml` (draft GitHub release)
4. Tag push triggers GitLab pipeline → `get_version()` returns `1.50.0` →
   artifacts built and published as `1.50.0`
5. Next build from `main` → `compute-version.sh` → `1.51.0-SNAPSHOT`

**No bump PR. No file modification. No STS approval. No wait loop.**

### Patch release from release/1.48._

1. Operator runs `utils/release.sh patch`
2. `release.sh`:
   - Validates branch is `release/X.Y._`
   - Calls `compute-version.sh --release --patch` → `1.48.3`
   - Checks `v_1.48.3` tag doesn't already exist
   - Creates annotated tag `v_1.48.3` on HEAD
   - Pushes tag (`git push origin v_1.48.3`)
3. Tag push triggers GitLab pipeline → `get_version()` returns `1.48.3` →
   artifacts built and published as `1.48.3`
4. Next build from `release/1.48._` → `compute-version.sh` → `1.48.4-SNAPSHOT`

No branch push needed — the tag push alone triggers the GitLab build pipeline.

### Major release from main

1. Operator runs `utils/release.sh major`
2. `release.sh`:
   - Validates branch is `main`
   - Calls `compute-version.sh --release --major` → `2.0.0`
   - Creates annotated tag `v_2.0.0` on HEAD
   - Creates branch `release/2.0._` from HEAD
   - Pushes tag + branch
3. Next build from `main` sees `v_2.0.0` → `2.1.0-SNAPSHOT`

**No special "major release commit off main" logic needed** — there's no
file to modify, so the tag goes directly on main's HEAD. The release branch
points to the same commit. Main is not polluted because there's no release
commit.

### Retag

Unchanged from current behavior: re-points an existing tag at the current HEAD
of a release branch. No version computation needed (uses the existing tag name).

### Release completion signal

The current system's bump-PR-merge was the completion signal that a release
finished. Removing it eliminates that cross-check. **The new completion signal
is the GitLab pipeline success for the tag build.** The operator monitors the
GitLab pipeline triggered by the tag push. If it fails, the release is
incomplete and the operator re-triggers the pipeline (not the release script).
The `update_assets.yml` workflow already polls Maven Central for the artifact
and only completes when the artifact is available — this serves as the
cross-check that artifacts were published.

## `get_previous_version` for benchmarks

The current `get_previous_version()` in `includes.sh` (lines 33-39) returns:
- `LOOKBACK=1` (last tag) when the current version is a snapshot
- `LOOKBACK=2` (second-to-last tag) when the current version is a release

Benchmark jobs run on branch builds (not tag builds), where the current
version is always a snapshot. So `LOOKBACK=1` → returns the last tag, which
is the last released version. **This behavior is correct and does not
change.** The function continues to work because:
- On branch builds: `get_current_version` returns a snapshot → `LOOKBACK=1`
  → last tag = last release = correct baseline
- On tag builds: `get_current_version` returns the tag version (non-snapshot)
  → `LOOKBACK=2` → second-to-last tag = previous release (benchmarks never
  run on tag builds, so this path is unused but harmless)

The only change to `includes.sh` is that `get_version()` calls
`compute-version.sh` instead of `./gradlew printVersion`, and the branch-suffix
block is removed (replaced by `compute-version.sh --branch-suffix`).

## Edge Cases

### No tags reachable from HEAD

`compute-version.sh` exits 1 with an error. This should only happen on a fresh
repo with no tags. The initial tag must be created manually once.

### Detached HEAD / CI tag builds

When `CI_COMMIT_TAG` is set (GitLab tag build), `get_version()` short-circuits
to return the tag version. This path is preserved in `includes.sh`.

### Version overflow (minor >= 99, patch >= 99)

`compute-version.sh` handles rollover: minor 99 → major+1, minor 0, patch 0.
Same for patch 99 → minor+1, patch 0. This matches the current fake `gradlew`
in the test suite. Patch-99 rollover on a release branch producing a minor
version (e.g., `1.48.99` → `1.49.0`) is a theoretical edge case that is
unlikely in practice and would be caught by the tag-exists check.

### PROFILER_VERSION C++ macro

The native code embeds `PROFILER_VERSION` as a string at compile time. This
flows from `build.gradle.kts` `version` → `ddprof-lib` `componentVersion` →
`nativeBuild.version` → `-DPROFILER_VERSION="..."` compiler flag. Since the
version is computed at Gradle configuration time (before any compile task),
the macro will always reflect the computed version. No changes needed to
`build-logic/` or C++ code. `malloc-shim` has its own `version = "0.1"` which
is unrelated and unchanged.

### In-flight bump PRs at migration time

If a release is mid-flight (tag created, bump PR open) when the new code
ships, the bump PR is orphaned. **Migration plan:** merge the new code only
when no bump PRs are in flight. The last release before migration must have
its bump PR merged (or manually closed) first. After migration, any orphaned
`automated/bump-*` branches can be deleted manually. The `approve-trivial.yml`
workflow will no longer classify them as release bumps, so they would be
treated as generic trivial PRs (which is harmless — they'd be approved and
merged, but the version line they modify is now ignored).

## Implementation Stages

The work is broken into stages. Each stage is independently testable and
committable, but the final PR contains all stages.

### Stage 1: Version computation script

- Create `utils/compute-version.sh`
- Comprehensive unit tests in `utils/tests/test_compute_version.sh`
- Does NOT touch any existing files yet
- Can be tested in isolation

### Stage 2: Gradle integration + shallow clone fixes

- Modify `build.gradle.kts` to compute version dynamically
- Remove dipien plugin, `gradle/scm.gradle`, `gradle/semantic-version.gradle`
- Remove hardcoded `version = "..."` line
- Add `fetch-depth: 0` to all GitHub Actions checkout steps
- Verify `ddprof-lib` and `malloc-shim` pick up the computed version
- Verify `PROFILER_VERSION` macro still works
- Local build verification

### Stage 3: GitLab CI integration

- Modify `.gitlab/scripts/includes.sh` `get_version()` to call
  `compute-version.sh`
- Remove the branch-suffix block from `get_version()` (replaced by
  `compute-version.sh --branch-suffix`)
- `get_previous_version()` is unchanged (still works correctly)
- Verify `prepare.sh`, `build.sh`, `deploy.sh`, `stresstests.sh` still work

### Stage 4: Release script rewrite

- Rewrite `.github/scripts/release.sh` to eliminate bump PR flow
- Simplify `.github/workflows/release-validated.yml` to remove bump PR steps,
  STS label token, wait step, and `bump_*` outputs
- Remove `validate-release-bump.sh`, `wait-release-bump.sh`
- Remove `self.release-bump.label-pr.sts.yaml`
- Simplify `approve-trivial.yml` (remove release-bump validation path)
- Remove `release-bump-ci` job from `ci.yml` AND remove deleted scripts from
  `release-automation-tests` job's `bash -n`/`shellcheck` list
- Update `utils/release.sh` and `utils/README.md`

### Stage 5: Test rewrite

- Rewrite `.github/scripts/tests/test_release_automation.sh` for the new flow
- New tests: tag creation, branch creation, version computation after release
- Remove all bump-PR-specific test scenarios

### Stage 6: Cleanup and documentation

- Remove `utils/finalize-release-bump.sh` if it still exists (test asserts
  it doesn't)
- Update any remaining references to the old versioning system
- Final verification of all CI workflows
