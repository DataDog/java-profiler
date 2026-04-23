---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 10:22:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 836 |
| Sample Rate | 13.93/sec |
| Health Score | 871% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 73-82 cores)</summary>

```
1776953783 82
1776953788 82
1776953793 77
1776953798 77
1776953803 77
1776953808 77
1776953813 73
1776953818 73
1776953823 73
1776953828 73
1776953833 73
1776953838 75
1776953843 75
1776953848 75
1776953853 75
1776953858 75
1776953863 75
1776953868 75
1776953873 75
1776953878 75
```
</details>

---

