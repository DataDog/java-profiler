---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 06:16:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 48-75 cores)</summary>

```
1792145518 75
1792145523 73
1792145528 73
1792145533 73
1792145538 73
1792145543 73
1792145548 73
1792145553 73
1792145558 73
1792145563 73
1792145568 73
1792145573 73
1792145578 73
1792145583 73
1792145588 73
1792145593 48
1792145598 48
1792145603 48
1792145608 48
1792145613 48
```
</details>

---

