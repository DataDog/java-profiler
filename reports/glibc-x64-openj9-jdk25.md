---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 04:32:55 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 8 |
| Allocations | 434 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 22-28 cores)</summary>

```
1776932904 28
1776932909 26
1776932914 26
1776932919 26
1776932924 26
1776932929 26
1776932934 26
1776932939 26
1776932944 26
1776932949 26
1776932954 26
1776932959 26
1776932964 26
1776932969 26
1776932974 26
1776932979 26
1776932984 26
1776932989 26
1776932994 26
1776932999 22
```
</details>

---

