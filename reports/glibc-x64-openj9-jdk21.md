---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-20 05:36:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 56-61 cores)</summary>

```
1776677431 60
1776677436 60
1776677441 57
1776677446 57
1776677451 57
1776677456 57
1776677461 57
1776677466 57
1776677471 57
1776677476 59
1776677481 59
1776677486 59
1776677491 59
1776677496 59
1776677501 59
1776677506 59
1776677511 59
1776677516 59
1776677521 61
1776677526 61
```
</details>

---

