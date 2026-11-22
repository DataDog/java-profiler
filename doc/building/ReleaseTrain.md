<!-- Copyright 2026, Datadog, Inc -->

# Release Train

The release train automates the path from a passing main branch to a
published minor release and an updated dd-trace-java. It has three stages:
nightly certification, the weekly Friday release, and the dependency bump.
Major and patch releases stay manual ([Versioning](Versioning.md),
[utils/README.md](../../utils/README.md)).

## Nightly certification

The `Release Certification` workflow (`.github/workflows/certification.yml`)
runs at 04:00 UTC on the `main` HEAD. Its suite:

- `testDebug` and `testAsan`, regular and slow, gtests included — the same
  gate `release-validated.yml` runs before a manual release
- the fuzz job (same as the nightly sanitized run)
- the `dd-trace-integration` cells (`prepare-patched-agent` and the four
  `integration-test-*` cells) of the commit's GitLab pipeline; the workflow
  waits for and reads those cells, it does not re-run them

When every part passes, the workflow attaches a git note on the certified
commit under `refs/notes/certification` and pushes the notes ref. The note is
a single-line JSON object with the commit, timestamp, workflow run URL and
suite summary.

When any part fails, the workflow notifies the Slack channel and files a
high-priority PROF ticket titled
`java-profiler nightly certification failed on <sha>`. A repeat failure on
the same commit updates the existing open ticket instead of filing a new one.

A commit that carries a certification note is certified. Any commit on
`main` newer than the last release tag can become the release candidate once
certified; there is no recency window.

## Friday release

The `Release Train` workflow (`.github/workflows/release-train.yml`) runs
Fridays at 11:00 UTC (12:00 CET; 13:00 CEST in summer, GitHub cron is fixed
to UTC). It picks the newest certified commit that the newest `v_*` release
tag does not cover:

- certified commit newer than the last release → dispatch
  `release-validated.yml` with `release_type=minor`, `dry_run=false`, pinned
  to the certified commit; the workflow then watches the release run
- otherwise → skip with the reason, notified to Slack

The train never releases two versions from the same certified commit and
never releases a commit older than the last release. Both rules are enforced
in `pick-release-candidate.sh` (tested by
`.github/scripts/tests/test_release_train.sh`) and re-checked in the
workflow before dispatch.

Both workflows accept manual `workflow_dispatch` runs. `Release Train` takes
an optional `sha` input to release a specific certified commit (the commit
must carry a certification note) and a `dry_run` input that dispatches the
release validation without creating a tag.

## dd-trace-java dependency bump

After a release is published and its artifacts are live on Maven Central,
the `Update Release Assets` workflow (`.github/workflows/update_assets.yml`)
runs `bump-ddtrace.sh`, which opens a **draft** PR on `DataDog/dd-trace-java`
from branch `ddprof/bump-<version>`. The change is two files:
`gradle/libs.versions.toml` (`ddprof` version) and
`dd-java-agent/ddprof-lib/gradle.lockfile`. The PR carries the labels
`type: bug fix`, `comp: profiling` and `tag: ai generated` and is merged by
a human. A run that finds an open PR from a previous attempt or a toml that
already pins the new version exits without changes.

## Required secrets

| Secret | Used by | Purpose |
|---|---|---|
| `GITLAB_API_TOKEN` | certification | read the `dd-trace-integration` cell results from `gitlab.ddbuild.io` |
| `ATLASSIAN_BASE_URL`, `ATLASSIAN_USER_EMAIL`, `ATLASSIAN_API_TOKEN` | certification | file PROF tickets; missing secrets downgrade the notification to Slack-only with a warning |
| `SLACK_WEBHOOK` | certification, release train | failure and skip notifications |
| `DDTRACE_GH_TOKEN` | update assets | open the bump PR on `DataDog/dd-trace-java`; missing secret skips the bump with a warning |

The certification suite cannot certify without the GitLab token: the
`dd-trace-integration` verdict is a required part of the certification.

## Failure handling

- **Certification fails** → Slack notification and PROF ticket immediately;
  the commit is not certified. The train skips until a nightly run
  certifies the commit or a successor.
- **Release run fails** → the train reports the conclusion in its summary
  and notifies Slack. Re-run the train by hand (`workflow_dispatch`, same
  candidate) after fixing the cause; the candidate is still unreleased.
- **Missed certification window** (no green nightly all week) → the train
  skips. The train never releases an older certified commit once a newer
  one exists, and the pinned-sha override enforces the same rule, so the
  recovery path is a manual release via `utils/release.sh` or a manual
  re-run of the certification workflow on a newer commit.
