---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:10:50 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 65-72 cores)</summary>

```
1794355471 72
1794355476 72
1794355481 70
1794355486 70
1794355491 70
1794355496 70
1794355501 70
1794355506 70
1794355511 70
1794355516 70
1794355521 70
1794355526 70
1794355531 65
1794355536 65
1794355541 65
1794355546 65
1794355551 65
1794355556 65
1794355561 65
1794355566 65
```
</details>

---

