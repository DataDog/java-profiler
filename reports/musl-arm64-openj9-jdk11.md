---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:47:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 10 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793788907 48
1793788912 43
1793788917 43
1793788922 43
1793788927 43
1793788932 43
1793788937 43
1793788942 43
1793788947 43
1793788952 43
1793788957 43
1793788962 43
1793788967 43
1793788972 43
1793788977 43
1793788982 43
1793788987 43
1793788992 43
1793788997 43
1793789002 43
```
</details>

---

