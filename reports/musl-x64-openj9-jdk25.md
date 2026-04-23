---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 18:00:41 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 42-61 cores)</summary>

```
1776981432 61
1776981437 61
1776981442 61
1776981447 61
1776981452 61
1776981457 61
1776981462 61
1776981467 61
1776981472 61
1776981477 61
1776981482 61
1776981487 61
1776981492 61
1776981497 61
1776981502 61
1776981507 61
1776981512 61
1776981517 61
1776981522 42
1776981527 42
```
</details>

---

