---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-09 07:12:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1791544033 27
1791544038 27
1791544043 27
1791544048 27
1791544053 27
1791544058 27
1791544063 27
1791544068 27
1791544073 27
1791544078 27
1791544083 27
1791544088 27
1791544093 27
1791544098 27
1791544103 27
1791544108 27
1791544113 32
1791544118 32
1791544123 32
1791544128 32
```
</details>

---

