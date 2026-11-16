---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 12:37:26 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 85-89 cores)</summary>

```
1794850056 85
1794850061 85
1794850066 85
1794850071 85
1794850076 85
1794850081 87
1794850086 87
1794850091 89
1794850096 89
1794850101 89
1794850106 89
1794850111 89
1794850116 89
1794850121 89
1794850126 89
1794850131 89
1794850136 89
1794850141 89
1794850146 89
1794850151 89
```
</details>

---

