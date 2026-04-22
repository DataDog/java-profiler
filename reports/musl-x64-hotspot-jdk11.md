---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-22 12:39:21 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 850 |
| Sample Rate | 14.17/sec |
| Health Score | 886% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1776875686 24
1776875691 24
1776875696 24
1776875701 24
1776875706 24
1776875711 24
1776875716 24
1776875721 24
1776875726 24
1776875731 24
1776875736 24
1776875741 24
1776875746 24
1776875751 24
1776875756 24
1776875761 24
1776875766 24
1776875771 24
1776875776 19
1776875781 19
```
</details>

---

