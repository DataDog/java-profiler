---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 04:28:58 EDT

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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 14.40/sec |
| Health Score | 900% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776673428 64
1776673433 64
1776673438 64
1776673443 64
1776673448 64
1776673453 64
1776673458 64
1776673463 64
1776673468 64
1776673473 64
1776673478 64
1776673483 64
1776673488 64
1776673493 64
1776673498 64
1776673503 64
1776673508 64
1776673513 64
1776673518 64
1776673523 64
```
</details>

---

