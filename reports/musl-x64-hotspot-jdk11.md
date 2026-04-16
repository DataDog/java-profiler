---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-16 08:32:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1776342269 52
1776342274 52
1776342279 52
1776342284 52
1776342289 52
1776342294 52
1776342299 52
1776342304 52
1776342309 52
1776342314 52
1776342319 52
1776342324 52
1776342329 52
1776342334 47
1776342339 47
1776342344 47
1776342349 47
1776342354 47
1776342359 47
1776342364 47
```
</details>

---

