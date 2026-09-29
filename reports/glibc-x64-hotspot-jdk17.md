---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-29 07:07:49 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 25-29 cores)</summary>

```
1790679794 25
1790679799 25
1790679804 25
1790679809 25
1790679814 25
1790679819 27
1790679824 27
1790679829 29
1790679834 29
1790679839 29
1790679844 29
1790679849 29
1790679854 29
1790679859 29
1790679864 29
1790679869 29
1790679874 29
1790679879 27
1790679884 27
1790679889 27
```
</details>

---

