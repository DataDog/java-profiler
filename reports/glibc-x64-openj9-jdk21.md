---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-15 14:28:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 10 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 87-92 cores)</summary>

```
1776277379 91
1776277384 91
1776277389 91
1776277394 91
1776277399 91
1776277404 92
1776277409 92
1776277414 90
1776277419 90
1776277424 90
1776277429 90
1776277434 92
1776277439 92
1776277444 90
1776277449 90
1776277454 90
1776277459 87
1776277464 87
1776277469 89
1776277474 89
```
</details>

---

