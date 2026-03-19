---
description: Analyze divergences from upstream async-profiler, propose grouped PRs, and open draft PRs.
---

# Contribute Upstream Workflow

You are orchestrating the contribution of java-profiler divergences back to the upstream async-profiler project. These are all changes in our repo relative to upstream — not just uncommitted local modifications. Follow these steps precisely.

## Configuration

- **Fork repo**: `git@github.com:DataDog/async-profiler.git`
- **Upstream repo**: `async-profiler/async-profiler` (for PR target)
- **Upstream branch**: `master`
- **Analysis script**: `utils/check_contribution_candidates.sh`
- **Report dir**: `build/contribution-reports/`

## Step 1: Run Analysis

Execute the analysis script to generate reports:

```bash
./utils/check_contribution_candidates.sh
```

If it fails, diagnose and report the error to the user. Do not proceed.

## Step 2: Parse Results

Find the most recent JSON report in `build/contribution-reports/` (highest timestamp). Read it to get the list of files with contributable hunks.

Also read the corresponding markdown report to understand the actual diff hunks for each file.

If there are zero candidates, tell the user and stop.

## Step 3: Filter Out Existing PRs

Before proposing new PRs, check what's already open from DataDog against upstream:

```bash
gh pr list --repo async-profiler/async-profiler --author DataDog --state open --json number,title,body,files
```

For each open PR, extract the list of files it touches. Then cross-reference with the candidate files from Step 2:

- If a candidate file is already fully covered by an open PR (i.e., the PR touches that file and addresses the same type of change), **exclude it** from proposals
- If a candidate file is only partially covered (the open PR addresses some hunks but not others), keep the uncovered hunks as candidates
- When presenting proposals in Step 4, mention any skipped files and the existing PR that covers them, so the user has full visibility

Analyze the remaining contributable hunks across candidate files and group them into logical PR proposals. Guidelines:

- **Related changes go together**: e.g., a bug fix touching `stackWalker.cpp` and `vmStructs.cpp` for the same issue = one PR
- **Independent changes are separate**: unrelated fixes in different files = separate PRs
- **Each PR should be self-contained**: it should make sense on its own, compile on its own, and have a clear rationale
- **Keep PRs small**: prefer multiple small PRs over one large one

For each proposed PR, prepare:
- A descriptive title (e.g., "Fix null pointer check in stackWalker", "Add bounds validation in VMStruct")
- The list of files and hunks it covers
- A brief rationale explaining why this change benefits upstream

## Step 5: Present Proposals to User

Show the user a numbered list of proposed PRs with:
- Title
- Files involved
- Brief description of the change
- Number of hunks

Use `AskUserQuestion` with `multiSelect: true` to let the user pick which PRs to create. Offer all proposals as options.

If the user selects none, stop.

## Step 6: Create Selected PRs

For each selected PR, perform the following:

### 6a. Clone the Fork (once)

Clone `git@github.com:DataDog/async-profiler.git` to a temp directory. Reuse this clone for all PRs.

```bash
FORK_DIR=$(mktemp -d "${TMPDIR:-/tmp}/async-profiler-fork.XXXXXX")
git clone git@github.com:DataDog/async-profiler.git "$FORK_DIR"
cd "$FORK_DIR"
git remote add upstream https://github.com/async-profiler/async-profiler.git
git fetch upstream
git checkout -b temp upstream/master
git branch -D master 2>/dev/null || true
git checkout -b master
git branch -D temp
```

### 6b. Create Feature Branch

For each PR, create a branch from upstream master:

```bash
cd "$FORK_DIR"
git checkout master
BRANCH_NAME="contribute/<slug>-$(date +%Y%m%d)"
git checkout -b "$BRANCH_NAME"
```

Where `<slug>` is a short kebab-case description derived from the PR title.

### 6c. Port Changes

Apply only the relevant contributable hunks for this PR to the upstream files:

1. For each file in the PR, find the corresponding upstream file in `src/` of the fork
2. Apply the contributable hunks using careful manual editing (use the Edit tool)
3. **Critical**: Ensure NO Datadog-specific references leak through (DD_, ddprof, Datadog, datadog, DDPROF, context.h, counters.h, tagger, QueueItem)
4. If a hunk cannot be cleanly applied because the upstream file diverged, skip it and note it for the user

### 6d. Verify Build

Attempt a basic build check:

```bash
cd "$FORK_DIR"
make
```

If the build fails, analyze the error. If it's a simple fix (e.g., missing include), fix it. If it's complex, note it for the user and proceed anyway (the PR is draft).

### 6e. Commit and Push

```bash
cd "$FORK_DIR"
git add -A
git commit -m "<concise description of the change>"
git push origin "$BRANCH_NAME"
```

### 6f. Open Draft PR

Use `gh` to create a draft PR against upstream. **Important**: Before creating the first PR, fetch the target project's PR template from the upstream repo (`gh api repos/async-profiler/async-profiler/contents/.github/PULL_REQUEST_TEMPLATE.md` and decode the base64 content). The PR body **must** follow that template exactly — use all its sections, checkboxes, and footer verbatim. Fill in each section with the relevant content for this change.

```bash
gh pr create \
  --repo async-profiler/async-profiler \
  --base master \
  --head "DataDog:$BRANCH_NAME" \
  --draft \
  --title "<PR title>" \
  --body "<body following the upstream PR template>"
```

## Step 7: Report

After all selected PRs are created, show the user:
- A summary table of created PRs with their URLs
- Any hunks that could not be applied
- Any build issues encountered
- The temp directory path in case manual follow-up is needed

## Error Handling

- If `gh` is not authenticated, tell the user to run `gh auth login` and stop
- If the fork clone fails, check SSH key setup and report
- If a branch already exists on the fork, append a counter suffix (e.g., `-2`)
- Always clean up on fatal errors (remove temp directory)
