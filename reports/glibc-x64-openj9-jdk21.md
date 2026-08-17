---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 14:25:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 53-81 cores)</summary>

```
1786990917 81
1786990922 81
1786990927 73
1786990932 73
1786990937 73
1786990942 65
1786990947 65
1786990952 65
1786990957 65
1786990962 65
1786990967 65
1786990972 65
1786990977 65
1786990982 65
1786990987 65
1786990992 53
1786990997 53
1786991002 53
1786991007 53
1786991012 53
```
</details>

---

