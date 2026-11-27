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
- the `certify-dd-trace-integration` verdict from the candidate's main-push
  GitLab pipeline, mirrored to GitHub; it reuses the integration artifacts
  and does not re-run the test matrix

When the suite passes, the certification job attests `certified-commit.txt`:
the full commit SHA followed by one newline. It then indexes the commit under
`refs/notes/certification`. Notes support discovery, not authorization.

When any part fails, the workflow notifies the Slack channel and files a
high-priority PROF ticket titled
`java-profiler nightly certification failed on <sha>`. A repeat failure on
the same commit updates the existing open ticket instead of filing a new one.

The train and the major/minor release job reconstruct the file from the candidate
SHA. They verify its attestation against this repository, the certification workflow,
the main ref and the candidate source digest. A note alone does not pass either check.

## Friday release

The `Release Train` workflow (`.github/workflows/release-train.yml`) runs
Fridays at 11:00 UTC (12:00 CET; 13:00 CEST in summer, GitHub cron is fixed
to UTC). It picks the newest certified commit that the newest `v_*` release
tag does not cover:

- noted candidate newer than the last release, with a valid attestation → dispatch
  `release-validated.yml` with `release_type=minor`, `dry_run=false`, pinned
  to the certified commit; the workflow then watches the release run
- no eligible candidate → skip with the reason, notified to Slack
- missing or unverifiable attestation on the selected candidate → fail without dispatch

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

## Release environments

The release writer uses `release-mainline` for major/minor and `release-maintenance`
for patch/retag. Restrict the first environment to main, and the second to protected
maintenance branches. Require an independent reviewer and prevent self-review on the second.

Provision `RELEASE_ENV_PUSH_KEY` as an environment secret only. Remove repository-
and organization-level access to the old release key and revoke its push authority.
Referencing an environment in the workflow does not configure these protections.

## Required secrets

| Secret | Used by | Purpose |
|---|---|---|
| `ATLASSIAN_BASE_URL`, `ATLASSIAN_USER_EMAIL`, `ATLASSIAN_API_TOKEN` | certification | file PROF tickets; missing secrets downgrade the notification to Slack-only with a warning |
| `SLACK_WEBHOOK` | certification, release train | failure and skip notifications |
| `DDTRACE_GH_TOKEN` | update assets | open the bump PR on `DataDog/dd-trace-java`; missing secret skips the bump with a warning |

Certification uses the built-in `GITHUB_TOKEN` with `statuses: read` and
`contents: read` for its integration job. No GitLab credentials are needed
in GitHub.

The integration gate requires the newest
`dd-gitlab/certify-dd-trace-integration` status to be `success` for the exact
candidate SHA. It verifies the publisher's bot account and Datadog-owned
bridge app through GitHub's API on each snapshot.

GitLab creates this job for pushes of `main`, outside custom JDK pipelines.
The job uses `when: always` and replaces the default green cancellation
hook with fail-closed checks in `certify-main.sh`.

That script rejects cancelled or non-main execution and a missing or wrong
prepared-agent SHA. Both quarantine validation and aggregation use the policy blob
from the candidate commit, not an inherited path or a working-tree copy.

The aggregator enforces the [integration quarantine policy](TestingGuide.md#tier-3--dd-trace-integration-tests-gitlab-every-push).
Approved quarantined validation failures do not block certification.
Unquarantined failures and incomplete matrix results fail the verdict.

Ordinary job statuses are not certification evidence: a non-PR branch at the
same SHA can report green no-op jobs. Neither those statuses nor an overall
green pipeline can substitute for the main-only execution gate.

The waiter pauses up to three minutes between snapshots. GitHub's
`Retry-After` or exhausted-quota reset headers can extend that pause.
All reads and pauses share a six-hour deadline.

A failed verdict, invalid evidence, non-retryable API error, or timeout
blocks certification.

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
  mainline recovery path is to re-run certification on main. A manual major or
  minor release requires the same attestation as the train.
