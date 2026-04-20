---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 06:22:59 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1776680286 26
1776680291 26
1776680296 26
1776680301 26
1776680306 26
1776680311 28
1776680316 28
1776680321 28
1776680326 28
1776680331 28
1776680336 28
1776680341 28
1776680346 28
1776680351 28
1776680356 28
1776680361 28
1776680366 28
1776680371 28
1776680376 28
1776680381 28
```
</details>

---

