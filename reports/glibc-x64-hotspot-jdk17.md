---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 16:06:31 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (4 unique values: 46-52 cores)</summary>

```
1792612854 46
1792612859 46
1792612864 46
1792612869 48
1792612874 48
1792612879 48
1792612884 48
1792612889 48
1792612894 50
1792612899 50
1792612904 50
1792612909 50
1792612914 50
1792612919 50
1792612924 50
1792612929 50
1792612934 50
1792612939 50
1792612944 50
1792612949 50
```
</details>

---

