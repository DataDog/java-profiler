---
id: find-field-name-decoding
type: finding
status: implemented
depends_on: [find-option-c-descend-walk-design, find-leaktag-jfr-field-misalignment]
related: [ev-hotspot-lifo-visitation-order]
tags: [field-names, hop-labels, jvmti-spec, ReferenceChain, jfr, NEW-THIS-SESSION]
created: 20260902
updated: 20260902
---

# Per-hop retention-edge field names in datadog.ReferenceChain (edges array)

User ask: "record the field name through which the referrer reaches
referee in the refchains events". Answer: yes, via capture-at-admission +
spec-decode-at-emission. IMPLEMENTED and green (554 gtests incl. new decode
test, 9/9 reference-chain slow family, Java JMC parser test asserts the new
T_STRING|F_ARRAY field end to end).

## The three load-bearing facts (source-verified, not inferred)

1. JVMTI heap callbacks expose the field identity as
   reference_info->field.index - a jint ORDINAL over the referrer's
   FLATTENED field space, NOT a jfieldID and NOT a position in one
   GetClassFields result (found via a compile error against the real
   jvmti.h). The numbering is SPEC-DEFINED (jvmti.xml
   jvmtiHeapReferenceInfoField, lines ~3635-3690): count of all
   interfaces-implemented fields (transitive, each once) + superclass
   chain root-first (java.lang.Object's fields first) + own fields, each
   class's fields in GetClassFields order, all modifiers included. The
   interface-referrer branch (static interface constants) uses only the
   interface's own fields over its superinterfaces' count.
2. HotSpot's implementation matches the spec exactly:
   jvmtiTagMap.cpp ClassFieldMap::create_map_of_static_fields /
   create_map_of_instance_fields build exactly that ordinal
   (interfaces_field_count + superclass chain + JavaFieldStream), and
   GetClassFields returns the own-declared JavaFieldStream order
   (jvmtiEnv.cpp:2805-2847) - the two orders compose into the spec space.
3. During heap callbacks only tag/alloc JVMTI functions are callable -
   GetFieldName/GetClassFields are NOT. So the ordinal MUST be captured at
   admission (same cannot-replay-the-callback rationale as
   FrontierEntry::class_tag) and resolved to a name later, outside walks.

## Implementation

- FrontierEntry += referrer_field_index (jint, -1 = not a field edge) +
  edge_kind (u8, interior-hop edge kind) + referrer_class_tag (jlong,
  declaring class for root-attached static edges where the referrer is a
  class object with no parent entry). ~16B/entry, zero hot-path
  allocation; improveChain()/reparentToDurableRoot() refresh the edge
  identity on re-parent so a replaced chain's label describes the WINNING
  edge.
- reconstructChain() collects ChainHopEdge per hop; buildChainEvent()
  (signature now env-threaded: partial mock tables would crash on
  unmocked slots - the JFR-roundtrip crash lesson applied) calls
  fillHopEdgeLabels().
- hopLabelClassFor(): per-referrer-class decoded ordinal->name list,
  cached (cap 1024, cleared on restart; chains re-emit every dump, the
  decode walks the class's interface closure + superclass chain so caching
  is not optional). Decode = GetObjectsWithTags(class_tag) -> jclass;
  IsInterface picks the spec branch; JNI GetSuperclass walks the chain.
- FAIL-SAFE CONTRACT: any decode failure (class gone, ordinal out of the
  computed range, partial function table, null env) degrades to the edge
  KIND label ("element", "constant_pool", ...) - never a fabricated name.
  A wrong numbering on an unverified JVM degrades; it does not lie.
- Event: ReferenceChainEvent._edges (std::vector<std::string>, aligned
  leaf-to-root with _chain: edges[i] = the retention edge INTO chain[i]);
  new JFR field "edges" T_STRING|F_ARRAY written AFTER the chain array in
  both metadata and writer (the leakTag field-order invariant
  generalized); MAX_REFERENCE_CHAIN_EDGE_LABEL=96 shared between the
  collector and the writer's buffer reservation.

## JVMTI gotchas found the hard way (each caught by compile against the
real JDK 26 jvmti.h - the project's own headers are the ground truth)

- jvmtiHeapReferenceInfoField.index is a jint ordinal, not a jfieldID.
- GetMethodName is for METHODS; fields use GetFieldName.
- Modern JVMTI has NO GetSuperclass - it is a JNI function
  (jvmti.xml delivers superclass references via heap callbacks only).

## Verification

- gtest HopEdgeLabelsDecodeSpecFieldOrdinals: interface offset,
  superclass order, interface-referrer branch, and the fail-safe degrade
  all asserted against a fake hierarchy driven through the mock slots.
- referenceChainJfrRoundtrip_ut now seeds edge kinds and asserts the
  kind-label edges; ReferenceChainJfrParserTest (Java/JMC) asserts the
  "edges" field parses as a String[] with exact labels - the T_STRING
  F_ARRAY encoding is validated by a real JMC read, not assumed.
- 554 gtests green; reference-chain slow family 9/9 green (every emitted
  chain now carries edges).

## OPEN: J9 numbering compliance is INFERRED, not verified

The spec defines the numbering and J9 passes the walker's referrerIndex
through for FIELD refs (runtime/jvmti/jvmtiHeap10.c
J9GC_REFERENCE_TYPE_FIELD -> JVMTI_REFERENCE_FIELD), but the OMR
reference-chain-walker arithmetic that produces referrerIndex was not
source-located (unauthenticated GitHub search hit a wall; the walker lives
under eclipse-omr/openj9's gc side). The fail-safe design means a J9
mismatch degrades labels to kinds, never misnames - but verifying the J9
walker against the spec ordinal (a local openj9 checkout would make it a
one-file read) is the remaining follow-up. NOT a pod blocker.

## Value

Chains become readable retention paths ("LeakHolder.SINK ->
HashMap.table -> Entry.value") - the diagnostic point of the feature; also
directly names the holder field for the pod round-7 verification.
