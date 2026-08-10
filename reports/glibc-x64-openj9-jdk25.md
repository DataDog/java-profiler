---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 01:04:38 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 71-79 cores)</summary>

```
1786337939 71
1786337944 71
1786337949 71
1786337954 71
1786337959 71
1786337964 71
1786337969 71
1786337974 71
1786337979 71
1786337984 71
1786337989 71
1786337994 79
1786337999 79
1786338004 79
1786338009 79
1786338014 79
1786338019 79
1786338024 79
1786338029 79
1786338034 77
```
</details>

---

