---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 09:32:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 10 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1793194034 43
1793194039 43
1793194044 43
1793194049 43
1793194054 43
1793194059 43
1793194064 48
1793194069 48
1793194074 48
1793194079 48
1793194084 48
1793194089 48
1793194094 48
1793194099 47
1793194104 47
1793194109 47
1793194114 47
1793194119 47
1793194124 47
1793194129 47
```
</details>

---

