---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 03:38:51 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 920 |
| Sample Rate | 15.33/sec |
| Health Score | 958% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (4 unique values: 34-44 cores)</summary>

```
1789716413 40
1789716418 40
1789716423 40
1789716428 42
1789716433 42
1789716438 42
1789716443 42
1789716448 40
1789716453 40
1789716458 40
1789716463 40
1789716468 42
1789716473 42
1789716478 44
1789716483 44
1789716488 44
1789716493 34
1789716498 34
1789716503 34
1789716508 34
```
</details>

---

