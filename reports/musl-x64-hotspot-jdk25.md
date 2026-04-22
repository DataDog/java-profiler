---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-22 14:04:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 11 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (3 unique values: 30-59 cores)</summary>

```
1776880728 30
1776880733 30
1776880738 30
1776880743 30
1776880748 30
1776880753 30
1776880758 30
1776880763 30
1776880768 30
1776880773 30
1776880778 30
1776880783 30
1776880788 50
1776880793 50
1776880798 59
1776880803 59
1776880808 59
1776880813 59
1776880818 59
1776880823 59
```
</details>

---

