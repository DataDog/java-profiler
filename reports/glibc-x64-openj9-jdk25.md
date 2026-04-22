---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 14:05:07 EDT

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
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 12 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 42-51 cores)</summary>

```
1776880791 51
1776880796 42
1776880801 42
1776880806 42
1776880811 42
1776880816 42
1776880821 42
1776880826 42
1776880831 42
1776880836 42
1776880841 42
1776880846 42
1776880851 42
1776880857 42
1776880862 42
1776880867 42
1776880872 42
1776880877 42
1776880882 42
1776880887 42
```
</details>

---

