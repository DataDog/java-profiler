---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 14:02:52 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 12 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (6 unique values: 77-87 cores)</summary>

```
1776880760 84
1776880765 86
1776880770 86
1776880775 86
1776880780 86
1776880785 86
1776880790 86
1776880795 86
1776880800 77
1776880805 77
1776880810 77
1776880815 77
1776880820 77
1776880825 81
1776880830 81
1776880835 81
1776880840 81
1776880845 81
1776880850 81
1776880855 81
```
</details>

---

