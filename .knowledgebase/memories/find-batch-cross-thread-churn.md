---
id: find-batch-cross-thread-churn
title: Reference-chain completion nodes cross VM-thread allocation to BFS-thread reclamation on HotSpot
kind: finding
tags: [reference-chains, allocation, jvmti, cross-thread]
applies_to: [ddprof-lib/src/main/cpp/referenceChainWalk.cpp:heapReferenceCallback]
source: refchain-fragmentation/find-batch-cross-thread-churn
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


expandFrontier creates its completion set on the BFS caller, while heapReferenceCallback inserts nodes under HotSpot's VM_HeapWalkOperation on the VM thread; the BFS caller clears or destroys the set after FollowReferences returns. A custom allocator for this state must account for the cross-thread handoff - the collector's background-thread entry point does not make all its allocation thread-local, and resource release must wait until callback use and container ownership have ended. This does not quantify retained pages or assert the same callback actor on other JVM implementations.
