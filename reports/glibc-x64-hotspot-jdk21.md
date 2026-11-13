---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 08:55:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1794577839 86
1794577844 86
1794577849 86
1794577854 86
1794577859 88
1794577864 88
1794577869 88
1794577874 88
1794577879 88
1794577884 88
1794577889 88
1794577894 88
1794577899 88
1794577904 88
1794577909 88
1794577914 86
1794577919 86
1794577924 86
1794577929 86
1794577934 86
```
</details>

---

