---
id: ev-post-resync-deployment-verified
type: evidence
status: confirmed
depends_on: [ev-deployed-so-1481-no-symbols]
supersedes: []
related: [find-marker-tag-slot-index-mismatch, ev-jafar-zero-refchain-events]
tags: [hotdog, deployment, post-resync, md5, on-pod]
created: 2026-08-24
updated: 2026-08-24
---

# Phase 2: after the user's resync the feature IS deployed and enabled

## Source
Same pod `prof-analyzer-hotdog-jb-c944876b9-f762h` (never rescheduled —
still 44h old, `RESTARTS 5`), but the JVM was restarted in place at 14:29.

## Raw excerpts

New agent jar on disk:

```
  File: /usr/local/app/agent/dd-java-agent.jar
  Size: 37388225
 Birth: 2026-08-24 14:27:19.763707765 +0000
3b204607ab88b99e18e577d23368ca45  /usr/local/app/agent/dd-java-agent.jar
```

New JVM PID (231 is gone; `jcmd 231 JFR.check` -> "Could not find any
processes"):

```
root  20807  ... java -Xms7g -Xmx7g -XX:+UseG1GC ... -javaagent:agent/dd-java-agent.jar ...
      -Ddd.profiling.ddprof.liveheap.enabled=true
      -Ddd.profiling.experimental.ddprof.referencechains.enabled=true      <-- NEW
      -Ddatadog.slf4j.simpleLogger.log.com.datadog.profiling=debug
      -cp classpath/*:libs/* com.datadog.profiling.analyzer.Main
```

Newly loaded native library and its symbol scan:

```
/tmp/ddprof_root/pid_20807/scratch/libjavaProfiler-dd-tmp1075478356263294699.so
=== referencechain strings ===
1097                    # strings ... | grep -icE 'ReferenceChainTracker|referencechains'
=== md5 ===
4d1dc48eaccfb6d0c35831669b71a31a
=== JFR.check ===
20807:
Recording 1: name=dd-profiling maxsize=64.0MB maxage=5m (running)
```

Freshly uploaded JFR
(`/tmp/hotdog-jb-fresh3/prof-analyzer-hotdog-2026-08-24_14-46-42.156Z-ip-10-128-190-53.ec2.internal-stripe.jfr`,
12.6 MB) now declares the types:

```
datadog.ReferenceChain
datadog.ReferenceChainAbandoned
```

(plus new-in-this-build `datadog.UnwindFailure`,
`datadog.WallClockSamplingEpoch`, `datadog.DatadogProfilerClassRefCache`, …)
