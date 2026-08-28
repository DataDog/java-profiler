---
id: find-lambda-fragments-calltrace-id
type: finding
status: confirmed
depends_on: [q-allocation-site-selection, find-age-heuristic-insufficient]
supersedes: []
related: [q-allocation-site-selection]
tags: [root-cause, referenceChains, livenessTracker, allocation-site, call-trace-id, lambda, tid, NEW-THIS-SESSION]
created: 2026-08-28
updated: 2026-08-28
---

# Lambda allocation fragments call_trace_id, breaking site clustering

## Context

Allocation-site clustering (commit `0b492612b`) keyed per-site tracking
on `call_trace_id` — the full stack trace hash at allocation time.

## Problem

On-pod verification showed `dominant_gens=1` for every class every
epoch, even klass_id=5 with `gen_count=25`. Root cause: lambdas.

Lambda allocation sites produce synthetic methods whose call stacks
vary slightly across instances — different callers above the lambda,
JIT inlining changes, etc. The full-stack hash (`call_trace_id`)
fragments what is logically one allocation site into many distinct
IDs. 12 leaking [B instances from the same logical site get 12
different `call_trace_id`s → 12 sites × 1 generation each → no
clustering signal.

## Evidence

Pod logs (PID 51584, build `0b492612b`):
```
foldKlassCountsLocked minted=1 for klass_id=371 dominant_site=30064777208 dominant_gens=1
foldKlassCountsLocked minted=1 for klass_id=278 dominant_site=30064778118 dominant_gens=1
foldKlassCountsLocked minted=1 for klass_id=302 dominant_site=30064778443 dominant_gens=1
```
All `dominant_gens=1` despite high per-class `gen_count` (15-25).

## Fix

Switch clustering key from `call_trace_id` to `tid` (thread ID).

Rationale:
- **Stable**: thread ID doesn't vary with stack trace jitter
- **Naturally separates leak from noise**: leaking [B all from
  tid=172 (`simulated-memory-leak`), noise [B from tid=284 (`s3-netty-2`)
- **Matches leak taxonomy**: static-field leaks typically allocated by
  one thread; thread-local leaks ARE the thread
- **Already in TrackingEntry**, no new data plumbing
- **Multi-thread shared leak**: all contributing tids have similar
  generation counts → pick any → still a leaking instance → correct
- **Noise thread with many short-lived instances**: few surviving
  generations → loses to leak tids

The only failure mode: one tid has many long-lived noise instances and
another has fewer long-lived leak instances with the same generation
count. But per-instance chain caching (cd68be618) emits chains for all
of them — the backend aggregates by class.
