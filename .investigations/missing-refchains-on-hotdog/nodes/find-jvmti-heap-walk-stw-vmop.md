---
id: find-jvmti-heap-walk-stw-vmop
type: finding
status: confirmed
depends_on: []
related: [find-getobjectswithtags-quadratic-bottleneck, find-cpu-pain-budget-blocks-bfs, find-sweep-completes-but-bfs-starved]
tags: [root-cause, hotspot, jvmti, stw, design-constraint, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# JVMTI FollowReferences is a VM operation - a full-heap walk is ONE stop-the-world pause

From the openjdk-jdk21 source (user challenged the option-B sweep-lap
cost question; this killed option B):

- `FollowReferences`/`IterateOverReachableObjects` =
  `VM_HeapWalkOperation : public VM_Operation`
  (src/hotspot/share/prims/jvmtiTagMap.cpp:2379), submitted via
  `VMThread::execute`; the whole graph walk runs inside `doit()`
  (`:2934`, `while (!visit_stack()->is_empty()) visit(o)`).
  VM operations execute at a safepoint: the ENTIRE JVM is frozen for the
  walk's duration. Neither heap-walk op overrides
  `allow_nested_safepoints()`. There is no preemption, no yielding.

- Consequence: a full-graph intercept sweep on the hotdog analyzer's 7GB
  heap = a single ~10s stop-the-world pause per lap. (The 10s figure is
  the pod's own pre-deadline-bound pass cost, round-2 evidence.) On a
  traffic-serving analyzer this is categorically unacceptable - option B
  (intercept-only full-graph sweep) is DEAD as designed.

- What the existing design does instead is correct discipline: every
  walk is a VM op, so every pass caps its walk at ~15ms = ~15ms STW per
  pass, and the static sweep is a RESTRICTED walk (class-holder arrays ->
  classes -> static field values, a tiny subgraph) - ms-scale STW per
  chunk. The static sweep "completing laps" is therefore NOT evidence that
  full-graph walks are affordable; it only proves restricted subgraph
  walks are.

- Corollary for the coverage lottery: there is NO cheap "reach unknown
  holders of tagged objects" mechanism available to an external JVMTI
  agent. JFR's leak profiler avoids this by living inside HotSpot and
  riding the GC's own object traversal (leakprofiler closures during GC),
  which ddprof cannot do from outside.

- Distinct case: `GetObjectsWithTags` is NOT a VM op
  (jvmtiTagMap.cpp:1305, `get_objects_with_tags`): it scans the WHOLE tag
  map under the tag-map mutex per call - O(tag-map size) regardless of
  the number of tags requested. Measured on hotdog: 18-21ms/call at ~200k
  tag-map entries, ~5 calls/pass. It blocks other tag users rather than
  stopping the world, but it is the DOMINANT per-pass CPU/lock cost.
