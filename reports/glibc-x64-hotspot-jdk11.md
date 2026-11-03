---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 21:59:30 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 60-81 cores)</summary>

```
1793674443 81
1793674448 79
1793674453 79
1793674458 79
1793674463 79
1793674468 79
1793674473 79
1793674478 79
1793674483 79
1793674488 81
1793674493 81
1793674498 81
1793674503 81
1793674508 81
1793674513 81
1793674518 81
1793674523 81
1793674528 81
1793674533 60
1793674538 60
```
</details>

---

