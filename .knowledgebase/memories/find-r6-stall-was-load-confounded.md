---
id: find-r6-stall-was-load-confounded
title: stall and latency verdicts are confounded by host load - record load markers with every timing verdict
kind: finding
tags: [load, psi, stall, testing, benchmark]
applies_to: []
source: native-safety-hypothesis-loop/find-r6-stall-was-load-confounded
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


The mallinfo2 stall signature reproduced under pure CPU-spinner containers with
zero allocator activity, and idle repetitions of the same cell showed no stall:
cross-container load is a first-class confound for throughput and stall
comparisons on shared hosts. Timing-based verdicts need recorded load markers
(PSI, loadavg, cgroup throttling), and a loaded run must not pass or fail on
the load - it reports inconclusive or is rerun. Markers must be passive reads of
procfs/sysfs, never instrumentation inside the measured process.
