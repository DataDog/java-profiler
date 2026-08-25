---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-25 15:07:39 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (5 unique values: 76-88 cores)</summary>

```
1787684451 78
1787684456 78
1787684461 78
1787684466 78
1787684471 78
1787684476 76
1787684481 76
1787684486 76
1787684491 84
1787684496 84
1787684501 86
1787684506 86
1787684511 86
1787684516 88
1787684521 88
1787684526 88
1787684531 88
1787684536 88
1787684541 88
1787684546 88
```
</details>

---

