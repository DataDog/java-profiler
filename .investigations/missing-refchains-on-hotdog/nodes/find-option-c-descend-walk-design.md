---
id: find-option-c-descend-walk-design
type: design
status: committed
depends_on: [ev-leaktag-onpod-round5, ev-leaktag-onpod-round6]
related: [find-priority-queue-starves-bfs-crawl, find-per-tid-qualification-design, find-rotation-resize-blindspot]
tags: [option-C, descend-walk, thread-local, static-holder, referenceChains, NEW-THIS-SESSION]
created: 20260902
updated: 20260902
---

# Option C: candidate-scoped reach via bounded descend walks (both prongs, one mechanism)

User decision: implement BOTH prongs (taxonomy-driven, deliberately NOT
shaped by probing hotdog's simulator - "we don't want to overfit this
particular scenario").

## The unified mechanism

Both prongs are the same operation: a `FollowReferences(initial_object=anchor)`
with `batch_tags == nullptr` (so descent is gated only by hop_cap +
deadline), reusing heapReferenceCallback unchanged - leak-tag interception,
canary pruning, auto-mark, improveChain/reparent all work as-is. ctx.hop_cap
is lowered to `anchor_depth + DESCENT_HOPS` for the call so the walk is
bounded to a few hops BELOW the anchor. Children admitted by the walk get
parent links to the anchor's chain, so interception = complete chain in one
bounded STW. No queue-cascade design: admitted children joining the tail of
_pending_expand does not matter, the chain entries exist at admission time.

- **Prong 1 (thread-scoped, thread-retained taxonomy)**: new phase in
  runPassManualWalk; for each candidate's qualifying tids, look up the live
  Thread object, admit it as a root-attached frontier entry (root_kind=
  JVMTI_HEAP_REFERENCE_THREAD, depth 0), then descend-walk with:
  - DESCENT_HOPS below the Thread anchor,
  - an anchor gate on the Thread's own edges: descend only into
    ThreadLocal$ThreadLocalMap (the value type of BOTH threadLocals and
    inheritableThreadLocals) by exact class-tag match. Deliberately NOT
    jvmtiHeapReferenceInfoField.index matching: that index is a jint field
    ORDINAL, not a jfieldID (found via a compile error against the real
    jvmti.h), and its correspondence to GetClassFields order is a spec
    subtlety the design avoids depending on. Gate falls open (generic
    descent, still no-descend+hop-capped) if the class is not resolvable.
  - an exact-class no-descend set below that (ClassLoader, ProtectionDomain,
    ThreadGroup - contextClassLoader's graph would otherwise reach every
    loaded class and its statics; exact-tag match only, documented as such).
- **Prong 2 (static-holder taxonomy)**: rotation-tier collector with a
  wrapping cursor over the frontier table selecting parent_tag==0 &&
  root_kind==STATIC_FIELD && (FRONTIER or EXPANDED) && !isQueuedForRotation;
  each selected anchor is descend-walked (hop_cap = anchor.depth +
  DESCENT_HOPS). Covers collection-shaped static holders (static Map ->
  table -> Entry -> chunk is 3-4 hops) in ONE walk - no cascade needed.

## Key code facts the design relies on (all verified)

- heapReferenceCallback descent control: non-null batch_tags = one-hop gate;
  nullptr = hop_cap-gated generic descent. Depth computed from frontier
  parent lookup (parent.depth + 1), so hop_cap lowering bounds walk depth.
  Caveat (documented in code): a pre-existing frontier entry reachable in
  the subgraph carries its global depth, so its subtree can be walked deeper
  than DESCENT_HOPS - still bounded by global hop_cap + deadline.
- jvmtiHeapReferenceInfoField.index IS the jfieldID for FIELD references -
  the anchor field gate can match field IDs resolved before the walk (only
  JVMTI GetClassFields/GetFieldName, both legal outside heap callbacks).
- nextTag() restarts at 1 per search; anchor idempotency = GetTag ->
  frontier->lookup -> reuse-or-retag (stale thread tag after restart would
  otherwise alias a reissued tag).
- FrontierEntry carries parent_tag/depth/state/root_kind/class_tag - the
  prong-2 filter is directly expressible.
- THREAD root_kind ranks durability 1 (referenceChains.h rootKindDurability)
  - thread anchor chains get correct (transient-tier) labeling.
- runPass + pollWatchedTargets both run on threadLoop serialized - retained
  qualifying tids are safe to read in the walk phase.

## Round-7 follow-up (user-picked option 2, commit c6635fe0e)

Pod round 7 (ev-leaktag-onpod-round7): both prongs live, interception
still zero - the tagged chunks sit past the 6-hop descend cap (static
anchor walks admitted whole 3000+-edge task subgraphs but stopped
short) or under an uncovered root kind. Fixes in ONE rebuild:
- DESCENT_HOPS 6 -> 16: the walk is deadline-bounded per slice either
  way; already-admitted entries are skipped so repeated passes march
  deeper each pass.
- collectStaticFieldAnchorsForRotation now also selects root-attached
  JNI_GLOBAL entries (the remaining durable root kind - same collector,
  same wrapping cursor, same bounded walks).
- Round 8 = deploy 9d3d0afe6 and watch the same three lines
  (walk engagement, leak-tag intercepted, first chain's edges names).

## Round-8 verdict (ev-leaktag-onpod-round8): BOTH fixes live, interception STILL zero

Both hypotheses from round 7 are REFUTED as sufficient explanations:
16-hop walks complete un-truncated over all 4 root-attached static
anchors (per-pass edges 10→3608, rotation cycling different anchors),
JNI_GLOBAL anchors selected in the same tier — zero interceptions. The
app's actual retention shape (found in its bytecode, diagnosis-only):
ProfileAnalyzer.LEAK_BUFFER, a static final List<byte[]> wrapped in
Collections.unmodifiableList, 3-4 hops from the root static — textbook
prong-2 taxonomy, well inside the cap. The local scenario intercepts
the identical shape, so the walk mechanism is sound in-process. The
remaining suspect is tier MEMBERSHIP on the pod: the
Collections$UnmodifiableList wrapper (a) never admitted root-attached,
(b) root_kind misclassified, or (c) admitted root-attached then
replaced by a chain-attached entry (improveChain / reparentToDurableRoot
both produce parent_tag!=0 entries — plausible: the wrapper is reachable
via many chains and improveChain favors deeper chain-attached entries).
TEMP per-anchor diagnostic (c9a57f681) logs every walked anchor's class
signature + parent/root_kind/state — round 9 = deploy it and read the
wrapper's tier state directly.

## New machinery

- tid -> jthread global-ref registry in ReferenceChainTracker, fed from
  Profiler::onThreadStart/onThreadEnd (profiler.cpp already calls
  ReferenceChainTracker::instance(); register gated on _enabled,
  unregister deliberately NOT - a thread registered while enabled must
  release its global ref even after the recording stopped). PLUS a
  one-time registerExistingThreads() GetAllThreads sweep at
  Profiler::start(): a leaking thread is typically alive since before the
  recording began (the first ThreadLocalLeakScenario run caught this:
  walked=0 with the leak thread unregistered), and onThreadStart never
  fires for it. The sweep lives in the Profiler::start() lifecycle, NOT in
  RCT::start(): the JFR-roundtrip gtest calls RCT::start() directly against
  a partial mock JVMTI table (no GetAllThreads slot) and crashed on the
  null function pointer - a real-lifecycle-only operation must run from
  the real lifecycle.
- RCT retains per-candidate qualifying tids from each poll (bounded copy of
  KlassCandidate::qualifying_tids), zeroed per poll so a dropped candidate
  stops being walked.
- DESCENT_HOPS = 6 (ThreadLocalMap -> table[] -> Entry -> value -> holder ->
  chunk is 5-6 hops; static Map shape is 3-4).
- Cost: each anchor walk is one bounded FollowReferences (deadline + hop
  cap + per-pass anchor caps: THREAD_WALK_MAX_ANCHORS=4,
  STATIC_ANCHOR_ROTATION_BUDGET=4); prong 1 runs before the static sweep on
  its own deadline slice, prong 2 at the head of rotation's slice.

## Verification (shape-agnostic, all green)

- gtests (mock scripted heap, no live JVM): ThreadWalkDescendsOnly-
  ThreadLocalMapAndInterceptsLeak (both anchor-admission paths, both gates
  distinct - anchor gate vs no-descend - plus interception + THREAD-rooted
  chain shape) and StaticAnchorRotationWalksRootAttachedStaticHolders
  (collector filter + wrapping cursor + depth-3 interception through a
  static Map -> table -> Entry -> chunk walk). 553 gtests green.
- Java slow suite: NEW ThreadLocalLeakReferenceChainTest +
  ThreadLocalLeakScenario (ExternalLauncher mode threadlocal-leak) - the
  missing thread-local taxonomy scenario: ThreadLocal-held growing byte[]
  collection, correlated [tl-correlation-found] end-to-end with the thread
  walk engaging live (walked=1 edges=18). Full reference-chain slow family
  9/9 green (ToGcRoot, UnboundedCache, correlation loose+tight, external
  static-field, aggressive, seams).
- The pod only CONFIRMS the taxonomy coverage; it does not steer it (no
  probing of hotdog's simulator shape - user's explicit constraint).
  Pod round 7 = deploy and watch interception count.

## Commits (pushed to origin/jb/reference-chains-pi)

- 186468437: descend-walk core (both prongs, gates, phase wiring,
  tid->Thread registry + start sweep) + the 2 gtests.
- 01c591eea: ThreadLocalLeakScenario + ThreadLocalLeakReferenceChainTest
  + threadlocal-leak launcher mode.
- 93868362e: memory sync (this node).

Deploy handle: build 93868362e.
