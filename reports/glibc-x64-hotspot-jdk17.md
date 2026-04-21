---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-21 10:50:24 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 11 |
| Allocations | 418 |

<details>
<summary>CPU Timeline (3 unique values: 71-83 cores)</summary>

```
1776782634 83
1776782639 83
1776782644 83
1776782649 83
1776782654 83
1776782659 83
1776782664 83
1776782669 83
1776782674 83
1776782679 83
1776782684 83
1776782689 83
1776782694 83
1776782699 83
1776782704 71
1776782709 71
1776782714 71
1776782719 71
1776782724 71
1776782729 73
```
</details>

---

