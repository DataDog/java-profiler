---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:37:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1794850049 83
1794850054 83
1794850059 83
1794850064 83
1794850069 83
1794850074 83
1794850079 83
1794850084 83
1794850089 83
1794850094 83
1794850099 85
1794850104 85
1794850109 85
1794850114 85
1794850119 85
1794850124 85
1794850129 85
1794850134 85
1794850139 85
1794850144 85
```
</details>

---

