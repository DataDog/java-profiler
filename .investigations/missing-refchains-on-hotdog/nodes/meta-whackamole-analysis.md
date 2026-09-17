---
id: meta-whackamole-analysis
type: meta
status: confirmed
depends_on: [meta-circle-review, find-canary-found-criterion-unmigrated, find-refchains-log-flood-configurable, find-urgentoom-null-fn-mislabel, find-wrapper-demotion-self-parent, find-tier1-tail-starvation]
related: [find-holistic-design-issues, find-test-seam-aliasing, find-klass-id-notation-mismatch, find-canary-stuck-restart-wipes-frontier]
tags: [meta, root-pattern, defect-taxonomy, strategy, methodology, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# Meta-review 2: are we running in circles? (post-goal, requested at round 19)

## Verdict

**Rounds 13-16: no — convergent.** Meta-review 1's prescription (measure
the coverage invariant first) was followed: the funnel was measured,
the fresh lane + demotion guard + quota were the measured consequences,
and the END GOAL (leak-correlated events) verified at round 16. Facts
monotone, each fix distinct.

**Rounds 17-19: yes — the shape is whackamole.** Three rounds since the
goal: two were about our OWN diagnostics (log flood, knob escapes, tier
miscalibration), one about a lifecycle bug (canary found criterion) that
existed since the marker→leak-tag migration — i.e., since ~round 12, on
every search, invisible because nothing asserted it. The whackamole
signature: **deploy → observe one broken link → fix → deploy → a different
broken link appears**. The per-iteration cost is a deploy+hours, n=1, and
each verification only checks the symptom that motivated the fix.

## The defect taxonomy (all 30+ fixed defects, classified by PRODUCING mechanism)

1. **Scheduler starvation under diverse load** (~12 defects — the largest
   cluster): anchor-holder eviction, tail starvation x2, priority-queue
   starvation, shared-deadline starvation, sweep-never-completes,
   EMA-batch collapse, GetObjectsWithTags quadratic, CPU-pain-budget
   blocks, the at-risk FIFO flood pin. Shape: one shared
   budget/queue/cursor + a heterogeneous population deterministically
   starves whatever matters. Each fix re-tuned ONE scheduler parameter;
   no global liveness/fairness invariant was ever asserted anywhere.
2. **Keyspace/identity confusion** (~6): marker-tag slot mismatch,
   klass-id notation mismatch, leaktag-JFR field misalignment,
   representative-changes-lose-canary, candidate1-never-tagged, and
   round-19's found criterion. Root: THREE tag keyspaces (marker/leak/
   frontier) + one JVMTI tag slot per object + per-JVM id instability.
   Every cross-space join is a bug farm; round 19 was a join that broke
   when one space was deprecated.
3. **Half-migrated designs** (2 proven, the class with the highest
   future risk): marker→leak-tag migration (found criterion + rep path
   left on the old contract); the TEST_LOG migration to the level gate
   (header-inline sites + tick-tiering left behind). Shape: a design
   change ships in pieces; consumers of the old contract are never
   enumerated.
4. **Test-seam gaps — the suite is green while the system is broken**
   (~8): test-seam aliasing, reset() missing clears, UrgentOOM null-fn
   (5 weeks of lost signal), every round where 348 gtests passed and the
   pod still failed. Root: unit tests verify components; NOTHING
   verifies the integrated pipeline. **The pod is the only end-to-end
   oracle — that IS the whackamole generator.**
5. **State lifetime across search restarts** (~4): restart-wipes-frontier,
   ages-vector, discovered tags surviving, representative refresh. Every
   new process-wide state adds a hand-written clear-site obligation;
   the reset contract is enforced by discipline, not by test.
6. **Observability as a defect source** (rounds 17-18): diagnostics
   added under time pressure, ungated, unmeasured — then needing their
   own fixing rounds.
7. **Deploy environment drift** (~3, mostly solved by per-build markers).

## The structural statement

The system has grown: a scheduler (tiers/queues/budgets) + three tag
keyspaces + per-search state + a poll/chase state machine. Its
verification apparatus is: 348 unit gtests (components) + a staging pod
(integration, ~hours/iteration, n=1). **Every class-1/2/3/5 defect is
invisible to the unit suite by construction.** So the pod finds them one
deploy at a time — in whatever order they happen to fire. Whackamole is
not a discipline failure; it is the predictable output of this
verification topology.

## The non-whackamole exit

Stop making the pod the oracle. Two moves:

- **P0 — build the missing oracle once**: a system-level simulation
  harness ("pod in a jar") — the REAL tracker loop over a mock JVMTI
  topology encoding every pod-discovered shape (synchronized wrapper with
  its mutex self-edge, flood classes, leak chunks, noise, thread-locals),
  running multiple search lifetimes + restarts, asserting INVARIANTS
  (liveness, canary resolution, natural completion, log budget, quotas,
  restart hygiene, boundedness, healthy-app dormancy). Every invariant
  maps 1:1 to a real round's bug — 7 of the last 10 pod rounds would
  have been a red local test BEFORE any deploy. See
  design-pod-in-a-jar-harness.
- **P1-P4 — close the specific generator classes**: keyspaces audit +
  dead marker-path retirement (class 2/3), always-on per-search health
  counters so pod verification is one line not grep archaeology (class
  6 + observability), reset-contract invariant test (class 5), deferred
  queue triaged to harness-flagged-only (no more pod-driven fixes).

The alternative — continue pod-driven — predicts rounds 20+ of the same:
the scheduler, keyspaces, and restart state each still hold unfixed
members of their class (see the deferred queue in STATE), and they will
surface one deploy at a time.

## Execution status

P0 EXECUTED (round 20): the harness is built and all invariants live in
CI — the pod is no longer the only end-to-end oracle. P1 (keyspaces
audit + marker-path retirement) and P2 (health line) are next; P4's
deferred queue is harness-flagged-only.

## Answer to the user's question

No on the goal (achieved, round 16, reproduced on a second JVM). Yes on
the process since. The fix is not another patch — it is P0 + P1-P4 above,
then upstreaming review becomes mechanical instead of exploratory.
