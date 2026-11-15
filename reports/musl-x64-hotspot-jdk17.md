---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-15 18:02:47 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 79-91 cores)</summary>

```
1794783520 79
1794783525 79
1794783530 79
1794783535 79
1794783540 79
1794783545 79
1794783550 81
1794783555 81
1794783560 81
1794783565 81
1794783570 81
1794783575 81
1794783580 81
1794783585 81
1794783590 81
1794783595 81
1794783600 81
1794783605 81
1794783610 81
1794783615 89
```
</details>

---

