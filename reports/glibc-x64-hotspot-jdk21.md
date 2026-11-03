---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 21:59:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1793674463 48
1793674468 48
1793674473 48
1793674478 48
1793674483 48
1793674488 48
1793674493 51
1793674498 51
1793674503 51
1793674508 51
1793674513 51
1793674518 51
1793674523 51
1793674529 51
1793674534 51
1793674539 51
1793674544 51
1793674549 51
1793674554 51
1793674559 51
```
</details>

---

