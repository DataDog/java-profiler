---
id: find-per-class-caching-blocks-instances
type: finding
status: fixed
depends_on: [find-representative-changes-lose-canary]
supersedes: []
related: [find-representative-changes-lose-canary]
tags: [root-cause, fix, referenceChains, resolved-chains, per-instance, caching, NEW-THIS-SESSION]
created: 2026-08-28
updated: 2026-08-28
---

# Per-class resolved-chain caching blocks all but the first instance

## Observation

JFR analysis of the real ddprof recording (not jcmd) showed 2
`datadog.ReferenceChain` events:

1. `targetTag=-4611686018427387906` (marker tag) — depth=14, rootKind=unknown
   (canary chain for [B, but rootKind was "unknown")
2. `targetTag=5940` — depth=1, rootKind=first_observed_via:jni_local
   (auto-mark chain for the **noise** [B — 136B, s3-netty-2 thread)

The leaking [B instances (12 × 78MB, `simulated-memory-leak` thread,
ages 33-168, held via static-field ArrayList at depth=14) were never
emitted. The noise [B at depth=1 (136B, JNI local root) was admitted
first by BFS, auto-marked, its chain built and cached. Per-class
caching (`_resolved_chains` keyed by `klass_id`) meant the class was
marked as "has a chain" — `no_chain_cached` was false — and all
further [B instances (including the actual leak) were skipped.

## Root cause

`_resolved_chains` was keyed by `klass_id` (u32). For common classes
like `[B` with thousands of live instances, the first chain found
(often noise — a shallow JNI-local instance 1-2 hops from a root)
permanently blocked all other chains for the same class.

## Fix (COMMITTED cd68be618)

Key `_resolved_chains` by frontier tag (jlong) instead of klass_id.
Each discovered instance gets its own chain entry. All chains are
emitted to JFR; the profiling backend aggregates by class.

- `cacheResolvedChain`: first arg is `jlong source_tag`, not `u32 klass_id`
- Discovered path: build chains for ALL discovered instances (not just
  first that succeeds), skip if already cached for that tag
- Remove `no_chain_cached` early-out
- Remove per-klass prune: chains expire on search restart (frontier wipe)
- `MAX_RESOLVED_CHAINS`: 128 (5×8 discovered + 5 canary + headroom)
- Tests updated: key by frontier tag, `PruneStopsReemitting` →
  `ChainPersistsAfterRepresentativeDies`
