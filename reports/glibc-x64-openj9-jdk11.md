---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 07:24:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (6 unique values: 69-75 cores)</summary>

```
1776252036 70
1776252041 70
1776252046 70
1776252051 70
1776252056 70
1776252061 71
1776252066 71
1776252071 73
1776252076 73
1776252081 73
1776252086 73
1776252092 73
1776252098 72
1776252103 72
1776252108 69
1776252113 69
1776252118 69
1776252124 75
1776252129 75
1776252135 75
```
</details>

---

