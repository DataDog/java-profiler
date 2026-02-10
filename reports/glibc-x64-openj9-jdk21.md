---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-10 17:36:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 13 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 55-67 cores)</summary>

```
1770762499 67
1770762504 67
1770762509 57
1770762514 57
1770762519 57
1770762524 57
1770762529 57
1770762534 57
1770762539 57
1770762544 57
1770762549 57
1770762554 57
1770762559 57
1770762564 57
1770762569 59
1770762574 59
1770762579 59
1770762584 59
1770762589 59
1770762594 55
```
</details>

---

