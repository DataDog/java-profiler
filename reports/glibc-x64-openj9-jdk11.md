---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 08:27:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1786019019 47
1786019024 47
1786019029 47
1786019034 47
1786019039 47
1786019044 47
1786019049 47
1786019054 47
1786019059 47
1786019064 49
1786019069 49
1786019074 49
1786019079 49
1786019084 49
1786019089 49
1786019094 49
1786019099 49
1786019104 49
1786019109 49
1786019114 49
```
</details>

---

