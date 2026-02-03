---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 11:55:42 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 7 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1770137455 32
1770137460 32
1770137465 32
1770137470 32
1770137475 32
1770137480 27
1770137485 27
1770137490 27
1770137495 27
1770137500 32
1770137505 32
1770137510 32
1770137515 32
1770137520 32
1770137525 32
1770137530 32
1770137535 32
1770137540 32
1770137545 32
1770137550 32
```
</details>

---

