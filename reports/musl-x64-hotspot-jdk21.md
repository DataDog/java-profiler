---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:41:09 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 46-77 cores)</summary>

```
1793799351 46
1793799356 48
1793799361 48
1793799366 48
1793799371 48
1793799376 48
1793799381 48
1793799386 48
1793799391 48
1793799396 50
1793799401 50
1793799406 50
1793799411 50
1793799416 55
1793799421 55
1793799426 77
1793799431 77
1793799436 77
1793799441 77
1793799446 77
```
</details>

---

