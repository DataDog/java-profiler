---
id: find-ages-vector-not-cleared
type: finding
status: confirmed
depends_on: [q-dominant-gens-still-one-with-tid]
supersedes: []
related: [q-dominant-gens-still-one-with-tid]
tags: [bug, fix, referenceChains, livenessTracker, ages, vector, inflation, NEW-THIS-SESSION]
created: 20260828
updated: 20260828
---

# ages vector not cleared between epochs

## Context

Per-thread diagnostic (5e4493dbf) showed `gen_count=33` for klass_id=4
but all threads had `age_count=1`. User challenged: 11 distinct ages
across 5 threads means at least one thread has ≥3 ages — mathematically
impossible to have all threads at 1.

## Root cause

`KlassCountScratch::ages` is a `std::vector<u32>`. When the scratch
slot is reused across epochs (after `_klass_count_scratch_size = 0`),
the vector is **never cleared**. `push_back` adds to stale ages from
previous epochs. So `gen_count=33` was accumulated across multiple
epochs, not within one.

Meanwhile `oldest_count` and `thread_count` ARE reset to 0, so
per-thread tracking is per-epoch only.

## Impact

- Logged `gen_count` was inflated (cumulative across epochs)
- Ring-buffer slope was **unaffected** — it measures rate of change
  of `ages.size()`, which equals the per-epoch increment regardless
  of the absolute value
- So the leak signal was correct, but the diagnostic logs were
  misleading

## Fix (commit 36c7fc8c8)

Added `slot.ages.clear()` before `slot.ages.push_back((u32)age)` in
the new-slot branch of `accumulateKlassCount()`. After fix, on-pod
logs show `gen_count=1` for a class with 1 surviving object per epoch
— correct.
