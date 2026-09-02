---
id: ev-leaktag-onpod-round8
type: evidence
status: confirmed
depends_on: [ev-leaktag-onpod-round7, find-option-c-descend-walk-design]
related: [find-field-name-decoding, find-depth0-durable-root-upgrade-gap]
tags: [pod-verification, round-8, descend-walk, interception-zero, leak-buffer, NEW-THIS-SESSION]
created: 20260902
updated: 20260902
---

# Pod round 8: 16-hop + JNI_GLOBAL walks live, interception STILL zero — retention shape is a textbook prong-2 static List, so the suspect is which anchors enter the tier

Deploy: user redeployed the latest build (post-c6635fe0e: DESCENT_HOPS
16 + JNI_GLOBAL anchor tier) on RENAMED pod
`prof-analyzer-hotdog-jb1-668df5bcff-f75l8` (profiling-stg; pod name
changed from hotdog-jb to hotdog-jb1), JVM 4445, agent
`1.66.0-SNAPSHOT~e188d0ff7f` (datadog.ProfilerSetting in-chunk).

## Verified live this round

- Tagging healthy: `tagLeakInstances summary klass_id=5 tid=4655
  tagged=8 need_set=8→0 max_size=78643216`, ages up to 317 (new pod →
  new klass/tid ids vs round 7's 7/5025).
- Prong 1: `walkCandidateThreadLocals candidates=1 tids=1 walked=1
  edges_admitted=0` every pass (idempotent after the ThreadLocalMap
  admission).
- Prong 2: `walkStaticFieldAnchors selected=4 walked=4 truncated=0` —
  per-pass edges_admitted spans 10 → 3608 (rotation cycling through
  different anchors; large walks are first-encounter passes, small ones
  re-walks of already-admitted subgraphs).
- `intercepted=0` across both streaming windows (23k and 271k log
  lines). runPass line sample: `edges_admitted=1597 frontier=132307
  pendingExpand=121519 priorityExpand=1008 candidateFound=0/1
  discoveredCounts=[8,0,0,0,0]`.
- JFR chunks (`/tmp/ddprof_root/pid_4445/jfr/2026_09_02_16_33_35_4445/`):
  ZERO `datadog.HeapLiveObject` events in ANY chunk — liveness samples
  are not flowing to the recording (BCI_LIVENESS path in
  flightRecorder.cpp:2471 exists; why nothing emits is UNRESOLVED —
  secondary, see q-heapliveobject-absent-on-pod-chunks). No
  ReferenceChain events either (expected: zero interceptions).

## The app's actual retention shape (found in the pod's own bytecode, diagnosis-only)

`com.datadog.profiling.analyzer.steps.ProfileAnalyzer`:

```java
private static final List<byte[]> LEAK_BUFFER;   // static final field
```

- Initialized via `Collections.unmodifiableList(...)` (javap: the
  `<clinit>`-region `invokestatic java/util/Collections.unmodifiableList`).
- Fed by a dedicated `new Thread(runnable, "simulated-memory-leak")`.
- Self-trims at a heap-usage threshold: `List.clear()` + `System.gc()`
  + log "simulated-memory-leak: heap usage {}/{} ({}%) >= {}%, dropping
  {} chunks".
- Taxonomy: 3-4 hops from the root-attached static (wrapper → backing
  ArrayList → elementData array → byte[] chunks). This is EXACTLY
  prong 2's shape — the 16-hop walks over every root-attached static
  should reach the tagged chunks and intercept.

## The verdict

Local scenario intercepts the identical static-List shape (machinery
sound in-process). Both prongs live and un-truncated at 16 hops, all
4 root-attached static anchors walked every pass, anchor rotation
cycling — yet zero interceptions. The remaining suspect is WHICH
entries enter the anchor tier on the pod:
1. `LEAK_BUFFER`'s wrapper (java.util.Collections$UnmodifiableList)
   never admitted root-attached (parent_tag==0, root_kind=STATIC_FIELD),
2. admitted but root_kind misclassified, or
3. admitted root-attached then REPLACED by a chain-attached entry
   (improveChain/reparentToDurableRoot both produce parent_tag!=0
   entries — plausible: the wrapper is reachable via many chains).

Per-anchor diagnostic (committed c9a57f681, TEMP): `walkStaticFieldAnchors
anchor tag= class= parent= root_kind= state= field_index=` per walked
anchor — will name the wrapper's absence/misclassification directly.

Operational: commit signing (1Password SSH agent) failed at session end
("communication with agent failed" for every agent key); worked again
after the agent recovered. The commit sat staged overnight.
