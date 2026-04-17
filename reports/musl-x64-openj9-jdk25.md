---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-17 07:49:02 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 62-93 cores)</summary>

```
1776426258 65
1776426263 65
1776426268 65
1776426273 65
1776426278 65
1776426283 65
1776426288 65
1776426293 65
1776426298 65
1776426303 62
1776426308 62
1776426313 62
1776426318 62
1776426323 62
1776426328 62
1776426333 62
1776426338 62
1776426343 62
1776426348 62
1776426353 66
```
</details>

---

