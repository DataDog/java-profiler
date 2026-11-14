---
id: find-duplicate-emplace
title: libstdc++ unordered_map::emplace allocates a node even when the key already exists
kind: finding
tags: [allocation, libstdc++, emplace]
applies_to: [ddprof-lib/src/main/cpp/referenceChainWalk.cpp:trackLeakAccumulation]
source: refchain-fragmentation/find-duplicate-emplace
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


On libstdc++ (verified with a counting allocator: 100k duplicate attempts caused 100k node allocations, ~3.2 MB requested, map size 1), emplace on an existing key still allocates and frees a node. Duplicate attempts are part of the reference-chain fanout's normal early-stop path. Use non-allocating duplicate lookup (find-then-emplace or try_emplace) on hot paths; this is observed library behavior, not a C++ guarantee.
