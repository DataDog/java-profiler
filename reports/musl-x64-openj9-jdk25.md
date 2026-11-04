---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 00:08:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 440 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 19-58 cores)</summary>

```
1793768540 19
1793768545 19
1793768550 19
1793768555 19
1793768560 19
1793768565 19
1793768570 40
1793768575 40
1793768580 40
1793768585 40
1793768590 40
1793768595 40
1793768600 40
1793768605 40
1793768610 40
1793768615 40
1793768620 40
1793768625 40
1793768630 58
1793768635 58
```
</details>

---

