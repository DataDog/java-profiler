---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:48:55 EDT

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
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 73-79 cores)</summary>

```
1793187859 73
1793187864 73
1793187869 73
1793187874 73
1793187879 73
1793187884 73
1793187889 73
1793187894 73
1793187899 73
1793187904 73
1793187909 73
1793187914 73
1793187919 73
1793187924 73
1793187929 73
1793187934 73
1793187939 73
1793187944 73
1793187949 73
1793187954 79
```
</details>

---

