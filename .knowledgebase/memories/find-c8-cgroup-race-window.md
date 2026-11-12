---
id: find-c8-cgroup-race-window
title: C8 race valid but reviewer interleaving unreachable; real window = _initialized/_gc_generations set before initialize_table; fix lives only in #798
kind: finding
tags: [pr-797, os_linux, cgroup, stack-layering]
applies_to: []
source: feedback-1/find-c8-cgroup-race-window
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C8 race valid but reviewer interleaving unreachable; real window = _initialized/_gc_generations set before initialize_table; fix lives only in #798

## Reasoning chain
Writers run once/process (sanity_checked static, _initialized gate). Window: RC enabled GC events earlier; later gcgenerations start sets _gc_generations (2102) & _initialized (2130) before initialize_table (2161); onGC reads path. Torn read bounded (NUL always present). rc-4 g_container_mem_lock has double-lock snapshot gap + dual-hierarchy probe contradicting own comment. Recommend compute-once publish + fix _initialized order.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/C.md. Lines at 9521394e8.

## Follow-up (2026-10-01)
- The user proposed a "can't happen" comment. Pushed back: the window is reachable. Fix the publish order first, then document it as write-once-before-release-flag.
