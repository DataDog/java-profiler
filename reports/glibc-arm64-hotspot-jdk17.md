---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 14:30:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
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
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 43-51 cores)</summary>

```
1794943500 43
1794943505 43
1794943510 43
1794943515 43
1794943520 43
1794943525 43
1794943530 43
1794943535 43
1794943540 43
1794943545 47
1794943550 47
1794943555 47
1794943560 47
1794943565 47
1794943570 47
1794943575 47
1794943580 47
1794943585 47
1794943590 51
1794943595 51
```
</details>

---

