---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 03:42:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1776670360 38
1776670365 38
1776670370 38
1776670375 38
1776670380 38
1776670385 38
1776670390 38
1776670395 43
1776670400 43
1776670405 43
1776670410 43
1776670415 43
1776670420 43
1776670425 43
1776670430 43
1776670435 43
1776670440 43
1776670445 43
1776670450 43
1776670455 43
```
</details>

---

