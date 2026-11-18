---
id: find-prior-trail-inaccuracies
title: Prior rc-4 trail claims contradicted by code
kind: finding
tags: [pr-797, cairn-hygiene]
applies_to: []
source: feedback-1/find-prior-trail-inaccuracies
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Prior rc-4 trail claims contradicted by code

## Reasoning chain
- find-fix-sweep-refchains-cpp: invalidation queue "mutex-guarded, capped by MAX_PENDING_CHAIN_INVALIDATIONS" — rc-4 uses SpinLock, constant absent (git grep), vector unbounded.
- find-fix-sweep-misc #4: "one _enabled volatile check per GC" — RCT _enabled is plain bool and never cleared, so epoch work also runs.
- find-rc3-restack-audit #6: adopt-on-reread listed as fix — only narrows the race.

## Evidence
- evidence/B.md, evidence/D.md

## Follow-up (2026-10-01)
- Corrections applied in place, with `[Corrected 2026-10-01 by feedback-1]` markers, in jb-rc-4-profiler-wiring/reference-chain-review-fixes: find-fix-sweep-refchains-cpp item 5, find-fix-sweep-misc item 4, find-rc3-restack-audit item 6. find-fix-sweep-liveness item 9 was annotated with the rc-4 two-lock gap.
