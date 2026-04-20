---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 05:36:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 32-51 cores)</summary>

```
1776677393 51
1776677398 51
1776677403 51
1776677408 46
1776677413 46
1776677418 46
1776677423 46
1776677428 46
1776677433 46
1776677439 46
1776677444 46
1776677449 46
1776677454 46
1776677459 46
1776677464 46
1776677469 46
1776677474 46
1776677479 46
1776677484 46
1776677489 37
```
</details>

---

