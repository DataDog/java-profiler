---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 09:09:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 11 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794319439 51
1794319444 51
1794319449 51
1794319454 51
1794319459 51
1794319464 51
1794319469 51
1794319474 51
1794319479 51
1794319485 51
1794319490 64
1794319495 64
1794319500 51
1794319505 51
1794319510 51
1794319515 51
1794319520 51
1794319525 51
1794319530 51
1794319535 51
```
</details>

---

