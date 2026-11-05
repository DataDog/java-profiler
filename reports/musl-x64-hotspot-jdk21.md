---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 11:16:28 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 72-77 cores)</summary>

```
1793894989 77
1793894994 77
1793894999 72
1793895004 72
1793895009 72
1793895014 72
1793895019 72
1793895024 72
1793895029 72
1793895034 72
1793895039 72
1793895044 72
1793895049 72
1793895054 72
1793895059 72
1793895064 72
1793895069 72
1793895074 72
1793895080 72
1793895085 72
```
</details>

---

