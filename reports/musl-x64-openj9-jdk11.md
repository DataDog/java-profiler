---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:19:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 878 |
| Sample Rate | 14.63/sec |
| Health Score | 914% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 68-77 cores)</summary>

```
1794582899 77
1794582904 77
1794582909 75
1794582914 75
1794582919 75
1794582924 70
1794582929 70
1794582934 70
1794582939 70
1794582944 68
1794582949 68
1794582954 68
1794582959 68
1794582964 68
1794582969 68
1794582974 68
1794582979 68
1794582984 68
1794582989 68
1794582994 68
```
</details>

---

