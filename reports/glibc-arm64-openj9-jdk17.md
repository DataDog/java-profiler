---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-15 18:26:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 328 |
| Sample Rate | 5.47/sec |
| Health Score | 342% |
| Threads | 9 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 14 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1794784915 46
1794784920 46
1794784925 46
1794784930 46
1794784935 46
1794784940 46
1794784945 46
1794784950 46
1794784955 46
1794784960 46
1794784965 44
1794784970 44
1794784975 44
1794784980 44
1794784985 44
1794784990 44
1794784995 44
1794785000 44
1794785005 46
1794785010 46
```
</details>

---

