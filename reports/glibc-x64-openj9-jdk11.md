---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 18:56:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794268278 96
1794268283 96
1794268288 94
1794268293 94
1794268298 94
1794268303 94
1794268308 94
1794268313 94
1794268318 96
1794268323 96
1794268328 96
1794268333 94
1794268338 94
1794268343 94
1794268348 94
1794268353 94
1794268358 94
1794268363 94
1794268368 94
1794268373 94
```
</details>

---

