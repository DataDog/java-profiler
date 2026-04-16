---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 07:10:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (3 unique values: 55-68 cores)</summary>

```
1776337334 55
1776337339 55
1776337344 55
1776337349 55
1776337354 68
1776337359 68
1776337364 68
1776337369 68
1776337374 68
1776337379 68
1776337384 68
1776337389 68
1776337394 68
1776337399 68
1776337404 68
1776337409 68
1776337414 63
1776337419 63
1776337424 63
1776337429 63
```
</details>

---

