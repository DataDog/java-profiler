---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 17:10:04 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 49-57 cores)</summary>

```
1778187905 49
1778187910 49
1778187915 51
1778187920 51
1778187925 51
1778187930 51
1778187935 51
1778187940 57
1778187945 57
1778187950 57
1778187955 57
1778187960 57
1778187965 57
1778187970 57
1778187975 57
1778187980 57
1778187985 57
1778187990 57
1778187995 57
1778188000 57
```
</details>

---

