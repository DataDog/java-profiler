---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 08:55:21 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 40-48 cores)</summary>

```
1794577838 45
1794577843 45
1794577848 48
1794577853 48
1794577859 43
1794577864 43
1794577869 43
1794577874 43
1794577879 43
1794577884 43
1794577889 43
1794577894 43
1794577899 40
1794577904 40
1794577909 40
1794577914 40
1794577919 40
1794577924 40
1794577929 40
1794577934 40
```
</details>

---

