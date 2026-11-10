---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 06:41:13 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 81-84 cores)</summary>

```
1794310600 83
1794310605 83
1794310610 83
1794310615 83
1794310620 81
1794310625 81
1794310630 81
1794310635 81
1794310640 81
1794310645 81
1794310650 81
1794310655 81
1794310660 81
1794310665 81
1794310670 81
1794310675 81
1794310680 81
1794310685 81
1794310690 81
1794310695 82
```
</details>

---

