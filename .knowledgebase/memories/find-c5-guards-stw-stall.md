---
id: find-c5-guards-stw-stall
title: C5 valid maintainability; ~60 manual pairs, 4 early-return; unflagged STW stall on _resolved_chains_lock fixed only in #798
kind: finding
tags: [pr-797, spinlock, guards, stw, stack-layering]
applies_to: []
source: feedback-1/find-c5-guards-stw-stall
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C5 valid maintainability; ~60 manual pairs, 4 early-return; unflagged STW stall on _resolved_chains_lock fixed only in #798

## Reasoning chain
invalidateResolvedChain in heapReferenceCallback (referenceChainWalk.cpp:423) takes lock dump thread holds while copying cache (referenceChainEvents.cpp:768-773). rc-4 deferResolvedChainInvalidation fixes it but is a SpinLock and unbounded (prior trail wrong about mutex + MAX_PENDING_CHAIN_INVALIDATIONS).

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/B.md. Lines at 9521394e8.
