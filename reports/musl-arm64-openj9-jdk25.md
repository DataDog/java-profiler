---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-03 15:15:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 10 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1788462453 48
1788462458 48
1788462463 48
1788462468 48
1788462473 48
1788462478 28
1788462483 28
1788462488 28
1788462493 28
1788462498 28
1788462503 28
1788462508 28
1788462513 28
1788462518 28
1788462523 28
1788462528 28
1788462533 28
1788462538 28
1788462543 28
1788462548 28
```
</details>

---

