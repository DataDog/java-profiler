---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 19:07:43 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1035 |
| Sample Rate | 17.25/sec |
| Health Score | 1078% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 51-73 cores)</summary>

```
1793836946 73
1793836951 73
1793836956 73
1793836961 73
1793836966 73
1793836971 73
1793836976 73
1793836981 51
1793836986 51
1793836991 51
1793836996 51
1793837001 51
1793837006 51
1793837011 51
1793837016 51
1793837021 51
1793837026 51
1793837031 51
1793837036 51
1793837041 51
```
</details>

---

