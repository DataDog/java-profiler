---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-01 05:55:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (5 unique values: 25-49 cores)</summary>

```
1793530256 30
1793530261 30
1793530266 25
1793530271 25
1793530276 27
1793530281 27
1793530286 27
1793530291 27
1793530296 27
1793530301 27
1793530306 32
1793530311 32
1793530316 49
1793530321 49
1793530326 49
1793530331 49
1793530336 49
1793530341 49
1793530346 49
1793530351 49
```
</details>

---

