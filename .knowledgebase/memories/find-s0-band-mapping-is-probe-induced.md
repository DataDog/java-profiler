---
id: find-s0-band-mapping-is-probe-induced
title: measurement probes perturb what they measure - record markers passively and snapshot before instrumenting
kind: finding
tags: [measurement, probe, mmap, testing, benchmark]
applies_to: []
source: native-safety-hypothesis-loop/find-s0-band-mapping-is-probe-induced
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


A band mapping attributed to allocator/kernel behavior appeared only after the
probe wrote its own marker file: the instrumentation's footprint created the
effect it measured. Placement and mapping experiments need a pre-instrumentation
snapshot (4/4 rows showed the effect absent at S0, present at S1), and load
markers must be passive reads of procfs/sysfs - never writes into, code
execution inside, or attaches to the measured process.
