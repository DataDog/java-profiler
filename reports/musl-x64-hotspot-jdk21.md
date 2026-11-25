---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:14:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 72-78 cores)</summary>

```
1795630059 72
1795630064 72
1795630069 72
1795630074 72
1795630079 72
1795630084 72
1795630089 72
1795630094 72
1795630099 72
1795630104 72
1795630109 72
1795630114 72
1795630119 72
1795630124 72
1795630129 72
1795630134 72
1795630139 74
1795630144 74
1795630149 74
1795630154 78
```
</details>

---

