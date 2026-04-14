---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-14 06:19:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (5 unique values: 48-80 cores)</summary>

```
1776161497 80
1776161502 80
1776161507 80
1776161512 80
1776161517 80
1776161522 80
1776161527 80
1776161532 80
1776161537 76
1776161542 76
1776161547 66
1776161552 66
1776161557 66
1776161562 66
1776161567 66
1776161572 66
1776161577 66
1776161582 68
1776161587 68
1776161592 68
```
</details>

---

