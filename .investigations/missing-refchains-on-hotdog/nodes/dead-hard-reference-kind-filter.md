---
id: dead-hard-reference-kind-filter
type: deadend
status: refuted
depends_on: [ev-kind-counts-constant-pool-dominates]
supersedes: []
related: [find-candidate1-never-tagged]
tags: [referenceChains, static-field, constant-pool, reference-kind, filter, refuted, NEW-THIS-SESSION]
created: 2026-08-26
updated: 2026-08-26
---

# Hard reference_kind filter (drop ALL non-STATIC_FIELD) — superseded by per-class quota

## What was tried

Implemented at `referenceChains.cpp:1672-1686` (uncommitted, this
session's first iteration): when `ctx->static_field_seed` is true and
the referrer is the opened class object (`*referrer_tag_ptr < 0`), skip
admission (`return 0`) for any `reference_kind !=
JVMTI_HEAP_REFERENCE_STATIC_FIELD`. This dropped ALL non-STATIC_FIELD
edges (CONSTANT_POOL, INTERFACE, SUPERCLASS, CLASS_LOADER, etc.) during
the static-field seed sweep.

## Why it was rejected

User's real-world leak taxonomy (from direct field experience):
- **Static fields** — most common leak source
- **Unmaintained collections in singletons, reachable via static fields** —
  common; the singleton is reached via a static field, the collection via
  the singleton's instance fields
- **Thread-local leaks** — possible; `Thread.threadLocals` is an instance
  field of `Thread` objects, reached via `JVMTI_HEAP_ROOT_THREAD` in the
  general root enumeration path (`heapRootCallback`, line 2169), NOT via
  static fields. So thread-local leaks are NOT in scope of the
  static-field sweep at all — unaffected by any filter on this path.

The hard filter completely excluded CP-based leaks. While CP leaks are
rarer than static-field leaks (CONSTANT_POOL volume is 5-15x STATIC_FIELD
per class, systemically — see `ev-kind-counts-constant-pool-dominates`),
they are still a real leak category. The user's explicit requirement:
"we need to design a system working with this priority and not pushing
completely out one or the other."

## What replaced it

Per-class non-static quota (`find-candidate1-never-tagged`'s updated fix
section): STATIC_FIELD edges always admitted; non-STATIC_FIELD edges
admitted up to `STATIC_FIELD_SWEEP_NON_STATIC_CAP_PER_CLASS = 32` per
class per lap, then dropped for the rest of that class. Cap resets on
class boundary. This keeps CP-based leaks in scope (bounded) while
prioritizing static fields — exactly the "priority, not exclusion" the
user asked for.

## What this rules out

Any design that completely drops a real leak category from the
static-field sweep. The sweep must admit non-static edges in at least a
bounded quantity to keep CP-based leaks discoverable.
