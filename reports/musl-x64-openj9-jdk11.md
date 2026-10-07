---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 12:48:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 67-69 cores)</summary>

```
1791391372 67
1791391377 67
1791391382 67
1791391387 67
1791391392 67
1791391397 67
1791391402 67
1791391407 67
1791391412 67
1791391417 67
1791391422 67
1791391427 67
1791391432 67
1791391437 67
1791391442 67
1791391447 67
1791391452 67
1791391457 69
1791391462 69
1791391467 69
```
</details>

---

