---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-12 12:07:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 82-96 cores)</summary>

```
1794502903 82
1794502908 82
1794502913 82
1794502918 82
1794502923 84
1794502928 84
1794502933 89
1794502938 89
1794502943 89
1794502948 96
1794502953 96
1794502958 96
1794502963 96
1794502968 96
1794502973 96
1794502978 96
1794502983 96
1794502988 96
1794502993 96
1794502998 96
```
</details>

---

