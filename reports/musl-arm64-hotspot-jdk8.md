---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 08:55:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 344 |
| Sample Rate | 5.73/sec |
| Health Score | 358% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 22-48 cores)</summary>

```
1794577849 22
1794577854 22
1794577859 22
1794577864 22
1794577869 35
1794577874 35
1794577879 35
1794577884 35
1794577889 35
1794577894 35
1794577899 35
1794577904 35
1794577909 35
1794577914 35
1794577919 48
1794577924 48
1794577929 48
1794577934 48
1794577939 48
1794577944 48
```
</details>

---

