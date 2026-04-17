---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-17 12:00:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776441379 64
1776441384 64
1776441389 64
1776441394 64
1776441399 64
1776441404 64
1776441409 64
1776441414 64
1776441419 64
1776441424 59
1776441429 59
1776441434 59
1776441439 59
1776441444 59
1776441449 59
1776441454 59
1776441459 59
1776441464 59
1776441469 59
1776441474 59
```
</details>

---

