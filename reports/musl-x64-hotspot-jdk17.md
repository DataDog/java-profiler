---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 17:10:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (6 unique values: 71-82 cores)</summary>

```
1778187909 73
1778187914 73
1778187919 73
1778187924 73
1778187929 71
1778187934 71
1778187939 81
1778187944 81
1778187949 81
1778187954 81
1778187959 81
1778187964 81
1778187969 81
1778187974 81
1778187979 80
1778187984 80
1778187989 80
1778187994 80
1778187999 80
1778188004 80
```
</details>

---

