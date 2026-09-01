---
id: find-depth0-durable-root-upgrade-gap
type: finding
status: confirmed-and-fixed
depends_on: [find-gate-bypass-representative-paths]
related: [find-gate-bypass-representative-paths, find-rotation-resize-blindspot]
tags: [root-cause, fix, root-kind, gate, durability, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Depth-0 root-kind upgrade never fired for root-like heap edges

Found while fixing the seams test (its target stayed
`root_kind=24 (STACK_LOCAL)` through every poll even though it was also
the direct value of a static field).

## Root cause

`maybeUpgradeRootAttachedRootKind()` (the durability tie-break: a later,
more durable root discovery upgrades an entry's root_kind) was wired ONLY
into `heapRootCallback`'s ALREADY_ADMITTED case. But the static-field sweep
delivers its class -> field edges through `heapReferenceCallback`, where a
class referrer (negative tag) is deliberately treated as ROOT-LIKE
(`parent_tag == 0`, depth 0 - class objects are never frontier entries).
Root-like edges on already-admitted entries fell through every handler:
`improveChain` and `reparentToDurableRoot` both require `parent_tag != 0`.
So an object first admitted through a stack local kept its transient
classification FOREVER, even after the sweep proved static retention.

## Production impact

Real: a leak instance is typically a local variable while being stored
into the static/field-held collection - root enumeration admits it as
STACK_LOCAL first, the static discovery arrives later, and the depth-0
chain was then noise-gated (`depth < 2 && isTransientRootKind`) exactly
like the noise it was meant to distinguish.

## Fix

`heapReferenceCallback` now calls
`maybeUpgradeRootAttachedRootKind(*tag_ptr, reference_kind)` for
root-like edges to already-admitted entries (same tie-break as the root
callback), with `invalidateResolvedChain()` so a cached chain rebuilds
with the upgraded root. Durability ranking (STATIC_FIELD/SYSTEM_CLASS=3 >
JNI_GLOBAL=2 > transient=1) unchanged.
