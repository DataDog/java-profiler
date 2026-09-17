---
id: ev-leaktag-onpod-round12
type: evidence
status: confirmed
depends_on: [ev-leaktag-onpod-round11, find-anchor-live-feed-design]
related: [find-anchor-holder-eviction, find-option-c-descend-walk-design]
tags: [pod-verification, round-12, wrapper-class, synchronized, diagnostic-fix, NEW-THIS-SESSION]
created: 20260915
updated: 20260915
---

# Pod round 12 (build 5218bd1dd + diagnostic fix): wrapper class is
# SynchronizedRandomAccessList, NOT UnmodifiableRandomAccessList

Deployed build 5218bd1dd (includes 8ca24a524 round-12 diagnostic) to pod
`prof-analyzer-hotdog-jb-d9d8cf-plwpx` (JVM 244587, started 07:26 UTC).
The diagnostic fired ZERO times — the wrapper never appeared in any anchor
walk.

## ROOT CAUSE: wrong wrapper class name

Bytecode inspection of `prof-analyzer-0.0.1.jar` on the pod reveals:

```
private static final java.util.List<byte[]> LEAK_BUFFER;
// static initializer:
86: new           // class java/util/ArrayList
90: invokespecial // Method java/util/ArrayList."<init>":()V
93: invokestatic  // Method java/util/Collections.synchronizedList:(Ljava/util/List;)Ljava/util/List;
96: putstatic     // Field LEAK_BUFFER:Ljava/util/List;
```

**LEAK_BUFFER = `Collections.synchronizedList(new ArrayList<>())`**, NOT
`Collections.unmodifiableList`. The wrapper class is
`Collections$SynchronizedRandomAccessList`, NOT
`Collections$UnmodifiableRandomAccessList`.

The round-12 diagnostic (commit 8ca24a524) checked for
`strstr(sig, "UnmodifiableRandomAccessList")` — it will NEVER match the
actual wrapper. **Fixed this session**: broadened the check to also match
`SynchronizedRandomAccessList` and `SynchronizedList`. Rebuilt and
redeployed (JVM 244587).

**Implication for round 11**: the "wrapper WAS walked" observation at
21:10 UTC (ev-leaktag-onpod-round11) identified the wrapper as
`UnmodifiableRandomAccessList` — that was a DIFFERENT unmodifiable list
(a decoy), not the LEAK_BUFFER wrapper. The LEAK_BUFFER wrapper
(`SynchronizedRandomAccessList`) was never walked in round 11 either.

## Secondary finding: rotation phase always truncated

All 11 `walkStaticFieldAnchors selected=20` lines in the container log
show `truncated=1` with only `walked=1-13` of 20 selected anchors. The
collector's cursor (`_static_anchor_rotation_cursor`) advances past ALL
20 selected entries, but collector-sourced unwalked anchors are
**deliberately not requeued** (only FIFO-sourced unwalked anchors are
requeued to the FIFO front). So an anchor selected at position 14-20 that
is truncated before being walked is skipped until the cursor wraps around
the entire frontier table (~50k entries / 20 per pass = ~2500 passes =
~2.3 hours at 3.3s/pass).

The wrapper, if admitted as root-attached, is only walked when:
1. The cursor rotates to its position (~2.3 hours), AND
2. The walk is not truncated before reaching it

This explains why the wrapper was "never walked" in this recording
(54 min of search before terminal) and was only intermittently walked
in round 11 (hours of recording).

## Search state

The candidate (klass_id=8 [B) flapped out due to self-reinforcing dropout
(same pattern as round 11): candidate slot drops → watched-tid boost
clears → tracked sample thins → negative slope keeps candidate out.
`selectLeakCandidates returning 0 candidates` → `search_state=2`
(terminal). secondsToOOM ~4400s (73 min to OOM); urgency path opens at
<1800s (~50 min away).

## Next steps

1. Wait for urgency path (secondsToOOM < 1800) → urgent search opens
   without candidate, urgency tracking tags everything (100% admission)
   → search restarts → sweep + rotation run → wrapper walked → diagnostic
   fires with correct class name.
2. Consider fixing the rotation truncation issue: requeue collector-sourced
   unwalked anchors (same as FIFO requeue), or prioritize anchors with
   leak-tagged children.
3. The diagnostic fix (SynchronizedRandomAccessList) is deployed but
   uncommitted — commit after verification.
