---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-26 07:40:59 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 8 |
| Allocations | 316 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1793014543 29
1793014548 29
1793014553 29
1793014558 29
1793014563 29
1793014568 29
1793014573 29
1793014578 29
1793014583 32
1793014588 32
1793014593 32
1793014598 32
1793014603 32
1793014608 32
1793014613 32
1793014618 32
1793014623 32
1793014628 32
1793014633 29
1793014638 29
```
</details>

---

