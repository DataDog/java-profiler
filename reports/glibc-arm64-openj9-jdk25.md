---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 12:01:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 2 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1791301983 42
1791301988 43
1791301993 43
1791301998 43
1791302003 43
1791302008 48
1791302013 48
1791302018 48
1791302023 48
1791302028 48
1791302033 48
1791302038 48
1791302043 48
1791302048 48
1791302053 48
1791302058 43
1791302063 43
1791302068 43
1791302073 43
1791302078 43
```
</details>

---

