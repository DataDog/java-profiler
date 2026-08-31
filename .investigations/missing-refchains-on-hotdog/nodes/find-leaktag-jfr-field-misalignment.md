---
id: find-leaktag-jfr-field-misalignment
type: finding
status: confirmed
depends_on: [find-leak-tag-pool-implementation]
supersedes: []
related: [find-leak-tag-pool-implementation]
tags: [root-cause, fix, jfr, jfrMetadata, flightRecorder, leak-tag, contextAttributes, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# HeapLiveObject.leakTag parsed from the wrong bytes (context-attribute shift)

## Symptom (recording 20260831-103955)

User: "none of the actually leaking tracked instance has a tag" — all
78MB [B rows showed leakTag=0, two 32-byte rows showed leakTag=75/50.

## Root cause

Metadata declared `leakTag` BEFORE `|| contextAttributes`
(jfrMetadata.cpp), but the binary write put `leak_tag` AFTER
`writeContextSnapshot()` — which writes spanId, rootSpanId, THEN the N
context-attribute values (flightRecorder.cpp:1918). Parsers therefore
read leakTag from the first context-attribute byte: rows with a tracing
context show an attribute encoding (75/50), rows without show 0. The
recording says NOTHING about the actual table state — the pod logs do
(`tagLeakInstances tagged=28`, rep JVMTI tag read back 0x4000000F).

## Invariant (for any future per-event field)

writeContextSnapshot() emits spanId, rootSpanId, then numContextAttributes()
attribute values. A per-event field must be declared on the SAME side of
`|| contextAttributes` in the metadata as its write is on the opposite
side of writeContextSnapshot() in the binary — i.e. both before, or both
after.

## Fix (commit 0db70994d)

leakTag declared between `weight` and `spanId`; written after `weight`,
before writeContextSnapshot(). Binary and metadata now both read:
`... weight, leakTag, spanId, localRootSpanId, [attrs]`.

## Verification pending

Redeploy → 28 tagged rows (incl. all 78MB [B) should show leakTag in
[0x40000000, 0x40000100).
