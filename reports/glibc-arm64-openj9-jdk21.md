---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 05:47:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793788959 48
1793788964 48
1793788969 48
1793788974 48
1793788979 48
1793788984 48
1793788989 48
1793788994 48
1793788999 48
1793789004 48
1793789009 48
1793789014 48
1793789019 48
1793789024 48
1793789029 48
1793789034 48
1793789039 48
1793789044 48
1793789049 48
1793789054 48
```
</details>

---

