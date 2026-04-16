---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-16 06:24:10 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 30-32 cores)</summary>

```
1776334530 31
1776334535 31
1776334540 31
1776334545 31
1776334550 32
1776334555 32
1776334560 32
1776334565 32
1776334570 32
1776334575 32
1776334580 32
1776334585 32
1776334590 32
1776334595 32
1776334600 32
1776334605 32
1776334610 32
1776334615 32
1776334620 32
1776334625 32
```
</details>

---

