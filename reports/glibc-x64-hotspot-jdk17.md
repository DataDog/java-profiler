---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-22 14:04:00 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 80-85 cores)</summary>

```
1776880760 81
1776880765 85
1776880770 85
1776880775 85
1776880780 82
1776880785 82
1776880790 82
1776880795 82
1776880800 82
1776880805 82
1776880810 82
1776880815 82
1776880820 82
1776880825 82
1776880830 82
1776880835 82
1776880840 82
1776880845 82
1776880850 82
1776880855 80
```
</details>

---

