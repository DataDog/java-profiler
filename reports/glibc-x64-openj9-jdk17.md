---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-13 12:35:45 EDT

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
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1791908947 28
1791908952 28
1791908957 28
1791908962 28
1791908967 28
1791908972 28
1791908977 28
1791908982 28
1791908987 28
1791908992 28
1791908997 28
1791909002 30
1791909007 30
1791909012 30
1791909017 30
1791909022 30
1791909027 30
1791909032 30
1791909037 30
1791909042 30
```
</details>

---

