---
id: find-c4-maxcap-hoist
title: C4 valid (unnecessary), expensive overstated: maxCapacity() exclusive-locks per hop on cold path; hot sibling in STW trackLeakAccumulation
kind: finding
tags: [pr-797, frontier, spinlock, stw]
applies_to: []
source: feedback-1/find-c4-maxcap-hoist
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C4 valid (unnecessary), expensive overstated: maxCapacity() exclusive-locks per hop on cold path; hot sibling in STW trackLeakAccumulation

## Reasoning chain
maxCapacity() exclusive lock (frontier.h:246); _table_max_cap immutable outside test seam; sibling referenceChainEvents.cpp:185 already hoists. Hot sibling referenceChainWalk.cpp:594 per-hop lookup inside FollowReferences. Comment at referenceChainWalk.cpp:620-626 claims pending-writer deadlock that SpinLock (spinLock.h:93-98) cannot produce.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/B.md. Lines at 9521394e8.

## Follow-up (2026-10-01)
- Hot path: trackLeakAccumulation ancestor loop (walk.cpp:592-606), with up to hop_cap=200 hops per watched admitted edge. Each hop is a lookup plus an unordered_map find/emplace, inside STW.
- Fix 1: break when the ancestor is already in _leak_parent_fanout (the loop only emplaces missing entries). This turns O(N×depth) into O(N+depth). Caveat at the hop cap.
- Fix 2: withSharedLock + lookupLocked around the loop only. insert() at :512 precedes the call at :530.
- Proposed only; the user has not approved code changes.
