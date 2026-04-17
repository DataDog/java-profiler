---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-17 12:00:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 10 |
| Allocations | 172 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1776441356 64
1776441361 64
1776441366 64
1776441371 64
1776441376 64
1776441381 64
1776441386 64
1776441391 64
1776441396 62
1776441401 62
1776441406 62
1776441411 62
1776441416 62
1776441421 62
1776441426 64
1776441431 64
1776441436 64
1776441441 64
1776441446 64
1776441451 64
```
</details>

---

