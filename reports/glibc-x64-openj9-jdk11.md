---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:05:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 25-28 cores)</summary>

```
1776693496 28
1776693501 28
1776693506 28
1776693511 26
1776693516 26
1776693521 26
1776693526 26
1776693531 26
1776693536 26
1776693541 26
1776693546 26
1776693551 26
1776693556 28
1776693561 28
1776693566 25
1776693571 25
1776693576 25
1776693581 25
1776693586 25
1776693591 25
```
</details>

---

