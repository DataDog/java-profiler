---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-06 09:39:29 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1770388474 32
1770388479 32
1770388484 32
1770388489 29
1770388494 29
1770388499 29
1770388504 29
1770388509 29
1770388514 29
1770388519 29
1770388524 29
1770388529 29
1770388534 29
1770388539 29
1770388544 29
1770388549 29
1770388554 29
1770388559 29
1770388564 29
1770388569 29
```
</details>

---

