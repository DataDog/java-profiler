# Implementation Plan: Tag-Based Versioning

Reference: [TagBasedVersioning.md](TagBasedVersioning.md) for design rationale.

Each stage produces a commit. All commits land in one PR.

---

## Stage 1: Version computation script

### Files created
- `utils/compute-version.sh`
- `utils/tests/test_compute_version.sh`

### `utils/compute-version.sh` specification

**Shebang:** `#!/usr/bin/env bash`, `set -euo pipefail`

**Arguments:**
```
--release          Print release version (strip -SNAPSHOT, apply bump)
--major            Bump major (for --release)
--minor            Bump minor (for --release)
--patch            Bump patch (for --release)
--branch-suffix <branch>  Append -<branch>-SNAPSHOT for non-main, non-release
--help             Print usage
```

**Algorithm:**

1. Parse arguments. Default mode: snapshot (no `--release`).

2. Detect current branch:
   - `${CI_COMMIT_BRANCH:-}` (GitLab) → use if non-empty
   - `${GITHUB_REF_NAME:-}` (GitHub Actions) → use if non-empty and not a tag ref
   - `git rev-parse --abbrev-ref HEAD` → fallback
   - If HEAD is a tag (detached, `CI_COMMIT_TAG` set or `git describe --exact-match`), print the tag version and exit.

3. Find most recent reachable tag:
   ```bash
   latest_tag=$(git tag --merged HEAD --list 'v_*' | sed 's/^v_//' | sort -V | tail -1)
   ```
   If empty → exit 1 with error "no version tags found".

4. Parse tag into major.minor.patch:
   ```bash
   IFS=. read -r major minor patch <<<"$latest_tag"
   ```

5. Determine bump type:
   - If `--release` with explicit `--major`/`--minor`/`--patch` → use that
   - If `--release` without explicit bump:
     - Branch is `main` → minor bump
     - Branch matches `release/X.Y._` → patch bump
     - Other branches → minor bump (same as main, plus suffix)
   - If not `--release` (snapshot mode):
     - Branch is `main` → minor bump → `X.(Y+1).0-SNAPSHOT`
     - Branch matches `release/X.Y._` → patch bump → `X.Y.(Z+1)-SNAPSHOT`
     - Other branches → minor bump → `X.(Y+1).0-<branch>-SNAPSHOT`

6. Apply bump with rollover:
   - minor: if minor >= 99 → major+1, minor=0, patch=0; else minor+1, patch=0
   - patch: if patch >= 99 → minor+1, patch=0 (with minor rollover); else patch+1
   - major: major+1, minor=0, patch=0

7. Assemble version string:
   - `--release` → `major.minor.patch` (no suffix)
   - snapshot, main/release → `major.minor.patch-SNAPSHOT`
   - snapshot, other branch with `--branch-suffix` → `major.minor.patch-<sanitized_branch>-SNAPSHOT`

8. Print to stdout, exit 0.

**Branch sanitization for suffix:** replace `/` with `_` (matches current `includes.sh` behavior).

**Tag detection on detached HEAD:** If `CI_COMMIT_TAG` is set and matches `v_X.Y.Z`, strip `v_` and print `X.Y.Z` directly. No bump.

### `utils/tests/test_compute_version.sh` specification

Hermetic test using a temp git repo. Test groups:

1. **No tags → exit 1**
2. **Tag on HEAD, no flags → release version** (tag `v_1.48.0` on HEAD, branch `main` → `1.49.0-SNAPSHOT`)
3. **Tag on HEAD, `--release --minor` → `1.49.0`**
4. **Tag on HEAD, `--release --major` → `2.0.0`** (from `v_1.49.0`)
5. **Tag on HEAD, `--release --patch` → `1.48.1`** (from `v_1.48.0` on `release/1.48._`)
6. **Release branch patch bump** (branch `release/1.48._`, tag `v_1.48.2` → `1.48.3-SNAPSHOT`)
7. **Release branch first patch** (branch `release/1.50._`, tag `v_1.50.0` → `1.50.1-SNAPSHOT`)
8. **Feature branch suffix** (branch `feat/foo`, tag `v_1.49.0`, `--branch-suffix feat/foo` → `1.50.0-feat_foo-SNAPSHOT`)
9. **Minor rollover** (tag `v_1.99.0` → `2.0.0-SNAPSHOT`)
10. **Patch rollover** (tag `v_1.48.99` on `release/1.48._` → `1.49.0-SNAPSHOT`)
11. **Multiple tags, highest wins** (tags `v_1.48.0`, `v_1.48.2`, `v_1.50.0` on main → `1.51.0-SNAPSHOT`)
12. **Tag not reachable from HEAD is ignored** (tag `v_1.99.0` on a different branch → not used)
13. **`CI_COMMIT_TAG` short-circuit** (env `CI_COMMIT_TAG=v_1.48.3` → prints `1.48.3`)
14. **Sort correctness** (tags `v_1.9.0`, `v_1.10.0` → `v_1.10.0` wins, not `v_1.9.0`)

### Verification
```bash
bash utils/tests/test_compute_version.sh
```

### Commit
`Add tag-based version computation script`

---

## Stage 2: Gradle integration + shallow clone fixes

### Files modified
- `build.gradle.kts`
- `.github/workflows/ci.yml`
- `.github/workflows/test_workflow.yml`
- `.github/workflows/nightly.yml`
- `.github/workflows/codecheck.yml`
- `.github/workflows/cache_java.yml`

### Files removed
- `gradle/scm.gradle`
- `gradle/semantic-version.gradle`

### `build.gradle.kts` changes

Remove from `buildscript` block:
```kotlin
classpath("com.dipien:semantic-version-gradle-plugin:2.0.0")
```

Remove:
```kotlin
version = "1.49.0-SNAPSHOT"
apply(plugin = "com.dipien.semantic-version")
version = findProperty("ddprof_version") as? String ?: version
```

Add (after the `plugins` block, before `allprojects`):
```kotlin
val computedVersion = providers.exec {
  commandLine(rootProject.layout.projectDirectory.file("utils/compute-version.sh").asFile.absolutePath)
}.standardOutput.asText.get().trim()

version = findProperty("ddprof_version") as? String ?: computedVersion
```

### Shallow clone fixes

For each listed workflow, add `fetch-depth: 0` to every `actions/checkout` step:
```yaml
- uses: actions/checkout@3d3c42e5aac5ba805825da76410c181273ba90b1 # v7.0.1
  with:
    fetch-depth: 0
```

Workflows and checkout step line numbers (approximate, verify before editing):
- `ci.yml`: lines 29, 77, 118, 217, 268
- `test_workflow.yml`: lines 65, 228, 367, 546
- `nightly.yml`: line 40
- `codecheck.yml`: lines 24, 75
- `cache_java.yml`: lines 154, 213, 265, 322

### Verification
```bash
./gradlew printVersion 2>&1 | head  # should fail - no printVersion task
./gradlew help  # should succeed, version computed from tags
```
Verify `PROFILER_VERSION` macro: `./gradlew :ddprof-lib:assembleDebugJar` then check the compiled `.so` or JAR metadata.

### Commit
`Replace stored version with tag-based computation`

---

## Stage 3: GitLab CI integration

### Files modified
- `.gitlab/scripts/includes.sh`

### `.gitlab/scripts/includes.sh` changes

**`get_version()` rewrite:**

Replace the `./gradlew printVersion` path with:
```bash
function get_version() {
  rm -f .version

  if [[ "${CI_COMMIT_TAG}" =~ ^v_[0-9.]+(-SNAPSHOT)?$ ]]; then
    echo "${CI_COMMIT_TAG//v_/}"
    return
  fi

  local branch="${CI_COMMIT_BRANCH:-${CI_COMMIT_REF_NAME:-}}"
  local version
  if [ -n "$branch" ] && [ "$branch" != "${CI_DEFAULT_BRANCH:-main}" ] && [ "$branch" != "main" ] && [[ ! "$branch" =~ ^release/ ]]; then
    version=$(utils/compute-version.sh --branch-suffix "$branch")
  else
    version=$(utils/compute-version.sh)
  fi

  if [ -z "$version" ]; then
    echo "ERROR: Failed to determine version from compute-version.sh" >&2
    return 1
  fi
  echo "$version"
}
```

This removes:
- The `./gradlew printVersion` invocation
- The ad-hoc branch-suffix `sed` logic (lines 20-26) that incorrectly suffixed release branches

`get_current_version()` and `get_previous_version()` are unchanged — they call `get_version()` which now uses `compute-version.sh`.

### Verification
- `bash .gitlab/scripts/tests/includes_test.sh` (existing test)
- Manual: simulate `CI_COMMIT_BRANCH=main` and verify output matches `compute-version.sh`

### Commit
`Use compute-version.sh in GitLab CI`

---

## Stage 4: Release script rewrite

### Files modified
- `.github/scripts/release.sh`
- `.github/workflows/release-validated.yml`
- `.github/workflows/approve-trivial.yml`
- `.github/workflows/ci.yml`
- `utils/release.sh`
- `utils/README.md`

### Files removed
- `.github/scripts/validate-release-bump.sh`
- `.github/scripts/wait-release-bump.sh`
- `.github/chainguard/self.release-bump.label-pr.sts.yaml`

### `.github/scripts/release.sh` rewrite

The new release script is dramatically simpler. No bump PRs, no file modifications, no STS tokens, no wait loop.

**Structure:**
```bash
#!/usr/bin/env bash
set -euo pipefail

TYPE=$1        # MINOR | MAJOR | PATCH | RETAG
DRYRUN=${2:-}

BRANCH=$(git branch --show-current)
SOURCE_SHA=$(git rev-parse HEAD)
RELEASE_BRANCH=

# Compute release version
if [ "$TYPE" == "RETAG" ]; then
  # ... existing retag logic, unchanged ...
  exit 0
fi

# Validate branch
if [ "$TYPE" == "PATCH" ]; then
  [[ $BRANCH =~ ^release/[0-9]+\.[0-9]+\._$ ]] || { echo "error"; exit 1; }
  RELEASE_VERSION=$(utils/compute-version.sh --release --patch)
else
  [ "$BRANCH" == "main" ] || { echo "error"; exit 1; }
  if [ "$TYPE" == "MAJOR" ]; then
    RELEASE_VERSION=$(utils/compute-version.sh --release --major)
  else
    RELEASE_VERSION=$(utils/compute-version.sh --release --minor)
  fi
fi

RELEASE_BRANCH="release/${RELEASE_VERSION%.*}._"

# Check tag doesn't exist
if git rev-parse "v_${RELEASE_VERSION}" >/dev/null 2>&1; then
  echo "::error::Tag v_${RELEASE_VERSION} already exists"
  exit 1
fi

# Create annotated tag
git tag -a "v_${RELEASE_VERSION}" -m "Release v_${RELEASE_VERSION} (${TYPE,,}) from ${BRANCH}"

# Create release branch (minor/major only)
if [ "$TYPE" != "PATCH" ]; then
  git branch "$RELEASE_BRANCH"
fi

# Push
if [ -n "$DRYRUN" ]; then
  echo "[DRY-RUN] Would push tag v_${RELEASE_VERSION}"
  if [ "$TYPE" != "PATCH" ]; then
    echo "[DRY-RUN] Would push branch $RELEASE_BRANCH"
  fi
else
  if [ "$TYPE" == "PATCH" ]; then
    git push origin "v_${RELEASE_VERSION}"
  else
    git push --atomic origin "v_${RELEASE_VERSION}" "$RELEASE_BRANCH"
  fi
fi

# Output
if [ -n "${GITHUB_OUTPUT:-}" ]; then
  echo "release_version=$RELEASE_VERSION" >> "$GITHUB_OUTPUT"
  echo "release_branch=$RELEASE_BRANCH" >> "$GITHUB_OUTPUT"
  echo "source_sha=$SOURCE_SHA" >> "$GITHUB_OUTPUT"
fi
```

**Removed from the old script:**
- `check_not_stuck` (no stored version to be stuck)
- `./gradlew incrementVersion` calls
- `./gradlew printVersion` calls
- `git add build.gradle.kts` / `git commit` (no file to modify)
- Bump PR creation (`gh api --method POST .../pulls`)
- Bump PR labeling (`gh api .../labels`)
- `git commit --amend` synchronize trick
- `validate-release-bump.sh` calls
- `wait-release-bump.sh` calls
- `BUMP_LABEL_TOKEN` / `GITHUB_TOKEN` / `BUMP_BRANCH` / `BUMP_SHA` logic
- `FIRST_PATCH` special case (no longer needed)

### `.github/workflows/release-validated.yml` simplification

**`validate-inputs` job:**
- Replace `BASE=$(./gradlew printVersion -Psnapshot=false ...)` with:
  ```bash
  RELEASE_VERSION=$(utils/compute-version.sh --release --${TYPE,,})
  ```
- Remove `ALREADY_RELEASED`, `FIRST_PATCH`, `PATCH` parsing, `MAJOR`/`MINOR`/`PATCH` conditional blocks
- Remove `STUCK_PR` lookup
- Keep: branch validation, SHA validation, tag-exists check, release branch computation

**`create-release` job:**
- Remove `Setup SSH agent` step
- Remove `Federate release bump label token` step
- Remove `Wait for exact bump approval and selected CI, then merge` step
- Remove `bump_branch`, `bump_head_sha`, `bump_pr_number`, `bump_pr_url` from outputs
- Keep: `release_version`, `release_branch`, `source_sha`, `base_branch` outputs
- The `Create release` step just calls `./.github/scripts/release.sh ${TYPE^^} $DRY_RUN`
- Remove `id-token: write` permission (no STS federation needed)
- Remove `pull-requests: write` permission (no PR creation)
- Remove `checks: read` and `statuses: read` permissions (no CI waiting)

**`pre-release-tests` and `pre-release-slow-tests` jobs:** unchanged.

### `.github/workflows/approve-trivial.yml` simplification

- Remove the `Classify pull request` step (release_bump classification)
- Remove the `Validate release bump before approval` step
- Remove the `Revalidate release bump immediately before approval` step
- Keep: `Authorize trivial labeler`, `Check for an existing exact approval`, STS federation, `Approve exact current commit`
- The `self.approve-trivial.approve-pr.sts.yaml` policy is unchanged

### `.github/workflows/ci.yml` changes

1. Remove `release-bump-ci` job (lines ~233-253)
2. In `release-automation-tests` job, remove from the `bash -n` list:
   ```
   .github/scripts/validate-release-bump.sh \
   .github/scripts/wait-release-bump.sh \
   ```
3. In `release-automation-tests` job, remove from the `shellcheck` list:
   ```
   .github/scripts/validate-release-bump.sh \
   .github/scripts/wait-release-bump.sh \
   ```
4. Keep `test_release_automation.sh` in both lists (it will be rewritten in Stage 5)

### `utils/release.sh` changes

- Update the `show_usage` function: remove "Creates annotated git tag" + "opens version-bump PR" → just "Creates annotated git tag"
- Update the `Release Flow` comment block: remove bump PR step
- The actual workflow dispatch logic is unchanged (it triggers `release-validated.yml`)

### `utils/README.md` changes

- Remove all references to bump PRs, version-bump PRs, "Merge the bump PR"
- Update the release flow description to match the new tag-only flow

### Verification
- `bash -n .github/scripts/release.sh`
- `shellcheck .github/scripts/release.sh`
- Run the test suite (Stage 5 rewrites it, but the old tests will fail — that's expected and fixed in Stage 5)

### Commit
`Rewrite release automation for tag-based versioning`

---

## Stage 5: Test rewrite

### Files modified
- `.github/scripts/tests/test_release_automation.sh`

### New test structure

The test suite is rewritten to test the new release flow. All bump-PR-specific
scenarios are removed. New test groups:

**Trivial approval tests (kept from old suite):**
- `expect_trivial_success`/`expect_trivial_failure` for labeler authorization
- These test `validate-trivial-approval.sh` which is unchanged

**Release script tests (new, hermetic with local bare remote):**

1. **Minor release from main:**
   - Setup: bare remote, main branch, tag `v_1.48.0` on HEAD
   - Run `release.sh MINOR`
   - Assert: tag `v_1.49.0` created on HEAD
   - Assert: branch `release/1.49._` created
   - Assert: `release_version=1.49.0` in outputs
   - Assert: main HEAD unchanged (no commit added)

2. **Major release from main:**
   - Setup: tag `v_1.49.0` on main HEAD
   - Run `release.sh MAJOR`
   - Assert: tag `v_2.0.0` created
   - Assert: branch `release/2.0._` created
   - Assert: main HEAD unchanged

3. **Patch release from release branch:**
   - Setup: `release/1.48._` branch, tag `v_1.48.2` on HEAD
   - Run `release.sh PATCH`
   - Assert: tag `v_1.48.3` created
   - Assert: no new branch created
   - Assert: `release_version=1.48.3` in outputs

4. **First patch on new release branch:**
   - Setup: `release/1.50._` branch, tag `v_1.50.0` on HEAD
   - Run `release.sh PATCH`
   - Assert: tag `v_1.50.1` created

5. **Tag already exists → fail:**
   - Setup: tag `v_1.49.0` already exists
   - Run `release.sh MINOR`
   - Assert: exit 1

6. **Patch from main → fail:**
   - Run `release.sh PATCH` on main
   - Assert: exit 1

7. **Minor from release branch → fail:**
   - Run `release.sh MINOR` on `release/1.48._`
   - Assert: exit 1

8. **Dry-run:**
   - Run `release.sh MINOR --dry-run`
   - Assert: no tag/branch pushed to remote

9. **Version computation after release:**
   - After minor release creates `v_1.49.0`, checkout main
   - Run `compute-version.sh` → `1.50.0-SNAPSHOT`
   - Checkout `release/1.48._`, run `compute-version.sh` → `1.48.3-SNAPSHOT` (if `v_1.48.2` is the latest reachable)

**Workflow/script content assertions (kept from old suite):**
- `release.sh` does not contain `set -x` (credential safety)
- `release.sh` does not contain `gh pr merge`
- `release.sh` does not contain `incrementVersion`
- `release.sh` does not contain `printVersion`
- `release.sh` does not contain `BUMP_LABEL_TOKEN`
- `finalize-release-bump.sh` does not exist
- `validate-release-bump.sh` does not exist
- `wait-release-bump.sh` does not exist
- `self.release-bump.label-pr.sts.yaml` does not exist
- `approve-trivial.yml` does not contain `release_bump`
- `ci.yml` does not contain `release-bump-ci`
- `ci.yml` does not contain `validate-release-bump`
- `release-validated.yml` does not contain `printVersion`
- `release-validated.yml` does not contain `wait-release-bump`
- `release-validated.yml` does not contain `bump_pr_number`

**Approve-trivial workflow assertions (kept, simplified):**
- `approve-trivial.yml` contains `github.event.label.name == 'trivial'`
- `approve-trivial.yml` contains `github.event.sender.login`
- STS federation step exists
- Approval is pinned to validated SHA

### Verification
```bash
bash -n .github/scripts/tests/test_release_automation.sh
shellcheck .github/scripts/tests/test_release_automation.sh
.github/scripts/tests/test_release_automation.sh
```

### Commit
`Rewrite release automation tests for tag-based versioning`

---

## Stage 6: Cleanup and documentation

### Files modified
- `doc/Versioning/TagBasedVersioning.md` — update if any implementation details diverged

### Files to check
- `utils/finalize-release-bump.sh` — should not exist (test asserts this)
- `git grep -n "printVersion\|incrementVersion\|dipien\|scmVersion\|semantic-version"` — should return nothing in active code
- `git grep -n "validate-release-bump\|wait-release-bump\|release-bump-ci"` — should return nothing
- `git grep -n "BUMP_LABEL_TOKEN\|bump_branch\|bump_pr"` — should return nothing

### Final verification
- `bash utils/tests/test_compute_version.sh`
- `bash .gitlab/scripts/tests/includes_test.sh`
- `.github/scripts/tests/test_release_automation.sh`
- `./gradlew help` (version computed)
- `./gradlew spotlessCheck`
- `shellcheck` on all modified shell scripts

### Commit
`Final cleanup and documentation`
