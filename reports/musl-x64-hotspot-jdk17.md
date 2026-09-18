---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 03:34:35 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1789716453 79
1789716458 79
1789716463 79
1789716468 79
1789716473 79
1789716478 79
1789716483 79
1789716488 79
1789716493 79
1789716498 79
1789716503 79
1789716508 77
1789716513 77
1789716518 77
1789716523 77
1789716528 77
1789716533 77
1789716538 77
1789716543 77
1789716548 77
```
</details>

---

