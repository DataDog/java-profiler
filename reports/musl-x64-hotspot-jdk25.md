---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:02:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 37-41 cores)</summary>

```
1794427029 41
1794427034 41
1794427039 41
1794427044 39
1794427049 39
1794427054 39
1794427059 39
1794427064 39
1794427069 39
1794427074 39
1794427079 39
1794427084 39
1794427089 39
1794427094 39
1794427099 39
1794427104 39
1794427109 39
1794427114 39
1794427119 39
1794427124 37
```
</details>

---

