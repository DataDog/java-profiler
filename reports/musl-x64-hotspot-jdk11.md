---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:32:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1051 |
| Sample Rate | 17.52/sec |
| Health Score | 1095% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1789716418 91
1789716423 91
1789716428 91
1789716433 91
1789716438 91
1789716443 91
1789716448 91
1789716453 91
1789716458 91
1789716463 91
1789716468 91
1789716473 91
1789716478 91
1789716483 91
1789716488 91
1789716493 89
1789716498 89
1789716503 89
1789716508 89
1789716513 89
```
</details>

---

