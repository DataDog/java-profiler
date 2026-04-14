---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-14 04:48:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 27-39 cores)</summary>

```
1776156203 27
1776156208 28
1776156213 28
1776156218 28
1776156223 28
1776156228 28
1776156233 28
1776156238 28
1776156243 28
1776156248 28
1776156253 28
1776156258 33
1776156263 33
1776156268 33
1776156273 33
1776156278 33
1776156283 33
1776156288 33
1776156293 33
1776156298 39
```
</details>

---

