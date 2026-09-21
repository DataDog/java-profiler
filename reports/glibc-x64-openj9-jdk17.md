---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 05:26:30 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 56-96 cores)</summary>

```
1789982386 56
1789982391 79
1789982396 79
1789982401 79
1789982406 79
1789982411 79
1789982416 79
1789982421 79
1789982426 79
1789982431 79
1789982436 79
1789982441 79
1789982446 79
1789982451 79
1789982456 79
1789982461 96
1789982466 96
1789982471 96
1789982476 96
1789982481 96
```
</details>

---

