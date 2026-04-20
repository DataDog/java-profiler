---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:05:08 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1776693466 24
1776693471 24
1776693476 24
1776693481 28
1776693486 28
1776693491 28
1776693496 28
1776693501 32
1776693506 32
1776693511 32
1776693516 32
1776693521 32
1776693526 32
1776693531 32
1776693536 32
1776693541 32
1776693546 32
1776693551 32
1776693556 32
1776693561 32
```
</details>

---

