---
id: find-canary-continue-skips-discovered-instances
type: finding
status: fixed
depends_on: [find-representative-changes-lose-canary]
supersedes: []
related: [find-representative-changes-lose-canary]
tags: [root-cause, fix, referenceChains, canary, discovered-instances, control-flow, NEW-THIS-SESSION]
created: 2026-08-27
updated: 2026-08-27
---

# Canary path `continue` skipped discovered-instances check

## Observation

After deploying the auto-mark fix (`7bd7255c3`), the live pod showed all
5 candidates with `buildCanaryChainEvent -> 0` and no chain events being
emitted. The [B candidate (klass_id=2) had a marker tag, so it entered
the canary path in `pollWatchedTargets()`. The canary path ended with
`continue`, skipping the discovered-instances check that was added
below it.

## Root cause

The discovered-instances chain-building code was placed *after* the
canary `if (tag <= MARKER_TAG_BASE) { ... continue; }` block. Since the
[B candidate has a marker tag, it took the canary path and hit
`continue`, never reaching the discovered-instances check. The
auto-marking in the callback was correctly recording discovered
instances, but `pollWatchedTargets` never checked them for canary
candidates.

This was a bug in the fix itself (`7bd7255c3`), not a pre-existing
defect.

## Fix (COMMITTED 5d06d7328)

Removed the `continue` from the canary path so it falls through to the
discovered-instances check. Both canary and non-canary paths now try
discovered instances when no chain is cached for the class. The
discovered-instances check is guarded by `no_chain_cached` so it only
runs when the canary path didn't already produce a chain.

## Lesson

When adding a new code path that must run for *all* candidates, verify
it is not placed after an existing `continue`/`break` that would skip
it. The canary path's `continue` was correct *before* the
discovered-instances feature existed — adding the new check below
without removing the `continue` silently disabled it for all canary
candidates.
