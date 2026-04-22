---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-22 11:31:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 52-63 cores)</summary>

```
1776871329 52
1776871334 52
1776871339 52
1776871344 52
1776871349 52
1776871354 52
1776871359 52
1776871364 52
1776871369 52
1776871374 63
1776871379 63
1776871384 58
1776871389 58
1776871394 53
1776871399 53
1776871404 53
1776871409 53
1776871414 53
1776871419 53
1776871424 53
```
</details>

---

