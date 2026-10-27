---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:00:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1793098450 91
1793098455 91
1793098460 91
1793098465 91
1793098470 91
1793098475 91
1793098480 91
1793098485 91
1793098490 91
1793098495 91
1793098500 91
1793098505 89
1793098510 89
1793098515 89
1793098520 89
1793098525 89
1793098530 89
1793098535 89
1793098541 89
1793098546 89
```
</details>

---

