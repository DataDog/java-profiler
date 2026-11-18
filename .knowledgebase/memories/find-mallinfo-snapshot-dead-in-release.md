---
id: find-mallinfo-snapshot-dead-in-release
title: The mallinfo2 arena snapshot is compiled out of shipped glibc binaries; malloc_* counters are always 0 in production
kind: finding
tags: [mallinfo, build, release, glibc, bug]
applies_to: []
source: malloc-arena-detection/find-mallinfo-snapshot-dead-in-release
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# The mallinfo2 arena snapshot is compiled out of shipped glibc binaries; malloc_* counters are always 0 in production

## Reasoning chain
DD_HAVE_MALLINFO2 requires __GLIBC__ headers >= 2.33 at COMPILE time (ddprof-lib/src/main/cpp/flightRecorder.cpp:13-17). Shipped glibc
.so files are built in the el8 image: .gitlab/scripts/rebuild-images.sh:63-64 map BUILD_IMAGE_{X64,ARM64}_GLIBC to
.gitlab/base/el8/Dockerfile, BASE_IMAGE_GLIBC=almalinux:8 (images.yml:22, comment "requires GLIBC_2.27"),
i.e. glibc 2.28 headers -> macro undefined -> updateMallocArenaStats() body is empty.
Verified on the released artifact: ddprof-1.52.1.jar (Maven Central) linux-x64 and linux-arm64 libjavaProfiler.so
contain the string "malloc_arena_bytes" (counter table) but no "mallinfo"/"mallinfo2" import.
Also: the in-code comment "arena: bytes obtained from the OS via brk" is inaccurate — int_mallinfo sums
av->system_mem over ALL arenas (glibc 2.39 malloc.c ~5312-5313); keepcost is main_arena top only.

## Evidence
- git tag --contains 2b4ace6c7 -> v_1.52.0, v_1.52.1
- grep -a on extracted .so: `1 malloc_arena_bytes`, no mallinfo.
- ev-glibc-source-answers.md Q1.

## What this rules out
- Treating the existing snapshot as a live always-on baseline. Any design must resolve mallinfo2 at runtime
  (dlsym, fallback mallinfo() with int truncation on < 2.33) or use another source.
- Fix: PROF-16350 (filed 2026-10-26): dlsym("mallinfo2") at runtime instead of compile-time gate; the gtest mallocArenaStats_ut.cpp is behind the same macro, so CI never exercised the shipped binary.
