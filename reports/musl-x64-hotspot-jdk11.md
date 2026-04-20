---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:20:33 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1776694404 32
1776694409 32
1776694414 32
1776694419 32
1776694424 32
1776694429 27
1776694434 27
1776694439 27
1776694444 27
1776694449 27
1776694454 27
1776694459 27
1776694464 27
1776694469 27
1776694474 27
1776694479 27
1776694484 27
1776694489 27
1776694494 27
1776694499 27
```
</details>

---

