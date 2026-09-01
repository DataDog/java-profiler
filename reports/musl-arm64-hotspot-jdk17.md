---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-01 12:13:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 14 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788278932 64
1788278937 64
1788278942 64
1788278947 64
1788278952 64
1788278957 64
1788278962 64
1788278967 64
1788278972 64
1788278978 64
1788278983 64
1788278988 64
1788278993 64
1788278998 64
1788279003 64
1788279008 64
1788279013 64
1788279018 64
1788279023 64
1788279028 64
```
</details>

---

