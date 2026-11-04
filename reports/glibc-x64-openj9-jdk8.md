---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 17:02:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 370 |
| Sample Rate | 6.17/sec |
| Health Score | 386% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 43-54 cores)</summary>

```
1793829510 43
1793829515 43
1793829520 43
1793829525 43
1793829530 43
1793829535 43
1793829540 51
1793829545 51
1793829550 51
1793829555 51
1793829560 52
1793829565 52
1793829570 52
1793829575 52
1793829580 52
1793829585 54
1793829590 54
1793829595 54
1793829600 54
1793829605 54
```
</details>

---

