---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-19 21:19:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (6 unique values: 51-71 cores)</summary>

```
1776647620 51
1776647625 51
1776647630 56
1776647635 56
1776647640 56
1776647645 56
1776647650 60
1776647655 60
1776647660 60
1776647665 60
1776647670 56
1776647675 56
1776647680 56
1776647685 65
1776647690 65
1776647695 71
1776647700 71
1776647705 71
1776647710 71
1776647715 67
```
</details>

---

