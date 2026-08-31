---
id: find-hotdog-deploy-last-mile
type: finding
status: confirmed
depends_on: [find-refchains-not-deployed]
supersedes: []
related: [ev-post-resync-deployment-verified, find-onpod-evidence-methodology]
tags: [deployment, tooling, hotdog, patch-dd-java-agent]
created: 2026-08-24
updated: 2026-08-24
---

# Getting a branch build of ddprof-lib onto a hotdog pod is not scripted in this repo

## Reasoning chain

Having established the feature simply wasn't deployed, the next question
was how it gets deployed. The pieces exist but the last mile does not
live in java-profiler:

1. `./gradlew :ddprof-lib:jar`
2. `utils/patch-dd-java-agent.sh` (`DD_AGENT_JAR=… DDPROF_JAR=…`) produces
   `dd-java-agent-patched.jar`. dd-trace-java does **not** need rebuilding;
   this is exactly what `.gitlab/dd-trace-integration/.gitlab-ci.yml:57-61`
   does for integration tests.
3. Getting the patched jar into the pod (overwrite
   `/usr/local/app/agent/dd-java-agent.jar` and restart the JVM, or rebake
   the hotdog image) — this step belongs to the prof-analyzer/hotdog
   service repo, not here.
4. Enabling it. `referencechains=true` is a native ddprof option string
   (`ddprof-lib/src/main/cpp/arguments.cpp:85`, parsed at `:468-490`); the
   dd-trace-java property that plumbs it is
   `-Ddd.profiling.experimental.ddprof.referencechains.enabled=true`,
   which was absent pre-resync and present post-resync.

The user performed steps 3-4 manually ("I resynced and reuploaded the
agent"): the jar was replaced in place at 14:27 (md5
`3b204607ab88b99e18e577d23368ca45`) and the JVM restarted at 14:29 as PID
20807 — the pod itself was never rescheduled (still 44 h old).

## Evidence
- `evidence/ev-post-resync-deployment-verified.md`
- `utils/patch-dd-java-agent.sh`, `.gitlab/dd-trace-integration/.gitlab-ci.yml:57-61`
- `ddprof-lib/src/main/cpp/arguments.cpp:85,468-490`

## What this rules out
- Expecting a `hotdog-deploy` script in this repo. A background search of
  doc/, scripts/, Makefiles and CI yaml was run for one; the conclusion
  reflected in the session was that no such end-to-end path is scripted
  here.
