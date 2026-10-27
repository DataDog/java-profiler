---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 16:51:55 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793133959 51
1793133964 51
1793133969 51
1793133974 51
1793133979 51
1793133984 51
1793133989 51
1793133994 51
1793133999 51
1793134004 51
1793134009 51
1793134014 51
1793134019 51
1793134024 51
1793134029 51
1793134034 51
1793134039 51
1793134044 51
1793134049 51
1793134054 46
```
</details>

---

