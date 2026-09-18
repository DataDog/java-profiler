---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 05:01:28 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (6 unique values: 61-85 cores)</summary>

```
1789721783 66
1789721788 66
1789721793 66
1789721798 66
1789721803 66
1789721808 65
1789721813 65
1789721818 65
1789721823 65
1789721828 65
1789721833 65
1789721838 65
1789721843 65
1789721848 61
1789721853 61
1789721858 61
1789721863 85
1789721868 85
1789721873 73
1789721878 73
```
</details>

---

