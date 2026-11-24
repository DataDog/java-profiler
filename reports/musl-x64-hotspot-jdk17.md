---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:14:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1795529333 80
1795529338 80
1795529343 80
1795529348 80
1795529353 82
1795529358 82
1795529363 84
1795529368 84
1795529373 84
1795529378 84
1795529383 84
1795529388 84
1795529393 84
1795529398 84
1795529403 84
1795529408 84
1795529413 84
1795529418 84
1795529423 82
1795529428 82
```
</details>

---

