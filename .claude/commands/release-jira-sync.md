---
description: For a given release version, find its PRs, extract their JIRA tickets, and sync a "fixed_version" label + PR-link comment onto both the GitHub PRs and the JIRA tickets.
argument-hint: "<version> (e.g. 1.50.0, v_1.50.0, or a git tag)"
---

# Release / JIRA Fixed-Version Sync

You are syncing release bookkeeping between GitHub and Jira for one release of
`DataDog/java-profiler`. Given a version number, you will:

1. Find every commit/PR in that release.
2. Find each PR's own JIRA ticket (if any).
3. Label the PR `fixed_version: <tag>` on GitHub (if missing).
4. Label the JIRA ticket `fixed_version:<tag>` (Jira labels can't contain spaces) and
   add a comment linking the PR (if missing).

User arguments (raw): `$ARGUMENTS`

Treat the raw argument as the version, e.g. `1.50.0`, `v_1.50.0`, or `v1.50.0`.

## Step 0: Prerequisites

- Confirm `gh` is authenticated (`gh repo view --json nameWithOwner`) against
  `DataDog/java-profiler`.
- Confirm the `datadog-atlassian` MCP tools are available (try
  `mcp__datadog-atlassian__get_issue` on a throwaway lookup, or check the deferred
  tool list). If not authenticated, call `mcp__datadog-atlassian__authenticate`,
  give the user the URL, and wait for them to confirm before continuing.

## Step 1: Resolve the release tag

```bash
git fetch --tags
git tag -l | sort -V
```

Normalize the user's input to match this repo's tag convention (tags look like
`v_1.50.0`). Try, in order: the argument as given, `v_<version-with-leading-v-stripped>`,
`v<version>`. If nothing matches, list the closest tags (e.g. via `git tag -l | grep`)
and ask the user to disambiguate — do not guess silently.

Once resolved, find the immediately preceding tag by version-sorting all tags and
taking the one right before the target:

```bash
git tag -l | sort -V | grep -B1 "^<resolved_tag>$"
```

## Step 2: List commits/PRs in range

```bash
git log --oneline <prev_tag>..<resolved_tag>
```

Extract the PR number from each commit subject's trailing `(#NNN)`. Commits without
a PR number (rare, e.g. direct pushes) should be reported to the user but skipped
for labeling.

## Step 3: Find each PR's own JIRA ticket

For each PR number, fetch title + body:

```bash
gh pr view <num> --repo DataDog/java-profiler --json title,body -q '.title + "\n" + (.body // "")'
```

Look specifically for the PR template's own-ticket checkbox line, which looks like:

```
- [X] JIRA: [PROF-NNNNN](https://datadoghq.atlassian.net/browse/PROF-NNNNN)
```

Use **only** that checkbox line as the PR's own ticket — ignore other JIRA links that
may appear in the body prose (e.g. "this PR fixes X, which was found while working on
PROF-YYYYY" or "test case for PROF-ZZZZZ") since those reference *other* PRs' tickets,
not this one's. If the checkbox says `N/A` or `(none)`, or is absent, the PR has no
JIRA ticket — skip Jira steps for it but still handle the GitHub label.

Build a mapping: `PR number -> JIRA key (or none)`.

## Step 4: GitHub label

Determine the exact label string already in use in the repo for this kind of thing:

```bash
gh label list --repo DataDog/java-profiler --limit 200 | grep -i fixed_version
```

If a `fixed_version: <resolved_tag>` label already exists, reuse it verbatim
(matching existing spacing/case). If none exists for this tag yet, create the label
first:

```bash
gh label create "fixed_version: <resolved_tag>" --repo DataDog/java-profiler --color ededed --description "Version this PR's fix shipped in" --force
```

(`--force` updates color/description if a same-named label exists; harmless if not.)

For each PR from Step 2, check current labels:

```bash
gh pr view <num> --repo DataDog/java-profiler --json labels -q '[.labels[].name] | join(", ")'
```

If the `fixed_version: <resolved_tag>` label is not already present, add it:

```bash
gh pr edit <num> --repo DataDog/java-profiler --add-label "fixed_version: <resolved_tag>"
```

Skip PRs that already carry the label.

## Step 5: JIRA label + comment

For each `(PR number, JIRA key)` pair from Step 3 (skip PRs with no ticket):

1. `mcp__datadog-atlassian__get_issue` with the issue key, and read its
   `fields.labels` array to see what's already there.
2. If `fixed_version:<resolved_tag>` (no spaces — Jira labels forbid spaces) is not
   already in that array, call `mcp__datadog-atlassian__update_issue` with
   `fields: {"labels": [...existing_labels, "fixed_version:<resolved_tag>"]}` and
   `confirmed: true`. **Preserve existing labels** — this replaces the whole array,
   it does not merge.
3. Check whether a comment already links this PR (skim recent comments if the issue
   payload includes them, otherwise just check for idempotency by not re-commenting
   if you already did so in this run). If not already linked, call
   `mcp__datadog-atlassian__add_comment` with
   `body: "Fixed in https://github.com/DataDog/java-profiler/pull/<num>"`.

Multiple PRs can reference the same ticket only if they each carry that ticket's own
checkbox — in practice each ticket should map to exactly one PR's checkbox in a given
release, but it does happen (e.g. a fix landing in one release and being touched again
in a later one). When a ticket is claimed by more than one PR (in the same release or
across different releases):

- Add a `Fixed in <PR URL>` comment for **every** claiming PR that doesn't already have
  one — comments are additive history, never skip or overwrite them.
- For the **label**, only keep `fixed_version:<tag>` for the **latest** (most recent)
  release among the claiming PRs — remove/omit the label for any earlier release once a
  later one is known, so the label always reflects where the fix most recently shipped.
  This means the labels field for such a ticket may need to be *shrunk*, not just
  appended to: fetch current labels, drop any older `fixed_version:*` entries that are
  superseded by a newer claiming release, keep all non-`fixed_version` labels untouched,
  and set the result via `update_issue` (labels is a full replace, not a merge, for this
  case).
- Still flag the ticket to the user in the final report (as a note, not a blocker) so
  they're aware multiple PRs claim it — but proceed with the comment+label handling
  above rather than skipping it outright.

## Step 6: Report

Present one table to the user:

| PR | JIRA | GitHub label | JIRA label | JIRA comment |
|----|------|--------------|------------|--------------|

Mark each cell "added", "already present", or "n/a" (for PRs with no JIRA ticket, the
JIRA columns are "n/a"). Call out anything skipped due to ambiguity (e.g. PRs with no
resolvable PR number), and separately list any tickets claimed by multiple PRs (per the
multi-claim handling in Step 5) with which release ended up as the "latest" label.

## Error handling

- If a PR number from a commit subject doesn't resolve via `gh pr view` (e.g. it was
  a different repo's issue number, or deleted), report it and continue with the rest.
- If Jira update/comment calls fail (auth expired, permission), report per-ticket
  failures at the end rather than aborting the whole run.
- Never silently overwrite a JIRA issue's labels array — always fetch current labels
  first and append.
