---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:46:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1778582537 46
1778582542 46
1778582547 46
1778582552 46
1778582557 46
1778582562 46
1778582567 46
1778582572 46
1778582577 46
1778582582 46
1778582587 46
1778582592 46
1778582597 46
1778582602 46
1778582607 46
1778582612 41
1778582617 41
1778582622 41
1778582627 41
1778582632 41
```
</details>

---

