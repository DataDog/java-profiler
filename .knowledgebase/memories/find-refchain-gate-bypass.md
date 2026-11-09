---
id: find-refchain-gate-bypass
title: Reference-chain collector ran whole-heap searches with zero leak candidates because the leak-signal gate was bypassed
kind: finding
tags: [reference-chains, liveness, gate, ddprof, staging]
applies_to: []
source: writing-any-code-thoroughly/find-refchain-gate-bypass
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Reference-chain collector ran whole-heap searches with zero leak candidates because the leak-signal gate was bypassed

## Reasoning chain
Deployed staging prof-analyzer recordings (2026-10-28, ddprof 1.52.1,
agent 1.69.0-SNAPSHOT~1f1ca16508) showed the reference-chain collector active in
a healthy process. `DatadogProfilerConfig.gcGenerations = false` in BOTH
recordings while liveheap was on (modeMask 27 = CPU+wall+alloc+liveness,
memleakCapacity=8192, 27 HeapLiveObject samples). With `gcGenerationsEnabled()`
false, `ReferenceChainTracker::hasLeakSignal()` returned true UNCONDITIONALLY
(old referenceChains.cpp:813-819: "no population-trend signal to gate on at all
-> always true"). `canAffordNewSearch()` was then satisfied by the safepoint
pain budget alone, so searches started and restarted on the GC-epoch / 1-4 s
fallback cadence forever.

Runtime evidence (both recordings, identical signature):
- `reference_chain_frontier_table_capacity = 382074` (24,452,736 bytes) — the
  frontier table grew from INITIAL_TABLE_CAPACITY=1024 all the way to its
  auto-tuned cap (65536 x budget-ratio; budget ~5830 => ~17 GiB max heap).
- `reference_chain_candidate_count = 0`, `datadog.ReferenceChain` = 0,
  `datadog.ReferenceChainAbandoned` = 0 — a whole-heap BFS churning with
  nothing to chase for the entire recording.

Cost profile: bounded by the pain budgets (user: "not too resource hungry") +
~24.5 MB resident frontier table. Zero diagnostic value.

## Evidence
- JFR rec1 = ~/Downloads/20261028-153233_prof-analyzer_AaGDJTXZAAAGy7VwYt7AkgAA/main.jfr
- JFR rec2 = ~/Downloads/20261028-153726_prof-analyzer_AaGDKab0AAC6e_V87a60XgAA/main.jfr
- Queried via jafar jfr-mcp (SSE daemon localhost:3000, token ~/.jafar/mcp-sse.token;
  legacy SSE transport — the pi mcp.json `jbang` entry needs the absolute path
  ~/.jbang/bin/jbang and a session restart; driven instead via
  .scratch/jafar-batch.py).
- arguments.cpp:445 parses `referencechains` independently of `generations`;
  the doc's "requires generation tracking" was guidance, not enforced.

## What this rules out
- "The leak signal fired but the heap looks healthy" — candidate_count=0 and
  zero chain/abandonment events rule out any candidate-driven activity.
- OOM-urgent latch — secondsToOOM() returns -1 without the heap-floor ring.

## Open questions
- Why the deployed agent snapshot enabled referencechains without the
  generations forcing commit (agent branch jb/reference_chains e188d0ff7f
  forces generations=true). Snapshot hash 1f1ca16508 not in the local clone;
  user declined to chase (2026-10-28).
