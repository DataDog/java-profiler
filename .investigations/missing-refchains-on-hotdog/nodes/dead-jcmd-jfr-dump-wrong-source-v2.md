---
id: dead-jcmd-jfr-dump-wrong-source-v2
type: deadend
status: refuted
depends_on: []
supersedes: [dead-jcmd-jfr-dump-wrong-source]
related: []
tags: [methodology, wrong-evidence-source, jcmd, jfr, ddprof, NEW-THIS-SESSION]
created: 2026-08-28
updated: 2026-08-28
---

# jcmd JFR.dump does NOT capture ddprof native JFR events

## What happened

Used `jcmd <pid> JFR.dump name=dd-profiling filename=/tmp/dump.jfr` to
try to read `datadog.ReferenceChain` events. The dump showed only JDK
built-in event types — no `datadog.ReferenceChain`, no
`datadog.HeapLiveObject`, none of ddprof's custom events.

## Root cause

`jcmd JFR.dump` dumps the JVM's built-in JFR recording (managed by
`jdk.jfr` API). ddprof writes its own JFR chunks directly to
`/tmp/ddprof_root/pid_XXX/jfr/` via its native `FlightRecorder` class
(`flightRecorder.cpp`). These are two completely separate JFR writers.
`jcmd` has no visibility into ddprof's native writer.

## Correct method

To get ddprof's JFR events:
1. `kubectl cp` the chunk files from
   `/tmp/ddprof_root/pid_XXX/jfr/` on the pod, OR
2. Use the profiling toolkit `download.py` script to download uploaded
   profiles from the Profiling Toolkit API (if the service uploads
   profiles — hotdog staging does not).

## Lesson

This was already documented as `dead-jcmd-jfr-dump-wrong-source` but
was repeated again in this session. The mistake is easy to make because
`jcmd JFR.dump` appears to work (produces a .jfr file with events) —
it just produces the wrong JFR stream.
