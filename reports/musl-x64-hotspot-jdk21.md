---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:39:29 EST

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
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (5 unique values: 38-74 cores)</summary>

```
1795196089 72
1795196094 72
1795196099 72
1795196104 72
1795196109 72
1795196114 74
1795196119 74
1795196124 74
1795196129 74
1795196134 74
1795196139 74
1795196144 66
1795196149 66
1795196154 66
1795196159 66
1795196164 66
1795196169 66
1795196174 38
1795196179 38
1795196184 38
```
</details>

---

