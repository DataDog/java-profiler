---
id: find-onpod-evidence-methodology
type: finding
status: confirmed
depends_on: [ev-toolkit-and-onpod-methodology, ev-deployed-so-1481-no-symbols]
supersedes: []
related: [dead-jcmd-jfr-dump-wrong-source, dead-toolkit-prod-datacenter, find-refchains-not-deployed]
tags: [methodology, user-feedback, on-pod, evidence-quality]
created: 2026-08-24
updated: 2026-08-24
---

# Methodology: prove deployment state ON the pod, not from downloaded artifacts or image tags

## Reasoning chain

The first version of the phase-1 answer was assembled from Profiling
Toolkit downloads plus inference from the container image tag
(`v130436965-4aea7d55-amd64`, "built from branch=prod"). The user pushed
back:

> you should be able to read the pods from the pod

That is the stronger method, and it changed the evidence from inferential
to direct:

- `kubectl exec … jar xf /usr/local/app/agent/dd-java-agent.jar
   shared/META-INF/native-libs/linux-x64/libjavaProfiler.so` — read the
  artifact that is actually installed, out of the jar the JVM is actually
  loading via `-javaagent`.
- `md5sum` that against `/tmp/ddprof_root/pid_<PID>/scratch/libjavaProfiler-dd-tmp*.so`
  (the copy `DdprofLibraryLoader` extracted and the JVM mapped, found via
  `/proc/<PID>/maps`) — identical md5 closes the staleness question that
  otherwise always lingers in this codebase.
- `strings` for the feature's own symbols, and for the embedded version
  string, gives an artifact-identity answer that no metadata can dispute.

Practical constraints discovered: the pod has `/usr/bin/jar` but no
`unzip` and no `python3`; PIDs change when the agent is re-synced (231 →
20807), so always re-derive the PID with `ps aux | grep java` before
`jcmd`.

## Evidence
- `evidence/ev-toolkit-and-onpod-methodology.md`
- `evidence/ev-deployed-so-1481-no-symbols.md`

## What this rules out
- Trusting image tags / build metadata as evidence of which ddprof-lib is
  running. The jar is mutable in place on this pod (the user overwrote it
  live at 14:27 without rescheduling the pod), so the image tag stayed
  `v130436965-4aea7d55-amd64` while the contents changed completely.
