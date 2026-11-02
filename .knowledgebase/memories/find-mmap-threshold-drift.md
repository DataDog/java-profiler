---
id: find-mmap-threshold-drift
title: Freeing a large mmapped chunk raises glibc's mmap threshold (<=32MiB) and trim threshold (<=64MiB), routing large allocs into arenas that then stop trimming
kind: finding
tags: [glibc, mmap-threshold, arena]
applies_to: []
source: malloc-arena-detection/find-mmap-threshold-drift
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Freeing a large mmapped chunk raises glibc's mmap threshold (<=32MiB) and trim threshold (<=64MiB), routing large allocs into arenas that then stop trimming

## Reasoning chain
Rule in __libc_free (2.39 malloc.c:3379-3384); disabled by any explicit mallopt/tunable (no_dyn_threshold). trim_threshold can reach HEAP_MAX_SIZE so non-main heap tops effectively never shrink. Detectable only from sampled allocations (>=128KiB without IS_MMAPPED).

## Evidence
- Full derivation and citations in hyp-mmap-threshold-drift and evidence/ev-glibc-source-answers.md.

## What this rules out
- See hyp-mmap-threshold-drift.
