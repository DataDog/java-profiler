---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 03:42:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 7 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776670338 64
1776670343 64
1776670348 64
1776670353 64
1776670358 64
1776670363 64
1776670368 64
1776670373 64
1776670378 64
1776670383 64
1776670388 64
1776670393 64
1776670398 64
1776670403 64
1776670408 64
1776670413 64
1776670418 64
1776670423 64
1776670428 64
1776670433 64
```
</details>

---

