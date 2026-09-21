---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:26:29 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 10 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 58-70 cores)</summary>

```
1789982439 58
1789982444 58
1789982449 58
1789982454 70
1789982459 70
1789982464 70
1789982469 70
1789982474 70
1789982480 70
1789982485 70
1789982490 70
1789982495 70
1789982500 70
1789982505 68
1789982510 68
1789982515 68
1789982521 68
1789982526 68
1789982531 68
1789982536 68
```
</details>

---

