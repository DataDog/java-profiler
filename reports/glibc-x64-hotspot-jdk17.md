---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 09:32:07 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 86-96 cores)</summary>

```
1787232433 88
1787232438 88
1787232443 88
1787232448 88
1787232453 88
1787232458 88
1787232463 88
1787232468 88
1787232473 88
1787232478 88
1787232483 86
1787232488 86
1787232493 86
1787232498 94
1787232503 94
1787232508 94
1787232513 94
1787232518 94
1787232523 94
1787232528 96
```
</details>

---

