---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 12:39:47 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 52-71 cores)</summary>

```
1778171738 71
1778171743 71
1778171748 56
1778171753 56
1778171758 56
1778171763 56
1778171768 56
1778171773 56
1778171778 56
1778171783 56
1778171788 56
1778171793 56
1778171798 56
1778171803 56
1778171808 56
1778171813 56
1778171818 56
1778171823 56
1778171828 60
1778171833 60
```
</details>

---

