---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-22 08:14:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787400641 48
1787400646 48
1787400651 48
1787400656 48
1787400661 48
1787400666 48
1787400671 48
1787400676 48
1787400681 48
1787400686 48
1787400691 48
1787400696 48
1787400701 48
1787400706 48
1787400711 48
1787400716 48
1787400721 48
1787400726 48
1787400731 43
1787400736 43
```
</details>

---

