---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:34:56 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 59-76 cores)</summary>

```
1790090852 61
1790090857 61
1790090862 61
1790090867 61
1790090872 61
1790090877 61
1790090882 61
1790090887 61
1790090892 61
1790090897 59
1790090902 59
1790090907 59
1790090912 59
1790090917 59
1790090922 59
1790090927 59
1790090932 59
1790090937 59
1790090942 59
1790090947 61
```
</details>

---

