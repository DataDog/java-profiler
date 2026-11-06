---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 16:43:55 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 73-81 cores)</summary>

```
1794001088 81
1794001093 81
1794001098 81
1794001103 81
1794001108 81
1794001113 81
1794001118 81
1794001123 81
1794001128 81
1794001133 81
1794001138 81
1794001143 81
1794001148 81
1794001153 81
1794001158 81
1794001163 81
1794001168 81
1794001173 75
1794001178 75
1794001183 75
```
</details>

---

