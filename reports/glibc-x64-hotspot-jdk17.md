---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-14 05:49:16 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 885 |
| Sample Rate | 14.75/sec |
| Health Score | 922% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1786700634 96
1786700639 96
1786700644 96
1786700649 96
1786700654 96
1786700659 96
1786700664 96
1786700669 96
1786700674 96
1786700679 96
1786700684 96
1786700689 96
1786700694 96
1786700699 96
1786700704 96
1786700709 94
1786700714 94
1786700719 94
1786700724 94
1786700729 94
```
</details>

---

