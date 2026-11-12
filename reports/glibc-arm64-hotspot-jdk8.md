---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 10:09:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794495942 34
1794495947 39
1794495952 39
1794495957 39
1794495962 39
1794495967 39
1794495972 39
1794495977 39
1794495982 39
1794495987 39
1794495992 39
1794495997 39
1794496002 39
1794496007 39
1794496012 39
1794496017 39
1794496022 39
1794496027 39
1794496032 39
1794496037 39
```
</details>

---

