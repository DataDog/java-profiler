---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:02:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 88-93 cores)</summary>

```
1793829485 88
1793829490 88
1793829495 88
1793829500 93
1793829505 93
1793829510 91
1793829515 91
1793829520 91
1793829525 91
1793829530 91
1793829535 91
1793829540 91
1793829545 91
1793829550 91
1793829555 91
1793829560 91
1793829565 91
1793829570 91
1793829575 91
1793829580 91
```
</details>

---

