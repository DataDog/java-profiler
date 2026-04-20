---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 11:57:53 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 56-79 cores)</summary>

```
1776699945 79
1776699950 79
1776699955 79
1776699960 79
1776699965 77
1776699970 77
1776699975 77
1776699980 77
1776699985 77
1776699990 77
1776699995 77
1776700000 75
1776700005 75
1776700010 77
1776700015 77
1776700020 66
1776700025 66
1776700030 66
1776700035 66
1776700041 66
```
</details>

---

