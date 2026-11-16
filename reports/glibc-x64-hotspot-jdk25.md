---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:37:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 8 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 20-32 cores)</summary>

```
1794850073 32
1794850078 32
1794850083 32
1794850088 32
1794850093 32
1794850098 32
1794850103 32
1794850108 32
1794850113 32
1794850118 32
1794850123 20
1794850128 20
1794850133 20
1794850138 20
1794850143 20
1794850148 20
1794850153 20
1794850158 20
1794850163 20
1794850168 20
```
</details>

---

