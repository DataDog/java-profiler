---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 14:28:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1016 |
| Sample Rate | 16.93/sec |
| Health Score | 1058% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (6 unique values: 67-80 cores)</summary>

```
1776277364 80
1776277369 80
1776277374 79
1776277379 79
1776277384 79
1776277389 79
1776277394 79
1776277399 79
1776277404 75
1776277409 75
1776277414 75
1776277419 71
1776277424 71
1776277429 69
1776277434 69
1776277439 69
1776277444 69
1776277449 69
1776277454 69
1776277459 69
```
</details>

---

