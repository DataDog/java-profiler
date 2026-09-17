---
id: find-isqueuedforrotation-quad-scan
type: finding
status: fixed
depends_on: [find-priority-queue-starves-bfs-crawl, find-rotation-resize-blindspot]
related: [find-cpu-pain-budget-blocks-bfs]
tags: [fix, root-cause, performance, profiles, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# isQueuedForRotation() was O(N) per frontier-slot visit - ~200M comparisons per rotation pass

User flagged ReferenceChainTracker::isQueuedForRotation() showing
prominently in profiles. Root cause: the deque-linear-scan implementation
was documented as "sub-millisecond" with arithmetic that assumed ~256
per-SELECTION calls per pass - but the rotation collectors
(collectStaleRootKindEntriesForRotation /
collectStaleExpandedEntriesForRotation, referenceChains.cpp) call it for
EVERY FrontierTable slot they visit (~199k EXPANDED entries on a large
heap), each scanning up to PRIORITY_EXPAND_CAP (1024) deque entries:
~200M comparisons per rotation pass. The comment's assumption and the
call pattern disagreed; the call pattern wins.

Fix: PriorityExpandSet - fixed 2048-slot open-addressing membership index
(Fibonacci-hashed near-sequential frontier tags, linear probing, <=0.5
load), zero allocation after construction, maintained at every
_priority_expand mutation site (pushes insert, expandFrontier() drains
rebuild-from-deque at batch end - a rebuild is <=1024 inserts against the
~20ms GetObjectsWithTags call the same batch already paid; no tombstones
needed). isQueuedForRotation() is now O(1). All mutation sites are on the
engine thread under _engine_lock, so plain non-atomic access is safe;
gtest helpers that manipulate the deque directly keep the index in sync.

Verified: 543 gtests green (referenceChains_ut 101/101), slow suite 8/8,
testDebug failures unchanged (5, all pre-existing env-flaky subsystems).
