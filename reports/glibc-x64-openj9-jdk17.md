---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-07 07:56:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1786103483 92
1786103488 92
1786103493 90
1786103498 90
1786103503 90
1786103508 90
1786103513 90
1786103518 90
1786103523 90
1786103528 90
1786103533 90
1786103538 90
1786103543 90
1786103548 90
1786103553 90
1786103558 90
1786103563 92
1786103568 92
1786103573 92
1786103578 94
```
</details>

---

