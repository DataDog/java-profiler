---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-07 07:56:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 64-67 cores)</summary>

```
1786103468 64
1786103473 64
1786103478 64
1786103483 64
1786103488 64
1786103493 64
1786103498 64
1786103503 64
1786103508 64
1786103513 64
1786103518 64
1786103523 64
1786103528 64
1786103533 64
1786103538 64
1786103543 64
1786103548 67
1786103553 67
1786103558 67
1786103563 67
```
</details>

---

