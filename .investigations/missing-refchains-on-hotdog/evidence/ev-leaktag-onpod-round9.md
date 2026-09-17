---
id: ev-leaktag-onpod-round9
type: evidence
status: confirmed
depends_on: [ev-leaktag-onpod-round8, find-option-c-descend-walk-design]
related: [find-field-name-decoding, q-heapliveobject-absent-on-pod-chunks, find-anchor-holder-eviction]
tags: [pod-verification, round-9, anchor-tier, edges, heapliveobject, events-flowing, NEW-THIS-SESSION]
created: 20260903
updated: 20260903
---

# Pod round 9 (c9a57f681 diagnostic): anchor tier = 76 machinery statics, NO holder; events ARE flowing end-to-end in uploaded recordings

Deploy: c9a57f681 on pod `prof-analyzer-hotdog-jb1-668df5bcff-7h5n9`
(Renamed again; JVM 77972, agent .so extracted 09:43 UTC, contains the
diagnostic string — build verified BEFORE interpreting logs).

## Anchor diagnostic answer (the round-9 question)

`walkStaticFieldAnchors anchor tag=... class=...` lines: the tier cycles
through exactly **76 root-attached anchors** (selected=4/pass, wrapping
cursor), all `parent=0 root_kind=8 state=1(EXPANDED)`, and ALL are
machinery: jnr/jffi/kenai statics, charsets
(`Lsun/nio/cs/UTF_16LE;`...), `Ljava/lang/reflect/Method;`, `[I`. **Zero
`com/datadog` classes — not even ProfileAnalyzer's `log` Logger — and no
`Collections$UnmodifiableList`/`ArrayList` holder.** The LEAK_BUFFER
holder NEVER enters the anchor tier.

Sweep itself is healthy: k8 (STATIC_FIELD) tally ~1000-1100 edges/chunk,
cursor advancing 22651→23675 of 33098 classes, per-chunk admissions 0-11
(first lap admits; later laps ALREADY_ADMITTED).

## Events ARE flowing (uploaded recordings — local pod chunks are a bad source)

- Local pod chunks (kubectl cp) AND `jfr summary` of uploads show NO
  ReferenceChain/HeapLiveObject types, but the UPLOADED .jfr (toolkit
  download) contains both. Same artifact as round 2's "need merged upload"
  lesson — extends to HeapLiveObject. RULE: uploaded recordings are the
  only valid evidence source for dump-time events.
- 12 unique `datadog.ReferenceChain` events in one 60s upload
  (re-emitted from cache per dump, per design): depth-0 static_field
  chains (byte[] held by statics named `CRLF`, `buf`, `COLONSPACE`,
  `DASHDASH` — charset/constant machinery) and 5-13-hop jni_global chains
  through `Mac`/`HmacCore` (`k_opad`/`k_ipad`!) → ThreadLocalMap →
  ForkJoinWorkerThread — the tagged 128KB machinery cohort (klass_id=2,
  tid 78360) fully explained WITH per-hop edge names. The edges feature
  works on-pod, first real-world validation.
- `datadog.HeapLiveObject` events present, including `objectClass=byte[]
  size=78643216B eventThread=simulated-memory-leak age=99-108
  leakTag=1073741987/1073741990` — THE LEAK CHUNKS carry leak tags in the
  recording. Liveness is flowing; the local-chunk absence was an
  evidence-source artifact (q-heapliveobject RESOLVED).
- Correlation check: the 12 chains' targetTags (8479-9376, frontier tags)
  are DISJOINT from the leak tags (0x40000063/66) — leak chunks still
  have no chain (interception still zero, consistent with the holder
  never being walked).

## Interpretation

The ORIGINAL question ("zero datadog.ReferenceChain events") is
functionally RESOLVED: events flow end-to-end on-pod with named edges,
for the machinery cohort. The remaining correctness gap is now sharply
isolated: the LEAK_BUFFER holder never enters the anchor tier (76/76
anchors are machinery), so the tagged 78MB chunks are never enumerated by
any walk → no chain for the actual leak. Mechanism candidate confirmed
in code (see find-anchor-holder-eviction): parent_tag==0 is required by
the collector, improveChain replaces root-attached entries with
chain-attached ones, and re-rooting a chain-attached entry is explicitly
refused (referenceChains.cpp:2376, "known, documented limitation").

Operational: `jfr print --events datadog.ReferenceChain` CRASHES
(ClassCastException in PrettyWriter on the chain F_CPOOL|F_ARRAY field —
RecordedClass cannot cast to Object[]) — parse with JMC API instead
(RcDump.java pattern: accessors by identifier, ReferenceChainAssertions
has the canonical code). JMC classpath: flightrecorder-9.1.1.jar +
common-9.1.1.jar + lz4-java-1.4.0.jar from the Gradle cache.
