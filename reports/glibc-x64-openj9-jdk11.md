---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 05:36:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 27-46 cores)</summary>

```
1776677430 46
1776677435 46
1776677440 46
1776677445 46
1776677450 46
1776677455 46
1776677460 46
1776677465 46
1776677470 46
1776677475 46
1776677480 46
1776677485 46
1776677490 37
1776677495 37
1776677500 32
1776677505 32
1776677510 32
1776677515 32
1776677520 32
1776677525 32
```
</details>

---

