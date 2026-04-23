---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 04:28:36 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 43-62 cores)</summary>

```
1776932429 43
1776932434 43
1776932439 43
1776932444 43
1776932449 62
1776932454 62
1776932459 62
1776932464 62
1776932469 58
1776932474 58
1776932479 58
1776932484 58
1776932489 58
1776932494 58
1776932499 58
1776932504 58
1776932509 58
1776932514 60
1776932519 60
1776932524 60
```
</details>

---

