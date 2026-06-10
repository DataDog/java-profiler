---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-06-10 05:13:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 10 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (4 unique values: 43-64 cores)</summary>

```
1781082637 43
1781082642 43
1781082647 43
1781082652 43
1781082657 43
1781082662 43
1781082667 62
1781082672 62
1781082677 64
1781082682 64
1781082687 64
1781082692 64
1781082697 64
1781082702 64
1781082707 64
1781082712 64
1781082717 64
1781082722 64
1781082727 64
1781082733 64
```
</details>

---

