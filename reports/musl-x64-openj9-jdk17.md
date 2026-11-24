---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:13:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 988 |
| Sample Rate | 16.47/sec |
| Health Score | 1029% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1795529346 92
1795529351 92
1795529356 92
1795529361 92
1795529366 90
1795529371 90
1795529376 90
1795529381 90
1795529386 90
1795529391 90
1795529396 90
1795529401 90
1795529406 90
1795529411 90
1795529416 90
1795529421 90
1795529426 90
1795529431 90
1795529436 90
1795529441 90
```
</details>

---

