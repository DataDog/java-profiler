---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 05:58:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1794307990 59
1794307995 59
1794308000 59
1794308005 59
1794308010 59
1794308015 59
1794308020 59
1794308025 59
1794308030 61
1794308035 61
1794308040 61
1794308045 61
1794308050 61
1794308055 61
1794308060 61
1794308065 61
1794308070 61
1794308075 61
1794308080 61
1794308085 61
```
</details>

---

