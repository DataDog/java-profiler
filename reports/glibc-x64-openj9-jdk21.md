---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 16:32:02 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 10-32 cores)</summary>

```
1795382889 10
1795382894 10
1795382899 10
1795382904 10
1795382909 10
1795382914 10
1795382919 10
1795382924 10
1795382929 10
1795382934 10
1795382939 10
1795382944 10
1795382949 10
1795382954 10
1795382959 10
1795382964 10
1795382969 10
1795382974 10
1795382979 32
1795382984 32
```
</details>

---

