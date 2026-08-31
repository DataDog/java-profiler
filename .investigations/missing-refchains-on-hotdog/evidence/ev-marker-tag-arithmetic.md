---
id: ev-marker-tag-arithmetic
type: evidence
status: confirmed
depends_on: [ev-livelock-pod-logs]
supersedes: []
related: [find-marker-tag-slot-index-mismatch]
tags: [marker-tag, arithmetic, proof, referenceChains]
created: 2026-08-24
updated: 2026-08-24
---

# The logged marker tag decodes to slot 1, but the code uses index 0

## Definition (verified in the repo at HEAD 8114019c2)

`ddprof-lib/src/main/cpp/referenceChains.h:1924`

```cpp
static constexpr jlong MARKER_TAG_BASE = -(1LL << 62);
```

Pre-tagging assigns `MARKER_TAG_BASE - i` per candidate slot `i`
(`referenceChains.cpp:3384`, inside the `_candidate_count == 0` block).

## Arithmetic run in-session

```
$ python3 -c "base=-(1<<62); tag=-4611686018427387905; print(base); print(tag); print(base-tag)"
MARKER_TAG_BASE = -4611686018427387904
observed tag    = -4611686018427387905
decoded slot    = 1
```

The live log line reports `candidate[0]` while carrying the marker tag of
slot **1**. That mismatch is the bug: `pollWatchedTargets()` indexes the
per-candidate arrays with the loop position, not with the slot encoded in
the tag it just read.
