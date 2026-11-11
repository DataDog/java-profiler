---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:57:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 84-89 cores)</summary>

```
1794408830 84
1794408835 84
1794408840 84
1794408845 84
1794408850 84
1794408855 84
1794408860 84
1794408865 84
1794408870 84
1794408875 84
1794408880 86
1794408885 86
1794408890 86
1794408895 86
1794408900 86
1794408905 87
1794408910 87
1794408915 87
1794408920 87
1794408925 87
```
</details>

---

