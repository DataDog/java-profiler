# Round 14 on-pod verification + round-15 diagnosis (ev)

Deploy: 6eb72f994 (tiered anchor selection + restart hygiene) on
prof-analyzer-hotdog-jb-d9d8cf-rz992, JVM restarted 20:05:48Z, verified
2026-09-15 20:06-20:53Z. User deployed; agent verified from logs only.

## Round-14 mechanics VERIFIED WORKING

1. **Tiering works.** `anchorTierHistogram index=20499-30711 leak_tier=0
   container_tier=1328-1680 other_tier=17686-24651 budget=16` — the container
   cohort is **1633-1680**, far under the ~4k arithmetic gate. Container
   anchors are visibly walked first-class:
   ImmutableCollections$SetN/Set12/MapN/Map1/ListN, LinkedHashMap, HashSet,
   Collections$SingletonSet, **Collections$SynchronizedMap** (walked via
   at-risk FIFO), String (leftover budget flowing to tier 2, ~306 walks).
2. **Classification works** (containers tiered from pass ~27 onward). The
   `reconcileAnchorClassShapes container class <sig>` log appears ZERO times
   in every held window — explained, not a bug: classification is one-time
   per class per JVM (cache is JVM-lifetime, restartSearch keeps it), all
   ~100-200 anchor classes were classified in the first search's first
   passes (20:13-20:22, every captured buffer since has rotated past it).
   Later container_tier growth = new ANCHORS of already-classified classes.
3. **Restart hygiene works.** No stale-tag `reconstructChain failed` flavor
   observed; remaining `buildChainEvent false: target_tag=1073742079 not in
   frontier` is the genuine standing gap (chunk not yet admitted).
4. LEAK_BUFFER probe caught the real holder class sweep live:
   `sweeping holder class Lcom/datadog/profiling/analyzer/steps/ProfileAnalyzer;
   at index 24627` → `wrapper_tag=0` (pre-admission, expected on first
   crossing) → the containing chunk (24265→24777) completed cleanly
   (1146 edges, truncated=0) → **the wrapper WAS admitted root-attached into
   that search.**

## Round-15 root cause: tail starvation reproduced AT TIER-1 SCALE

Measured live (20:22-20:53, all in /tmp/pod_t*.log, pod_stream.log):

- **Search lifetimes collapsed to 44-75 passes** (vs round-13's ~190):
  frontier fills at 2.5-7.5k inserts/pass; cap-hit abandon observed at
  size=245170 at pass ~75 and again ~242440 at pass 44+. Fill composition:
  static sweep admits ~0.7-1.4k/pass, expand phase ~0-57, leak-accumulator
  noise seeding `trackLeakAccumulation fanout-insert` ~650/min (round-13
  documented this seeding as fanout=1 noise), remainder expansion/roots.
- **The wrapper's holder class sits at sweep index 24627 of ~33270** (app
  partition; class list re-partitioned app-first per call, index drifts
  ±50 with lambda churn). The sweep therefore admits the wrapper MID/LATE
  in a search (observed: pass ~43-44 of the current search).
- **Admission order = sweep order ⇒ the wrapper lands at the anchor-index
  TAIL** (~27000+ of 27739), i.e. **container-ordinal ~1634 of 1633 — the
  LAST container**. Walk owed at pass ~44 + (1634-cursor)/16 ≈ **pass 102+**.
  Search lifetime 44-75 ⇒ **deterministic miss by ~30-50 passes.**
- **Compounding: the searches are canary chases** (`canary search, 0/1
  candidates found, backoff_mult=16 ema_ms=191`) — the candidate is the [B
  leak class (klass_id=2, target tag 1073742079 = LEAK_TAG_BASE+255,
  tagged=42-53). The canary's candidate can only be "found" via a resolved
  chunk chain; the chain needs the wrapper walk; the wrapper walk needs
  ~102 passes in one search; the search caps at 44-75 AND the canary
  backoff (16 × ema 191ms ≈ 3s/pass) slows the very passes that would
  reach it. **Self-sustaining chase deadlock.**
- Sweep gate behavior measured: runs only while the loaded-class count
  changes (lambda churn keeps it open in waves); cursor wraps at count
  (~33253), resets to 0 if count shrinks below cursor (lambda unload);
  laps complete in ~2-10 min during churn waves; the real class is crossed
  roughly once per wave/lap.

## Round-15 fix direction (STW-free, surgical)

**Fresh-admission priority in the container tier**: anchors admitted since
the last collector pass (index high-water mark) — at minimum the
freshly-admitted CONTAINER-shaped ones — are walked FIRST in the very next
pass (newest-first). The wrapper admitted at pass N is walked at pass N+1
(classified by the same-pass reconcile, or fresh-priority independent of
shape). No new STW cost: same 16-walk budget, reordered. Breaks the chase
deadlock end-to-end: wrapper walk → subtree expansion admits the
leak-tagged chunk → buildChainEvent(tag=1073742079) resolves → candidate
found → canary exits → ReferenceChain event emitted.

Rejected/deferred: raising STATIC_ANCHOR_ROTATION_BUDGET 16→32 (STW risk,
anchor walks already compete with expansion for the pass deadline);
killing the seeding noise (correctness issue from round 13, only ~10-20%
of frontier fill); whole-heap anything (user hard constraint).

## Verification channels still open on pod

- wrapper probe line each lap: `sweeping holder class ...ProfileAnalyzer;
  at index 24627` → next laps should show wrapper_tag=<tag> parent=0
  root_kind=8 (admitted) — watch after any fix build too.
- `walkStaticFieldAnchors anchor ... class=Ljava/util/Collections$SynchronizedRandomAccessList;`
- `leak-tag intercepted`, `auto-marked chain`, `drainPendingChainEvents drained>0`,
  datadog.ReferenceChain events.
