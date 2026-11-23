---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 04:47:22 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (5 unique values: 59-72 cores)</summary>

```
1795426928 66
1795426933 66
1795426938 70
1795426943 70
1795426948 72
1795426953 72
1795426958 72
1795426963 66
1795426968 66
1795426973 68
1795426978 68
1795426984 68
1795426989 68
1795426994 68
1795426999 68
1795427004 68
1795427009 68
1795427014 68
1795427019 68
1795427024 59
```
</details>

---

