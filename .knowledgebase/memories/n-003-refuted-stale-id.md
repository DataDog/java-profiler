---
id: n-003-refuted-stale-id
title: n-003: REFUTED — no stale candidate klass id after class-map rotation
kind: dead-end
tags: [reference-chains, refuted]
applies_to: []
source: frontier-wait-untagged/n-003-refuted-stale-id
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# n-003: REFUTED — no stale candidate klass id after class-map rotation

- status: refuted
- evidence: /tmp/child-section3.log resolveClassMap lines

## What was suspected

The candidate's klass_id (2) vs the auto-marked objects' resolved klass_id (1)
looked like a stale id after a class-map rotation ("auto-mark klass_id=1
resolved but no candidate match (candidates=[2,...])" x94k).

## Reality

- id=1 = java/lang/String; id=2 = [B (byte[]) — the candidate id is CURRENT.
- The auto-marked objects are Strings — correctly not matching the byte[]
  candidate. The 94k lines are benign volume, not a bug.
- StringDictionary::rotate() is id-preserving (two-phase copy, commit
  434e0f4c6); clearAll() resets ids only at Profiler::start() (once, before
  any aliasing). Ids never went stale.

## Consequence

The candidateFound=0/1 has a different cause: the leak-tagged byte[] instances
are never VISITED by any walk (buildChainEvent "target_tag not in frontier" —
the leak tag has no frontier entry). The open thread is the discovery path:
why the fanout rotation prong never selects elementData (n-001/n-002 follow-up).
