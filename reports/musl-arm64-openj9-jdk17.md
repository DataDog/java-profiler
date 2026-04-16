---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-16 08:32:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
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
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 331 |
| Sample Rate | 5.52/sec |
| Health Score | 345% |
| Threads | 13 |
| Allocations | 98 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776342279 64
1776342284 64
1776342289 64
1776342294 64
1776342299 64
1776342304 64
1776342309 64
1776342314 64
1776342319 64
1776342324 64
1776342329 64
1776342334 64
1776342339 64
1776342344 64
1776342349 64
1776342354 64
1776342359 64
1776342364 64
1776342369 64
1776342374 64
```
</details>

---

