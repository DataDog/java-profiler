---
id: mallinfo2-compiled-out-in-release
title: The mallinfo2() arena counters are compiled out of shipped glibc binaries, because the release build uses glibc 2.28 headers
kind: finding
tags: [mallinfo, build, release, glibc, counters]
applies_to: [ddprof-lib/src/main/cpp/flightRecorder.cpp, .gitlab/base/el8/Dockerfile, .gitlab/scripts/rebuild-images.sh]
source: malloc-arena-detection/find-mallinfo-snapshot-dead-in-release
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


`DD_HAVE_MALLINFO2` is defined only when the glibc headers at COMPILE time are 2.33+
(`flightRecorder.cpp`, top of file), and `Recording::updateMallocArenaStats()` is empty without it. The shipped
glibc libraries are built in the AlmaLinux 8 image (glibc 2.28; `rebuild-images.sh` maps
`BUILD_IMAGE_{X64,ARM64}_GLIBC` to `.gitlab/base/el8/Dockerfile`), so the `malloc_*` counters are always 0 in
production. Verified on ddprof 1.52.1: the counter name is present, no `mallinfo2` import.
`mallocArenaStats_ut.cpp` is behind the same macro and runs on newer-glibc test images, so CI never exercises the
shipped binary.

Rule: never gate a runtime libc feature on `__GLIBC_MINOR__`; resolve it at runtime (`dlsym`). Tracked in
PROF-16350.
