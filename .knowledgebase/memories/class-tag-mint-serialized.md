---
id: class-tag-mint-serialized
title: Class-tag minting must go through ClassTagAllocator::getOrMint() (GetTag/SetTag under one mutex)
kind: finding
tags: [jvmti, tags, concurrency, refchains, liveness]
applies_to: [ddprof-lib/src/main/cpp/classTagAllocator.h]
source: feedback-1/find-c9-classtag-race
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


JVMTI has no tag compare-and-set. The reference-chain tracker (`resolveLoadedClasses()`,
`resolveContainerInterfaceTags()`) and `LivenessTracker::mintStableClassTagIfNeeded()` can tag the
same class concurrently. A bare GetTag -> mint -> SetTag sequence loses updates: one side caches
a tag the class object no longer carries, which silently breaks attribution for that class for
the rest of the session (no crash).

`ClassTagAllocator::getOrMint()` runs the sequence under a function-local `Mutex`. It is a
blocking mutex, not a spinlock, because it is held across JVMTI calls and application threads can
be callers. New class-tag minting sites must use it. `ClassTagGetOrMintRaceTest` (8 threads, slow
injected GetTag) fails if the lock is removed.
