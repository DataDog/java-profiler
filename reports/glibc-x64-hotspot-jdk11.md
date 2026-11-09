---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 15:36:43 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 51-61 cores)</summary>

```
1794256313 56
1794256318 56
1794256323 53
1794256328 53
1794256333 53
1794256338 53
1794256343 53
1794256348 53
1794256353 53
1794256358 53
1794256363 53
1794256368 53
1794256373 53
1794256378 51
1794256383 51
1794256388 61
1794256393 61
1794256398 61
1794256403 61
1794256408 51
```
</details>

---

