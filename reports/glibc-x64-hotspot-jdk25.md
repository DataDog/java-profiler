---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 05:47:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 77-80 cores)</summary>

```
1793788932 80
1793788937 80
1793788942 80
1793788947 80
1793788952 80
1793788957 80
1793788962 77
1793788967 77
1793788972 77
1793788977 77
1793788982 77
1793788987 77
1793788992 77
1793788997 77
1793789002 77
1793789007 77
1793789012 77
1793789017 77
1793789022 77
1793789027 77
```
</details>

---

