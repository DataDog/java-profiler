---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-01 10:51:20 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1790865860 30
1790865865 30
1790865870 30
1790865875 30
1790865880 30
1790865885 30
1790865890 30
1790865895 30
1790865900 30
1790865905 32
1790865910 32
1790865915 32
1790865920 32
1790865925 29
1790865930 29
1790865935 29
1790865940 29
1790865945 29
1790865950 29
1790865955 27
```
</details>

---

