---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:37:24 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 10 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 49-82 cores)</summary>

```
1795613630 82
1795613635 82
1795613640 82
1795613645 82
1795613650 73
1795613655 73
1795613660 73
1795613665 73
1795613670 75
1795613675 75
1795613680 75
1795613685 75
1795613690 75
1795613695 75
1795613700 75
1795613705 49
1795613710 49
1795613715 49
1795613720 49
1795613725 49
```
</details>

---

