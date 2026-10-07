---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 12:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 77-86 cores)</summary>

```
1791391397 84
1791391402 84
1791391407 84
1791391412 84
1791391417 84
1791391422 84
1791391427 84
1791391432 84
1791391437 84
1791391442 84
1791391447 84
1791391452 86
1791391457 86
1791391462 86
1791391467 86
1791391472 86
1791391477 86
1791391482 86
1791391487 86
1791391492 86
```
</details>

---

