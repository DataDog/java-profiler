---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 09:44:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1792676408 27
1792676413 27
1792676418 27
1792676423 27
1792676428 27
1792676433 27
1792676438 27
1792676443 27
1792676448 22
1792676453 22
1792676458 22
1792676463 22
1792676468 22
1792676473 22
1792676478 22
1792676483 22
1792676488 22
1792676494 22
1792676499 22
1792676504 22
```
</details>

---

