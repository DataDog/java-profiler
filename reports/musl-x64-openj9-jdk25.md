---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-05 15:03:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 916 |
| Sample Rate | 15.27/sec |
| Health Score | 954% |
| Threads | 12 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 93-96 cores)</summary>

```
1770321458 93
1770321463 93
1770321468 93
1770321473 93
1770321478 93
1770321483 93
1770321488 93
1770321493 93
1770321498 93
1770321503 93
1770321508 93
1770321513 93
1770321518 93
1770321523 93
1770321528 93
1770321533 93
1770321538 93
1770321543 96
1770321548 96
1770321553 96
```
</details>

---

