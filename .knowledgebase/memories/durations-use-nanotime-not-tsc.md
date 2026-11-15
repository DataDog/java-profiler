---
id: durations-use-nanotime-not-tsc
title: Measure elapsed durations with OS::nanotime(), not TSC::ticks() deltas
kind: finding
tags: [timing, tsc, refchains]
applies_to: [ddprof-lib/src/main/cpp/referenceChainAnchors.cpp]
source: feedback-1/find-c10-tsc-underflow
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


`TSC::ticks()` reads rdtsc on x86, which is not guaranteed monotonic across cores/sockets. An
end-minus-start `u64` delta that steps back underflows to a huge value. In the reference-chain
tracker such a value fed the safepoint cost accounting, which then disabled the search for the
rest of the process.

For durations that feed budgets or accumulators, use `OS::nanotime()` (monotonic clock). Its cost
is negligible at per-pass/per-follow sites.
