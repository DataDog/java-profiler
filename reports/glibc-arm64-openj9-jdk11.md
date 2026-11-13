---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 12:19:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 10 |
| Allocations | 185 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1794590084 51
1794590089 51
1794590094 51
1794590099 51
1794590104 51
1794590109 51
1794590114 51
1794590119 51
1794590124 51
1794590129 51
1794590134 51
1794590139 51
1794590144 51
1794590149 51
1794590154 51
1794590159 51
1794590164 51
1794590169 51
1794590174 51
1794590179 51
```
</details>

---

