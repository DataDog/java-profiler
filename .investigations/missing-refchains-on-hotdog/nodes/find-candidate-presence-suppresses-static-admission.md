---
id: find-candidate-presence-suppresses-static-admission
type: deadend
status: retracted
depends_on: [design-pod-in-a-jar-harness, meta-whackamole-analysis]
related: [find-round16-endgoal-verification, find-urgentoom-null-fn-mislabel]
tags: [deadend, retracted, harness-fixture-bug, capacity-contract, methodology, round-20, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# RETRACTED: "candidate presence suppresses static admission" — it was the harness builder's own dangling pointer

The round-20 harness's first "catch" (with a candidate armed, the next
pass does not admit the wrapper static) is RETRACTED. Root cause, traced
to ground with test-side mock instrumentation (holder array built and
filled, holder-elem seeding never firing):

The Bfs fixture's class-registration pattern captures
`&node_tags[node]` as the jclass identity
(`classes.push_back({(void*)&node_tags[classNode], ...})`). The
harness's topology builder then added 300 filler nodes, growing
`node_tags` past capacity — the vector reallocated and every captured
identity pointer DANGLED. `indexOfNode()` then returned -1 for those
classes in the static sweep: the holder array seeded no expandable
class, the STATIC_FIELD edges never replayed, the sweep lapped
admitting NOTHING, and the gate closed on the empty lap — all
silently, with the search state machine still reporting a clean
COMPLETED search.

## Why this mattered more than a test bug

The failure shape was maximally deceptive: no crash, no error, a
COMPLETED search, zero admissions. It survived ~6 bisect rounds
(looked like: candidate presence, budget starvation, restart-gate
state, check-placement artifacts — each partially true because the
dangling pointer made results order-dependent and non-monotone). The
capacity contract (reserve the full node count BEFORE any
`&node_tags[i]` capture) is now encoded as a comment at the builder +
the permanent TopologyCapacityContractStaticAdmits regression test.

## Methodology notes (the meta-value of this deadend)

1. The pod's round-18 "sporadic coverage" is NOT explained by this —
   that remains an open upstreaming-round question (batch selection
   determinism). The earlier pod-correlation hypothesis in this node's
   first version is withdrawn.
2. Fixture capture-pointer contracts are a NEW class of test-seam gap
   (same family as find-test-seam-aliasing / the reset() seam gap):
   the mock's data structures have invariants the tests must maintain,
   and violating them fails silently inside production code paths.
   When a harness "catches" something, FIRST bisect against the
   harness's own construction (the repro that failed with the full
   topology but passed with the minimal one pointed AT the builder
   all along).
3. The mock instrumentation approach (test-side printf in the mock
   JVMTI/JNI slots, gated by an env var) was decisive — printfs in
   TEST code are always available even in non-DEBUG builds.

## Outcome

With the capacity fix, ALL the harness invariants went live (see the
de15e521f commit): L1 leak chains, L2 canary resolution, L6 restart
hygiene (with the chains-persist-by-design contract), L4 log budget
(compile-aware), joining L3 natural completion and L8 dormancy.
128 tests, 127 pass, 1 skip-with-reason.
