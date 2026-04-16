---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-16 06:02:55 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1776333307 25
1776333312 25
1776333317 25
1776333322 30
1776333327 30
1776333332 30
1776333337 30
1776333342 30
1776333347 30
1776333352 30
1776333357 30
1776333362 30
1776333367 30
1776333372 30
1776333377 30
1776333382 30
1776333387 30
1776333392 32
1776333397 32
1776333402 32
```
</details>

---

