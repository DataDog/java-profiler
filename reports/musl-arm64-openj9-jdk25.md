---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 05:47:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793788912 48
1793788917 48
1793788922 48
1793788927 48
1793788932 48
1793788937 48
1793788942 48
1793788947 48
1793788952 48
1793788957 48
1793788962 48
1793788967 48
1793788972 48
1793788977 43
1793788982 43
1793788987 43
1793788992 43
1793788997 43
1793789002 43
1793789007 43
```
</details>

---

