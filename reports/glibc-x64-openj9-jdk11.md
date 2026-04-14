---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-14 06:19:14 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 929 |
| Sample Rate | 15.48/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 34-43 cores)</summary>

```
1776161503 34
1776161508 34
1776161513 34
1776161518 37
1776161523 37
1776161528 37
1776161533 37
1776161538 39
1776161543 39
1776161548 39
1776161553 39
1776161558 39
1776161563 39
1776161568 39
1776161573 39
1776161578 39
1776161583 39
1776161588 39
1776161593 39
1776161598 39
```
</details>

---

