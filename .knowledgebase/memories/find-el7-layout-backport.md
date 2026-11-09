---
id: find-el7-layout-backport
title: Oracle Linux 7 glibc 2.17 builds use backported malloc_state layouts that differ per arch (aarch64 = 2.27+, x86_64 = 2.23-2.26); offsets must be calibrated at runtime
kind: finding
tags: [glibc, malloc_state, el7, backport, calibration]
applies_to: []
source: malloc-arena-detection/find-el7-layout-backport
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Oracle Linux 7 glibc 2.17 builds use backported malloc_state layouts that differ per arch (aarch64 = 2.27+, x86_64 = 2.23-2.26); offsets must be calibrated at runtime

## Reasoning chain
Reproducer (build/arena-repro/arena_repro.c in worktree start-cairn-investigation, gitignored) with
upstream-2.17 offsets (next 2152) failed the walk on oraclelinux:7 arm64 (glibc-2.17-326.0.6.el7_9.3):
`bad-next`/`fault` in every scenario, detector disabled, no crash -> structural self-check works.
Raw dump of a non-main arena: +2160 = 0x0000ffff809f0570 (pointer into libc -> main_arena = next),
+2168 = 0 (next_free), +2176 = 1 (attached_threads), +2184 = +2192 = 0x21000 (system_mem, max_system_mem):
exactly the upstream 2.27+ layout. The vendor backported malloc struct changes.
Fix in prototype: try candidate layouts {2.17, 2.23-2.26, 2.27+} (version-preferred first), keep the first whose
full walk passes all checks (non-main structural check, exactly one main, closes at seed, system_mem > 0,
page-multiple, max >= sys). After calibration: oraclelinux:7 arm64 -> layout 2.27+ (preferred 2.17), walk
count == malloc_info heap count and per-arena system_mem multisets identical in all 24 results.

## Evidence
- results/oraclelinux-7-arm64.txt: 24x `layout=2 preferred=0 heap_info=32`, xml matched N/N.
- almalinux:8 (2.28) layout 2 heap_info 32; ubuntu:24.04 (2.39) layout 2 heap_info 48 — as predicted.

- amd64 (emulated): oraclelinux:7 glibc-2.17-326.0.9.el7_9.3.x86_64 calibrates to layout 1 (2.23-2.26: next 2152,
  attached 2168, system_mem 2176) in all 24 results, while aarch64 glibc-2.17-326.0.6.el7_9.3 uses layout 2.
  Same distro release, different struct per arch/build -> no static table can be correct.

## What this rules out
- A version -> offset table alone (breaks on enterprise distros with backports).
- Residual: a wrong candidate passing every check by coincidence is implausible (needs a closed cycle of
  structurally valid arenas) but the product should still read via SafeAccess.
