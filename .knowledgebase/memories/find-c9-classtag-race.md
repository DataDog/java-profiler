---
id: find-c9-classtag-race
title: C9 valid: GetTag/SetTag/adopt not atomic across RCT and LivenessTracker; lost update -> silent long-lived attribution loss, no crash
kind: finding
tags: [pr-797, classTagAllocator, jvmti-tags, race]
applies_to: []
source: feedback-1/find-c9-classtag-race
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C9 valid: GetTag/SetTag/adopt not atomic across RCT and LivenessTracker; lost update -> silent long-lived attribution loss, no crash

## Reasoning chain
Case1 RC last: LT stable_class_tag stale forever -> trackLeakAccumulation never matches. Case2 LT last: _class_tags misses actual tag -> no auto-mark discovery, klass ids 0. Sibling referenceChainAnchors.cpp:382-399; false comment livenessTracker.cpp:1047-1050. Fix: ClassTagAllocator::getOrMint under leaf blocking mutex.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/D.md. Lines at 9521394e8.
