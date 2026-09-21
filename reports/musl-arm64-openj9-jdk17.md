---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 07:21:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 12 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1789989433 16
1789989438 16
1789989443 16
1789989448 16
1789989453 16
1789989458 16
1789989463 16
1789989468 16
1789989473 16
1789989478 16
1789989483 16
1789989488 16
1789989493 16
1789989498 16
1789989503 16
1789989508 16
1789989513 16
1789989518 16
1789989523 16
1789989528 16
```
</details>

---

