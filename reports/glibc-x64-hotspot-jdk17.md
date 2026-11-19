---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 09:12:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (7 unique values: 46-59 cores)</summary>

```
1795097268 46
1795097273 46
1795097278 46
1795097283 46
1795097288 48
1795097293 48
1795097298 48
1795097303 49
1795097308 49
1795097313 47
1795097318 47
1795097323 47
1795097328 47
1795097333 47
1795097338 54
1795097343 54
1795097348 51
1795097353 51
1795097358 51
1795097363 51
```
</details>

---

