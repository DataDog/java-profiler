---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:53:30 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 38-64 cores)</summary>

```
1778582845 38
1778582851 38
1778582856 38
1778582861 38
1778582866 38
1778582871 38
1778582876 38
1778582881 38
1778582886 38
1778582891 38
1778582896 38
1778582901 41
1778582906 41
1778582911 41
1778582916 41
1778582921 41
1778582926 41
1778582931 41
1778582936 41
1778582941 64
```
</details>

---

