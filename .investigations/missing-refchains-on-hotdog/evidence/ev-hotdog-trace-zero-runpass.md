---
id: ev-hotdog-trace-zero-runpass
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-cpu-pain-budget-starves-canary-passes]
tags: [pod-logs, on-pod, trace, runPass, pollWatchedTargets, canary]
created: 2026-08-25
updated: 2026-08-25
---

# 45-second continuous trace: zero `runPass`, 1472 `pollWatchedTargets`

## Command

```
kubectl logs -n profiling-stg prof-analyzer-hotdog-jb-c944876b9-f762h \
  -c prof-analyzer -f --since=1s > /tmp/hotdog_trace.log
```
run for a fixed ~45-second wall-clock window, captured 25,865 lines.

## Key counts

```
grep -c "runPass done"          -> 0
grep -c "pollWatchedTargets"    -> 1472
grep -c "LivenessTracker::selectLeakCandidates" -> 23925
grep -c "shouldRunPass"         -> 0
grep -c "canAffordNewSearch"    -> 0
grep -c "searchState"           -> 0
grep -c "canary pruned"         -> 0
grep -c "canary: admitted"      -> 0
```

`pollWatchedTargets` sample output:
```
[TEST::INFO] ReferenceChainTracker::pollWatchedTargets candidate_count=5
[TEST::INFO] ReferenceChainTracker::pollWatchedTargets canary: klass_id=33319 qualifies but all 5 slots are occupied - not tracked this search
[TEST::INFO] ReferenceChainTracker::pollWatchedTargets candidate[0] klass_id=150
```

## Interpretation

`pollWatchedTargets()` is called unconditionally every `threadLoop()`
iteration (`referenceChains.cpp:801`, not gated on `should_run`), so its
1472 hits in 45s just confirm the thread is alive and looping at roughly
its expected cadence. The complete absence of any `runPass`-family log line
in the same window is the actual finding: `shouldRunPass()` is returning
false on every single iteration for the full 45 seconds. Since the loop's
own cadence sleeps cap out at ~1-2s per idle iteration (see
`find-threadloop-presleep-blocks-back-to-back`), a 45s silent stretch needs
a longer-lived gate — pointing at `_cpu_pain_budget.canStartNow()`
(`referenceChains.cpp:893`), the only branch in `shouldRunPass()` with no
`TEST_LOG`, as the mechanism (see `find-cpu-pain-budget-starves-canary-passes`).

## Methodology note (do not re-waste time on this)

`kubectl logs --since=<long duration>` (tried `90m`) and `--since-time=<pod
start>` both silently returned only ~45-60 seconds of actual content on this
pod — the extremely high `TEST_LOG` volume (tens of thousands of lines per
minute) fills whatever retention buffer the log driver keeps, with no error
or warning when older lines are unavailable. Historical evidence from
earlier in this pod's lifetime (the 5 confirmed abandon cycles referenced in
`ev-postfix-onpod-live-verification`) is no longer retrievable from live pod
logs at all. For any future retrospective query on this pod, do not rely on
`--since`/`--since-time` for windows longer than roughly a minute — capture
forward with `-f` instead if you need a clean window.
