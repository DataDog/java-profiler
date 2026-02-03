---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 07:53:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 10 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 916 |
| Sample Rate | 15.27/sec |
| Health Score | 954% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1770122947 30
1770122952 30
1770122957 30
1770122962 30
1770122967 30
1770122972 30
1770122977 30
1770122982 30
1770122987 30
1770122992 30
1770122997 30
1770123002 28
1770123007 28
1770123012 28
1770123017 28
1770123022 28
1770123027 28
1770123032 28
1770123037 28
1770123042 30
```
</details>

---

