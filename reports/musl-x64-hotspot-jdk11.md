---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-22 14:04:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 10 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 878 |
| Sample Rate | 14.63/sec |
| Health Score | 914% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (5 unique values: 33-68 cores)</summary>

```
1776880733 33
1776880738 33
1776880743 33
1776880748 33
1776880753 33
1776880758 33
1776880763 37
1776880768 37
1776880773 37
1776880778 37
1776880783 37
1776880788 37
1776880793 37
1776880798 37
1776880803 37
1776880808 68
1776880813 68
1776880818 46
1776880823 46
1776880828 46
```
</details>

---

