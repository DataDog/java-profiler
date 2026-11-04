---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 00:08:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1793768531 17
1793768536 17
1793768541 17
1793768546 17
1793768551 17
1793768556 17
1793768561 17
1793768566 15
1793768571 15
1793768576 15
1793768581 15
1793768586 15
1793768591 15
1793768596 15
1793768601 15
1793768607 15
1793768612 15
1793768617 15
1793768622 15
1793768627 15
```
</details>

---

