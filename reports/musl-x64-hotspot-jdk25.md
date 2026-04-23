---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-23 18:00:40 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 24-30 cores)</summary>

```
1776981400 24
1776981405 24
1776981410 28
1776981415 28
1776981420 26
1776981425 26
1776981430 26
1776981435 26
1776981440 26
1776981445 26
1776981450 26
1776981455 26
1776981460 26
1776981465 26
1776981470 26
1776981475 30
1776981480 30
1776981485 30
1776981490 30
1776981496 30
```
</details>

---

