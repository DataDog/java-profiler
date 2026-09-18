---
spec_id: REQ-text-13982
source: text
source_ref: (free text)
title: "It seems like java-profiler is interacting badly with wasmtime, when the later is loaded in the profiled JVM"
status: draft
clarity_score: null
created: 2026-04-15
implementing_session: null
implemented_pr: null
---

# It seems like java-profiler is interacting badly with wasmtime, when the later is loaded in the profiled JVM

It seems like java-profiler is interacting badly with wasmtime, when the later is loaded in the profiled JVM. It is either crashing or deadlocking, crashing much more often. When the app is running with just wasmtime library, it seems fine. I want to create a reproducer app where this crash can be debugged properly.
