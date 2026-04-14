---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-14 04:48:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 28-32 cores)</summary>

```
1776156319 29
1776156324 29
1776156329 29
1776156334 29
1776156339 29
1776156344 29
1776156349 29
1776156354 29
1776156359 29
1776156364 30
1776156369 30
1776156374 28
1776156379 28
1776156384 28
1776156389 28
1776156394 30
1776156399 30
1776156404 30
1776156409 30
1776156414 32
```
</details>

---

