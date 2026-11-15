---
id: find-c7-enabled-race
title: C7 formally valid: _enabled plain bool read by GC callbacks; benign at #797 (same-value write), real race at #798 (onThreadStart reader, false writes)
kind: finding
tags: [pr-797, atomics, lifecycle]
applies_to: []
source: feedback-1/find-c7-enabled-race
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C7 formally valid: _enabled plain bool read by GC callbacks; benign at #797 (same-value write), real race at #798 (onThreadStart reader, false writes)

## Reasoning chain
Never cleared by stop(); GC events never disabled. Recommend volatile+loadAcquire/storeRelease or std::atomic<bool>. Precedent LivenessTracker::_enabled plain bool pre-PR.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/B.md. Lines at 9521394e8.
