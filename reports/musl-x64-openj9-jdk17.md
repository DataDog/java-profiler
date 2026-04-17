---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-17 07:49:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (5 unique values: 62-93 cores)</summary>

```
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
1776426358 66
```
</details>

---

