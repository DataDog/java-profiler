---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-06 08:59:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 13 |
| Allocations | 95 |

<details>
<summary>CPU Timeline (3 unique values: 18-23 cores)</summary>

```
1786020940 23
1786020945 18
1786020950 18
1786020955 18
1786020960 18
1786020965 18
1786020970 18
1786020975 18
1786020980 18
1786020985 23
1786020990 23
1786020995 23
1786021000 23
1786021005 23
1786021010 23
1786021015 23
1786021020 23
1786021025 23
1786021030 23
1786021035 23
```
</details>

---

