---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-17 11:46:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 70-75 cores)</summary>

```
1776440572 75
1776440577 75
1776440582 75
1776440587 75
1776440592 75
1776440597 75
1776440602 75
1776440607 75
1776440612 75
1776440617 75
1776440622 75
1776440627 75
1776440632 75
1776440637 75
1776440642 70
1776440647 70
1776440652 70
1776440657 70
1776440662 70
1776440667 70
```
</details>

---

