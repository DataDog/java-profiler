---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 13:25:45 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1787246454 81
1787246459 81
1787246464 81
1787246469 81
1787246474 81
1787246479 81
1787246484 81
1787246489 81
1787246494 81
1787246499 81
1787246504 81
1787246509 81
1787246514 81
1787246519 81
1787246524 81
1787246529 81
1787246534 79
1787246539 79
1787246544 79
1787246549 79
```
</details>

---

