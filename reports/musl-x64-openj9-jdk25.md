---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 19:07:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 9 |
| Allocations | 443 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 35-76 cores)</summary>

```
1793836940 35
1793836945 35
1793836950 35
1793836955 35
1793836960 35
1793836965 35
1793836970 35
1793836975 35
1793836980 35
1793836985 35
1793836990 35
1793836995 35
1793837000 35
1793837005 35
1793837010 35
1793837015 35
1793837020 35
1793837025 68
1793837030 68
1793837035 68
```
</details>

---

