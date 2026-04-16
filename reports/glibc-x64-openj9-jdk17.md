---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-16 12:58:22 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 15-24 cores)</summary>

```
1776358407 19
1776358412 19
1776358417 19
1776358422 15
1776358427 15
1776358432 23
1776358437 23
1776358442 23
1776358447 23
1776358452 24
1776358457 24
1776358462 24
1776358467 24
1776358472 24
1776358477 24
1776358482 24
1776358487 24
1776358492 24
1776358497 24
1776358502 24
```
</details>

---

