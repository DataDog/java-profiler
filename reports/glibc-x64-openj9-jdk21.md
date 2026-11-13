---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:19:16 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 82-86 cores)</summary>

```
1794582909 82
1794582914 82
1794582919 82
1794582924 82
1794582929 82
1794582934 82
1794582939 86
1794582944 86
1794582949 86
1794582954 86
1794582959 86
1794582964 86
1794582969 86
1794582974 86
1794582979 86
1794582984 86
1794582989 86
1794582994 86
1794582999 86
1794583004 86
```
</details>

---

