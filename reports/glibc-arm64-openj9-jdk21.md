---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:44:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792676418 48
1792676423 48
1792676428 43
1792676433 43
1792676438 43
1792676443 43
1792676448 43
1792676453 43
1792676458 43
1792676463 43
1792676468 43
1792676473 43
1792676478 43
1792676483 48
1792676488 48
1792676493 48
1792676498 48
1792676503 48
1792676508 43
1792676513 43
```
</details>

---

