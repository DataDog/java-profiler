---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 19:07:45 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1793836917 92
1793836922 92
1793836927 92
1793836932 92
1793836937 92
1793836942 92
1793836947 92
1793836952 92
1793836957 92
1793836962 92
1793836967 92
1793836972 92
1793836977 94
1793836982 94
1793836987 94
1793836992 94
1793836997 94
1793837002 94
1793837007 92
1793837012 92
```
</details>

---

