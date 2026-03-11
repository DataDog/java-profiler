---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 05:27:47 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 39-77 cores)</summary>

```
1773221099 77
1773221104 77
1773221109 77
1773221114 77
1773221119 77
1773221124 77
1773221129 77
1773221134 77
1773221139 77
1773221144 77
1773221149 77
1773221154 56
1773221159 56
1773221164 61
1773221169 61
1773221174 61
1773221179 61
1773221184 61
1773221189 61
1773221194 61
```
</details>

---

