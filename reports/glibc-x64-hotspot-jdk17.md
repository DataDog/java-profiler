---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 12:37:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 77-83 cores)</summary>

```
1794850051 82
1794850056 82
1794850061 82
1794850066 82
1794850071 77
1794850076 77
1794850081 77
1794850086 77
1794850091 77
1794850096 77
1794850101 77
1794850106 77
1794850111 77
1794850116 77
1794850121 77
1794850126 77
1794850131 77
1794850136 79
1794850141 79
1794850146 77
```
</details>

---

