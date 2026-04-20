---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 05:36:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (5 unique values: 64-84 cores)</summary>

```
1776677495 84
1776677500 84
1776677505 66
1776677510 66
1776677515 66
1776677520 64
1776677525 64
1776677530 64
1776677535 64
1776677540 64
1776677545 66
1776677550 66
1776677555 66
1776677560 66
1776677565 69
1776677570 69
1776677575 69
1776677580 69
1776677585 69
1776677590 69
```
</details>

---

