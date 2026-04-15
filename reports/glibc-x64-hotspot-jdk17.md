---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 11:14:26 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 70-87 cores)</summary>

```
1776265682 84
1776265687 84
1776265692 84
1776265697 84
1776265702 84
1776265707 87
1776265712 87
1776265717 87
1776265722 87
1776265727 87
1776265732 87
1776265737 87
1776265742 87
1776265747 87
1776265752 87
1776265757 87
1776265762 87
1776265767 70
1776265772 70
1776265777 70
```
</details>

---

