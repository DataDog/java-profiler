---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:45:07 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778582454 59
1778582459 59
1778582464 59
1778582469 59
1778582474 59
1778582479 59
1778582484 59
1778582489 64
1778582494 64
1778582499 64
1778582504 64
1778582509 64
1778582514 64
1778582519 64
1778582524 64
1778582529 64
1778582534 64
1778582539 64
1778582544 64
1778582549 64
```
</details>

---

