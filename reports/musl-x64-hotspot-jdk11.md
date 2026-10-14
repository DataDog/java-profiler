---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 04:13:56 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (4 unique values: 66-76 cores)</summary>

```
1791965375 66
1791965380 66
1791965385 66
1791965390 66
1791965395 68
1791965400 68
1791965405 68
1791965410 68
1791965415 68
1791965420 76
1791965425 76
1791965430 76
1791965435 76
1791965440 76
1791965445 76
1791965450 76
1791965455 76
1791965460 76
1791965465 76
1791965470 74
```
</details>

---

