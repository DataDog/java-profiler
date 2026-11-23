---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 00:00:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1795409849 54
1795409854 54
1795409859 54
1795409864 54
1795409869 54
1795409874 54
1795409879 54
1795409884 54
1795409889 54
1795409894 54
1795409899 59
1795409904 59
1795409909 59
1795409914 59
1795409919 59
1795409924 59
1795409929 59
1795409934 59
1795409939 59
1795409944 59
```
</details>

---

