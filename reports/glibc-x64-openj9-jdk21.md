---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 11:31:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (4 unique values: 75-82 cores)</summary>

```
1795105595 80
1795105600 80
1795105605 80
1795105610 80
1795105615 82
1795105620 82
1795105625 80
1795105630 80
1795105635 80
1795105640 75
1795105645 75
1795105650 75
1795105655 75
1795105660 75
1795105665 75
1795105670 78
1795105675 78
1795105680 78
1795105685 78
1795105690 78
```
</details>

---

