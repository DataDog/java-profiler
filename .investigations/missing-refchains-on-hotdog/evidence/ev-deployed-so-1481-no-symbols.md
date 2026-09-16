---
id: ev-deployed-so-1481-no-symbols
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-refchains-not-deployed, find-onpod-evidence-methodology]
tags: [hotdog, deployment, native-lib, md5, ddprof-1.48.1, on-pod]
created: 2026-08-24
updated: 2026-08-24
---

# Phase 1: the deployed libjavaProfiler.so is ddprof-lib 1.48.1 with zero reference-chain symbols

## Source
Pod `prof-analyzer-hotdog-jb-c944876b9-f762h`, namespace `profiling-stg`,
container `prof-analyzer`, JVM PID 231 (pre-resync). All commands run via
`kubectl exec` on the pod itself.

## Raw excerpts

Loaded library, from `/proc/231/maps`:

```
/tmp/ddprof_root/pid_231/scratch/libjavaProfiler-dd-tmp927042133104699179.so
```

Symbol scan on the loaded scratch copy:

```
=== symbols mentioning ReferenceChain / LivenessTracker in .so ===
0                       # strings ... | grep -icE 'ReferenceChainTracker'
20                      # strings ... | grep -icE 'LivenessTracker|liveheap'
=== jar: reference chain native methods ===
0                       # pollReferenceChainTargets0
```

Extracting the jar-bundled `.so` on the pod with `jar xf` (the pod has
`/usr/bin/jar`, no `unzip`):

```
jar xf /usr/local/app/agent/dd-java-agent.jar shared/META-INF/native-libs/linux-x64/libjavaProfiler.so
-rw-r--r-- 1 root root 1367456 Feb  1  1980 libjavaProfiler.so
=== md5 ===
794906a03568ff284c2cb557af693e22  shared/META-INF/native-libs/linux-x64/libjavaProfiler.so
=== referencechain strings ===
0
=== compare vs scratch-loaded copy ===
794906a03568ff284c2cb557af693e22  /tmp/ddprof_root/pid_231/scratch/libjavaProfiler-dd-tmp927042133104699179.so
```

Version strings from the jar manifest and the bundled `.so`:

```
Manifest-Version: 1.0
Implementation-Version: 1.65.0      # dd-trace-java
1.48.1                              # embedded ddprof-lib version
```

Repo-side ancestry check:

```
$ git log --oneline v_1.48.1 -1
c96ea85f7 [Automated] Release 1.48.1
$ git merge-base --is-ancestor v_1.48.1 jb/reference-chains && echo yes || echo no
no
$ git log -1 --format=%cd v_1.48.1
Tue Aug 4 10:30:27 2026 +0200
```

Branch-only reference-chain commits (never in any release):

```
4993cb6c3 Add reference-chains architecture and design docs
6f1fd14e7 Add Java integration tests and chaos/repro harness for reference chains
1a3165d48 Add C++ unit tests for reference-chain tracking
dc8071dc9 Implement reference chains for surviving live-heap samples
5935c5cfa Add repro/sweep tooling and chaos-harness build wiring for reference chains
```

Deployment context:

```
image: 727006795293.dkr.ecr.us-east-1.amazonaws.com/prof-analyzer-hotdog:v130436965-4aea7d55-amd64
       @sha256:4e4db006b76f0c25b29bbd1b0165fcac73f9b48c5e479b54228e4f3810e52191
DD_ENV=staging  DD_SERVICE=prof-analyzer-hotdog  DD_VERSION=v130436965-4aea7d55-amd64
"version":"1.65.0~dd00372bdd"   (DATADOG TRACER CONFIGURATION status log)
```

Pre-resync JVM command line had no reference-chain flag; only:

```
-javaagent:agent/dd-java-agent.jar
-Ddd.profiling.ddprof.liveheap.enabled=true
```

Pod log grep over 24h for reference-chain activity: `0` matches.
