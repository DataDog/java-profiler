---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 04:47:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (5 unique values: 64-77 cores)</summary>

```
1795426912 64
1795426917 64
1795426922 64
1795426927 64
1795426932 64
1795426937 73
1795426942 73
1795426947 71
1795426952 71
1795426957 71
1795426962 71
1795426967 71
1795426972 71
1795426977 73
1795426982 73
1795426987 73
1795426992 73
1795426997 75
1795427002 75
1795427007 77
```
</details>

---

