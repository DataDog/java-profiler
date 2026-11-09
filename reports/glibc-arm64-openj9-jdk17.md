---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 16:18:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 9 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794258915 46
1794258920 46
1794258925 46
1794258930 46
1794258935 48
1794258940 48
1794258945 48
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
1794259000 48
1794259005 48
1794259010 48
```
</details>

---

