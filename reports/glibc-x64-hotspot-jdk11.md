---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 05:36:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (6 unique values: 41-61 cores)</summary>

```
1776677475 49
1776677480 52
1776677485 52
1776677490 43
1776677495 43
1776677500 43
1776677505 43
1776677510 43
1776677515 43
1776677520 43
1776677525 43
1776677530 43
1776677535 41
1776677540 41
1776677545 43
1776677550 43
1776677555 59
1776677560 59
1776677565 61
1776677570 61
```
</details>

---

