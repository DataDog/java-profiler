---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 10:34:19 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 75-88 cores)</summary>

```
1776695470 75
1776695475 75
1776695480 76
1776695485 76
1776695490 81
1776695495 81
1776695500 81
1776695505 85
1776695510 85
1776695515 88
1776695520 88
1776695525 88
1776695530 88
1776695535 88
1776695540 88
1776695545 88
1776695550 88
1776695555 88
1776695560 88
1776695565 88
```
</details>

---

