---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-12 03:21:23 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 66-76 cores)</summary>

```
1791789399 76
1791789404 76
1791789409 76
1791789414 76
1791789419 76
1791789424 76
1791789429 76
1791789434 76
1791789439 76
1791789444 74
1791789449 74
1791789454 74
1791789459 74
1791789464 74
1791789470 74
1791789475 74
1791789480 74
1791789485 72
1791789490 72
1791789495 72
```
</details>

---

