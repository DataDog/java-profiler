---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 11:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1793895029 92
1793895034 92
1793895039 92
1793895044 92
1793895049 94
1793895054 94
1793895059 94
1793895064 94
1793895069 94
1793895074 94
1793895079 94
1793895084 94
1793895089 94
1793895094 94
1793895099 94
1793895104 94
1793895109 96
1793895114 96
1793895119 96
1793895124 96
```
</details>

---

