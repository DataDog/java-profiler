---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 11:23:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791299914 30
1791299919 30
1791299924 30
1791299929 30
1791299934 30
1791299939 30
1791299944 32
1791299949 32
1791299954 32
1791299959 32
1791299964 32
1791299969 32
1791299974 32
1791299979 32
1791299984 30
1791299989 30
1791299994 30
1791299999 30
1791300004 30
1791300009 30
```
</details>

---

