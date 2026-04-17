---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-17 12:00:28 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 24-56 cores)</summary>

```
1776441354 56
1776441359 56
1776441364 56
1776441369 56
1776441374 56
1776441379 56
1776441384 56
1776441389 54
1776441394 54
1776441399 54
1776441404 54
1776441409 24
1776441414 24
1776441419 24
1776441424 24
1776441429 24
1776441434 24
1776441439 24
1776441444 24
1776441449 24
```
</details>

---

