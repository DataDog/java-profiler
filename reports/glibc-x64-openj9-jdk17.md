---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-07 08:27:33 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786105468 48
1786105474 48
1786105479 48
1786105484 48
1786105489 48
1786105494 48
1786105499 48
1786105504 48
1786105509 48
1786105514 48
1786105519 48
1786105524 48
1786105529 48
1786105534 48
1786105539 48
1786105544 48
1786105549 48
1786105554 48
1786105559 48
1786105564 43
```
</details>

---

