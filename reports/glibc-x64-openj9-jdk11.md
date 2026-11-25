---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:08:10 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1795618867 30
1795618872 30
1795618877 32
1795618882 32
1795618887 27
1795618892 27
1795618897 27
1795618902 27
1795618907 27
1795618912 27
1795618917 27
1795618922 27
1795618927 27
1795618932 27
1795618937 27
1795618942 27
1795618947 27
1795618952 27
1795618957 27
1795618962 27
```
</details>

---

