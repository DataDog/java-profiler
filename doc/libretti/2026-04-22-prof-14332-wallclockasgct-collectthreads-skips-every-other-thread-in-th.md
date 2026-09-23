---
spec_id: REQ-PROF-14332
source: jira
source_ref: PROF-14332
title: WallClockASGCT collectThreads skips every other thread in the no-filter fallback
status: draft
clarity_score: null
created: 2026-04-22
implementing_session: null
implemented_pr: null
---

# WallClockASGCT collectThreads skips every other thread in the no-filter fallback

## Summary

In `WallClockASGCT::timerLoop`, the `collectThreads` lambda's no-filter  
fallback advances the `ThreadList` iterator twice per loop body, silently  
skipping every other thread when the wallclock thread filter is disabled.

## Location

`ddprof-lib/src/main/cpp/wallClock.cpp:180-190`

```cpp
ThreadList *thread_list = OS::listThreads();
while (thread_list->hasNext()) {
    int tid = thread_list->next();           // <-- read #1
    // Don't include the current thread
    if (tid != OS::threadId()) {
        tids.push_back(tid);
    }
    tid = thread_list->next();               // <-- read #2 (unguarded!)
}
delete thread_list;
```

The second `thread_list->next()` runs unconditionally at the tail of each  
iteration; the next `hasNext()` check at the top of the loop sees the  
cursor already advanced past the last-handled tid. Net effect: only the  
1st, 3rd, 5th, ... threads in `/proc/self/task` are pushed into `tids`;  
the rest are dropped silently.

Additionally, when the list has an odd count, the final `next()` call  
reads past the end of the array — `next()` in the Linux implementation  
returns `_thread_array[_index++]` without a bounds check, so a caller  
running against a short list can read garbage.

## Impact

When `threadFilter->enabled()` is false (no context-based wallclock  
filtering), every wallclock tick samples only half the eligible threads,  
producing under-sampled wallclock profiles that aren't diagnosable from  
the output.

The typical `enabled()` path (context filter active) is unaffected; this  
only bites on the fallback.

## Fix

Remove the spurious extra `tid = thread_list->next();` at line 187.  
The `while (thread_list->hasNext()) { tid = thread_list->next(); ... }`
pattern is correct — one `next()` per iteration.

## Discovery

Flagged by a muse chorus review of PR-to-be [jb/signal-origin-validation  
branch](https://github.com/DataDog/java-profiler/tree/jb/signal-origin-validation)
(hypnos-augur finding #15) as an unrelated out-of-scope pre-existing bug.

## Scope

Pre-existing — not introduced by the signal-origin-validation work.  
Filed separately so it can land on its own small PR without blocking that  
work or being lost in the review.
