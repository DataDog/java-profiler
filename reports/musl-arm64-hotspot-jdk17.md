---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 03:42:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 10 |
| Allocations | 123 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1776670352 64
1776670357 62
1776670362 62
1776670367 62
1776670372 62
1776670377 64
1776670382 64
1776670387 64
1776670392 64
1776670397 64
1776670402 64
1776670407 64
1776670412 64
1776670417 64
1776670422 64
1776670427 64
1776670432 64
1776670437 64
1776670442 64
1776670447 64
```
</details>

---

