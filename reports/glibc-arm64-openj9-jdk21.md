---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 17:08:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 40-43 cores)</summary>

```
1794348306 40
1794348311 40
1794348316 40
1794348321 40
1794348326 41
1794348331 41
1794348336 41
1794348341 41
1794348346 41
1794348351 41
1794348356 41
1794348361 41
1794348366 41
1794348371 41
1794348376 41
1794348381 41
1794348386 43
1794348391 43
1794348396 43
1794348401 43
```
</details>

---

