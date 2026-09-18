---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:38:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789716423 48
1789716428 48
1789716433 48
1789716438 48
1789716443 48
1789716448 48
1789716453 43
1789716458 43
1789716463 43
1789716468 43
1789716473 43
1789716478 43
1789716483 43
1789716488 43
1789716493 43
1789716498 43
1789716503 43
1789716508 43
1789716513 43
1789716518 43
```
</details>

---

