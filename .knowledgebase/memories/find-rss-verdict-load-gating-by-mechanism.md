---
id: find-rss-verdict-load-gating-by-mechanism
title: gate load-sensitive verdicts on the load signal that actually distorts the measured quantity, not on host busyness
kind: finding
tags: [psi, load, rss, memory-gate, verdict, ci]
applies_to: [.gitlab/reliability/memory_trend_check.py]
source: native-safety-hypothesis-loop/find-r6-stall-was-load-confounded
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


A load bound calibrated on one host population silently breaks on another: a
CPU-pressure (psi cpu some avg10) bound set from an idle single VM (idle 0.0-0.2,
loaded 45-90) sat inside the normal operating band of shared CI hosts (observed
medians 11.7-40.3, 2026-11-10), turning every row of a memory gate inconclusive.
Choose gating signals by distortion mechanism: scheduler contention shapes
latency/stall verdicts but not RSS trends; memory pressure (reclaim) and cgroup
throttling of the measured workload do alter RSS. Record the non-gating signals
anyway - they explain verdicts later - and mark every bound provisional with
its observed basis, changing it only with recorded-run evidence and engineer
sign-off, never to make one run pass.
