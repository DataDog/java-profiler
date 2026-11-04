---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 17:02:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 74-83 cores)</summary>

```
1793829470 81
1793829475 81
1793829480 83
1793829485 83
1793829490 83
1793829495 83
1793829500 83
1793829505 74
1793829510 74
1793829515 74
1793829520 74
1793829525 74
1793829530 74
1793829535 74
1793829540 74
1793829545 74
1793829550 74
1793829555 74
1793829560 74
1793829565 74
```
</details>

---

