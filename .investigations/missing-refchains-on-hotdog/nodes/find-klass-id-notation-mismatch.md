---
id: find-klass-id-notation-mismatch
type: finding
status: confirmed-and-fixed
depends_on: [find-leak-tag-pool-implementation]
related: [find-leak-tag-pool-implementation, find-priority-queue-starves-bfs-crawl]
tags: [root-cause, fix, klass-id, PRODUCTION-BUG, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# LT vs RCT klass-id notation mismatch (production bug, broke ALL discovered matching)

## Root cause (proven from code)

Two resolution sequences for the same class produce TWO different
StringDictionary ids:
- LivenessTracker::resolveKlassId(): `Class.getName()` -> "com.foo.Bar"
  (DOT notation) -> Profiler::lookupClass()
- ReferenceChainTracker::resolveClassMap(): `GetClassSignature` ->
  normalizeClassSignature -> "com/foo/Bar" (SLASH notation, L/; stripped,
  slashes kept) -> same Profiler::lookupClass()

StringDictionary keys by the exact string, so the same class has two ids:
locally observed LivenessTracker id 63 vs ReferenceChainTracker id 2 for
the same class. Only ARRAY classes matched accidentally ("[B" is
notation-identical in both) - which is why the correlation child's byte[]
candidate matching appeared to work while ChainLink/CachedPayload never
matched.

## Production impact (the pod was exhibiting this all along)

Every auto-mark on the pod logged
`resolved but no candidate match (candidates=[4,139,0,0,0])` - the pod's
discovered-instance chain path NEVER matched anything. The chains that did
appear (8 noise + canary rep chains) came via the representative/marker
path, which needs no klass-id matching. Every round of pod debugging that
hypothesized "candidates not matching discovered instances" was seeing
exactly this bug.

## Fix

LivenessTracker::resolveKlassId() now uses the same
GetClassSignature + normalizeClassSignature + lookupClass sequence as
ObjectSampler::recordAllocation() and RCT's resolveClassMap() - the third
user of it. Also strictly cheaper (plain JVMTI call vs Class.getName()
JNI upcall that could allocate). flush_table()'s getName()-based
resolution for JFR event class names is deliberately unchanged (dot-form
rendering preserved).

## Third dot-form user found this session

`ReferenceChainTracker::tagAsRootForTest()` resolved klass ids via
`Class.getName()` too - the seam's entries were in dot space while the
aliased population entries (candidates) were in signature space, so no
candidate could ever match the seam's frontier entries. Same fix applied
(GetClassSignature + normalizeClassSignature + lookupClass). The mock
gtest fixture needed no change (its GetClassSignature mock already feeds
signature-form names).
