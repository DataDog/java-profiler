---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:27:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 885 |
| Sample Rate | 14.75/sec |
| Health Score | 922% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 18-21 cores)</summary>

```
1786454474 21
1786454479 21
1786454484 21
1786454489 21
1786454494 21
1786454499 21
1786454504 21
1786454509 21
1786454514 18
1786454519 18
1786454524 18
1786454529 18
1786454534 18
1786454539 18
1786454544 18
1786454549 18
1786454554 18
1786454559 18
1786454564 18
1786454569 18
```
</details>

---

