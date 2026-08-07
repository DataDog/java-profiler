---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-07 05:50:47 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 19-44 cores)</summary>

```
1786095957 19
1786095962 40
1786095967 40
1786095972 40
1786095978 40
1786095983 40
1786095988 40
1786095993 40
1786095998 40
1786096003 40
1786096008 40
1786096013 40
1786096018 40
1786096023 40
1786096028 40
1786096033 40
1786096038 40
1786096043 40
1786096048 40
1786096053 44
```
</details>

---

