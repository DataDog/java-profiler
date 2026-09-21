---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 03:29:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 21-32 cores)</summary>

```
1789975481 21
1789975486 21
1789975491 21
1789975496 21
1789975501 21
1789975506 21
1789975511 21
1789975516 21
1789975521 21
1789975526 21
1789975531 21
1789975536 21
1789975541 21
1789975546 21
1789975551 21
1789975556 21
1789975561 21
1789975566 21
1789975571 21
1789975576 21
```
</details>

---

