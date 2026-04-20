---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 05:36:46 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 27-46 cores)</summary>

```
1776677408 46
1776677413 46
1776677418 46
1776677423 46
1776677428 46
1776677433 46
1776677439 46
1776677444 46
1776677449 46
1776677454 46
1776677459 46
1776677464 46
1776677469 46
1776677474 46
1776677479 46
1776677484 46
1776677489 37
1776677494 37
1776677499 32
1776677504 32
```
</details>

---

