---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-22 12:02:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 41-45 cores)</summary>

```
1776873344 41
1776873349 41
1776873354 41
1776873359 41
1776873364 45
1776873369 45
1776873374 45
1776873379 45
1776873384 45
1776873389 45
1776873394 45
1776873399 45
1776873404 45
1776873409 45
1776873414 45
1776873419 45
1776873424 45
1776873429 45
1776873434 45
1776873439 45
```
</details>

---

