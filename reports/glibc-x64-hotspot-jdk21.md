---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-22 14:04:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (4 unique values: 25-30 cores)</summary>

```
1776880726 30
1776880731 30
1776880736 30
1776880741 30
1776880746 30
1776880751 30
1776880757 28
1776880762 28
1776880767 28
1776880772 28
1776880777 30
1776880782 30
1776880787 26
1776880792 26
1776880797 26
1776880802 26
1776880807 26
1776880812 26
1776880817 25
1776880822 25
```
</details>

---

