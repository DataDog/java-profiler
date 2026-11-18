---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:34:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 7 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (4 unique values: 43-64 cores)</summary>

```
1795015829 48
1795015834 48
1795015839 48
1795015844 48
1795015849 48
1795015854 48
1795015859 48
1795015864 48
1795015869 48
1795015874 48
1795015879 48
1795015884 48
1795015889 48
1795015894 43
1795015899 43
1795015904 59
1795015909 59
1795015914 59
1795015919 59
1795015924 59
```
</details>

---

