---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-23 12:59:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (5 unique values: 18-32 cores)</summary>

```
1776963329 20
1776963334 20
1776963339 20
1776963344 20
1776963349 20
1776963354 20
1776963359 18
1776963364 18
1776963369 25
1776963374 25
1776963379 25
1776963384 25
1776963389 25
1776963394 25
1776963399 30
1776963404 30
1776963409 30
1776963414 30
1776963419 30
1776963424 32
```
</details>

---

