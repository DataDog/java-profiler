---
id: find-c1-unistd-dead
title: C1 valid: unistd.h include in callTraceStorage.cpp is dead (10edb5fb5 residue)
kind: finding
tags: [pr-797, callTraceStorage, includes]
applies_to: []
source: feedback-1/find-c1-unistd-dead
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C1 valid: unistd.h include in callTraceStorage.cpp is dead (10edb5fb5 residue)

## Reasoning chain
Only PR change to the file; no unistd symbol used; main compiles without it. Remove.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/A.md. Lines at 9521394e8.
