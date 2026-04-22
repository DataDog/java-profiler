---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-22 12:39:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1776875769 27
1776875774 27
1776875779 27
1776875784 27
1776875789 28
1776875794 28
1776875799 28
1776875804 28
1776875809 28
1776875814 28
1776875819 28
1776875824 28
1776875829 28
1776875834 32
1776875839 32
1776875844 32
1776875849 32
1776875854 30
1776875859 30
1776875864 30
```
</details>

---

