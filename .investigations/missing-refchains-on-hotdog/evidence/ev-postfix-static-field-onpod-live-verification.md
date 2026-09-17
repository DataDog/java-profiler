---
id: ev-postfix-static-field-onpod-live-verification
type: evidence
status: confirmed
depends_on: [find-static-field-sweep-cursor-fix]
supersedes: []
related: []
tags: [pod-logs, on-pod, post-fix, live-verification, static-field, cursor, lap-truncation, NEW-THIS-SESSION]
created: 2026-08-25
updated: 2026-08-25
---

# Static-field sweep cursor/lap-truncation fix confirmed live on hotdog pod

## Deployment proof

Resynced by user. JVM PID 92618 (started 15:29). Scratch `.so` md5
`aeab8726e90e5f21e33393c3bfea043e`. `strings` on that file confirms
presence of `_static_field_sweep_cursor`, `static_field_cycle_complete`,
and the exact new `TEST_LOG` format `cycle_complete=%d sweep_cursor=%d`.

## Cursor advances correctly, real edges admitted

Multiple `runPass` samples across two separate check windows show
`sweep_cursor` advancing by exactly 512 per call, e.g.:

```
6656 -> 7168 -> 7680 -> 8192 -> 8704 -> 9216 -> 9728 -> 10240 -> 10752 -> 11264
32768 -> 33280 -> 33792 -> [wrap to 0] -> 512 -> 1024 -> 1536 -> 2048 -> 2560 -> 3072
```

`edges_admitted` per chunk is now real and varying (contrast with the
pre-fix pattern of 0-1 forever, see `find-static-field-sweep-never-completes`):
`3, 0, 1, 27, 0, 15, 1, 98, 7, 7` in one window; `331, 414, 737, 59` in
another; a later 2-minute check window showed `84, 320, 198` on
successive `runPass done` lines with `frontierSize` growing from 86817
to 87335 in step.

## Lap-truncation-latch behaves exactly as designed

Direct confirmation of the fix's core correctness property: a lap is
only "done" (`cycle_complete=1`) if **zero** chunks within it truncated.
Observed concrete example: chunk at `sweep_cursor=33792` reported
`truncated=1`; the very next chunk closed the lap
(`edges_admitted=59 truncated=0`, `sweep_cursor` wrapped to `0`) — and
`cycle_complete` was still correctly `0` for that closing chunk, because
an earlier chunk in the same lap had truncated. This is the exact
semantics the fix was designed to produce (see
`find-static-field-sweep-cursor-fix`'s "gated on cycle_complete" section),
observed under real production load, not just in the gtest mock.

`cycle_complete=1` has not been observed in any sample checked so far
(multiple windows, ~10+ minutes combined) — plausible given how large the
JDK bootstrap classlist tail is relative to the chunk size
(`STATIC_FIELD_SWEEP_CHUNK_CLASSES=512`); not itself evidence of a bug
since forward progress (cursor advancing, edges accumulating) is directly
observed every call.

## Health of the rest of the pipeline, unchanged/still good

`CANARY_STUCK` count: 0 across all windows checked this round. Frontier
grows cleanly and monotonically (e.g. 86817 -> 87137 -> 87335, and
separately observed growing past 64k earlier in the same deployment) with
no restarts/wipes observed.

## What this does NOT show

End-to-end candidate resolution is still 0/5 in every sample checked —
see `find-candidate1-never-tagged` and
`find-candidates-234-die-before-resolution`. The sweep mechanism working
correctly is necessary but evidently not sufficient; the bottleneck has
moved downstream of admission into BFS reach / candidate lifetime.
