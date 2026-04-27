---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-27 16:29:16 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 61-80 cores)</summary>

```
1777321170 78
1777321175 75
1777321180 75
1777321185 75
1777321190 75
1777321195 75
1777321200 80
1777321205 80
1777321210 80
1777321215 80
1777321220 80
1777321225 80
1777321230 80
1777321235 80
1777321240 80
1777321245 80
1777321250 61
1777321255 61
1777321260 61
1777321265 61
```
</details>

---

