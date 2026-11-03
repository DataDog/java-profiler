---
id: find-fixes-implemented
title: Fixes for #3/#4/#6/#8/#10 implemented (uncommitted) in /tmp/wt-pr797
kind: finding
tags: [fixes, pr-797]
applies_to: []
source: feedback-1/find-fixes-implemented
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Fixes for #3/#4/#6/#8/#10 implemented (uncommitted) in /tmp/wt-pr797

## Reasoning chain
User approved: #10 nanotime, #3 helper, #6 new helper, #8 cheap fix, #4 all proposed fixes, then regtests + coverage gaps.
- #10: refchain pass timing TSC::ticks() -> OS::nanotime(); *_ticks -> *_ns; ticks_to_millis -> /1000000; tsc.h include dropped (anchors, traversal).
- #3: arch.h atomicExchangeRelaxed(); used in ClassTagAllocator::resetForTest().
- #6: common.h ASSERT_ONLY(s) keyed on !NDEBUG; t_inGCCallback decl/extern/guard use it.
- #4: FrontierTable::capacity()/maxCapacity() take shared lock; reconstructChain hoists hop bound;
  trackLeakAccumulation ancestor walk under one withSharedLock + lookupLocked, early stop on
  LeakParentFanoutEntry::ancestors_recorded (seed inserts false); wrong deadlock comment fixed.
- #8: LivenessTracker::_container_limit_resolved storeRelease after getContainerMemoryLimit() in
  initialize_table(); onGC loadAcquire-gates getContainerMemoryUsage(). Key fact: initialize() sets
  _initialized (livenessTracker.cpp:2131) BEFORE initialize_table() (:2162), so _initialized cannot
  be the publish point. Threading comment at os_linux.cpp cgroup globals.
- Tests: TrackLeakAccumulationWalksPastSeededAncestor, TrackLeakAccumulationSiblingsShareRecordedAncestors
  (erases root to observe the early stop; accessor eraseLeakParentFanout), OnGCSkipsContainerUsageUntilLimitResolved
  (friend class LivenessTrackerTestAccessor - one-line production change).
- DEBUG rename proposal filed as PROF-16129 (not implemented).

## Evidence
- macOS: gtestRelease+gtestDebug full suite green; buildRelease (-DNDEBUG) green.
- Linux workspace-jb x86_64: os_linux.cpp compiled in gtest debug+release; new tests pass both configs.
- Mutation checks: seed inserting ancestors_recorded=true -> WalksPastSeededAncestor fails; removing early break
  -> SiblingsShare... fails; removing #8 gate on Linux -> OnGCSkips... fails (got 11070758912 vs 0).

## What this rules out
- Container-gate test is meaningless on macOS (getContainerMemoryUsage() always -1) - Linux-only signal.
