---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-08 14:27:52 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 47-66 cores)</summary>

```
1794165852 66
1794165857 66
1794165862 66
1794165867 66
1794165872 62
1794165877 62
1794165882 62
1794165887 62
1794165892 62
1794165897 62
1794165902 64
1794165907 64
1794165912 64
1794165917 47
1794165922 47
1794165927 47
1794165932 47
1794165937 47
1794165942 47
1794165947 47
```
</details>

---

