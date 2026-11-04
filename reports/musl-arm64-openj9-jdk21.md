---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 17:02:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 14 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793829500 48
1793829505 48
1793829510 48
1793829515 48
1793829520 48
1793829525 48
1793829530 48
1793829535 48
1793829540 48
1793829545 48
1793829550 48
1793829555 48
1793829560 48
1793829565 43
1793829570 43
1793829575 43
1793829580 43
1793829585 43
1793829590 43
1793829595 43
```
</details>

---

