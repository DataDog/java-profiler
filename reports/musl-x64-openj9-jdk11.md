---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-17 07:49:02 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 62-93 cores)</summary>

```
1776426264 65
1776426269 65
1776426274 65
1776426279 65
1776426284 65
1776426289 65
1776426294 65
1776426299 62
1776426304 62
1776426309 62
1776426314 62
1776426319 62
1776426324 62
1776426329 62
1776426334 62
1776426339 62
1776426344 62
1776426349 62
1776426354 66
1776426359 66
```
</details>

---

