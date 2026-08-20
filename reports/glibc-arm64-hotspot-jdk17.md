---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 09:32:06 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1787232433 43
1787232438 38
1787232443 38
1787232448 38
1787232453 38
1787232458 38
1787232463 38
1787232468 38
1787232473 38
1787232478 38
1787232483 38
1787232488 38
1787232493 38
1787232498 38
1787232503 38
1787232508 48
1787232513 48
1787232518 48
1787232523 48
1787232528 48
```
</details>

---

