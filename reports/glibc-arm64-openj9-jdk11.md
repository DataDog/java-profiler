---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:05:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776693493 64
1776693498 64
1776693503 64
1776693508 64
1776693513 64
1776693518 64
1776693523 64
1776693528 64
1776693533 64
1776693538 64
1776693543 64
1776693548 64
1776693553 64
1776693558 64
1776693563 64
1776693568 64
1776693573 64
1776693578 64
1776693583 64
1776693588 64
```
</details>

---

