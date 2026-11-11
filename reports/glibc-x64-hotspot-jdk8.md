---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-11 16:04:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 64-75 cores)</summary>

```
1794430795 64
1794430800 66
1794430805 66
1794430810 66
1794430815 66
1794430820 66
1794430825 66
1794430830 66
1794430835 66
1794430840 68
1794430845 68
1794430850 68
1794430855 68
1794430860 68
1794430865 70
1794430870 70
1794430875 68
1794430880 68
1794430885 68
1794430890 73
```
</details>

---

