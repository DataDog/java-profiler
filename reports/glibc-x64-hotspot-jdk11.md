---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 12:43:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1040 |
| Sample Rate | 17.33/sec |
| Health Score | 1083% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 65-71 cores)</summary>

```
1793291844 67
1793291849 67
1793291854 67
1793291859 67
1793291864 67
1793291869 67
1793291874 67
1793291879 67
1793291884 67
1793291889 67
1793291894 67
1793291899 65
1793291904 65
1793291909 65
1793291914 65
1793291919 65
1793291924 65
1793291929 69
1793291934 69
1793291939 69
```
</details>

---

