---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 05:59:56 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 861 |
| Sample Rate | 14.35/sec |
| Health Score | 897% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 25-27 cores)</summary>

```
1790070794 25
1790070799 25
1790070804 25
1790070809 25
1790070814 25
1790070819 25
1790070824 25
1790070829 25
1790070834 25
1790070839 25
1790070844 25
1790070849 25
1790070854 25
1790070859 25
1790070864 25
1790070869 25
1790070874 27
1790070879 27
1790070884 27
1790070889 27
```
</details>

---

