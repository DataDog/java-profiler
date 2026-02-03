---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 04:52:45 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 21-32 cores)</summary>

```
1770111779 32
1770111784 32
1770111789 32
1770111794 32
1770111799 32
1770111804 32
1770111809 32
1770111814 32
1770111819 32
1770111824 32
1770111829 32
1770111834 32
1770111840 32
1770111845 32
1770111850 23
1770111855 23
1770111860 21
1770111865 21
1770111870 21
1770111875 21
```
</details>

---

