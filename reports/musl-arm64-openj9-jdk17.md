---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 05:27:14 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1787390453 48
1787390458 48
1787390463 48
1787390468 47
1787390473 47
1787390478 47
1787390483 47
1787390488 47
1787390493 47
1787390498 47
1787390503 47
1787390509 47
1787390514 47
1787390519 47
1787390524 47
1787390529 48
1787390534 48
1787390539 48
1787390544 48
1787390549 48
```
</details>

---

