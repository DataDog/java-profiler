---
id: issue-target-identified
title: Issue #592 target identified: t07_body in thread_teardown_safety_ut.cpp
kind: finding
tags: []
applies_to: []
source: implement-github-issue-sphinx/issue-target-identified
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# Issue #592 target identified: t07_body in thread_teardown_safety_ut.cpp

**Finding (confirmed):** Issue #592's line references (sigsetjmp handler at 295; dead
`__pthread_unregister_cancel` / `sigaction` restore / `ProfiledThread::release()` at ~311-313,
inside a `while(true){pthread_testcancel();usleep(100);}` loop) match EXACTLY the glibc T-07
body in `ddprof-lib/src/test/cpp/thread_teardown_safety_ut.cpp` as merged by PR #591
(commit bcbbfcb81), NOT the production `run_with_cleanup` in libraryPatcher_linux.cpp.

## Evidence
- `git show bcbbfcb81:ddprof-lib/src/test/cpp/thread_teardown_safety_ut.cpp` lines 295, 306-313.
- PR #591 "Fix crash at thread exit" (merged); sphinx review finding turned into issue #592.

## State on main
- glibc path ALREADY fixed on main: dead statements removed; replaced by comment
  ("No matching __pthread_unregister_cancel...") + `__builtin_unreachable()`
  (current main lines ~314-329). Fix reached main via merge-queue commit a4a9cac35
  (content originated in PR-branch commit 2d69767d2 "Fix review comments").
- musl path (lines ~340-358) still has the same dead pattern:
  after `while(true){pthread_testcancel();usleep(100);}`:
  `pthread_cleanup_pop(0);` (lexically REQUIRED — push/pop are a paired do/while(0) macro
  on both glibc and musl) then dead `ProfiledThread::release(); return nullptr;`.
