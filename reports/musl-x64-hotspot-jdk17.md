---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 06:22:59 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 915 |
| Sample Rate | 15.25/sec |
| Health Score | 953% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 42-62 cores)</summary>

```
1776680288 42
1776680293 42
1776680298 42
1776680303 42
1776680308 51
1776680313 51
1776680318 60
1776680323 60
1776680328 60
1776680333 60
1776680338 60
1776680343 60
1776680348 60
1776680353 60
1776680358 60
1776680363 60
1776680368 60
1776680373 60
1776680378 60
1776680383 62
```
</details>

---

