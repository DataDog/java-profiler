<!-- Copyright 2026, Datadog, Inc -->

# Versioning

The profiler version is computed at build time from git tags — no version is
stored in any file. The single source of truth is
[`utils/compute-version.sh`](../../utils/compute-version.sh), which derives
the version from the most recent reachable `v_X.Y.Z` tag.

## Version computation rules

| Branch | Most recent tag | Computed version |
|---|---|---|
| `main` | `v_X.Y.Z` | `X.(Y+1).0-SNAPSHOT` |
| `release/X.Y._` | `v_X.Y.Z` | `X.Y.(Z+1)-SNAPSHOT` |
| Feature branch | (same as base) | `X.(Y+1).0-SNAPSHOT`, or `X.(Y+1).0-<branch>-SNAPSHOT` with `--branch-suffix <branch>` (`/` → `_`) |
| CI tag build (`CI_COMMIT_TAG` or GHA `GITHUB_REF_TYPE=tag` = `v_X.Y.Z`) | - | `X.Y.Z` (release, no snapshot) |

The branch suffix is only applied when the caller passes `--branch-suffix`. GitLab's
`get_version()` (`.gitlab/scripts/includes.sh`) does that for non-`main`, non-`release/*`
branches and hands the result to Gradle as `-Pddprof_version`. A plain local
`./gradlew` build calls `compute-version.sh` with no arguments, so a feature branch gets the
same version as `main`.

The tag short-circuit relies on those CI environment variables. A local checkout of a tag
commit without them is treated like any other commit and gets the next snapshot version.
Minor and patch components roll over at 99 (e.g. `1.99.x` on `main` → `2.0.0-SNAPSHOT`).

On `release/X.Y._` branches, only tags matching `v_X.Y.*` are considered, so
a merged mainline tag (e.g. `v_1.49.0`) can't produce a wrong-series version
on a `release/1.48._` branch.

Version sorting uses `sort -t. -k1,1n -k2,2n -k3,3n` (portable across GNU
and BSD sort).

## Gradle integration

`build.gradle.kts` computes the version at configuration time via
`providers.exec`, calling `utils/compute-version.sh`. Priority:

1. `-Pddprof_version` (set by GitLab CI jobs via `get_version()`)
2. `compute-version.sh` (local builds, GHA CI with full history)
3. `0.0.0-SNAPSHOT` fallback with visible warning (CodeQL autobuild, shallow
   clones without tags — never used for publishing)

## Release flow

Releases create only an annotated tag (and a release branch for minor/major).
No file modifications, no bump PRs.

- **Minor** (from `main`): tag `v_X.(Y+1).0` on HEAD, create branch
  `release/X.(Y+1)._`
- **Patch** (from `release/X.Y._`): tag `v_X.Y.(Z+1)` on HEAD
- **Major** (from `main`): tag `v_(X+1).0.0` on HEAD, create branch
  `release/(X+1).0._`

The tag push triggers the GitLab build/publish pipeline. The next build from
`main` (or the release branch) automatically sees the new tag and computes
the next snapshot version.

See [`utils/README.md`](../../utils/README.md) for the release workflow
and [`utils/release.sh`](../../utils/release.sh) for the operator entry point.
