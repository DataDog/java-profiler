---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 08:41:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (4 unique values: 41-51 cores)</summary>

```
1793799392 41
1793799397 41
1793799402 41
1793799407 41
1793799412 41
1793799417 46
1793799422 46
1793799427 46
1793799432 46
1793799437 46
1793799442 46
1793799447 46
1793799452 46
1793799457 51
1793799462 51
1793799467 49
1793799472 49
1793799477 49
1793799482 49
1793799487 49
```
</details>

---

