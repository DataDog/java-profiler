---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 12:07:08 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 60-62 cores)</summary>

```
1794502894 62
1794502899 62
1794502904 62
1794502909 62
1794502914 60
1794502919 60
1794502924 60
1794502929 60
1794502934 60
1794502939 60
1794502944 62
1794502949 62
1794502954 62
1794502959 61
1794502964 61
1794502969 61
1794502974 61
1794502979 61
1794502984 61
1794502989 61
```
</details>

---

