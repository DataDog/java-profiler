---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-11 16:04:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 44-53 cores)</summary>

```
1794430800 53
1794430805 53
1794430810 53
1794430815 53
1794430820 53
1794430825 53
1794430830 53
1794430835 53
1794430840 53
1794430845 53
1794430850 53
1794430855 53
1794430860 53
1794430865 53
1794430870 53
1794430875 53
1794430880 53
1794430885 44
1794430890 44
1794430895 44
```
</details>

---

