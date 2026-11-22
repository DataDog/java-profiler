---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 16:32:02 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 45-66 cores)</summary>

```
1795382884 47
1795382889 47
1795382894 47
1795382899 47
1795382904 47
1795382909 47
1795382914 47
1795382919 47
1795382924 47
1795382929 45
1795382934 45
1795382939 45
1795382944 45
1795382949 45
1795382954 66
1795382959 66
1795382964 49
1795382969 49
1795382974 49
1795382979 49
```
</details>

---

