---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-14 04:48:47 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 17-24 cores)</summary>

```
1776156360 24
1776156365 24
1776156370 24
1776156375 24
1776156380 24
1776156385 24
1776156390 24
1776156395 24
1776156400 24
1776156405 24
1776156410 24
1776156415 24
1776156420 24
1776156425 24
1776156430 24
1776156435 20
1776156440 20
1776156445 17
1776156450 17
1776156455 17
```
</details>

---

