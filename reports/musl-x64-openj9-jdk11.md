---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 07:42:10 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 878 |
| Sample Rate | 14.63/sec |
| Health Score | 914% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 80-89 cores)</summary>

```
1776857759 80
1776857764 80
1776857769 80
1776857774 80
1776857779 80
1776857784 80
1776857789 80
1776857794 80
1776857799 80
1776857804 80
1776857809 80
1776857814 80
1776857819 80
1776857824 80
1776857829 84
1776857834 84
1776857839 89
1776857844 89
1776857849 89
1776857854 81
```
</details>

---

