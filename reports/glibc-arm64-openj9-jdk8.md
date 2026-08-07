---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-07 07:56:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 15-16 cores)</summary>

```
1786103468 16
1786103473 16
1786103478 16
1786103483 16
1786103488 16
1786103493 16
1786103498 16
1786103503 16
1786103509 16
1786103514 16
1786103519 16
1786103524 16
1786103529 16
1786103534 16
1786103539 16
1786103544 15
1786103549 15
1786103554 15
1786103559 15
1786103564 15
```
</details>

---

