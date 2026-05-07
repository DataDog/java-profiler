---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 11:01:53 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (4 unique values: 72-83 cores)</summary>

```
1778165867 83
1778165872 83
1778165877 83
1778165882 83
1778165887 83
1778165892 78
1778165897 78
1778165902 78
1778165907 78
1778165912 78
1778165917 72
1778165922 72
1778165927 72
1778165932 72
1778165937 74
1778165942 74
1778165947 74
1778165952 74
1778165957 74
1778165962 74
```
</details>

---

