---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 12:07:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1794502960 75
1794502965 75
1794502970 75
1794502975 75
1794502980 75
1794502985 77
1794502990 77
1794502995 77
1794503000 77
1794503005 79
1794503010 79
1794503015 79
1794503020 77
1794503025 77
1794503030 77
1794503035 77
1794503040 77
1794503045 77
1794503050 77
1794503055 77
```
</details>

---

