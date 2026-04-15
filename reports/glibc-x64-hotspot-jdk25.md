---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-15 14:28:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 72-80 cores)</summary>

```
1776277374 80
1776277379 80
1776277384 80
1776277389 80
1776277394 76
1776277399 76
1776277404 76
1776277409 76
1776277414 76
1776277419 74
1776277424 74
1776277429 74
1776277434 74
1776277439 76
1776277444 76
1776277449 74
1776277454 74
1776277459 74
1776277464 74
1776277469 74
```
</details>

---

