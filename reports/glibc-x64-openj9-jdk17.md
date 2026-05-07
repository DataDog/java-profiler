---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 12:39:47 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 65-82 cores)</summary>

```
1778171764 65
1778171769 65
1778171774 80
1778171779 80
1778171784 80
1778171789 82
1778171794 82
1778171799 82
1778171804 82
1778171809 82
1778171814 82
1778171819 82
1778171824 82
1778171829 82
1778171834 82
1778171839 82
1778171844 82
1778171849 82
1778171854 82
1778171859 82
```
</details>

---

