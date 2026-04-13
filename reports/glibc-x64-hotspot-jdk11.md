---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-13 11:55:57 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 35-47 cores)</summary>

```
1776095486 44
1776095491 44
1776095496 44
1776095501 44
1776095506 44
1776095511 44
1776095516 44
1776095521 44
1776095526 43
1776095531 43
1776095536 43
1776095541 43
1776095546 43
1776095551 47
1776095556 47
1776095561 47
1776095566 47
1776095571 43
1776095576 43
1776095581 43
```
</details>

---

