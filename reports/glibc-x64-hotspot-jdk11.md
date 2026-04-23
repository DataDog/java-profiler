---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 18:00:38 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1776981410 62
1776981415 62
1776981420 62
1776981425 62
1776981430 62
1776981435 62
1776981440 62
1776981445 62
1776981450 62
1776981455 62
1776981460 64
1776981465 64
1776981470 64
1776981475 60
1776981480 60
1776981485 60
1776981490 60
1776981495 60
1776981500 60
1776981505 60
```
</details>

---

