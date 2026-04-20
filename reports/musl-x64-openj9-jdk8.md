---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-20 10:05:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 20-28 cores)</summary>

```
1776693473 20
1776693478 20
1776693483 24
1776693488 24
1776693493 24
1776693498 24
1776693503 24
1776693508 24
1776693513 24
1776693518 24
1776693523 24
1776693528 28
1776693533 28
1776693538 28
1776693543 28
1776693548 28
1776693553 28
1776693558 28
1776693563 28
1776693568 28
```
</details>

---

