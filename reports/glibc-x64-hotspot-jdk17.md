---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-06 07:13:55 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1039 |
| Sample Rate | 17.32/sec |
| Health Score | 1082% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1786014640 43
1786014645 43
1786014650 43
1786014655 43
1786014660 43
1786014665 43
1786014670 41
1786014675 41
1786014680 41
1786014685 41
1786014690 41
1786014695 46
1786014700 46
1786014705 46
1786014710 46
1786014715 46
1786014720 46
1786014725 46
1786014730 46
1786014735 46
```
</details>

---

