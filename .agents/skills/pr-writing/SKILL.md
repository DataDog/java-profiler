---
name: pr-writing
description: Writing rules for java-profiler PR titles and descriptions, PR comments and review replies, Jira ticket comments, and git commit messages. Use before writing or editing any of these.
---

# PR, comment and commit writing

These rules apply to PR titles and descriptions, commit messages, and every comment a
session writes: PR comments, review replies, Jira work-item comments. The template rule
applies to descriptions only.

## Measured numbers

Take counts, sizes, test totals and timings from a command's output, a saved log or a
CI result for the current candidate, never from memory, and name that source. Naming
the source is not a tool-run narrative. When the candidate changes, update the numbers
or say they are from an earlier commit.

## PR descriptions and comments

- **Follow the PR template strictly** (`.github/PULL_REQUEST_TEMPLATE.md`, descriptions
  only): fill in every section it defines or mark it N/A explicitly; do not invent a
  different structure.
- **Write from the actual diff.** Re-check the title and description after the scope
  changes. Describe crash or bug mechanisms only as far as the code and tests confirm.
- **Keep the description current as the branch evolves.** Whenever commits are added
  to a branch with an open PR (review fixes, a rebase replay, a scope change),
  re-verify the title and description against the new diff and update what no longer
  holds — sections, accepted costs, measured numbers.
- **Professional typesetting and layout.** Structure the description for scanning:
  short sections with meaningful headings, bullets for enumerations, tables for
  comparisons, `code spans` for identifiers and commands, fenced blocks for code/logs.
  Keep paragraphs to 2-4 sentences; never walls of text. Bold sparingly, for key
  terms only.
- **Write concisely and to the point**, in Simplified Technical English: short
  declarative sentences, one idea per sentence, no filler, no marketing tone.
  A reviewer reads the description before the diff — optimize for that first read.
- **Explain the WHYs, not the WHATs.** Focus on non-obvious motivation and
  limitations: why this approach was chosen, what alternatives were rejected and
  why, what constraints shaped the design, what the change does NOT fix. Do not
  reiterate what the code obviously shows.
- **Flag accepted costs.** When a change deliberately alters behavior with
  user-visible impact (JFR event schema, signal volume, resident memory, suppression
  scopes) or accepts a recurring per-call or footprint cost, state the decision and
  the accepted cost explicitly and flag it for reviewer acknowledgment — never leave
  it implicit in code, a test rename, or a leftover template marker.
- **Human review** (descriptions only). Under Additional Notes, state whether human
  review is required or recommended, and why, as the ticket's design records it. If the
  ticket records none, state your own assessment.
- **Only the final state matters.** Never include ephemeral working knowledge —
  investigation detours, dead-end hypotheses, intermediate states, tool runs,
  session history. If a detail did not survive into the final change, it does not
  belong in the description.
- The AGENTS.md **Comment budget** applies to PR descriptions too.

## Commits

- Base each commit message solely on the actual diff.
