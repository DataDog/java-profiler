---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 05:56:26 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 31-37 cores)</summary>

```
1795171824 31
1795171829 31
1795171834 31
1795171839 31
1795171844 37
1795171849 37
1795171854 37
1795171859 37
1795171864 37
1795171869 37
1795171874 37
1795171879 37
1795171884 37
1795171889 37
1795171894 37
1795171899 37
1795171904 37
1795171909 37
1795171914 37
1795171919 37
```
</details>

---

