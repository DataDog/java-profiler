---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-07 10:54:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 81-85 cores)</summary>

```
1778165467 81
1778165473 81
1778165478 81
1778165483 83
1778165488 83
1778165493 83
1778165498 83
1778165503 83
1778165508 83
1778165513 85
1778165518 85
1778165523 83
1778165528 83
1778165533 83
1778165538 85
1778165543 85
1778165548 85
1778165553 85
1778165558 85
1778165563 85
```
</details>

---

