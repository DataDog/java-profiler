---
id: deadend-batched-learn-runs
title: Batched learn runs over green packages (superseded)
kind: dead-end
tags: [test-order, tooling]
applies_to: []
source: writing-any-code-thoroughly/deadend-batched-learn-runs
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Batched learn runs over green packages (superseded)

Before the finalizer patch, learn mode could not complete on the red local
suite, so the index was built by running `-Ptests=<pkg>*` learn batches over
green packages (9 batches, wallclock/nativesocket/memleak/...). Worked but
tedious (~2-5 min per batch) and covered only batched packages. Superseded by
the one-line `finalizedBy("testOrderOfflineRestore")` patch to the mavenLocal
plugin, after which a full-suite learn on the red tree writes the complete
90-class index. Do not re-investigate batching.

## What this rules out
- Any need for package-batched learning or a green suite as a prerequisite.
