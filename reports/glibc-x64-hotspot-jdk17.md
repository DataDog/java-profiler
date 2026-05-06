---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-06 08:18:44 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 76-90 cores)</summary>

```
1778069729 76
1778069734 76
1778069739 76
1778069744 76
1778069749 76
1778069754 76
1778069759 80
1778069764 80
1778069769 90
1778069774 90
1778069779 90
1778069784 90
1778069789 90
1778069794 81
1778069799 81
1778069804 81
1778069809 81
1778069814 81
1778069819 81
1778069824 81
```
</details>

---

