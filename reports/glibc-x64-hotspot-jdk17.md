---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 06:18:58 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 56-96 cores)</summary>

```
1790244861 72
1790244866 72
1790244871 96
1790244876 96
1790244881 96
1790244886 96
1790244891 66
1790244896 66
1790244901 66
1790244906 66
1790244911 66
1790244916 66
1790244921 66
1790244926 66
1790244931 66
1790244936 66
1790244941 66
1790244946 66
1790244951 66
1790244956 56
```
</details>

---

