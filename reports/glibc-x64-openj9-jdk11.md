---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 15:32:41 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 49-72 cores)</summary>

```
1793388514 49
1793388519 49
1793388524 69
1793388529 69
1793388534 72
1793388539 72
1793388544 72
1793388549 72
1793388554 72
1793388559 72
1793388564 72
1793388569 72
1793388574 72
1793388579 72
1793388584 72
1793388589 72
1793388594 72
1793388599 72
1793388604 72
1793388609 70
```
</details>

---

