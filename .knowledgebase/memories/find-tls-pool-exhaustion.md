---
id: find-tls-pool-exhaustion
title: 64-slot ThreadLocalDataPool exhausted by unregistered threads: 6.85M dropped samples in staging prof-analyzer
kind: finding
tags: [malloc-tracer, threadlocaldatapool, nativemem, dropped-samples, staging]
applies_to: [ddprof-lib/src/main/cpp/mallocTracer.cpp, ddprof-lib/src/main/cpp/threadLocalDataPool.h]
source: writing-any-code-thoroughly/find-tls-pool-exhaustion
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# 64-slot ThreadLocalDataPool exhausted by unregistered threads: 6.85M dropped samples in staging prof-analyzer

## Reasoning chain
Both `thread_local_pool_exhausted` and `samples_dropped_thread_local` equal
6,853,922 in rec1 because they increment IN PAIRS: every failed
`ProfiledThread::acquireCurrent()` bumps the pool counter (in claim()) and the
caller's drop counter.

Mechanism:
- ThreadLocalDataPool has a hard 64 slots (threadLocalDataPool.h:9-13), sized
  for "JVM internal threads that start before the pthread_create interceptor
  is initialized - not many, 64 slots should be plenty".
- MallocTracer::maybeRecord() calls acquireCurrent() on EVERY intercepted
  malloc/free BEFORE the sampling gate (mallocTracer.cpp:311-322) - placement
  is deliberate (first-touch priming comment), but with nativemem on
  (modeMask 27) the pool becomes the acquisition fallback for EVERY
  unregistered thread.
- prof-analyzer is a Rust+JVM hybrid: 471 peak / 2,561 accumulated JVM threads
  (jdk.JavaThreadStatistics) plus tokio/grpc-C-core/zstd natives. Once >64
  concurrently-live unregistered threads exist, every malloc on every other
  thread fails forever: SignalBlocker + failed claim + 2 counter increments
  (~6,700 drop-pairs/s over the ~17 min recording).
- Impact: nativemem (and CPU/wall) coverage silently vanishes for those
  threads; only the counters show it.

Operator decision (2026-10-28): do NOT patch now; file a Jira ticket and
investigate whether a gate reorder interferes with the planned
sampler-per-thread design. Filed PROF-16366
(https://datadoghq.atlassian.net/browse/PROF-16366).

## Refined reorder design (would-be patch shape, NOT implemented)
Naively moving acquireCurrent() after shouldSample() SKEWS SAMPLING: the
reentrant hook call (profiler-internal malloc inside recordMalloc) would
decrement the global poisson counter before discovering the CS is held. The
safe shape is two paths:
- TLS present: ProfiledThread::current() (never claims) -> CriticalSection
  try-enter -> shouldSample -> recordMalloc. Reentrant call: CS try fails ->
  skip BEFORE touching the counter. Registered threads keep the cheap TLS hit.
- No TLS (pre-profiler/foreign thread): shouldSample FIRST; only on an actual
  sample, acquireCurrent() (pool claim at sample rate ~7/s) -> CS -> record.
Effect: the pool stops being a per-malloc client; claims happen at sample rate
and in signal-handler priming only - i.e. pre-profiler threads, per the
operator's rule.

## Evidence
- Feasibility analysis (recorded in PROF-16366):
  shouldSample() is thread-independent (global poisson counter,
  mallocTracer.cpp:286-300).
- Pool capacity math: ProfiledThread is a few hundred bytes; 64 -> 512 slots
  is ~0.25 MB.

## What this rules out
- "The drops are reference-chain related" - independent subsystem; the counts
  are identical across both recordings and unrelated to BFS activity.
