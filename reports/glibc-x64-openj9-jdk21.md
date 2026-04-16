---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-16 12:58:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 24 |
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
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 822 |
| Sample Rate | 13.70/sec |
| Health Score | 856% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 24-28 cores)</summary>

```
1776358412 28
1776358417 28
1776358422 28
1776358427 28
1776358432 28
1776358437 28
1776358442 28
1776358447 28
1776358452 28
1776358457 28
1776358462 28
1776358467 28
1776358472 28
1776358477 28
1776358482 28
1776358487 28
1776358492 28
1776358497 28
1776358502 28
1776358507 24
```
</details>

---

