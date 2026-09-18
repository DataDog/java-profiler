---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 03:32:07 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 41-61 cores)</summary>

```
1789716431 61
1789716436 61
1789716441 61
1789716446 61
1789716451 61
1789716456 61
1789716461 61
1789716466 61
1789716471 61
1789716476 61
1789716481 41
1789716486 41
1789716491 41
1789716496 41
1789716501 41
1789716506 41
1789716511 41
1789716516 41
1789716521 41
1789716526 41
```
</details>

---

