---
id: find-threadloop-presleep-blocks-back-to-back
type: finding
status: confirmed
depends_on: []
supersedes: []
related: [find-cpu-pain-budget-starves-canary-passes]
tags: [bug, referenceChains, threadLoop, cadence, canary, design-contradiction]
created: 2026-08-25
updated: 2026-08-25
---

# `threadLoop()` sleeps `cadence_ns` unconditionally BEFORE `shouldRunPass()` runs

## Reasoning chain

`threadLoop()` (`referenceChains.cpp:637-802`) contains two `OS::sleep`
call sites per iteration:

1. `:736-738` — `if (cadence_ns > 0) { OS::sleep(cadence_ns); }`, with
   **no other guard**, sitting right after the comment block at `:728-735`
   that claims "Run passes back-to-back... the cadence sleep is only kept
   as a fallback for an idle search... to avoid busy-waiting." This sleep
   runs on *every* iteration, unconditionally — including ones where a
   canary search is actively converging and `shouldRunPass()` (called
   later, at `:771`) would return true for the "run immediately" canary
   bypass.
2. `:775-776` — `if (!should_run && cadence_ns > 0) { OS::sleep(cadence_ns);
   ...}`, which correctly matches the comment at `:772-774` ("Only sleep
   when idle... skip the sleep to run passes back-to-back").

Only the second sleep is actually conditioned on `should_run`. The first
one contradicts its own neighboring comment: it fires before `should_run`
is even computed, so a canary-bypass-eligible pass still incurs one full
`cadence_ns` sleep per iteration regardless. On an idle iteration
(`should_run == false`), **both** sleeps fire back to back, doubling the
idle period to ~2×`cadence_ns` instead of the intended ~1×.

## Evidence

Read directly, `referenceChains.cpp:690-801` (see exact line numbers above).
No live-log evidence needed beyond the source itself — this is a structural
control-flow reading, not a runtime behavior that varies by heap state.

## What this rules out

Nothing on its own — this is an independent, always-reproducible ~1-2s/
iteration ceiling on pass frequency, not something that varies with heap
size or debt like `find-cpu-pain-budget-starves-canary-passes`. It cannot,
by itself, explain a 45-second silent window (max ~2s per idle iteration),
but it does mean that even once the pain-budget gate clears, the canary
bypass is still not truly "back-to-back" as designed — every pass, canary
or not, pays at least one `cadence_ns` sleep first.

## Not yet done

Not fixed. This is a design-level question (should the first sleep be
removed, or moved after the `should_run` check, or merged with the second
sleep block into one guarded sleep) that should be proposed to the user
before editing `threadLoop()`'s control flow, since it's core BFS-thread
scheduling shared by every reference-chain search, not just canary ones.
