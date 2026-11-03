---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 21:59:30 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 60-96 cores)</summary>

```
1793674443 96
1793674448 96
1793674453 96
1793674458 96
1793674463 96
1793674468 96
1793674473 96
1793674478 96
1793674483 96
1793674488 96
1793674493 96
1793674498 96
1793674503 96
1793674508 96
1793674513 96
1793674518 60
1793674523 60
1793674528 60
1793674533 60
1793674538 60
```
</details>

---

