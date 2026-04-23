---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 04:27:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 70-85 cores)</summary>

```
1776932328 74
1776932333 74
1776932338 74
1776932343 74
1776932348 76
1776932353 76
1776932358 76
1776932363 76
1776932368 76
1776932373 74
1776932378 74
1776932383 74
1776932388 74
1776932393 74
1776932398 74
1776932403 74
1776932408 74
1776932413 70
1776932418 70
1776932423 70
```
</details>

---

