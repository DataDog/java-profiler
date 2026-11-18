---
id: find-all-review-items-fixed
title: All 10 review items of 5357763282 addressed (commits ada1ee2d8, 58d965649)
kind: finding
tags: [pr797, review, class-tags, cgroup, locking]
applies_to: []
source: feedback-1/find-all-review-items-fixed
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# All 10 review items of 5357763282 addressed (commits ada1ee2d8, 58d965649)

## Reasoning chain
User required no deferrals. Second commit 58d965649 covers #1 (unistd include removed),
#2 partial (ClassTagAllocator::getOrMint rejects positive tags; resolveLoadedClasses never
adopts/re-resolves positive tags), #5 (ExclusiveLockGuard/SharedLockGuard at all manual
lock sites; logging/counters moved outside locks), #7 (volatile _enabled + storeRelease/loadAcquire
via enabled()), #8 compute-once (static-local limit, usage file picked once in g_memory_usage_file),
#9 (getOrMint serializes GetTag/SetTag under a function-local Mutex shared with LivenessTracker).

## Evidence
- macOS gtestDebug/gtestRelease/buildRelease: 0 failures.
- workspace-jb x86_64: referenceChains_ut 150/149, livenessTracker_ut 52/52 debug+release.
- Mutations caught: removing mint lock -> ConcurrentCallersAgreeOnOneTag fails; dropping
  positive-tag rejection -> GetOrMintMintsOnceAndRejectsPositiveTags fails; onGC gate forced
  true on Linux -> OnGCSkipsContainerUsageUntilLimitResolved fails (needs the up-front
  OS::getContainerMemoryLimit() call in the test).

## What this rules out
- #2 still not fully solvable in #797: #779 positive tags on class objects still hit the
  `*tag_ptr > 0` frontier arm on JDK 8; full isolation (separate jvmtiEnv) belongs in #779.
