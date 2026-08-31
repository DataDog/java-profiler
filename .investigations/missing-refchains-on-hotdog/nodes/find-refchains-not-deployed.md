---
id: find-refchains-not-deployed
type: finding
status: confirmed
depends_on: [ev-deployed-so-1481-no-symbols, ev-uploaded-jfr-no-refchain-types]
supersedes: []
related: [find-onpod-evidence-methodology, find-hotdog-deploy-last-mile, ev-post-resync-deployment-verified]
tags: [phase-1, deployment, resolved, ddprof-1.48.1]
created: 2026-08-24
updated: 2026-08-24
---

# Phase 1 (RESOLVED): the pod was running ddprof-lib 1.48.1, which has no reference-chain code

## Reasoning chain

The original question was "why zero `datadog.ReferenceChain` events". The
first answer turned out to be trivial and not a code bug at all: the
feature was never on the pod.

1. Uploaded profiles for `prof-analyzer-hotdog-jb` did not even *declare*
   `datadog.ReferenceChain` / `datadog.ReferenceChainAbandoned`. Absence
   of the type declaration (as opposed to a zero count) already implies
   the emitting code isn't in the binary. `datadog.HeapLiveObject` WAS
   present, so liveheap sampling itself worked — narrowing it to the
   reference-chain feature specifically.
2. The `.so` the JVM had actually mapped
   (`/tmp/ddprof_root/pid_231/scratch/libjavaProfiler-dd-tmp927042133104699179.so`)
   had **0** `ReferenceChainTracker` strings but **20** `LivenessTracker|liveheap`
   strings — same conclusion from the binary side.
3. To exclude a stale-scratch-extraction artefact, the bundled
   `shared/META-INF/native-libs/linux-x64/libjavaProfiler.so` was extracted
   from `dd-java-agent.jar` on the pod and md5'd:
   `794906a03568ff284c2cb557af693e22` — **byte-identical** to the loaded
   scratch copy. So image content == running content; not a staleness bug.
4. The embedded version string in that `.so` is `1.48.1`. Tag `v_1.48.1`
   (`c96ea85f7`, Tue Aug 4 2026) is **not an ancestor** of
   `jb/reference-chains`, and all reference-chain commits
   (`dc8071dc9` onwards) live only on that branch. So by construction the
   deployed artifact cannot contain the feature.
5. dd-trace-java was stock `1.65.0~dd00372bdd` from image
   `prof-analyzer-hotdog:v130436965-4aea7d55-amd64`; the deployment spec
   had no init container, volume or env override injecting a custom agent
   jar, and the JVM command line carried no reference-chain property.

## Evidence
- `evidence/ev-deployed-so-1481-no-symbols.md`
- `evidence/ev-uploaded-jfr-no-refchain-types.md`

## What this rules out
- Configuration/flag problem — there was no flag to set; the option
  `referencechains=…` (`ddprof-lib/src/main/cpp/arguments.cpp:85,468-490`)
  is parsed only by code that isn't in 1.48.1.
- Stale extracted native library (a known java-profiler failure mode):
  refuted by the byte-identical md5 between jar-bundled and scratch copy.
- Any hypothesis about the reference-chain algorithm itself, for the
  pre-resync data. That data is worthless for algorithm questions.

## Status note
Superseded as the *current* explanation by
`ev-post-resync-deployment-verified` — after the user resynced and
reuploaded the agent the feature IS present, and a genuine code bug
(`find-marker-tag-slot-index-mismatch`) took over as the cause of zero
events.
