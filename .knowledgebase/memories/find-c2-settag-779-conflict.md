---
id: find-c2-settag-779-conflict
title: C2 valid+severe: #779 and #797 share VM::jvmti() tag space; #779 positive count vs #797 negative identity collide on JDK8
kind: finding
tags: [pr-797, classTagAllocator, jvmti-tags, pr-779]
applies_to: []
source: feedback-1/find-c2-settag-779-conflict
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C2 valid+severe: #779 and #797 share VM::jvmti() tag space; #779 positive count vs #797 negative identity collide on JDK8

## Reasoning chain
#779 SetTag via VM::jvmti() gated hotspot_version()==8; RCT has no JDK gate, hasLeakSignal() true when liveness off (<11). #779-first: adopted positive tag hits *tag_ptr>0 arm (referenceChainWalk.cpp:401) -> improveChain on unrelated frontier entry; releaseSearchTags clears #779 dedup tag. #797-first: #779 over-patches and overwrites negative tag. Fix: separate jvmtiEnv (A for RC+LT or B for #779) + defensive asserts.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/A.md. Lines at 9521394e8.

## Follow-up (2026-10-01)
- Masking is not feasible. GetObjectsWithTags uses exact match (anchors:531,615; labels:212; traversal:545,936), so the identity would change on every #779 re-patch. The combination is also a read-modify-write and JVMTI has no tag CAS.
- A second env is just `JavaVM::GetEnv(JVMTI)` again: no re-attach, callable in the live phase. `can_tag_objects` is in HotSpot's always set (jdk8u jvmtiManageCapabilities.cpp init_always_capabilities). Use DisposeEnvironment at shutdown.
- Recommend B: move only #779's GetTag/SetTag pair, which is JDK8 HotSpot only, so no J9 concern. A would touch ~90 tag lines in 6 TUs, and FollowReferences/GetObjectsWithTags would have to move with them.
