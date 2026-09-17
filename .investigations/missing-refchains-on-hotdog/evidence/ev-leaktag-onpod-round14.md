# Round 14: tiered anchor selection (leak → container → other) + restart hygiene (ev)

Date: 2026-09-15, direction D (user-picked; C rejected on hard STW constraint),
implemented gated on the round-13 measurements and the cohort histogram ships
in the same build.

## What was implemented

1. **Tiered anchor selection** (collectStaticFieldAnchorsForRotation):
   - Tier 0: leak-tagged anchors (entry.leak_tag != 0) — always selected
     first, no cursor.
   - Tier 1: container-shaped anchors (own class implements
     java/util/Collection or java/util/Map) — cursor-fair within the tier.
   - Tier 2: everything else (String/Class/boxed/enum/unknown-shape) —
     cursor-fair, explicitly NOT guaranteed within one search lifetime.
   - No within-call wrap: a tier stops at its lap end and leftover budget
     flows to the next tier (re-walking covered anchors wastes budget).
   - The deterministic coverage guarantee: a container anchor admitted at
     any index position is walked within ceil(container_cohort / budget)
     passes of admission — kills the admission-order lottery (round-13:
     wrapper at position ~12-21k vs ~4k coverage).
2. **Class shape classification**:
   - `_class_shape_cache` (class tag → CONTAINER/NON_CONTAINER),
     process-lifetime (class tags are stable; NOT cleared on restart).
   - `reconcileAnchorClassShapes` runs per pass before selection, on the
     engine thread with JNI (outside heap callbacks/locks): up to
     ANCHOR_SHAPE_RECONCILE_BUDGET=128 distinct unclassified anchor classes
     per pass via ONE GetObjectsWithTags call, each classified by a
     depth-bounded superclass+interface BFS against the cached
     Collection/Map interface class tags.
   - Index entries store the anchor's OWN class tag (parallel array), so
     selection needs no JNI; classification lag demotes to tier 2 only
     until classified.
   - Class tags are NEGATIVE (namespace disjoint from positive frontier
     tags) — all new code uses `!= 0` as the resolved/unresolved test.
   - JNI local-ref hygiene: per-pop deletes + single-exit work-vector
     cleanup + EnsureLocalCapacity(512).
3. **Index dedupe O(1)**: companion `_static_anchor_index_tags` hash set
   (the old linear scan was O(n²) at the measured 28k population).
4. **Leak-tagged root-attached admits now indexed too** (interception
   branch) — a static directly holding a tagged chunk is tier 0.
5. **Restart hygiene**: restartSearch() (and the test reset) now clears
   `_candidate_discovered_tags/_count` — stale frontier tags previously
   survived into the next search, resolving into zeroed slots
   (reconstructChain failures, observed round 13) or live new-search
   entries (WRONG-OBJECT chain events — likely the earlier "noise [B"
   event).
6. **TEMP diagnostics (remove after pod verification)**:
   - `anchorTierHistogram index=... leak_tier=... container_tier=...
     other_tier=... budget=...` per pass — THE arithmetic gate (container
     cohort must be ≲4k for within-one-search coverage).
   - `reconcileAnchorClassShapes container class <sig> (class_tag=...)` —
     names each newly classified container (once per class per JVM).
   - Round-13 probe + klass_id walk log retained for verification.

## Known prior art (documented in STALE_EXPANDED_ROTATION_BUDGET's comment)

A class-shape priority tier was previously tried on the stale-expanded
collector and reverted: "no purely structural property can distinguish the
one specific container that is actually leaking from the thousands of
ordinary ones a real classpath contains." That argument does not apply to
anchor selection the same way — the tier is not trying to pick THE leaking
container, it is shrinking the coverage problem (all containers get covered
within ceil(cohort/budget) passes). BUT its premise (thousands of ordinary
containers) is exactly what the histogram measures: if container_tier ≫ 4k
on hotdog, this round's arithmetic fails too and the frontier-cap/lifetime
lever (config: _reference_chains_frontier_cap) is the next step.

## Verification

- 347 gtests OK (344 + 3 new: ContainerAnchorLeapsQueueAcrossLargeIndex —
  28k synthetic anchors, container at position 24k selected in the FIRST
  call, leak-tagged anchor leads; AnchorOtherTierFairCoverageAcrossWraps —
  40/budget16 = 16+16+8 full coverage, no within-call duplicates;
  RestartSearchClearsDiscoveredInstanceTags). Zero failures; only crash is
  the pre-existing UrgentOOMProjectionBypassesCandidateGate SIGSEGV (clean
  HEAD).
- spotlessApply clean; buildRelease -Pskip-tests clean.

## Pod verification plan (next deploy)

1. `anchorTierHistogram` — read container_tier vs ~4k. THE gate.
2. `reconcileAnchorClassShapes container class` — expect
   Collections$SynchronizedRandomAccessList classified CONTAINER early.
3. `LEAK_BUFFER probe` — wrapper admitted root-attached (unchanged).
4. `walkStaticFieldAnchors anchor ... class=...SynchronizedRandomAccessList
   klass_id=29448` — within ceil(cohort/16) passes of admission.
5. `leak-tag intercepted` + `datadog.ReferenceChain` events — the end goal.
6. Confirm `reconstructChain failed` lines GONE (stale discovered tags).
