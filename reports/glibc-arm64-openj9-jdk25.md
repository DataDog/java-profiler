---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 16:51:55 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 11 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 49-53 cores)</summary>

```
1793133958 49
1793133963 49
1793133968 49
1793133973 49
1793133978 49
1793133983 49
1793133988 49
1793133993 49
1793133998 49
1793134003 49
1793134008 49
1793134013 49
1793134018 49
1793134023 49
1793134028 53
1793134033 53
1793134038 53
1793134043 53
1793134048 53
1793134053 53
```
</details>

---

