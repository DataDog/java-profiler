---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 05:50:43 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 85-89 cores)</summary>

```
1786095968 89
1786095973 89
1786095978 89
1786095983 85
1786095988 85
1786095993 85
1786095998 85
1786096003 87
1786096008 87
1786096013 87
1786096018 87
1786096023 87
1786096028 87
1786096033 87
1786096038 87
1786096043 87
1786096048 87
1786096053 87
1786096058 89
1786096063 89
```
</details>

---

