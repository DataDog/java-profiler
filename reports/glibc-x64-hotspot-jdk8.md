---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-17 14:55:32 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 56-77 cores)</summary>

```
1794944977 56
1794944982 56
1794944987 56
1794944993 56
1794944998 56
1794945003 59
1794945008 59
1794945013 68
1794945018 68
1794945023 77
1794945028 77
1794945033 77
1794945038 77
1794945043 77
1794945048 73
1794945053 73
1794945058 73
1794945063 73
1794945068 73
1794945073 73
```
</details>

---

