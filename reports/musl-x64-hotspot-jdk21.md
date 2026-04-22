---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-22 12:02:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1776873349 34
1776873354 34
1776873359 34
1776873364 34
1776873369 34
1776873374 34
1776873379 34
1776873384 34
1776873389 34
1776873394 34
1776873399 34
1776873404 34
1776873409 34
1776873414 32
1776873419 32
1776873424 32
1776873429 32
1776873434 32
1776873439 32
1776873444 32
```
</details>

---

