---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 16:04:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 63-86 cores)</summary>

```
1794430815 84
1794430820 84
1794430825 84
1794430830 84
1794430835 86
1794430840 86
1794430845 86
1794430850 86
1794430855 76
1794430860 76
1794430865 76
1794430870 76
1794430875 76
1794430880 76
1794430885 76
1794430890 76
1794430895 83
1794430900 83
1794430905 83
1794430910 83
```
</details>

---

