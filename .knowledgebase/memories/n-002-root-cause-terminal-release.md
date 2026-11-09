---
id: n-002-root-cause-terminal-release
title: n-002: ROOT CAUSE — terminal COMPLETED releases tags; restart storm makes EXPANDED unobservable
kind: finding
tags: [reference-chains, root-cause, jvmti]
applies_to: []
source: frontier-wait-untagged/n-002-root-cause-terminal-release
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# n-002: ROOT CAUSE — terminal COMPLETED releases tags; restart storm makes EXPANDED unobservable

- status: confirmed
- evidence: build/logs/20261014-174441 (instrumented child section /tmp/child-section2.log), OpenJDK jvmtiTagMap.cpp

## Chain (each step verified)

1. The scenario wires no representative → `_watched_leak_klass_count == 0`.
2. Each pass: static sweep admits LEAK_BUFFER's SynchronizedList (verified:
   `sweep_static_edge class_tag=-8 referee_tag=0 referee_klass=34` once per
   walk — 36 = 4 statics x 9 laps), expandFrontier expands it, nothing pending
   → `!has_pending_frontier && _watched_leak_klass_count == 0` →
   **SearchState::COMPLETED** (referenceChainTraversal.cpp:1110).
3. The terminal pass ITSELF releases every frontier tag:
   `if (_search_state != RUNNING) { _tags_released = releaseSearchTags(...); }`
   (referenceChainTraversal.cpp:1192, and the terminal no-op branch at 1008).
4. `shouldRunPass()` sees terminal, `canAffordNewSearch()` cools the safepoint
   pain budget (~1.5-83ms) then `restartSearch()` — identical walk repeats
   (edges_admitted=19058 twice); `_watched_leak_klass_count==0` again →
   COMPLETED → release. Storm of 9+ identical searches in the 45s window.
5. The scenario's poll (`getReferenceChainFrontierStateForTest0`) takes
   `_engine_lock` — it can only read BETWEEN passes (blocked mid-pass), and
   between passes the tags are released → `GetTag(holder)=0` → state -1.
   The 45s wait can NEVER observe EXPANDED in this regime.

## Why intermittent

Pass/fail depends on whether any pass stays RUNNING long enough (e.g. a
truncated pass → `has_pending_frontier` true → no COMPLETED → tags persist →
poll observes EXPANDED). The one observed passing run (--no-daemon,
build/logs/20261014-164358, `[chain-found] byte[]`) had a different pass
history. Machine load/scheduling decides.

## Instrumentation notes (reverted)

- Temporary TEST_LOG lines were added to referenceChainWalk.cpp /
  referenceChainTraversal.cpp and reverted via git checkout (worktree clean).
- JVMTI facts verified from OpenJDK master jvmtiTagMap.cpp:
  `iterate_over_class` reports static fields unconditionally once the class
  mirror is visited; the callback's return gates the visit
  (`res & JVMTI_VISIT_OBJECTS (0x100) → check_for_visit(referree)`;
  returning 0 prunes). jvmtiHeapReferenceKind: CLASS_LOADER=4,
  PROTECTION_DOMAIN=6, INTERFACE=7, STATIC_FIELD=8, CONSTANT_POOL=9,
  SUPERCLASS=10.
- Statics of the scenario class ARE reported by FollowReferences every lap
  (LEAK_BUFFER edge included) — the native sweep design works; the failure is
  the observe-window race, not a missing admission.

## Pre-bug state

The EXPANDED-wait + seam machinery arrived with the branch's review-fix
commits (a28220dc1/fa035dfa4/13bbd3d65/7414cd169/a849954f8). Bisection: 2/2
failures at a849954f8 (pre-address commit) → NOT introduced by the address
commit 6855e4b5e.

## Fix directions (decision open)

A. Test-side: wire a representative (setKlassPopulationRepresentativeForTest0)
   like LeakingCacheScenario → `_watched_leak_klass_count > 0` → search stays
   RUNNING → tags persist → wait observes EXPANDED. Changes the tracker mode
   the scenario runs in (canary/rotation behavior).
B. Test-side: replace the EXPANDED wait with a restart-storm-tolerant signal
   (pass-counter deltas + rotation seam), accepting tags are ephemeral.
C. Product-side: keep tags on terminal-COMPLETED (release only on
   ABANDONED/restart) — changes product semantics, needs justification.
