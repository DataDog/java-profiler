---
id: find-jvm-amplification
title: HotSpot JVMTI heap traversal allocates tag nodes and per-operation storage outside profiler containers
kind: finding
tags: [reference-chains, jvmti, allocation, hotspot]
applies_to: [hotspot/share/prims/jvmtiTagMap.cpp, hotspot/share/utilities/objectBitSet.inline.hpp]
source: refchain-fragmentation/find-jvm-amplification
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


From the OpenJDK 21u source (mechanisms visible in Microsoft HotSpot 21 allocation stacks): callback tag changes allocate JVM tag-table nodes (CallbackWrapper::post_callback_tag_update, JvmtiTagMapTable::add, ResourceHashtableBase::put_when_absent); ClassFieldMap allocates field descriptors and its scoped cache is cleared at the end of every heap operation, so separate walks recreate metadata for the same classes; the operation's ObjectBitSet lazily allocates ~1 MiB bitmap fragments per 64 MiB heap range, released at destruction.

Replacing profiler STL containers cannot remove these JVM allocations; fewer tags or heap operations may affect them but must preserve coverage and pause constraints. VM-thread allocation stacks omit the asynchronous BFS caller, so filtering traces only for ReferenceChainTracker misses JVM-induced work.
