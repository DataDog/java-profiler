---
id: find-rolling-resume-expandfrontier
type: finding
status: fixed
depends_on: [find-shared-deadline-starves-expand]
supersedes: []
related: [find-static-field-sweep-cursor-fix]
tags: [fix, referenceChains, expandFrontier, rolling-resume, cursor, truncation, NEW-THIS-SESSION]
created: 2026-08-27
updated: 2026-08-27
---

# Rolling resume for expandFrontier: pop processed entries on truncated batch

## Observation

When `FollowReferences` truncates mid-batch (budget exhausted), the
entire batch was left at the front of `_pending_expand` for retry. On
the next pass, `GetObjectsWithTags` + `FollowReferences` re-walked
already-expanded entries — idempotent but wasteful (re-paying the full
O(tag_map × batch) GOTW cost and the FollowReferences STW for entries
that need no work).

## Fix (COMMITTED b2acdaee2)

Added `_last_visited_batch_tag` to `PassContext`, updated by the
callback's `batch_tags` descent gate (the point where the callback
decides to descend into a batch entry). After `FollowReferences` returns
truncated:

- Entries fully processed BEFORE the truncation point are popped
  (mark EXPANDED if live, clear if dead)
- The partially-visited entry (at `_last_visited_batch_tag`) stays:
  some of its children may have been admitted before the abort, and
  the rest are discovered on retry (admitObject is idempotent)
- Entries after the partial one stay (never visited)

Same resumable-cursor pattern as `admitStaticFieldRoots()`'s sweep
cursor.

## Test

`RollingResumePopsProcessedEntriesOnTruncatedBatch` — static-field root
→ listNode → 20 chain children, budget=4, 20 distractors. Verifies
listNode gets EXPANDED after truncated expand, all children eventually
admitted across passes.
