---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:06:30 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1794430855 45
1794430860 45
1794430865 45
1794430870 45
1794430875 45
1794430880 45
1794430885 45
1794430890 45
1794430895 45
1794430900 45
1794430905 45
1794430910 45
1794430915 64
1794430920 64
1794430925 44
1794430930 44
1794430935 44
1794430940 44
1794430945 44
1794430950 42
```
</details>

---

