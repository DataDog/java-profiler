---
id: find-priority-queue-starves-bfs-crawl
type: finding
status: confirmed
depends_on: [find-ema-batch-collapse, find-leak-tag-pool-implementation]
supersedes: []
related: [find-leak-tag-pool-implementation, find-ema-batch-collapse, find-holistic-design-issues, q-coverage-tracking-per-combination]
tags: [root-cause, fix, referenceChains, expandFrontier, priority-queue, starvation, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# _priority_expand flood starves the BFS crawl (three compounding blockers)

## Observed on-pod (round 3, build 0db70994d, PID 48355)

- Pass throughput recovered (AIMD works: batch oscillates 34→17→81 around the
  25ms per-call budget, ~12 passes/min, deadline-bounded) BUT:
- `_priority_expand` grew 39k→103k in 20 min; `_pending_expand` (66k→77k) was
  NEVER drained once.
- `leak-tag intercepted`: 0 fires in 20+ min despite 129 tagged instances.
- Only the same 8 noise chains, cached and re-emitted (batch=8 × 3 drains).
- `leak_accumulation_tags=0` every pass (growth-gated tier dead in steady
  state); `leak_parents=19058` in the fanout, unreachable.

## Causal chain (all links proven from code + logs)

1. Rotation collectors enqueue 256+16 stale entries/pass into
   `_priority_expand`; each phase's 50ms deadline allows only ~2 gotw calls
   (~150-300 entries) of drain. Inflow > outflow every pass.
2. expandFrontier drains priority STRICTLY FIRST
   (`from_priority = !_priority_expand.empty()`), so a never-empty priority
   queue means pending is never touched: the BFS's own frontier never
   expands new territory. The singleton holders sit in pending.
3. Without holder expansion, parents of the 129 leak-tagged arrays are never
   walked → interception can never fire.
4. `tagLeakInstances` SetTag overwrites frontier tags of already-admitted
   instances (admission-order hole) — orphaning entries and making
   correlation depend on the very re-walks that are starved.
5. MAX_DISCOVERED_INSTANCES_PER_CLASS=8 slots are first-come-first-served —
   the 8 noise instances permanently occupy them; even admitted leak
   instances would be silently discarded at discovery recording.
6. `isQueuedForRotation` linear scan over the 103k queue (26M comparisons
   per pass, under the frontier shared lock) adds hidden pass cost.

## Fix (commit pending)

1. FAIR-SHARE DRAIN: expandFrontier alternates batches between priority and
   pending when both non-empty (priority still first each call) + hard cap
   PRIORITY_EXPAND_CAP=1024 with skip-when-full at every push site
   (collectors + admitObject fallback to pending). Caps bound memory AND
   the isQueuedForRotation scan; alternation guarantees pending progress
   regardless of inflow/outflow arithmetic (the cap alone does NOT fix
   starvation - a capped-but-pinned queue still never empties).
2. tagLeakInstances state machine on the CURRENT JVMTI tag: frontier tag →
   correlateAdmittedLeakTag (setLeakTag on the entry + recordDiscovered,
   NEVER retag); no tag → SetTag (first tagging or re-establishment after a
   search restart wiped tags via releaseSearchTags); leak tag already
   present → record only.
3. recordDiscoveredInstance with leak-preferential eviction: noise fills
   empty slots only; a leak-correlated discovery evicts an uncorrelated
   slot (and invalidates its cached chain) when full.
4. Fanout-priority in collectStaleExpandedEntriesForRotation: leak parents
   selected ahead of the blind table lap (rotating cursor), breaking the
   steady-state deadlock of the growth-gated tier.
5. reparentToDurableRoot: equal-depth (depth-1) re-parent from a transient
   root to a durable one — improveChain cannot express it (needs strictly
   deeper), and the hotdog static shape is depth-0 root → depth-1 elements,
   so without it noise-admitted leak instances would stay transient-rooted
   forever.
6. Discovered-loop gate: depth==0 or (depth==1 && transient root) suppressed
   (+ invalidate cached noise so drain stops re-emitting); depth==1 durable
   root KEPT (it is the real direct-static-retention shape — a blanket
   depth>1 filter would drop it; static sweep admits static-field VALUES as
   depth-0 roots, referrer rtag<0 → root-like).
