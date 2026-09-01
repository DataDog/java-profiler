---
id: find-engine-seam-data-race
type: finding
status: confirmed-and-fixed
depends_on: [find-test-seam-aliasing]
related: [find-dangling-jclass-local-ref-cache, find-priority-queue-starves-bfs-crawl]
tags: [root-cause, fix, threading, crash, test-seams, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Seam-driven runPass/poll races the BFS thread on unsynchronized engine maps

Observed: SIGSEGV in `ClassTagTable::insert`'s unordered_map rehash, from a
test thread inside `resolveLoadedClasses()` (runPass) while the BFS thread
was mid-pass of its own (the seams test creates a live leak candidate, so
threadLoop runs passes concurrently with the test's synchronous
runReferenceChainPass0/pollReferenceChainTargets0).

## Root cause

runPass()/pollWatchedTargets() mutate plain containers
(`_class_tags`, `_candidate_*`, `_leak_parent_fanout`, ...) with no
cross-thread locking - safe only because threadLoop was the single caller.
The JNI-entered seams added a second caller.

## Fix

`Mutex _engine_lock` serializes the two engine drivers at entry:
`runPassSerialized()` / `pollWatchedTargetsSerialized()` (lock-scoped
wrappers) used by BOTH threadLoop and javaApi.cpp's seam functions. Full
pthread mutex, not a spin lock - the critical section is a whole BFS pass
(tens of ms). Lock order is engine_lock -> inner locks (frontier spinlock,
LivenessTracker's table lock); no reverse path exists.
`resetSearchStateForTest` was already safe (stopThread() first).

## Semantic residual (not a memory bug)

threadLoop still interleaves BETWEEN the test's steps: it can re-admit the
seam-tagged target via root enumeration, SetTag races tagAsRootForTest,
and the chunked static-field sweep can lap before the fixture populates
the holder. The seams test's fixture must therefore not depend on a
particular discovery order (see find-test-seam-aliasing's scenario rules).
