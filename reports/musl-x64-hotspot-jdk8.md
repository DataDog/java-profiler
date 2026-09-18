---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 03:34:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1789716422 96
1789716427 96
1789716432 96
1789716437 96
1789716442 96
1789716447 96
1789716452 96
1789716458 96
1789716463 96
1789716468 96
1789716473 96
1789716478 96
1789716483 96
1789716488 76
1789716493 76
1789716498 76
1789716503 76
1789716508 76
1789716513 76
1789716518 76
```
</details>

---

