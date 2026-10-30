---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 09:50:44 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 34-53 cores)</summary>

```
1793368004 53
1793368009 53
1793368014 53
1793368019 53
1793368024 53
1793368029 41
1793368034 41
1793368039 36
1793368044 36
1793368049 36
1793368054 36
1793368059 36
1793368064 36
1793368069 36
1793368074 36
1793368079 36
1793368084 36
1793368089 41
1793368094 41
1793368100 41
```
</details>

---

