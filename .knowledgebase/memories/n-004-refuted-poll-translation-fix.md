---
id: n-004-refuted-poll-translation-fix
title: n-004: proposed poll-side leak->frontier translation REFUTED; real defect is the test seam's observation window
kind: dead-end
tags: [reference-chains, refuted, test-seam]
applies_to: []
source: frontier-wait-untagged/n-004-refuted-poll-translation-fix
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# n-004: proposed poll-side leak->frontier translation REFUTED; real defect is the test seam's observation window

## Status: COMPLETED (refutation of own proposal, section6 evidence)

## The proposal under test
In pollWatchedTargets, when the representative's current JVMTI tag is a leak tag, translate it to
the frontier entry that stored it, then buildChainEvent(frontier_tag).

## Why it is WRONG (proven from code + /tmp/child-section6.log)
1. Object-tag lifecycle (code): interception writes the FRONTIER tag onto the object
   (referenceChainWalk.cpp heapReferenceCallback) and stores the leak tag ON the entry
   (setLeakTag). While that entry is live, nothing re-sets the leak tag on the object
   (tagLeakInstances correlates, never retags - livenessTracker.cpp block comment "frontier tag on
   object: already admitted - correlate the entry, never retag"). Therefore:
   leak-tag-on-object <==> NO live frontier entry for the object.
2. So at exactly the moments the poll reads the leak tag (3129 polls in section6, all after the
   restart at line 530085), there is NOTHING to translate to - the entry that held the leak tag was
   cleared by releaseSearchTags() at the restart.
3. And when an entry IS live, the poll already succeeds: section6 line ~513300:
   "buildChainEvent target_tag=10573 chain_size=5 chain[0]=2 depth=3 root_kind=8
   leak_tag=1073742079 -> 1". The chain was built 10x (once per search generation), exact expected
   shape (byte[] <- elementData <- ArrayList <- SynchronizedList <- STATIC_FIELD).
4. Interception count distribution: ALL 17 tagged chunks intercepted exactly 10x each
   (170 lines) = the static-anchor descend prong re-walks LEAK_BUFFER's whole subtree once per
   search (batch_tags=nullptr descends through tagged intermediates; no-descend list does not
   cover byte[]). Discovery is deterministic per search. The v1 fanout-flooding concern is moot for
   THIS prong.
5. The engine restarts searches ~every 2.4s (10 searches / 45s run) - steady-state behavior
   (terminal COMPLETED -> canAffordNewSearch -> restart), NOT the n-002 storm.

## The REAL defect (test seam)
resolvedChainTargetTagForTest (referenceChainEvents.cpp:502) has two gates:
- gate 1: isLeakTag(object_tag) -> return 0 immediately (lateChunk carries its leak tag most of
  the time, esp. after every restart's clearTag+GC retag cycle)
- gate 2: cached chain must be from CURRENT search generation (source_search_ns == _search_start_ns)
Observable success window per search = [interception+poll build, next restart) ~= 1.4s per 2.4s
cycle. Scenario samples once per round + every 1.5s in the tail; in failing runs every sample
lands in a closed window for the whole run. The JFR dump contains up to 10 correct events the
whole time - the scenario just never dumps (requiredTargetTag==0 -> continue).

## Corrected fix (option A)
Seam-side leak-tag fallback in resolvedChainTargetTagForTest (ForTest code, exactly one caller:
StaticFieldGrowingCollectionScenario): when isLeakTag(object_tag), scan _resolved_chains for the
newest entry with event._target_tag == object_tag; return it. Leak tags are per-object stable
(pool, released only on object death), so no generation check needed and no numeric-tag-reuse
hazard (unlike frontier tags, which restartSearch re-mints from 1 - the documented reason for
gate 2). restartSearch INTENTIONALLY preserves _resolved_chains (referenceChains.cpp ~line 923
comment), so the previous search's chain is always present.

## Breakage surface (verified)
- getReferenceChainResolvedTargetTagForTest0: single Java caller (StaticFieldGrowingCollectionScenario only)
- Locks: scan runs under the seam's existing _engine_lock -> _resolved_chains_lock acquisition;
  no new locks, no allocation, bounded by cache size (dozens)
- Staleness accepted: chain may be from an earlier search; justified (heap position of lateChunk
  never changes; JFR dump matching already tolerates event age; scenario's passesRun gate covers
  post-creation ordering)
- Header comment at referenceChains.h:1385 documents the "0 for leak-tagged" contract - must be
  updated with the fallback
- v3 scenario representative (=LEAK_BUFFER the list) is independently broken 0/6: candidate klass
  becomes SynchronizedList -> no tracked instances -> no leak tags ever minted on any byte[] ->
  interception/discovery pipeline never engages for lateChunk. Must revert to byte[] rep (v2
  wiring) alongside the seam fix.
