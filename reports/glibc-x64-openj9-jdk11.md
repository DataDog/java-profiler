---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 11:41:37 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1776699083 43
1776699088 43
1776699093 43
1776699098 43
1776699103 43
1776699108 43
1776699113 43
1776699118 43
1776699123 43
1776699128 43
1776699133 43
1776699138 43
1776699143 43
1776699148 43
1776699153 43
1776699158 43
1776699163 45
1776699168 45
1776699173 45
1776699178 45
```
</details>

---

