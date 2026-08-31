---
id: find-gate-bypass-representative-paths
type: finding
status: confirmed-and-fixed
depends_on: [find-priority-queue-starves-bfs-crawl]
related: [find-priority-queue-starves-bfs-crawl, find-leak-tag-pool-implementation, q-resize-instrumentation-rescan-priority]
tags: [root-cause, fix, gate, noise, canary, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Noise gate bypassed by canary/representative chain paths + depth-0 design flaw

Caught by the local repro (LeakTagCorrelationReferenceChainTest) on its
first runs - the exact wrinkles the harness was built to find.

## Defect 1: gate coverage

The discovered-loop gate (suppress transient-rooted shallow chains) existed
ONLY in pollWatchedTargets' discovered-instances loop. Three other
cacheResolvedChain() sites in pollWatchedTargets bypassed it:
- buildCanaryChainEvent (dead-representative path)
- buildCanaryChainEvent (live canary marker path)
- buildChainEvent (normal representative path)

A seeded noise-class representative got a stack-local-rooted depth-1 chain
cached via the canary path, and snapshot-and-keep re-emitted it in every
dump forever - the same "noise chains re-emitted forever" symptom observed
on the pod (the pod's 8 depth-1 noise chains were plausibly exactly this).

Fix: file-local `suppressChainEvent()` predicate shared by ALL cache sites
(each also calls invalidateResolvedChain so cached noise stops re-emitting).

## Defect 2: depth==0 unconditional suppression was wrong

The round-4 gate suppressed depth==0 UNCONDITIONALLY. That drops real
direct-retention chains: a static field's value ITSELF is a depth-0 root
(the singleton collection), a `thread` root is the thread-local-leak
taxonomy. Corrected predicate: `depth < 2 && isTransientRootKind(root)`
only. Durable-rooted depth-0/1 chains are real; deeper chains pass
regardless.

## Scenario lesson (fixture, not profiler)

Holding the noise representative in a STATIC field makes that one instance
genuinely durably retained - the profiler is RIGHT to emit a
`NoisePayload@depth0:static_field` chain for it (observed). Transient
retention requires a non-static handoff (run()-local exchanger-style
holder, reference dropped after take).
