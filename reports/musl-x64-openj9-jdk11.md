---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:20:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 84-89 cores)</summary>

```
1776694407 84
1776694412 84
1776694417 86
1776694422 86
1776694427 86
1776694432 86
1776694437 86
1776694442 86
1776694447 86
1776694452 86
1776694457 86
1776694462 86
1776694467 86
1776694472 86
1776694477 86
1776694482 86
1776694487 86
1776694492 86
1776694497 86
1776694502 84
```
</details>

---

