---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 19:07:42 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 9 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 35-39 cores)</summary>

```
1793836978 39
1793836983 39
1793836988 39
1793836993 39
1793836998 39
1793837003 39
1793837008 39
1793837013 39
1793837018 39
1793837023 39
1793837028 39
1793837033 39
1793837038 39
1793837043 39
1793837048 39
1793837053 39
1793837058 39
1793837063 39
1793837068 39
1793837073 39
```
</details>

---

