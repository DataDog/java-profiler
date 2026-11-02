---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 05:56:16 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1793616715 27
1793616720 27
1793616725 27
1793616730 27
1793616735 27
1793616740 27
1793616745 27
1793616750 27
1793616755 27
1793616760 27
1793616765 27
1793616770 29
1793616775 29
1793616780 27
1793616785 27
1793616790 27
1793616795 27
1793616800 27
1793616805 27
1793616810 29
```
</details>

---

