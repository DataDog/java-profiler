---
id: jvmti-class-tags-negative-shared-env
title: JVMTI object tags are shared per env; class-identity tags are negative and a positive tag on a class is never a class tag
kind: finding
tags: [jvmti, tags, refchains, liveness]
applies_to: []
source: feedback-1/find-c2-settag-779-conflict
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


JVMTI tags are per `jvmtiEnv`, and everything that uses `VM::jvmti()` shares one tag per object.
The reference-chain tracker and LivenessTracker use the tag on a class object as its identity and
mint it from `ClassTagAllocator`, which hands out strictly negative values. Positive tags on class
objects occur legitimately: `heapReferenceCallback()` admits a not-yet-class-tagged class object
reached over a non-CLASS edge as an ordinary frontier object (frontier tags are positive). Any
other feature that stores data in a class tag through the same env collides with both.

Rules:
- Never adopt a positive tag as a class tag. `ClassTagAllocator::getOrMint()` returns 0 for it, and
  `resolveLoadedClasses()` neither adopts nor re-resolves positive tags.
- A feature that needs its own per-class tag data should obtain a separate `jvmtiEnv` (another
  `GetEnv` call) rather than share `VM::jvmti()`. Masking bits in a shared tag does not work:
  `GetObjectsWithTags` matches exact values and JVMTI has no tag compare-and-set.
