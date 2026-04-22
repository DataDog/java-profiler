---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-22 04:39:06 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (6 unique values: 57-65 cores)</summary>

```
1776846931 59
1776846936 59
1776846941 59
1776846946 59
1776846951 59
1776846956 59
1776846961 59
1776846966 61
1776846971 61
1776846976 57
1776846981 57
1776846986 57
1776846991 57
1776846996 62
1776847001 62
1776847006 62
1776847011 62
1776847016 62
1776847021 60
1776847026 60
```
</details>

---

