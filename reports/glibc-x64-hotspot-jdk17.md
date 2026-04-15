---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 14:28:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 83-89 cores)</summary>

```
1776277429 87
1776277434 87
1776277439 87
1776277444 87
1776277449 87
1776277454 87
1776277459 87
1776277464 87
1776277469 87
1776277474 87
1776277479 87
1776277484 89
1776277489 89
1776277494 89
1776277499 89
1776277504 89
1776277509 89
1776277514 89
1776277519 85
1776277524 85
```
</details>

---

