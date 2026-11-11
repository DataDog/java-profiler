---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:29:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 79-89 cores)</summary>

```
1794392620 86
1794392625 86
1794392630 86
1794392635 79
1794392640 79
1794392645 79
1794392650 79
1794392655 79
1794392660 79
1794392665 79
1794392670 79
1794392675 79
1794392680 79
1794392685 79
1794392690 79
1794392695 89
1794392700 89
1794392705 89
1794392710 89
1794392715 89
```
</details>

---

