---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 05:46:57 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 9 |
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
<summary>CPU Timeline (4 unique values: 51-69 cores)</summary>

```
1795084948 59
1795084953 59
1795084958 59
1795084964 59
1795084969 59
1795084974 59
1795084979 59
1795084984 64
1795084989 64
1795084994 64
1795084999 64
1795085004 64
1795085009 64
1795085014 64
1795085019 64
1795085024 64
1795085029 69
1795085034 69
1795085039 69
1795085044 69
```
</details>

---

