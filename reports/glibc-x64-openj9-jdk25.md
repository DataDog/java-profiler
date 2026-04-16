---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-16 12:58:22 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 8 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 13-17 cores)</summary>

```
1776358401 13
1776358406 13
1776358411 13
1776358416 13
1776358421 13
1776358426 13
1776358431 13
1776358436 13
1776358441 13
1776358446 13
1776358451 13
1776358456 13
1776358461 13
1776358466 13
1776358471 13
1776358476 13
1776358481 13
1776358486 13
1776358491 17
1776358496 17
```
</details>

---

