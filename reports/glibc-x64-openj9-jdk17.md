---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 11:33:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 46-54 cores)</summary>

```
1794932966 46
1794932971 46
1794932976 46
1794932981 46
1794932986 46
1794932991 46
1794932996 46
1794933001 46
1794933006 46
1794933011 46
1794933016 46
1794933021 46
1794933026 46
1794933031 46
1794933036 46
1794933041 46
1794933046 46
1794933051 46
1794933056 54
1794933061 54
```
</details>

---

