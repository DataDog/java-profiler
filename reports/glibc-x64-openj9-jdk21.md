---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:45:49 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 57-79 cores)</summary>

```
1786527658 65
1786527663 65
1786527668 65
1786527673 65
1786527678 57
1786527683 57
1786527688 57
1786527693 57
1786527698 57
1786527703 57
1786527708 57
1786527713 79
1786527718 79
1786527723 77
1786527728 77
1786527733 77
1786527738 77
1786527743 77
1786527748 77
1786527753 77
```
</details>

---

