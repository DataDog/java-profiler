---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-23 18:00:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 7 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 17-29 cores)</summary>

```
1776981405 19
1776981410 19
1776981415 19
1776981420 19
1776981425 19
1776981430 19
1776981435 19
1776981440 17
1776981445 17
1776981450 17
1776981455 17
1776981460 17
1776981465 17
1776981470 17
1776981475 17
1776981480 19
1776981485 19
1776981490 19
1776981495 19
1776981500 19
```
</details>

---

