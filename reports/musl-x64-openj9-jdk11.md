---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:54:35 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 10 |
| Allocations | 558 |

<details>
<summary>CPU Timeline (3 unique values: 79-87 cores)</summary>

```
1791470910 79
1791470915 79
1791470920 79
1791470925 79
1791470930 79
1791470935 79
1791470940 79
1791470945 79
1791470950 79
1791470955 79
1791470960 79
1791470965 79
1791470970 79
1791470975 79
1791470980 81
1791470985 81
1791470990 81
1791470995 81
1791471000 81
1791471005 81
```
</details>

---

