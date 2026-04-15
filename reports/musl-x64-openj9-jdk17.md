---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 07:24:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 9 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (4 unique values: 23-27 cores)</summary>

```
1776252023 23
1776252028 23
1776252033 23
1776252038 23
1776252043 27
1776252048 27
1776252053 27
1776252058 27
1776252063 27
1776252068 27
1776252073 27
1776252078 25
1776252083 25
1776252088 25
1776252093 25
1776252098 25
1776252103 25
1776252108 24
1776252113 24
1776252118 24
```
</details>

---

