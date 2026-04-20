---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 06:22:58 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 36-64 cores)</summary>

```
1776680337 64
1776680342 64
1776680347 64
1776680352 64
1776680357 64
1776680362 64
1776680367 36
1776680372 36
1776680377 36
1776680382 36
1776680387 36
1776680392 36
1776680397 36
1776680402 36
1776680407 36
1776680412 36
1776680417 36
1776680422 36
1776680427 36
1776680432 36
```
</details>

---

