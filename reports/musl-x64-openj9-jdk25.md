---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 11:41:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 41-48 cores)</summary>

```
1776699063 48
1776699068 48
1776699073 48
1776699078 48
1776699083 48
1776699088 48
1776699093 48
1776699098 48
1776699103 48
1776699108 48
1776699113 48
1776699118 41
1776699123 41
1776699129 41
1776699134 41
1776699139 41
1776699144 41
1776699149 41
1776699154 41
1776699159 41
```
</details>

---

