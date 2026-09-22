---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 17:00:43 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 28-64 cores)</summary>

```
1790110479 28
1790110484 28
1790110489 28
1790110494 28
1790110499 28
1790110504 28
1790110509 64
1790110514 64
1790110519 34
1790110524 34
1790110529 34
1790110534 34
1790110539 34
1790110544 34
1790110549 34
1790110554 34
1790110559 34
1790110564 34
1790110569 34
1790110574 34
```
</details>

---

