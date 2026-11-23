---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:28:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 10 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 12 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 27-36 cores)</summary>

```
1795429448 28
1795429453 28
1795429458 28
1795429463 28
1795429468 28
1795429473 28
1795429478 28
1795429483 28
1795429488 28
1795429493 28
1795429498 28
1795429503 27
1795429508 27
1795429513 27
1795429518 27
1795429523 27
1795429528 27
1795429533 27
1795429538 32
1795429543 32
```
</details>

---

