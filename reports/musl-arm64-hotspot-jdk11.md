---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 11:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 10 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793895004 48
1793895009 48
1793895014 48
1793895019 48
1793895024 48
1793895029 48
1793895034 48
1793895039 48
1793895044 48
1793895049 48
1793895054 48
1793895059 48
1793895064 48
1793895069 48
1793895074 48
1793895079 48
1793895084 48
1793895089 48
1793895094 48
1793895099 48
```
</details>

---

