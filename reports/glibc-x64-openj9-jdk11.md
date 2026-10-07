---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 12:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 811 |
| Sample Rate | 13.52/sec |
| Health Score | 845% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1791391372 86
1791391377 86
1791391382 86
1791391387 86
1791391392 86
1791391397 86
1791391402 86
1791391407 86
1791391412 86
1791391417 86
1791391422 84
1791391427 84
1791391432 84
1791391437 84
1791391442 84
1791391447 84
1791391452 84
1791391457 84
1791391462 82
1791391467 82
```
</details>

---

