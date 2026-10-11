---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-11 01:02:44 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 39-41 cores)</summary>

```
1791694690 41
1791694695 41
1791694700 41
1791694705 41
1791694710 41
1791694715 41
1791694720 41
1791694725 41
1791694730 41
1791694735 41
1791694740 41
1791694745 41
1791694750 41
1791694755 41
1791694760 41
1791694765 41
1791694770 41
1791694775 41
1791694780 39
1791694785 39
```
</details>

---

