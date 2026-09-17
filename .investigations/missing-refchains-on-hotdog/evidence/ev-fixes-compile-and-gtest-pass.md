---
id: ev-fixes-compile-and-gtest-pass
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-marker-tag-slot-index-mismatch, find-one-shot-pretag-gate, find-canary-stuck-abandon-detector]
tags: [build, gtest, verification, referenceChains]
created: 2026-08-24
updated: 2026-08-24
---

# Fix A/B/C compile cleanly and pass the existing referenceChains gtest suites

## What was run

```
./gradlew :ddprof-lib:compileDebug -Pskip-gtest
```
-> `BUILD SUCCESSFUL`, 69 C++ source files compiled.

```
./gradlew :ddprof-lib:gtestDebug_referenceChains_ut
```
-> 89/89 tests passed, including `SearchRestartTest` cases exercising
`shouldRunPass`/candidate restart/urgent-bypass paths touched by Fix B/C.

```
./gradlew :ddprof-lib:gtestDebug_referenceChainJfrRoundtrip_ut
```
-> 1/1 test passed (`ProducesValidStandaloneJfrWithChainEvent`), confirming
the `flightRecorder.cpp` `kReasons` table change didn't break JFR
serialization of `ReferenceChainAbandoned`.

## Caveat — does not confirm the actual fix

None of these 90 tests exercises **more than one** canary candidate, so
they cannot by themselves confirm Fix A's slot-decode correction or Fix
B's growing-admission logic against the specific multi-candidate scenario
observed on the hotdog pod (`hyp-regression-of-five-fixes`'s caveat
applies here too). This is exactly the sub-question flagged in
`q-implement-two-fixes` and still open: add a multi-candidate regression
test. All this evidence establishes is: the changes compile, and they do
not regress any existing single-candidate/urgent-bypass/pain-budget
behavior.

## State at time of this evidence

Uncommitted changes on `jb/reference-chains`, HEAD `8114019c2` (diverged,
not committed):
- `ddprof-lib/src/main/cpp/referenceChains.cpp`
- `ddprof-lib/src/main/cpp/referenceChains.h`
- `ddprof-lib/src/main/cpp/flightRecorder.cpp`

No on-pod re-verification has been done — the hotdog pod's deployed `.so`
still predates these fixes.
