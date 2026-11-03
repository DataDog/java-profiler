---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 07:41:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 27-43 cores)</summary>

```
1793709437 43
1793709442 43
1793709447 43
1793709452 43
1793709457 43
1793709462 43
1793709467 31
1793709472 31
1793709477 27
1793709483 27
1793709488 27
1793709493 27
1793709498 27
1793709503 27
1793709508 27
1793709513 27
1793709518 29
1793709523 29
1793709528 27
1793709533 27
```
</details>

---

