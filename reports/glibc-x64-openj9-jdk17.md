---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 13:14:50 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 86-96 cores)</summary>

```
1790096977 86
1790096982 86
1790096987 86
1790096992 86
1790096997 86
1790097002 86
1790097007 86
1790097012 86
1790097017 86
1790097022 86
1790097027 86
1790097032 86
1790097037 86
1790097042 86
1790097047 86
1790097052 86
1790097057 86
1790097062 86
1790097067 96
1790097072 96
```
</details>

---

