---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 12:39:44 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1078 |
| Sample Rate | 17.97/sec |
| Health Score | 1123% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1776962018 28
1776962023 28
1776962028 28
1776962033 28
1776962038 28
1776962043 28
1776962048 28
1776962053 28
1776962058 23
1776962063 23
1776962068 23
1776962073 23
1776962078 23
1776962083 23
1776962088 28
1776962093 28
1776962098 23
1776962103 23
1776962108 23
1776962113 23
```
</details>

---

