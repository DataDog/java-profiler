---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:31:19 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (6 unique values: 68-83 cores)</summary>

```
1776694886 72
1776694891 72
1776694896 68
1776694901 68
1776694906 68
1776694911 75
1776694916 75
1776694921 75
1776694926 77
1776694931 77
1776694936 77
1776694941 77
1776694946 77
1776694951 77
1776694956 77
1776694961 77
1776694966 77
1776694971 83
1776694976 83
1776694981 83
```
</details>

---

