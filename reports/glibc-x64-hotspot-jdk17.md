---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 06:42:59 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1031 |
| Sample Rate | 17.18/sec |
| Health Score | 1074% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 51-65 cores)</summary>

```
1778582344 65
1778582349 65
1778582354 51
1778582359 51
1778582364 53
1778582369 53
1778582374 53
1778582379 53
1778582384 53
1778582389 56
1778582394 56
1778582399 56
1778582404 56
1778582409 56
1778582414 56
1778582419 56
1778582424 56
1778582429 56
1778582434 56
1778582439 54
```
</details>

---

