---
id: q-heapliveobject-absent-on-pod-chunks
type: question
status: confirmed
depends_on: [ev-leaktag-onpod-round8, ev-leaktag-onpod-round9]
related: [find-leak-tag-pool-implementation]
tags: [heapliveobject, liveness, jfr, evidence-source, RESOLVED, NEW-THIS-SESSION]
created: 20260902
updated: 20260903
---

# RESOLVED: HeapLiveObject events are absent from LOCAL pod chunks but present in UPLOADED recordings

Round 9 settled it: the uploaded .jfr (toolkit download) contains
`datadog.HeapLiveObject` events — including the 78MB leak chunks
(`eventThread=simulated-memory-leak`, leakTags 1073741987/1073741990,
ages 99-108) — while the local chunks under
`/tmp/ddprof_root/pid_XXX/jfr/` contain neither HeapLiveObject nor
ReferenceChain (same artifact as round 2's "need merged upload" lesson).

## Resolution

Not an emission bug: liveness flows and leak tags reach the recording.
The round-8 "zero HeapLiveObject in any chunk" observation was an
evidence-source artifact.

## Standing evidence rule

Dump-time / liveness events must be verified from UPLOADED recordings
(profiling-toolkit download.py, us1.staging.dog), never from local pod
chunk files. Also: `jfr print` crashes on datadog.ReferenceChain
(PrettyWriter ClassCastException on the chain F_CPOOL|F_ARRAY field) —
use the JMC API (RcDump pattern / ReferenceChainAssertions
findAccessor).
