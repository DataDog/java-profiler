---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 10:39:49 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (4 unique values: 46-77 cores)</summary>

```
1795793625 46
1795793630 46
1795793635 46
1795793640 46
1795793645 46
1795793650 46
1795793655 46
1795793660 49
1795793665 49
1795793670 49
1795793675 49
1795793680 49
1795793685 49
1795793690 49
1795793695 68
1795793700 68
1795793705 68
1795793710 68
1795793715 68
1795793720 68
```
</details>

---

