---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-04 14:55:25 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 52-64 cores)</summary>

```
1788547897 62
1788547902 62
1788547907 62
1788547912 64
1788547917 64
1788547922 64
1788547927 64
1788547932 64
1788547937 64
1788547942 64
1788547947 62
1788547952 62
1788547957 60
1788547962 60
1788547967 58
1788547972 58
1788547977 58
1788547982 58
1788547987 58
1788547992 54
```
</details>

---

