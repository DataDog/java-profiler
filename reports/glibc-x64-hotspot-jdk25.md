---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:05:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1795449510 66
1795449515 66
1795449520 66
1795449525 66
1795449530 66
1795449535 66
1795449540 66
1795449545 66
1795449550 66
1795449555 66
1795449560 66
1795449565 66
1795449570 66
1795449575 66
1795449580 66
1795449585 66
1795449590 66
1795449595 66
1795449600 66
1795449605 66
```
</details>

---

