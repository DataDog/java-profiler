---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 04:54:00 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 7 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 4 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1794390401 54
1794390406 54
1794390411 59
1794390416 59
1794390421 59
1794390426 59
1794390431 59
1794390436 59
1794390441 59
1794390446 59
1794390452 59
1794390457 59
1794390462 59
1794390467 59
1794390472 59
1794390477 59
1794390482 59
1794390487 59
1794390492 59
1794390497 59
```
</details>

---

