---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 17:10:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (6 unique values: 71-82 cores)</summary>

```
1778187910 73
1778187915 73
1778187920 73
1778187925 71
1778187930 71
1778187935 71
1778187940 81
1778187945 81
1778187950 81
1778187955 81
1778187960 81
1778187965 81
1778187970 81
1778187975 81
1778187980 80
1778187985 80
1778187991 80
1778187996 80
1778188001 80
1778188006 80
```
</details>

---

