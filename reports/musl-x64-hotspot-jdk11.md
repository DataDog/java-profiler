---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:02:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 9 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (2 unique values: 69-74 cores)</summary>

```
1794427029 69
1794427034 69
1794427039 69
1794427044 69
1794427049 69
1794427054 69
1794427059 74
1794427064 74
1794427069 74
1794427074 74
1794427080 74
1794427085 74
1794427090 74
1794427095 74
1794427100 74
1794427105 74
1794427110 74
1794427115 74
1794427120 74
1794427125 74
```
</details>

---

