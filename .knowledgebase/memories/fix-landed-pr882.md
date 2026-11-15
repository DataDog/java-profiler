---
id: fix-landed-pr882
title: Fix implemented, verified, PR #882 opened
kind: finding
tags: []
applies_to: []
source: implement-github-issue-sphinx/fix-landed-pr882
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# Fix implemented, verified, PR #882 opened

- Branch issue-592 rebased on origin/main (525a28442), pushed.
- Commits: 9303927f3 (musl t07_body dead-code removal: drop `ProfiledThread::release();
  return nullptr;`, keep pthread_cleanup_pop(0), add comment + __builtin_unreachable());
  b412cd098 (colima docs).
- Verified via colima/docker container gtests: musl and glibc debug,
  `:ddprof-lib:gtestDebug_thread_teardown_safety_ut` BUILD SUCCESSFUL; direct binary run:
  14/14 PASSED on musl incl. ForcedUnwindWithConcurrentSignalDoesNotCrash; 1/1 on glibc filter.
- spotlessApply run in container (host has no JDK).
- PR #882: Draft, label AI, body contains "Closes #592", template followed.
- No other defect-class instances: forced_unwind_ut.cpp loops end their functions (one
  already has __builtin_unreachable() at line ~198); libraryPatcher_linux.cpp already uses
  the idiom (pop(1)/unreachable).
- Design critique (524f9af7): no blocking findings; non-blocking items all addressed
  (comment wording, repo scan, PR-body history explanation, pop(0) kept).
