---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:39:01 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 36 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 46-77 cores)</summary>

```
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
1795793725 68
1795793730 68
1795793735 68
1795793740 68
```
</details>

---

