---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 04:28:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 12 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1776932420 77
1776932425 77
1776932430 77
1776932435 77
1776932440 77
1776932445 77
1776932450 77
1776932455 77
1776932460 77
1776932465 77
1776932470 77
1776932475 75
1776932480 75
1776932485 75
1776932490 75
1776932495 75
1776932500 75
1776932505 75
1776932510 75
1776932515 75
```
</details>

---

