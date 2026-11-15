---
id: find-c3-atomics-style
title: C3 valid style-only: classTagAllocator mixes arch.h helper and raw __atomic; volatile only for helper signature
kind: finding
tags: [pr-797, atomics, style]
applies_to: []
source: feedback-1/find-c3-atomics-style
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C3 valid style-only: classTagAllocator mixes arch.h helper and raw __atomic; volatile only for helper signature

## Reasoning chain
Same builtin family; relaxed correct. Recommend raw __atomic_fetch_add, drop volatile. Sweep: RCT/LT/FrontierTable mix volatile+helpers, raw builtins, std::atomic; _table_size mixed orderings.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/A.md. Lines at 9521394e8.

## Follow-up (2026-10-01)
- Survey: ~287 raw __atomic, ~104 std::atomic, 32 __sync, ~63 helper calls repo-wide. Reference-chain code is helper-based; classTagAllocator.h:71 is the only raw __atomic line there.
- Recommendation revised from (a) to (b): add an `atomicExchange` helper to arch.h and keep volatile. This is a new helper and needs the user's OK.
