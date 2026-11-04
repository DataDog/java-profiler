---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 05:47:34 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1793788896 84
1793788901 84
1793788906 84
1793788911 84
1793788916 84
1793788921 84
1793788927 84
1793788932 84
1793788937 84
1793788942 84
1793788947 84
1793788952 84
1793788957 84
1793788962 84
1793788967 84
1793788972 84
1793788977 82
1793788982 82
1793788987 84
1793788992 84
```
</details>

---

