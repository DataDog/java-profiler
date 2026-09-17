---
id: q-implement-two-fixes
type: question
status: confirmed
depends_on: [find-marker-tag-slot-index-mismatch, find-one-shot-pretag-gate, find-canary-search-cannot-terminate]
supersedes: []
related: [find-canary-stuck-abandon-detector, ev-fixes-compile-and-gtest-pass]
tags: [decision-made, fix, implemented]
created: 2026-08-24
updated: 2026-08-24
---

# RESOLVED: yes — both fixes were implemented, plus a third (Fix C)

## Reasoning chain

Both fixes were offered at the end of the session ("Want me to implement
both?"). The user answered with `/investigation seed …` instead, so
**neither is approved and nothing has been changed** — no files modified,
nothing committed, HEAD still `8114019c2`.

### Fix A — decode the slot from the tag in `pollWatchedTargets()`

Mirrors what `heapReferenceCallback()` already does at
`referenceChains.cpp:1510`. Touches `referenceChains.cpp:3478` and `:3485`:

```cpp
int slot = (int)(MARKER_TAG_BASE - tag);
bool built = buildCanaryChainEvent(slot, &event);
… cacheResolvedChain(klass_id, std::move(event), _candidate_frontier_tags[slot], …);
```

Note `buildCanaryChainEvent()` already range-checks its argument against
`_candidate_count` (`referenceChains.h:2094-2097`), so a stale slot >=
`_candidate_count` degrades to a clean `false` rather than an OOB read.
The `TEST_LOG` at `:3473-3475` and `:3479-3481` should log the slot too,
otherwise the same inconsistency remains invisible in logs.

### Fix B — rework the `_candidate_count == 0` gate

`referenceChains.cpp:3375-3397`. Must admit newly-flagged candidates and
retire dead ones, otherwise a churning candidate set (5 selected vs 3
latched, as seen live) will pin the search in `RUNNING` again even with
Fix A. Interacts with the completion condition at `:3101-3103` and with
`_candidate_found_bits` bit positions, so the two have to be designed
together.

## Sub-questions not yet answered
- Is a regression test with **more than one** canary candidate needed?
  The existing integration test exercised a single candidate, which is
  precisely why this escaped (see `hyp-regression-of-five-fixes`).
- Should the `!isUrgent()` suppression of the TTL/abandon path
  (`referenceChains.cpp:3090-3091`) gain an absolute backstop, so a
  livelocked urgent search still eventually resets rather than burning
  STW budget forever?

## Evidence
- `nodes/find-marker-tag-slot-index-mismatch.md`
- `nodes/find-one-shot-pretag-gate.md`
- `nodes/find-canary-search-cannot-terminate.md`
