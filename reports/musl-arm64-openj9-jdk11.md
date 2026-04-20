---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:05:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 12 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

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

