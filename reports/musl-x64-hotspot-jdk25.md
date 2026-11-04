---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 08:41:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1793799370 32
1793799375 32
1793799380 32
1793799385 32
1793799390 32
1793799395 32
1793799400 32
1793799405 23
1793799410 23
1793799415 23
1793799420 23
1793799425 23
1793799430 23
1793799435 23
1793799440 23
1793799445 23
1793799450 23
1793799455 23
1793799460 23
1793799465 23
```
</details>

---

