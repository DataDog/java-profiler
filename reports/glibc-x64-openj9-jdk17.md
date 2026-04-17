---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-17 12:00:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1776441454 32
1776441459 32
1776441464 32
1776441469 32
1776441474 32
1776441479 32
1776441484 32
1776441489 30
1776441494 30
1776441499 30
1776441504 30
1776441509 30
1776441514 30
1776441519 30
1776441524 30
1776441529 30
1776441534 30
1776441539 30
1776441544 30
1776441549 30
```
</details>

---

