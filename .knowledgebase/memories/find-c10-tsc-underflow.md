---
id: find-c10-tsc-underflow
title: C10 partially valid: x86 rdtsc may step back; unguarded u64 deltas -> ~6e9 ms pain debt disables RC search for process life; 5 such sites
kind: finding
tags: [pr-797, tsc, pacing, pain-budget]
applies_to: []
source: feedback-1/find-c10-tsc-underflow
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C10 partially valid: x86 rdtsc may step back; unguarded u64 deltas -> ~6e9 ms pain debt disables RC search for process life; 5 such sites

## Reasoning chain
tsc.h:88 rdtsc-_offset. ticks_to_millis wraps to ~6e9 ms -> _search_pain_ms (traversal:1070) -> canAffordNewSearch false. Sites anchors:109, traversal:204,629,886,1041. Comment traversal:1042 falsely says monotonic. Recommend OS::nanotime() for durations, keep TSC for JFR _start_time.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/D.md. Lines at 9521394e8.

## Follow-up (2026-10-01)
- nanotime cost is fine: every TSC pair brackets one FollowReferences (an STW heap op of ms), O(batches+anchors) per pass. Linux vDSO clock_gettime costs tens of ns (a syscall of about 1µs without vDSO); macOS uses mach_absolute_time. The same function already uses nanotime around GetObjectsWithTags (traversal:544-548).
