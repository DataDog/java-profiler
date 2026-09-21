---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 05:26:29 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 61-96 cores)</summary>

```
1789982391 96
1789982396 61
1789982401 61
1789982406 61
1789982411 61
1789982416 61
1789982421 61
1789982426 61
1789982431 61
1789982436 61
1789982441 61
1789982446 61
1789982451 61
1789982456 61
1789982461 61
1789982466 61
1789982471 61
1789982476 61
1789982481 61
1789982486 61
```
</details>

---

