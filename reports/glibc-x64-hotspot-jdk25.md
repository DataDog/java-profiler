---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:36:22 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 57-79 cores)</summary>

```
1794396716 79
1794396721 79
1794396726 79
1794396731 79
1794396736 79
1794396741 79
1794396746 79
1794396751 79
1794396756 57
1794396761 57
1794396766 57
1794396771 57
1794396776 57
1794396781 57
1794396786 57
1794396791 57
1794396796 57
1794396801 57
1794396806 57
1794396811 57
```
</details>

---

