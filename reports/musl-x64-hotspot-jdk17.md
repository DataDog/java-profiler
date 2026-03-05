---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-05 13:29:13 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 12 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 49-86 cores)</summary>

```
1772734976 56
1772734981 56
1772734986 56
1772734991 56
1772734997 56
1772735002 56
1772735007 56
1772735012 56
1772735017 49
1772735022 49
1772735027 49
1772735032 84
1772735037 84
1772735042 84
1772735047 84
1772735052 84
1772735057 84
1772735062 86
1772735067 86
1772735072 86
```
</details>

---

