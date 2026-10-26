---
id: glibc-malloc-state-layout-calibration
title: malloc_state field offsets differ by glibc version, distro build and architecture; calibrate them at runtime
kind: finding
tags: [glibc, malloc_state, layout, backport, calibration]
applies_to: []
source: malloc-arena-detection/find-el7-layout-backport
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


Known layouts (x86_64 == aarch64 for upstream; offsets in bytes):

| Layout | next | attached_threads | system_mem | max_system_mem |
|---|---|---|---|---|
| upstream 2.17-2.22 | 2152 | - | 2168 | 2176 |
| upstream 2.23-2.26 | 2152 | 2168 | 2176 | 2184 |
| upstream 2.27-2.42 | 2160 | 2176 | 2184 | 2192 |
| upstream 2.43+ (fastbins removed) | 2072 | 2088 | 2096 | 2104 |

Version alone is not enough: Oracle Linux 7 glibc 2.17 uses the 2.27-2.42 layout on aarch64
(`2.17-326.0.6.el7_9.3`) and the 2.23-2.26 layout on x86_64 (`2.17-326.0.9.el7_9.3`) because of vendor backports.
glibc 2.43 removed `fastbinsY` and `have_fastchunks`, shifting everything by 88 bytes.

Calibrate: try each candidate (version-preferred first) and accept the first whose full walk passes the
structural check (see glibc-arena-list-walk), returns to the seed, and yields plausible values (`system_mem`
non-zero and page-aligned, `max_system_mem >= system_mem`). Fail closed when none passes. New glibc releases can
add layouts, so test against `malloc_info()` on current distro images.
