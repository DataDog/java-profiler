---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-21 14:31:18 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 8 |
| Allocations | 433 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1776795829 47
1776795834 51
1776795839 51
1776795844 51
1776795849 51
1776795854 51
1776795859 51
1776795864 51
1776795869 51
1776795874 51
1776795879 51
1776795884 48
1776795889 48
1776795894 48
1776795899 48
1776795904 48
1776795909 48
1776795914 48
1776795919 48
1776795924 48
```
</details>

---

