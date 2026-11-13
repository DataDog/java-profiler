<!-- Copyright 2026, Datadog, Inc. -->

# Bits Review Merge Gate — Specification and Design

**Status:** The gate is implemented in this change set and its hermetic local
tests pass. It is not activated: `bits-review/head` is not a required check
on `main`, no protection setting or Octo-STS installation state was changed, and
no enforcement claim applies. Activation needs separate approval.

## Goal and scope

Require a completed Bits Code Review PASS for the current head of each pull
request targeting `main`. Apply the rule to human, bot, dependency, documentation,
and fork pull requests. Do not add path-based or author-based exemptions.

The gate is an additional merge requirement. It does not replace CI, signing,
human reviews, or conversation resolution. Preserve existing admin bypass rights.
Do not add a label, comment, or maintainer override.

## Evidence and terminology

A **result** is a published Bits summary review, not an inline finding or an
ordinary approval. The two supplied examples are GitHub `COMMENTED` reviews:

| Example | Review commit | Metadata verdict |
| --- | --- | --- |
| [Review on PR 985](https://github.com/DataDog/java-profiler/pull/985#pullrequestreview-5872953227) | `1dcc3fa57582f2b595403f2b6a54e4464f352223` | FAIL |
| [Review on PR 968](https://github.com/DataDog/java-profiler/pull/968#pullrequestreview-5872101609) | `1115eb583f475b62544d634bb12bf750ae913e04` | PASS |

Their bodies contain `autotest-meta` metadata with a `verdict` field. The supplied
REST records use `commit_id`; the evaluator reads GraphQL `commit.oid`.
Use the API commit field, not badge text, a shortened hash, or a body link.

The [Bits onboarding documentation](https://datadoghq.atlassian.net/wiki/spaces/Autotest/pages/7297566123)
describes these comments as non-blocking. Requiring GitHub approvals does not
turn the metadata verdict into a merge requirement.

## Policy contract

Bind evaluation to the repository, pull request, and exact current head SHA.
Only a result from that pull request and SHA can satisfy the policy.

| Condition | Required outcome |
| --- | --- |
| Latest candidate is a trusted, valid, never-edited PASS for the current head | Pass the Bits requirement |
| Latest candidate is a trusted FAIL for the current head | Block |
| No completed result exists for the current head | Block |
| PASS exists only for another SHA or another pull request | Block |
| Latest result is dismissed or its verdict metadata is invalid | Block; do not fall back to an older PASS |
| Latest bot candidate has an actual body edit | Block, even if the original bot made the edit; require a fresh summary review |
| Latest Bits-marked result is from an unlisted bot | Block as untrusted origin; it cannot pass |
| A newer valid result replaces FAIL with PASS on the same SHA | Pass |
| A newer valid result replaces PASS with FAIL on the same SHA | Block after reevaluation |
| Another review starts after PASS on the same SHA | Keep the completed PASS until a new result or invalidation arrives |
| Push or rebase changes the head SHA | Require a result for the new SHA |
| Evaluation cannot establish a valid current PASS | Do not publish success |

“Latest” means submission order among candidate Bot reviews for the same PR and
SHA, including untrusted origins. Compare submission times as UTC instants, with
review ID as a tie-breaker. An edit does not make an older review newer.
Webhook arrival order is not authority.

Select the latest result before checking its dismissal state and verdict validity.
Filtering invalid or dismissed results first would allow an older PASS to reappear.
An unrelated review must not satisfy the requirement. Two conservative exceptions
can block: a latest Bits-marked review from an unlisted bot, and a latest edited
review from any bot whose markers are absent and whose origin cannot be established.
Copied markers from a User account are ignored.

A dismissed FAIL is not a PASS. Resolving findings, replying to them, or receiving
human approval does not clear FAIL. A new valid Bits PASS or an existing authorized
admin bypass is needed.

## Architecture

The gate uses a project-owned evaluator and publisher. It publishes under the
dedicated, stable status context `bits-review/head`. The context is not a
required check until activation.

```text
PR/review events + recovery sweep + manual retry
                         |
             trusted per-SHA reevaluation
                         |
         all open main PRs sharing that head
                         |
            separate result check per PR
                         |
            success only if every PR passes
                         |
           required status check on main
```

The shared-SHA result is a conjunction, not a transferable approval. An unreviewed
duplicate PR blocks the reviewed PR until the duplicate gets PASS or closes, or
an existing authorized admin bypass is used. This block-only denial risk is accepted.

### Trusted result recognition

The approved allowlist contains the numeric identities below. Each must also have
GitHub actor type `Bot`. The allowlist belongs in trusted main-branch code.

| Login | GitHub user ID |
| --- | --- |
| `datadog-official[bot]` | `214633350` |
| `datadog-datadog-prod-us1[bot]` | `88084959` |
| `datadog-datadog-prod-us1-2[bot]` | `261164178` |
| `datadog-datadog-us1-prod[bot]` | `298424163` |
| `datadog-prod-us1-3[bot]` | `266080212` |
| `datadog-prod-us1-4[bot]` | `266080418` |
| `datadog-prod-us1-5[bot]` | `266081015` |
| `datadog-prod-us1-6[bot]` | `266788760` |

PASS requires trusted origin and validated Bits summary metadata, including the
`datadog-code-review` reviewer ID `bad90057-5c12-4101-ad47-d91c9dff0f90` and
`datadog-autotest:v1:prod` marker. A badge alone never establishes a result.

A latest Bits-marked review from an unlisted bot blocks as untrusted origin, even
if its text says PASS. This prevents an unlisted shard's FAIL from being ignored.
A bot capable of copying the markers can cause a false block, not a false PASS.

A submitted Bot review on the exact head is a candidate when its body contains
`autotest-meta`, `datadog-code-review`, or `datadog-autotest`, or when it was edited.
An edited markerless review is included even from an unlisted bot. An unedited,
unmarked Bot review is ignored. Pending reviews and null commit references are
out of scope; known User-authored reviews are ignored.

Every latest edited bot candidate blocks, including a valid-looking summary edited
by its original bot. Require a fresh trusted summary review to clear that block.
This avoids trusting the current body solely from its original author identity.

Over-blocking unrelated edited bot reviews is accepted. This also closes the case
where an unlisted shard erases its markers and would otherwise expose an older
trusted PASS. A newer trusted valid Bits PASS can clear the conservative block.

Determine an actual edit only from GraphQL `lastEditedAt != null`. Do not treat a
creation revision or edit-history count as edit proof. Do not query or trust editor
history to permit an edited PASS. A [bot-authored review with a human editor](https://github.com/DataDog/java-profiler/pull/615#pullrequestreview-4565721745)
provides a concrete reason for this restriction.

GitHub's signal for an app-authored body edit must be proved in a live test before
activation. If it is absent, return the provenance design for a decision instead
of weakening the no-fallback rule.

### Evaluation and publication

The Python evaluator (`.github/scripts/bits_review_gate.py` and
`.github/scripts/bits_review_gate_policy.py`) uses only the standard library.
Its policy functions consume normalized records; an injectable API transport
supports hermetic tests. The CLI has `resolve` and `publish --sha H` subcommands.

Read every page of the REST open-PR list and the GraphQL review connection. Preserve
review ID, actor type, numeric actor ID, login, state, body, commit OID, submission
time, and raw `lastEditedAt`. Do not fetch edit-history records.

GraphQL errors, including partial-data responses, missing required response
structure, and transport failures produce `api-error`. Malformed required PR data
or possible-candidate data produces `invalid-input`. A marked or edited review
with an unclassifiable author or ordering field must not expose an older PASS.
Known User-authored reviews remain ignored. Network and server errors get at most
three attempts; client errors are not retried.

After validation, use this outcome order:

| Condition | Reason | Commit status |
| --- | --- | --- |
| Snapshot API failure or invalid required data | `api-error` or `invalid-input` | `error` |
| No candidate | `missing` | `pending` |
| Latest candidate dismissed | `dismissed` | `failure` |
| Latest candidate from an unlisted Bot | `untrusted-origin` | `failure` |
| Latest allowlisted candidate edited | `edited-summary` | `failure` |
| Latest allowlisted candidate has invalid markers | `malformed:<sub>` | `failure` |
| Valid metadata says FAIL | `fail` | `failure` |
| Valid metadata says PASS | `pass` | `success` |

Valid metadata has one `autotest-meta` comment with exactly one case-sensitive
`verdict=PASS` or `verdict=FAIL` token, one matching reviewer-ID comment, and the
production environment marker with no conflicting environment marker. Malformed
sub-reasons distinguish missing metadata, unknown or conflicting verdicts,
reviewer-ID mismatch, and an invalid environment marker. Ignore badge text and
delivery markers when deciding the verdict.

Conjoin the separate outcomes for all open `main` PRs whose head is H, including
drafts. Severity is `error`, then `failure`, then `pending`, then `success`.
The lowest PR number governs equal-severity outcomes. Link the governing review,
or its PR when no review governs. Build URLs from API numbers, not review text.
Limit the status description to 140 characters and include its reason.

Serialize writers with concurrency group `bits-review-gate-<sha>` and
`cancel-in-progress: false`. The writer reads snapshot S1 and computes its decision,
then reads S2. Compare SHA-256 fingerprints of canonical JSON covering PR
membership/head/base/state, every normalized review field, body digests, and error
flags with their locations. Retain raw edit times and identity/order inputs.

If fingerprints differ, discard the earlier decision and continue from the new
snapshot. After three unstable comparisons, exit without writing. If the open-PR
set for H was read successfully and is empty, write nothing. Never infer H from
the workflow's `GITHUB_SHA`.

Before writing, read all status pages and select the newest `bits-review/head`
entry created by `dd-octo-sts[bot]`, ordered by creation time and ID. Suppress the
write only when its state, description, and target URL match the desired status.
A failed status read must not suppress a safety update. An error decision fails
the run even when an unchanged-status match suppresses its POST. Failed writes
also fail the run.

Only the all-PASS branch may publish success. Failure to start or write, or unstable
snapshots with no write, can leave an older status visible. These paths do not
establish that GitHub is blocking merges.

### Events, permissions, and environments

Cover pull request creation, reopening, head synchronization, and retargeting to
`main`. Cover result submission, editing, and dismissal. A retry must reevaluate
live state; it must not replay a saved success.

The writer must run trusted base-branch code with only the permissions it needs.
Never execute PR code, interpolate review bodies into shell commands, or execute
artifacts supplied by an untrusted workflow.

Support GitHub-hosted Linux runners, same-repository PRs, fork PRs, and dependency
bot PRs. Fork and bot permission restrictions must be tested. A read-only
`pull_request_review` job alone is not a complete publishing design.

Use a hermetic evaluator test suite that works in a clean checkout without GitHub
credentials. Agent harness choice must not affect the merge decision; local hooks
and agent instructions are not enforcement.

The no-op receiver listens to `pull_request_review` submitted, edited, and dismissed
events. It also listens to `pull_request` edited events as a retarget-away hint.
It has empty permissions, no checkout, no artifacts, and no token-bearing step.

The publisher listens to receiver `workflow_run` completion and unfiltered
`pull_request_target` opened, reopened, synchronize, edited, and closed events
(the resolver guard drops title/body-only `edited` runs; see resolver behavior
below). Both publisher jobs require `github.ref == 'refs/heads/main'`. They check out
`refs/heads/main` with `persist-credentials: false`. Pin third-party actions to
full commit SHAs. Pass event selectors through environment variables, never
interpolated into shell commands.

The resolver has content-read and pull-request-read permissions. Per-SHA publish
jobs additionally have status-read and OIDC token-write permissions. The read-only
GitHub token never publishes the authoritative status. Do not set a job environment
that changes the OIDC subject.

Resolver behavior is fixed:

- PR events resolve the PR's live head by number, including close and retarget events.
  A `pull_request_target` `edited` event with no base change (title/body-only edit)
  resolves to no SHAs: the resolver guard fails open on the env-only selectors
  `GITHUB_PR_ACTION`, `GITHUB_CHANGES_BASE_REF`, and `GITHUB_CHANGES_BASE_SHA`, so
  only retarget edits resolve.
- Receiver completion resolves its run head plus live open-main heads matching PR
  numbers or head repository/branch. If none match, scan all open-main heads.
- Schedule and input-free manual dispatch resolve all open-main heads.
- Validate numbers and full SHAs, deduplicate, and fail rather than truncate if the
  result exceeds 256 distinct SHAs. Emit a JSON array through `GITHUB_OUTPUT`.

A 30-minute scheduled sweep provides recovery, not a maximum-refresh or availability
promise. Fork associations, token claims, and permission behavior need a test drive.

### Repository enforcement

The selected activation proposal adds the dedicated status to the existing classic
branch protection on `main`. Do not add a second ruleset. Preserve unrelated
protections and existing admin bypass. A workflow without a required status does
not enforce the merge policy.

Use the existing `dd-octo-sts` app as publisher, with a repository policy that
grants only status-write authority. Bind issuance to the trusted gate workflow on
`refs/heads/main`, the protected-ref claim, and its allowed event types. Use a
read-only `GITHUB_TOKEN` for reads. Do not use it to publish the authoritative status.

App-source binding does not isolate the gate from internal services that also hold
status-write authority as `dd-octo-sts`. Those services are accepted as trusted
infrastructure. Candidate-controlled workflows must not obtain the publisher token.
The installation permission and exact policy claims must be tested before activation.
The repository policy file `.github/chainguard/self.bits-review-gate.publish-status.sts.yaml`
carries exactly these claims:

```yaml
issuer: https://token.actions.githubusercontent.com
subject_pattern: repo:DataDog/java-profiler:(pull_request|ref:refs/heads/main)
claim_pattern:
  event_name: (pull_request_target|workflow_run|schedule|workflow_dispatch)
  ref: refs/heads/main
  ref_protected: "true"
  job_workflow_ref: DataDog/java-profiler/\.github/workflows/bits-review-gate\.yml@refs/heads/main
permissions:
  statuses: write
```

Octo-STS matches every pattern against the entire claim or subject value: it
compiles `subject_pattern` and each `claim_pattern` entry as `^(?:<pattern>)$`
(full-value matching; anchored compilation since v0.10.0, fixing
GHSA-mwqh-2vg8-rhj3). The unanchored alternations above are therefore whole-value
matches: event_name `pull_request` or ref `refs/heads/main-x` is rejected. Do not
add manual `^...$` anchors: around a top-level `|` they bind as `(^A)|(B$)`, the
partial-match leak the app-level wrapping exists to prevent.

When separately authorized, propose required context `bits-review/head` with expected
publisher app ID `1157446`. Read the live protection and rules into a fresh baseline
immediately before an authorized change. The change is additive: preserve every
existing required context and check, the existing `strict` value, `enforce_admins`,
and every unrelated field. Initialize the gate's context with `strict: false` only
when the fresh baseline has no required checks; never replace the checks list
unconditionally or disable an existing strict requirement. If the fresh baseline
differs from these assumptions, stop and revise the proposal before any authorized
write. Read back and compare the settings against the fresh baseline after the change.

GitHub status storage is commit-scoped. The conjunction across shared-head PRs is
the approved isolation policy. Prove that one PR's review cannot satisfy another
PR and that closing a blocking duplicate causes reevaluation.

## Consistency and availability limits

The accepted consistency model is asynchronous. A later FAIL or invalidation can
arrive before GitHub receives the blocking status. Normal processing delay is
accepted; this design does not claim an atomic review-and-merge operation.

A delivery outage or a writer that cannot start or publish can leave an earlier
success visible on the same SHA. A newly opened PR that reuses a green SHA can
also see that status before shared-head reevaluation. This is not an atomic
PR-admission gate. Conservative reads do not remove these external windows.

A running review on a SHA with PASS does not revoke that PASS by itself. This design
does not require Bits review-start signals, automatically trigger reviews, or change
Bits rollout settings. A PR that never gets a result remains blocked by policy.

Do not add a numerical freshness or delivery-latency promise without measurement
and approval. Stronger guarantees need a separate lifecycle or merge-path design.

## Alternatives not selected

| Alternative | Reason |
| --- | --- |
| Require ordinary GitHub approvals | Does not enforce the Bits metadata verdict |
| Require conversation resolution | Does not establish a current-head PASS |
| Match a badge or any PASS text | Does not establish trusted origin, latest result, or reviewed SHA |
| Add only local hooks or agent instructions | Does not enforce ordinary GitHub merges |
| Use the documented MergeGate ARP rule | Not the specified Bits verdict contract; documented to fail open on ARP errors |
| Add native Bits or Devflow support first | Not the selected project-owned route |

The [MergeGate documentation](https://datadoghq.atlassian.net/wiki/spaces/DEVX/pages/4948100574/MergeGate)
is the source for the documented ARP behavior. No claim is made that every possible
platform configuration has been ruled out.

## Acceptance and verification

The local cases are implemented as permanent hermetic tests and pass; they make no
claim about live GitHub behavior. Test-drive and production-check cases are one-time
evidence tied to the exact candidate, configuration, and observed head SHA; they
remain open until activation is separately authorized.

| ID | Environment | Required evidence |
| --- | --- | --- |
| AC1 | local | Fixtures from the supplied reviews produce FAIL and PASS for their respective SHAs; shortened or wrong SHAs do not match |
| AC2 | local | Missing, stale, wrong-PR, and wrong-author results cannot pass; all approved account identities are covered; a latest Bits-marked unknown-bot result blocks |
| AC3 | local | PASS→FAIL and FAIL→PASS follow submission order, including timestamp ties, out-of-order events, and an edit to an older review |
| AC4 | local | Dismissed, edited, or malformed latest candidates block without fallback; valid-looking original-author edits cannot pass; erased markers and unrelated edited bots cannot expose an older PASS |
| AC5 | local | Pagination, unknown or conflicting verdicts, API errors, and unrelated reviews take the specified branches |
| AC6 | local | Controlled interleavings prove head changes and stale runs cannot publish success for the wrong candidate or overwrite a newer decision |
| AC7 | test-drive | Same-repository, fork, and dependency bot PRs receive status updates without running PR-controlled code in the privileged writer |
| AC8 | test-drive | A push invalidates an earlier PASS; submission, edit, dismissal, and retry update the head status; an actual bot body edit exposes the edit signal used by the evaluator |
| AC9 | test-drive | A branch workflow cannot obtain publisher authority; each shared-head PR needs its own PASS; a missing-review duplicate blocks and closing it reevaluates the SHA |
| AC10 | production-check | Over a controlled test PR lifecycle, an ordinary non-bypass actor cannot merge without PASS and becomes eligible with PASS, subject to other checks |
| AC11 | production-check | Read-back confirms the required publisher, main-only scope, unchanged unrelated protections, and preserved admin bypass |
| AC12 | test-drive | Token exchange is denied for event_name `pull_request` and for ref `refs/heads/main-x` (no publisher token minted), proving full-value claim matching before activation |

Run the repository's adjacent script tests and CI safety checks for implementation
changes. Run `:ddprof-lib:qualityChecks` through the documented build wrapper for
documentation changes. Live checks must not merge a test PR or change protection
settings without explicit authorization.

## Rollout, recovery, and review

The design and policy contract are approved; the implementation is complete in
this change set. The evaluator, receiver, publisher, and repository policy file
are in place, with hermetic local tests passing. No test PR has been driven and
no live path is claimed.

1. On authorized test PRs, validate the real event and permission paths while the
   status is not required. No enforcement claim applies yet.
2. Obtain separate approval to require the status on `main`. Read back the settings
   and run the production checks with a non-bypass identity.

Security and repository-access-control review is required for the privileged writer,
publisher authority, and enforcement settings. No profiler runtime, public API,
JFR schema, or signal-handler behavior changes are included.

For an isolated false positive or outage, use only the existing authorized admin
bypass. A rollback of the required-check setting is a separate administrative
change needing explicit approval; record that enforcement is then disabled.

The evaluator reads review metadata only. It adds no profiler runtime overhead and
runs no LLM inference. GitHub API traffic scales with the review pages inspected
per reevaluation; avoid fetching source trees or rerunning the build matrix.

## Design synchronization and significant deviations

This document is the design source of truth through merge. Update it with each
implementation change that alters the described behavior, authority boundary,
interface, failure mode, or verification method. Reconcile it against the full
candidate before requesting review and before merge.

Record significant necessary deviations here with their reason, policy impact,
approval state, and required verification. A proposed deviation is not permission
to implement it. Keep the policy contract and acceptance criteria consistent with
approved decisions; do not weaken them to make an implementation pass.

The following material refinements are approved and reflected in the contract above:

| Decision | Reason and accepted impact | Required verification |
| --- | --- | --- |
| Eight-account allowlist; unknown marked bots block | A two-account allowlist can ignore a newer shard's FAIL; copied bot markers may cause false blocks | Identity, ordering, unknown-origin, and marker-copy cases |
| Conservative edited-bot candidates, including unknown origins | Erased metadata must not uncover an older PASS; unrelated edited bot reviews may block | Actual-edit detection, unknown-origin erasure, and live bot-edit signal |
| No edited summary can pass | Original author identity does not authenticate later text; even original-bot edits require a fresh review | Valid-looking edited PASS, original-author edit, and fresh-review recovery cases |
| Main-workflow-bound Octo-STS publisher | Branch workflows can share the Actions identity; existing internal Octo-STS status writers remain trusted | Token-claim restrictions and attempted branch-workflow spoofing |
| Shared-SHA conjunction | Statuses cannot express independent PR approval; a duplicate PR may block other PRs on the same head | Separate results per PR, duplicate closure and retargeting |

The implementation also includes event-driven updates, a 30-minute recovery sweep,
per-SHA serialization, and unchanged-status suppression. Their decision logic is
covered by the local hermetic tests; live delivery of the updates is test-drive
evidence (AC7–AC9).

The completed implementation records no significant deviation from this design:
every described behavior, authority boundary, and verification method is implemented
as specified, with no policy weakening.

## Implementation and activation boundaries

The technical choices above are the implemented baseline. The evaluator and its
tests use only the standard library. The tests are split by policy, API, publication,
and workflow contracts, plus a hermetic runner; each file stays reviewable.

Activation remains separate. It requires live proof of app-authored edit detection,
API identity mapping, fork and dependency-bot delivery, token-claim restrictions,
expected publisher binding, and non-bypass enforcement. If a technical constraint
requires changing the policy, stop and obtain approval before changing the design
or implementing that deviation.

## GitHub references

- [Workflow events and fork behavior](https://docs.github.com/en/actions/reference/workflows-and-actions/events-that-trigger-workflows)
- [Secure use of pull_request_target](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target)
- [Required status checks and successful conclusions](https://docs.github.com/en/pull-requests/how-tos/merge-and-close-pull-requests/troubleshooting-required-status-checks)
- [Protected branches and expected status publishers](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches)
