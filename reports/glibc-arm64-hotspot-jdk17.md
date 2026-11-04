---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:02:38 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1793829485 45
1793829490 45
1793829495 45
1793829500 45
1793829505 45
1793829510 45
1793829515 45
1793829520 45
1793829525 45
1793829530 48
1793829535 48
1793829540 48
1793829545 48
1793829550 48
1793829555 48
1793829560 48
1793829565 48
1793829570 48
1793829575 48
1793829580 48
```
</details>

---

