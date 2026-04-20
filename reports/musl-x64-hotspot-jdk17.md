---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 03:42:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 24-28 cores)</summary>

```
1776670343 28
1776670348 28
1776670353 28
1776670358 28
1776670363 28
1776670368 28
1776670373 28
1776670378 28
1776670383 28
1776670388 28
1776670393 28
1776670398 28
1776670403 28
1776670408 28
1776670413 28
1776670418 28
1776670423 28
1776670428 24
1776670433 24
1776670438 24
```
</details>

---

