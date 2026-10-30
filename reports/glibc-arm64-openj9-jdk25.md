---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 09:50:45 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 34-41 cores)</summary>

```
1793368029 36
1793368034 36
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
1793368099 41
1793368104 41
1793368109 39
1793368114 39
1793368119 39
1793368124 34
```
</details>

---

