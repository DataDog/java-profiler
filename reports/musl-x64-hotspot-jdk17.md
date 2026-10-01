---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-10-01 11:00:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 85-85 cores)</summary>

```
1790866513 85
1790866518 85
1790866523 85
1790866528 85
1790866533 85
1790866538 85
1790866543 85
1790866548 85
1790866553 85
1790866558 85
1790866564 85
1790866569 85
1790866574 85
1790866579 85
1790866584 85
1790866589 85
1790866594 85
1790866599 85
1790866604 85
1790866609 85
```
</details>

---

