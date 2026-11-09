---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 16:18:59 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794258899 36
1794258904 36
1794258909 36
1794258914 36
1794258919 36
1794258924 36
1794258929 36
1794258934 36
1794258939 48
1794258944 48
1794258950 48
1794258955 48
1794258960 48
1794258965 48
1794258970 48
1794258975 48
1794258980 48
1794258985 48
1794258990 48
1794258995 48
```
</details>

---

