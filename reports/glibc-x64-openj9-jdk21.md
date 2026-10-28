---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 09:32:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1793194059 63
1793194064 63
1793194069 63
1793194074 63
1793194079 63
1793194084 63
1793194089 63
1793194094 63
1793194099 63
1793194104 63
1793194109 63
1793194114 63
1793194119 63
1793194124 63
1793194129 61
1793194134 61
1793194139 61
1793194144 61
1793194149 61
1793194154 63
```
</details>

---

