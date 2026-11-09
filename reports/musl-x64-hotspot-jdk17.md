---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-09 05:57:49 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 44-48 cores)</summary>

```
1794221505 48
1794221510 48
1794221515 48
1794221520 48
1794221525 48
1794221530 48
1794221535 44
1794221540 44
1794221545 44
1794221550 44
1794221555 44
1794221560 44
1794221565 44
1794221570 44
1794221575 44
1794221580 44
1794221585 46
1794221590 46
1794221595 46
1794221600 44
```
</details>

---

