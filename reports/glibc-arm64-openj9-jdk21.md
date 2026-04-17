---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-17 12:00:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1776441359 54
1776441364 54
1776441369 54
1776441374 54
1776441379 54
1776441384 54
1776441389 54
1776441394 54
1776441399 54
1776441404 54
1776441409 54
1776441414 54
1776441419 54
1776441424 54
1776441429 54
1776441434 54
1776441439 54
1776441444 54
1776441449 59
1776441454 59
```
</details>

---

