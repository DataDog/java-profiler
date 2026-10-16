---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 06:16:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 10-32 cores)</summary>

```
1792145509 10
1792145514 10
1792145519 10
1792145524 10
1792145529 10
1792145534 10
1792145539 10
1792145544 10
1792145549 10
1792145554 10
1792145559 10
1792145564 10
1792145569 10
1792145574 10
1792145579 10
1792145584 10
1792145589 10
1792145594 10
1792145599 10
1792145604 32
```
</details>

---

