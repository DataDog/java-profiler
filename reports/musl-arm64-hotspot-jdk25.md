---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 08:05:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 33-48 cores)</summary>

```
1794402074 33
1794402079 33
1794402084 33
1794402089 33
1794402094 33
1794402099 33
1794402104 43
1794402109 43
1794402114 43
1794402119 43
1794402125 43
1794402130 43
1794402135 43
1794402140 43
1794402145 43
1794402150 43
1794402155 43
1794402160 43
1794402165 43
1794402170 43
```
</details>

---

