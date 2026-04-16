---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-16 06:02:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 7-12 cores)</summary>

```
1776333323 8
1776333328 8
1776333333 8
1776333338 8
1776333343 8
1776333348 8
1776333353 8
1776333358 8
1776333363 8
1776333368 8
1776333373 12
1776333378 12
1776333383 7
1776333388 7
1776333393 7
1776333398 7
1776333403 7
1776333408 7
1776333413 7
1776333418 7
```
</details>

---

