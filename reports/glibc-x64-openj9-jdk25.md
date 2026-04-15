---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 14:28:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1776277347 79
1776277352 79
1776277357 79
1776277362 79
1776277367 79
1776277372 79
1776277377 79
1776277382 79
1776277387 77
1776277392 77
1776277397 75
1776277402 75
1776277407 77
1776277412 77
1776277417 77
1776277422 77
1776277427 77
1776277432 77
1776277437 77
1776277442 77
```
</details>

---

