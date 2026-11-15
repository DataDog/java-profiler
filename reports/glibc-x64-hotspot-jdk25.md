---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 18:02:45 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1794783565 65
1794783570 65
1794783575 65
1794783580 65
1794783585 65
1794783590 65
1794783595 65
1794783600 65
1794783605 65
1794783610 65
1794783615 65
1794783620 65
1794783625 65
1794783630 65
1794783635 65
1794783640 65
1794783645 63
1794783650 63
1794783655 63
1794783660 63
```
</details>

---

