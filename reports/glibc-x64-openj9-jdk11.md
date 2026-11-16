---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 19:49:08 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1794789901 91
1794789906 91
1794789911 91
1794789916 91
1794789921 91
1794789926 91
1794789931 89
1794789936 89
1794789941 89
1794789946 89
1794789951 89
1794789956 89
1794789961 89
1794789966 89
1794789971 89
1794789976 89
1794789982 89
1794789987 89
1794789992 89
1794789997 89
```
</details>

---

