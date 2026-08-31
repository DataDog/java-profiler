---
id: ev-leaktag-onpod-round1
type: evidence
status: verified
related: [find-leak-tag-pool-implementation, find-ema-batch-collapse, find-leaktag-jfr-field-misalignment, q-coverage-tracking-per-combination]
tags: [pod-logs, on-pod, post-fix, live-verification, leak-tag, batch-collapse, jfr, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# On-pod round 1 of the leak-tag redesign (build 1ce2b4f03)

Pod prof-analyzer-hotdog-jb-86d8bf5854-zng9s, PID 32849 (restart 10:22Z).
15-min log capture (`kubectl logs --since=15m`, analyzed as
/tmp/hotdog-15m.log) + uploaded recording 20260831-103955.

## What worked

- `tagLeakInstances tagged=28` — pool tagging live, re-tagging idempotent
  (already-tagged entries counted, not re-acquired).
- Representative JVMTI tag read back 0x4000000F (real pool tag).
- Adaptive CPU: multiplier=15.0 firing (canary active, no emergency),
  refill_rate=0.45.
- Chains cached for 8 discovered [B instances and drained to JFR:
  `Profiler::dump reference-chain batch=8 write_dropped=0`.
- Depth==0 filter active (no depth-0 chains emitted).
- Search/rotation/sweep all running; frontier 220-225k.

## What failed

- **batch_size=2** (find-ema-batch-collapse): 3 runPass/15min, ~1000 gotw
  calls per pass, 10.4s CPU spend per pass (debt 10436ms), edges/pass ~100.
- **emergency never fired** — wrong counter (frontier progress, see node).
- **The 8 chains are noise**: depth=1 jni_local/stack_local, targetTags are
  frontier tags (7167/7267/7291/7554/7807/7810/7818/7821), NOT leak tags —
  admitted via the ordinary path (leak_tag=0). BFS (crawling at batch=2)
  never reached the leak-tagged 78MB [B instances.
- **leakTag column garbage** (find-leaktag-jfr-field-misalignment):
  75/50 on rows with context, 0 without; user's "only two entries tagged"
  was the misparse, not the table state.
- **Marker re-tag leftover found in code**: pollWatchedTargets' tag==0
  branch still SetTag(MARKER_TAG_BASE - slot) — resurrects the dead
  mechanism when a rep is temporarily untagged. Removed in 0db70994d.

## Unresolved

- Whether the leak-tag interception fires on-pod (no TEST_LOG in that
  build; the 8 "discovered" came from the ordinary auto-mark). The gtest
  (LeakTagInterceptionConvertsToFrontierTagAndCorrelates) proves the
  mechanism; 0db70994d adds the interception TEST_LOG for on-pod proof.
- Coverage semantics still per-object (q-coverage-tracking-per-combination).

Fix round 2 = commit 0db70994d (alignment + AIMD + deadline + priority
tagging + emergency counter + marker re-tag removal). Awaits redeploy.
