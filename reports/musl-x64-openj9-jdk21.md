---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:32:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (5 unique values: 34-94 cores)</summary>

```
1789716428 94
1789716433 94
1789716438 74
1789716443 74
1789716448 76
1789716453 76
1789716458 76
1789716463 76
1789716468 76
1789716473 76
1789716478 76
1789716483 76
1789716488 36
1789716493 36
1789716498 34
1789716503 34
1789716508 34
1789716513 34
1789716518 34
1789716523 34
```
</details>

---

