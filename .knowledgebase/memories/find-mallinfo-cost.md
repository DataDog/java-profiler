---
id: find-mallinfo-cost
title: mallinfo2/malloc_info walk every free chunk under each arena lock: usable only at JFR-chunk cadence, totals only
kind: finding
tags: [glibc, mallinfo, cost]
applies_to: []
source: malloc-arena-detection/find-mallinfo-cost
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# mallinfo2/malloc_info walk every free chunk under each arena lock: usable only at JFR-chunk cadence, totals only

## Reasoning chain
int_mallinfo is O(free chunks) per arena and holds that arena's mutex for its whole walk; malloc_info adds the heap chain and XML. No arena count. Acceptable once per JFR chunk; not for higher-frequency polling.

## Evidence
- Full derivation and citations in hyp-mallinfo-poll and evidence/ev-glibc-source-answers.md.

## What this rules out
- See hyp-mallinfo-poll.
