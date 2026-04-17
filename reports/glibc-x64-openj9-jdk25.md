---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-17 08:49:14 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (7 unique values: 66-77 cores)</summary>

```
1776429983 68
1776429988 68
1776429993 66
1776429998 66
1776430003 70
1776430008 70
1776430013 70
1776430018 70
1776430023 70
1776430028 70
1776430033 70
1776430038 70
1776430043 76
1776430048 76
1776430053 76
1776430058 77
1776430063 77
1776430068 75
1776430073 75
1776430078 75
```
</details>

---

