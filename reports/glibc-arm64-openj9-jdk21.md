---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 06:45:22 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 54-56 cores)</summary>

```
1786358498 54
1786358503 54
1786358508 54
1786358513 54
1786358518 54
1786358523 54
1786358528 54
1786358533 56
1786358538 56
1786358543 56
1786358548 56
1786358553 56
1786358558 56
1786358563 56
1786358568 56
1786358573 56
1786358578 56
1786358583 56
1786358588 56
1786358593 56
```
</details>

---

