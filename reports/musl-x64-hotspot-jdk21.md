---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-14 12:40:13 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 909 |
| Sample Rate | 15.15/sec |
| Health Score | 947% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 81-89 cores)</summary>

```
1791995650 84
1791995655 84
1791995660 84
1791995666 84
1791995671 84
1791995676 82
1791995681 82
1791995686 82
1791995691 82
1791995696 84
1791995701 84
1791995706 84
1791995711 84
1791995716 84
1791995721 81
1791995726 81
1791995731 81
1791995736 81
1791995741 81
1791995746 81
```
</details>

---

