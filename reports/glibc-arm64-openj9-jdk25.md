---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-26 06:57:15 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1793011991 38
1793011996 38
1793012001 38
1793012006 38
1793012011 38
1793012016 38
1793012021 43
1793012026 43
1793012031 43
1793012036 43
1793012041 43
1793012046 43
1793012051 43
1793012056 43
1793012061 43
1793012066 43
1793012071 43
1793012076 43
1793012081 43
1793012086 43
```
</details>

---

