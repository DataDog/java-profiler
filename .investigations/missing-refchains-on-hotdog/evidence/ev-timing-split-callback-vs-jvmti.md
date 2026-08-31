---
id: ev-timing-split-callback-vs-jvmti
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-candidate1-never-tagged, dead-hard-reference-kind-filter]
tags: [timing, callback, jvmti, FollowReferences, safepoint, overhead-split, NEW-THIS-SESSION]
created: 2026-08-26
updated: 2026-08-26
---

# Timing split: our callback 5-17%, JVMTI heap-walking 83-92%

## Setup

Temporarily bumped `_pass_deadline_ns` to 200ms (override at
`referenceChains.cpp:2337`, commit `fd18425c6`) and added an RAII
`ScopedCallbackTimer` that accumulates TSC ticks inside
`heapReferenceCallback()` only when `static_field_seed` is true. After each
`FollowReferences` call, logs:
- `follow_ms` — total FollowReferences wall-time
- `callback_ms` — cumulative time in our callback code
- `jvmti_ms` — follow - callback (JVMTI's own object-iteration/metadata-walk cost)
- `callback_pct` — our share of total
- `callback_count` — total callbacks delivered

## Data (31 samples, sorted)

| follow_ms | callback_ms | jvmti_ms | callback_pct | callbacks |
|-----------|-------------|----------|--------------|-----------|
| 3-4       | 0           | 3-4      | 5-9%         | 4.5-6.6k  |
| 5-6       | 0           | 4-6      | 5-7%         | 6.2-8.2k  |
| 7-8       | 0-1         | 6-8      | 5-10%        | 7.1-16k   |
| 9-11      | 0-1         | 8-10     | 5-12%        | 8.3-13.7k |

One outlier at 35% (10ms follow, 3ms callback).

## Conclusion

Our callback code (`admitObject` + quota check + kind_counts tally) is
**5-17% of total wall-time** (0-1ms per chunk). JVMTI's own heap-walking
(reading object metadata, iterating class fields, resolving oops,
delivering callbacks) is **83-92%** (3-10ms per chunk).

**Deferring `admitObject` out of the safepoint would save at most 5-17%**
— not enough to fix truncation under a 50ms deadline. The bottleneck is
JVMTI delivering 5k-16k CP callbacks per chunk, not our callback code
processing them.

The only way to avoid the CP callback volume is to not let
`FollowReferences` descend into the class's metadata graph at all — i.e.,
use `GetClassFields` + JNI `GetStaticObjectField` to read static fields
directly, without triggering CP/interface/superclass callbacks. This
would also eliminate the STW entirely (both APIs are non-Heap-category,
no `VMThread::execute()`).

## Side effect: sweep completes cleanly at 200ms

With the 200ms deadline, **all chunks complete without truncation**
(`truncated=0` on every chunk). `edges_admitted` jumped from 0-5 (under
50ms shared budget) to 369-2155 per chunk. A full lap completed
(`cycle_complete=1` observed, `last_static_field_class_count` advanced
from 33677 → 33752). This confirms the sweep mechanism is healthy —
the truncation was a budget-sharing problem, not a sweep-cost problem.
