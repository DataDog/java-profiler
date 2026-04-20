---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 05:36:45 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 46-50 cores)</summary>

```
1776677453 46
1776677458 46
1776677463 46
1776677468 48
1776677473 48
1776677478 50
1776677483 50
1776677488 50
1776677493 50
1776677498 47
1776677503 47
1776677508 47
1776677513 47
1776677518 47
1776677523 47
1776677528 47
1776677533 47
1776677538 47
1776677543 47
1776677548 47
```
</details>

---

