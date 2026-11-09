---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 16:19:00 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 78-84 cores)</summary>

```
1794258870 78
1794258875 78
1794258880 78
1794258885 80
1794258890 80
1794258895 82
1794258900 82
1794258905 84
1794258910 84
1794258915 84
1794258920 84
1794258925 84
1794258930 84
1794258935 84
1794258940 84
1794258945 84
1794258950 84
1794258955 84
1794258960 84
1794258965 84
```
</details>

---

