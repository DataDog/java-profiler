---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-03 15:15:25 EDT

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
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 8 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788462458 64
1788462463 59
1788462468 59
1788462473 59
1788462478 59
1788462483 59
1788462488 59
1788462493 59
1788462498 59
1788462503 64
1788462508 64
1788462513 64
1788462518 64
1788462523 64
1788462528 64
1788462533 64
1788462538 64
1788462543 64
1788462548 64
1788462553 64
```
</details>

---

