---
id: design-pod-in-a-jar-harness
type: design
status: implemented-live
depends_on: [meta-whackamole-analysis]
related: [find-round16-endgoal-verification, find-fresh-lane-verification, find-canary-found-criterion-unmigrated, find-refchains-log-flood-configurable, find-urgentoom-null-fn-mislabel]
tags: [design, system-test, invariants, harness, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# Design: "pod in a jar" — system-level simulation harness (the whackamole exit)

STATUS (round 20, de15e521f): BUILT AND FULLY LIVE — all six invariants
run in CI (128 tests / 127 pass / 1 skip-with-reason): L1 leak chains,
L2 canary resolution, L3 natural completion, L6 restart hygiene
(asserting the designed chains-persist contract), L8 dormancy, L4 log
budget (compile-aware — live in DEBUG-built test binaries). The
construction addendum below records what it took; the first-catch
retraction (find-candidate-presence-suppresses-static-admission)
records the builder's own capacity-contract lesson.

One new gtest suite driving the REAL ReferenceChainTracker loop
(threadLoop cadence or directly-driven passes with a fake clock) over a
mock JVMTI heap topology. No kubectl, no deploy, seconds per run.

## Topology builder (encodes every pod-discovered shape)

- 1 static holder (the LEAK_BUFFER shape) holding a synchronized-list
  wrapper — including its `mutex == this` self-edge (round 16's fix-A
  shape) and a real ArrayList c → elementData → chunks subgraph
- K leak-tagged [B chunks that ACCUMULATE per simulated poll (the leak)
- Flood classes: ≥16 statics each of 2-3 classes at high volume (the
  quota/flood shape, round 15-16)
- Direct-static [B noise + transient-root [B noise (the suppression-
  filter shapes) + thread-locals with candidate tids
- Optional healthy-app mode: no candidates at all (the accidental
  control run — dormancy invariant)
- Configurable scale knobs: anchors count, flood volume, pass budget,
  frontier cap, search lifetime — the matrix that took 10 pod rounds to
  explore one point at a time

The BfsTest suite's mock JVMTI machinery (65 tests) already implements
the FollowReferences/poll primitives — this harness composes them into a
full-loop driver rather than inventing mocks.

## Invariants (each maps to real rounds it would have caught)

- **L1 liveness/coverage**: every leak-tagged chunk reachable from a
  walked static has a cached chain with target_tag = its leak tag
  within K passes. [rounds 9-16: the entire funnel saga]
- **L2 canary resolution**: the chase reports 1/1 within K passes of the
  first leak-tag chain (round 19 — fails on the pre-788d7b2a7 build; the
  found-criterion bug becomes a CI failure, not a 3-JVM pod mystery)
- **L3 natural completion**: a healthy-topology search exits "all
  candidates found" — exits-by-frontier-cap/no-progress are harness
  failures (rounds 10-19; also covers the sweep-truncation flag
  cycle_complete oddity)
- **L4 log budget**: at any rcDebugLevel, no distinct log line shape
  exceeds N lines/pass (rounds 17-18: the 800k flood AND the two tier
  stragglers become assertion failures — capture stdout per pass and
  group by line prefix)
- **L5 quotas/monotonicity**: per-class FIFO ≤ 64, self_edge_skips and
  quota counters monotonic, FIFO+queue sizes within caps (round 16)
- **L6 restart hygiene**: after restartSearch, enumerate and assert
  ZERO surviving state — tags, frontier entries, discovered slots,
  resolved chains, marker/leak tags, rotation queues (rounds 12-14's
  restart-survivor bugs + the reset() contract as a TEST, not discipline)
- **L7 boundedness**: no per-search structure grows across M consecutive
  searches (the rotation-resize-blindspot class)
- **L8 dormancy**: healthy topology → zero searches, zero candidates,
  zero log volume (the 3h accidental control, encoded)

Plus a soak mode: M simulated search generations with a leak that grows
and occasionally mutates shape (holder changes klass) — the
representative/canary lifecycle under churn.

## What this changes operationally

- Every class-1/2/3/5/6 defect becomes locally reproducible in seconds:
  the pod stops being the oracle. Deploys become verification, not
  discovery.
- Pod verification collapses to the always-on health line (P2) + one
  level-1 window — checking numbers, not grepping for surprises.
- Upstreaming review runs the harness as the regression net.

## Construction addendum (what it took, round 20 — for the next extension)

- The driver replicates threadLoop's body EXACTLY (shouldRunPass ->
  runPass -> poll, poll unconditional) with a fake clock SEEDED FROM
  OS::nanotime() — the pain budgets' _last_update_ns is real-clock
  based, so a fake epoch at ~0 blocks every pass (only the
  pass-running tests catch this; dormancy passes either way).
- Assertions on tags MUST use tags_ever_assigned, never node_tags: a
  completed search releases node_tags (the fixture's own comment
  documents this; re-learned in bisect).
- The first pass's budget auto-scales 10x (arguments.cpp), so budget=N
  does not mean N edges on pass one; a "multi-pass" search needs a
  filler graph, not just a small budget.
- Two-phase bring-up resolves the klass-id circularity (candidates need
  the id; the id comes from the system's own resolve() over a real
  admission): throwaway candidate arms the signal -> pass 1 admits ->
  classTags-based id resolution (class tags are process-lifetime,
  survive completion+release) -> restart -> re-seed leak tags (the
  poll's re-tagging) -> poll BEFORE the first pass (slots register in
  the poll; admission auto-mark needs the slot to exist).
- The Bfs fixture lacks the NewLocalRef JNI slot
  (PollWatchedTargetsTest wires its own) — resolveCandidateRepresentative
  crashes without it.
- The gtest binary is non-DEBUG: TEST_LOG is compiled out — probe with
  ASSERT/EXPECT-based diagnostics, not logs.

## Cost and sequencing (proposal)

- P0 harness core (topology builder + L1-L3, L6) — 1 focused session;
  reuses BfsTest mocks + the tier/quota fixtures from round-16 tests
- P0b L4 log-budget + L8 dormancy + soak — small follow-up
- P1 keyspaces audit + dead marker-path retirement — half session
  (grep-driven consumer enumeration; one gtest per join)
- P2 always-on per-search health line (Counters: exits-by-reason,
  canary-resolved-pass histogram, coverage ratio) — small
- P3 = L6 (already in P0), P4 deferred queue triaged to harness-flagged

Not proposed: any new pod-driven fix rounds. The deferred queue (sporadic
batch coverage, cycle_complete, reconstructChain noise, wrapper tier
position, TEMP diag slimming) is handled by the harness or deliberately
accepted for upstreaming.
