---
id: find-already-admitted-blocks-deeper-chain
type: finding
status: confirmed
depends_on: [find-per-class-caching-blocks-instances]
supersedes: []
related: [find-per-class-caching-blocks-instances]
tags: [root-cause, fix, referenceChains, admitObject, already-admitted, depth-1, chain, jni-local, NEW-THIS-SESSION]
created: 20260828
updated: 20260828
---

# Already-admitted objects block deeper chain reconstruction

## Context

After per-instance chain caching (cd68be618) and allocation-site
clustering (2c50bf0cd, 36c7fc8c8), 8 ReferenceChain events were
emitted for [B on-pod. But the user reported chains are depth=1 with
only [B and no holder — not useful for diagnosing the leak.

## Root cause

`admitObject()` checks `if (*tag_ptr != 0) return ALREADY_ADMITTED;`
— once an object is tagged and admitted, it's never re-admitted.

When [B is first reached as a JNI-local root (referrer_tag_ptr ==
nullptr, parent_tag=0, depth=0), it gets tagged. When the
static-field → ArrayList → [B path reaches it later with a non-zero
parent_tag and deeper depth, `ALREADY_ADMITTED` is returned and the
deeper chain is lost.

`reconstructChain()` then walks parent_tag back to root, but
parent_tag == 0 → chain is just [referrer_klass of the [B itself] →
depth=1, no holder.

## Fix (commit d30538fe3)

`FrontierTable::improveChain(tag, parent_tag, referrer_klass, depth,
root_kind)` — when `admitObject` encounters an already-tagged object
and the new path has a non-zero parent_tag, call `improveChain` to
replace the shallow root-attached entry with the deeper chain-attached
entry. Only improves if the new depth is greater than the existing
depth (never degrades a deeper chain to a shallower one).

## Evidence

On-pod logs show `buildCanaryChainEvent false: never pruned
(candidate=0 parent_tag=0 frontier_tag=0)` — the canary representative
was never reached by BFS. The 8 discovered instances were admitted as
roots (parent_tag=0), giving depth=1 chains.
